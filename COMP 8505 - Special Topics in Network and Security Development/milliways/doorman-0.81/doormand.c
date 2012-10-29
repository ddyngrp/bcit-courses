/*****************************************************************************

    File: "doormand.c"

    Copyright (C) 2003  Bruce Ward

    This file is part of the Doorman Daemon & Portknocker client.

    Doorman/Portknocker is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Doorman/Portknocker is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Doorman/Portknocker; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/


// --------------------------------------------------------------------------
//   JBW | v0.1   |  Oct.8  2003 | Initial version
//   JBW | v0.5   |  Jun 26 2004 | Changed method of parsing guest-list.
//                               | Doesn't suck as bad now.
//   JBW | v0.5.1 |  Jul 3  2004 | Removed use of mask bits in salting secret
//   JBW | v0.8   |  Jul 23 2004 | Added checks for NULL return after all 
//                               | 'token' calls. Changed pcap timeouts to 0.
//                               | Both thanks to Leonid Shalupov.
//                               | Changed authentication method to get rid
//                               | of time-sync requirements between client
//                               | & doorman.  MUCH better now.
//   JBW | V0.81  |  Aug 10 2005 | Removed use of Berkeley DB to simplify
//                               | autoconf stuff.
//                               | This makes the 'C' code simpler, as well.
// --------------------------------------------------------------------------



#include "config.h"

#ifndef __USE_BSD
#  define __USE_BSD
#endif


#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <sys/socket.h>
#ifdef HAVE_SYS_SOCKIO_H
#  include <sys/sockio.h>
#endif
#ifdef HAVE_NETINET_IN_SYSTM_H
#  include <netinet/in_systm.h>
#endif
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#ifndef __FAVOR_BSD
#  define __FAVOR_BSD
#endif
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <strings.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

#ifdef HAVE_PCAP_H
#  include <pcap.h>
#else
#  ifdef HAVE_PCAP_PCAP_H
#    include <pcap/pcap.h>
#  else
#    include "Replacement_fns/pcap.h"
#  endif
#endif

#include <limits.h>
#include <fcntl.h>
#include <dirent.h>

#ifdef HAVE_MD5GLOBAL_H
#  include <md5global.h>
#endif

#ifdef HAVE_MD5_H
#  include <md5.h>
#else
#  ifdef HAVE_OPENSSL_MD5_H
#    include <openssl/md5.h>
#  else
#    ifdef HAVE_INN_MD5_H
#      include <inn/clibrary.h>
#      include <inn/md5.h>
#    endif
#  endif
#endif

#ifdef HAVE_HMAC_MD5_H
#  include <hmac-md5.h>
#endif

#ifndef MD5_DIGEST_LENGTH
#  define MD5_DIGEST_LENGTH  HMAC_MD5_SIZE
#endif

#ifndef INADDR_NONE
#  define INADDR_NONE ((in_addr_t) 0xffffffff)
#endif

#ifndef IP_OFFMASK
#  define IP_OFFMASK 0x1fff 
#endif

#define ARCHIVE_RECLEN (MD5_DIGEST_LENGTH + sizeof(time_t))



#define __USE_GNU 1
#include <string.h>
#undef __USE_GNU

#ifndef ulong
#  define ulong unsigned long
#endif
#ifndef uint32_t
#  define uint32_t unsigned int
#endif
#ifndef uint16_t
#  define uint16_t unsigned short
#endif
#ifndef uint8_t
#  define uint8_t unsigned char
#endif

#ifndef in_addr_t
#  define in_addr_t u_int
#endif

#include "constants.h"
#include "utilities.h"


char *run_script (char *script, char *fmt, ...) ;

// prepare_guestlist is defined in 'lexer.l'
int prepare_guestlist (char *filename, void ***returned_guest_list) ;

#define MAX_PGM_LEN (128)


//  --- G L O B A L  V A R I A B L E S  ---

int      G_lexer_phase ;
pcap_t   *G_cap ;
FILE     *G_errlog ;
char     G_pidfile[_POSIX_PATH_MAX] ;
int      G_pidfile_is_ours ;
int      G_hash_fd ;
int      G_reconfigure ;
int      G_dump_headers ;
int      G_waiting_for_syn_packet ;
int      G_waitfor ;
int      G_link_header_length ;
int      G_conn_delay_1, G_conn_delay_2 ;
char     G_fw_add[_POSIX_PATH_MAX] ;
char     G_fw_del[_POSIX_PATH_MAX] ; 
char     G_fw_broad_rule[256] ;
char     G_fw_narrow_rule[256] ;

// --------- E N D  G L O B A L S ---------



typedef struct addrdata {
    uint32_t addr ;
    uint32_t mask ;
} addrdata ;



// structure of a hash-archive record

typedef struct archive_record {
    unsigned char hash[MD5_DIGEST_LENGTH] ;
    time_t        time ;
} archive_record ;




void sigchild (int signal)
{
    wait(NULL) ;
//    DEBUG "Caught SIGCHLD.") ;
}



void sigalarm (int signal)
{
    if (G_waiting_for_syn_packet) {
        WARN "Timed out waiting for SYN packet. Exiting.") ;
        if (G_fw_broad_rule[0]) run_script(G_fw_del, G_fw_broad_rule) ;
        if (G_fw_narrow_rule[0]) run_script(G_fw_del, G_fw_narrow_rule) ;
        exit (0) ;
    } else {
        DEBUG "Caught unexpected SIGALRM. Ignored.") ;
    }
}



void sighup (int signal)
{
    if (G_pidfile_is_ours) {
        NOTICE "Caught SIGHUP; re-configuring.") ;
        G_reconfigure = TRUE ;
        pcap_close(G_cap) ;
        close (G_hash_fd) ;
    } else {
        NOTICE "Child caught SIGHUP. Ignored.") ;
    }
}



void shutitdown (int signal)
{
#ifdef HAVE_STRSIGNAL
    NOTICE "Caught '%s'; shutting down.",  strsignal(signal)) ;
#else
    NOTICE "Caught signal #%d; shutting down.",  signal) ;
#endif
    pcap_close(G_cap) ;
    close (G_hash_fd) ;
    
    if (G_fw_broad_rule[0]) run_script(G_fw_del, G_fw_broad_rule) ;
    if (G_fw_narrow_rule[0]) run_script(G_fw_del, G_fw_narrow_rule) ;
    
    if (G_pidfile_is_ours) unlink(G_pidfile) ;

    exit (0) ;
}


/*******************************************************************
void sigsegv (int signal)
{
    EMERG "Uh-oh! We caused a SEGMENTATION FAULT; shutting down.");
    
    if (G_fw_broad_rule[0]) run_script(G_fw_del, G_fw_broad_rule) ;
    if (AG_fw_narrow_rule[0]) run_script(G_fw_del, G_fw_narrow_rule) ;
    
    exit (1) ;
}
*******************************************************************/


void croak (int err, char *fmt, ...)
{
    va_list    args ;
    char       *p, buffer[2048] ; 
    
    p = buffer ;
    va_start(args, fmt) ;
    p += vsprintf (buffer, fmt, args) ;
    va_end(args) ;

    if (err) {
        err_log ("doormand", LOG_NOMARK, LOG_EMERG, buffer) ;
    } else {
        err_log ("doormand", LOG_NOMARK, LOG_NOERR|LOG_EMERG, buffer) ;
    }
    fclose (G_errlog) ;

    if (G_pidfile_is_ours) unlink(G_pidfile) ;

    exit (1) ;
}



void usage(char c)
{
    char   pathname[_POSIX_PATH_MAX] ;
    char   msg[] =
        "Usage :\n"
        "  doormand [-h] [-v] [-D] [-p pidfile] [-f config-file]\n"
        "    -h              print this message and quit.\n"
        "    -v              print version number and quit.\n"
        "    -D              Debug mode\n"
        "                    (don't daemonize; log to stderr;\n"
        "                    stay attached to the console;\n"
        "                    skip file-ownership checks)\n"
        "    -X              do a debugging heX dump of packet headers\n"
        "    -p pidfile      write process id to 'pidfile'.\n"
        "    -f config-file  specify a configuration file.\n" ;

    fprintf (stderr, "%cDoorman daemon %s  %s\n", c, VERSION, __DATE__) ;
    fprintf (stderr, "%s", msg) ;

#ifdef CONFIG_DIR
    strncpy (pathname, CONFIG_DIR, _POSIX_PATH_MAX) ;
    strncat (pathname, "/doormand.cf", _POSIX_PATH_MAX) ;
#else
    strcpy (pathname, "/usr/local/etc/doormand/doormand.cf") ;
#endif
    fprintf (stderr, "    (default config. file is '%s')\n", pathname) ;
}



int get_interface_address (char *device, char *ipbuffer, int bufferlen)
{
    int                 err, fd ;
    struct ifreq        if_request ;
    struct sockaddr_in  *sa_in ;

    fd = socket (PF_INET, SOCK_DGRAM, 0) ;
    if (fd < 0) croak(errno, "Can't create a socket") ;

    bzero (&if_request, sizeof(if_request)) ;
    strncpy (if_request.ifr_name, device, IFNAMSIZ) ;
    err = ioctl (fd, SIOCGIFADDR, &if_request) ;

    if (err) return errno ;

    sa_in = (struct sockaddr_in*)&if_request.ifr_addr ;
    strncpy (ipbuffer, inet_ntoa(sa_in->sin_addr), bufferlen) ;

    close (fd) ;

    return 0 ;
}



// XXX  TODO return ptr to 'struct bpf_program  program' to avoid mem leak

int open_a_pcap (char    *device,
                 int     timeout,
                 pcap_t  **returned_pcap,
                 char    *program_fmt, ...)
                             
{
    static int          first_call = TRUE ;
    pcap_t              *pcap ;
    uint32_t            localnet, netmask ;
    char                *p ;
    char                ebuf[PCAP_ERRBUF_SIZE + 2] ;
    int                 datalink, hdr_len, err ;
    struct bpf_program  program ;
    va_list             args ;
    char                pgm_buffer[256] ;

//  Some of the values in the following array may differ from platform
//  to platform.   Offsets are from <net/bpf.h> 
//  '-1' is used here to mean 'unknown'
//
//  These offsets are useful ONLY if the link header is followed 
//  immediately by an IP header.
//
//  Literal constants are used to avoid "Variations-In-Header-File Hell".
//
//  *** Offsets 0-10 should be common to all, but check
//  *** the header files on your platform for the higher-numbered ones.
//  *** If you find that any of these are incorrect, or know the
//  *** values of any marked -1 (unknown), PLEASE email
//  *** <bward2@users.sourceforge.net> with the correct value.
//
    int datalink_header_lengths[] = {
    //    hdr len      code      data link type
    //    -------      --- ---------------------------
             0,    //   0  no link-layer encapsulation
            14,    //   1  Ethernet (10Mb)
            -1,    //   2  Experimental Ethernet (3Mb)
            -1,    //   3  Amateur Radio AX.25
            -1,    //   4  Proteon ProNET Token Ring
            -1,    //   5  Chaos
            22,    //   6  IEEE 802 Networks
            10,    //   7  ARCNET
            16,    //   8  Serial Line IP
             4,    //   9  PPP, Point-to-point Protocol
            16,    //  10  FDDI
    //    .............................................
            -1,    //  11  LLC/SNAP encapsulated atm
             0,    //  12  raw IP
            -1,    //  13
            -1,    //  14
            -1,    //  15  BSD/OS Serial Line IP
            -1,    //  16  BSD/OS Point-to-point Protocol
            -1,    //  17  isdn4linux: rawip
            -1,    //  18  isdn4linux: ip
            -1,    //  19  LANE 802.3(Ethernet) ?   ATM Classical IP ?
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  //  20-29
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  //  30-39
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  //  40-49
            -1,    //  50  PPP over serial with HDLC encapsulation
             8,    //  51  PPP over Ethernet
                  -1,-1,-1,-1,-1,-1,-1,-1,  //  52-59
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  //  60-69
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  //  70-79
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  //  80-89
            -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,  //  90-99
            -1,-1,-1,-1,                    // 100-103
            -1,    // 104  Cisco HDLC
            -1,    // 105  IEEE 802.11 wireless
            -1,    // 106
            -1,    // 107
             0,    // 108  OpenBSD DLT_LOOP; loopback devices
            -1,    // 109
            -1,    // 110
            -1,    // 111
            -1,    // 112
             8,    // 113  This is for Linux cooked sockets (Tnx to Markus Hoffmann)
            -1,    // 114  Apple LocalTalk hardware
            -1,    // 115  Acorn Econet
            -1,    // 116  Reserved for use with OpenBSD ipfilter
            -1,    // 117  DLT_PFLOG ??
            -1,    // 118  Registered for Cisco-internal use
            -1,    // 119  Reserved for 802.11 cards using the PrismII chips...
            -1,    // 120  Rsvd for Aironet 802.11 with Aironet link-layer hdr
    } ;

    char *datalink_names_1[] = {
        "no link-layer encapsulation",
	"Ethernet (10Mb)",
	"Experimental Ethernet (3Mb)",
	"Amateur Radio AX.25",
	"Proteon ProNET Token Ring",
	"Chaos",
	"IEEE 802 Networks",
	"ARCNET",
	"Serial Line IP",
	"PPP, Point-to-point Protocol",
	"FDDI",
	"LLC/SNAP encapsulated atm",
	"raw IP",
	"-UNKNOWN-",
	"-UNKNOWN-",
	"BSD/OS Serial Line I",
	"BSD/OS Point-to-point Protocol",
	"isdn4linux: rawip",
	"isdn4linux: ip",
	"LANE 802.3(Ethernet)?  ATM Classical IP?"
    } ;

    char *datalink_names_2[] = {
        "Cisco HDLC",
        "IEEE 802.11 wireless",
	"-UNKNOWN-",
	"-UNKNOWN-",
        "OpenBSD DLT_LOOP or loopback device",
	"-UNKNOWN-",
	"-UNKNOWN-",
	"-UNKNOWN-",
	"-UNKNOWN-",
        "Linux cooked socket",
        "Apple LocalTalk hardware",
        "Acorn Econet",
        "OpenBSD ipfilte",
        "DLT_PFLOG (?)",
        "- UNKNOWN Cisco -",
        "802.11 card using the PrismII chip",
        "Aironet 802.11 with Aironet link-layer hdr"
    } ;




    pcap = pcap_open_live (device, SNAPLEN, FALSE, timeout, ebuf) ;
    if (pcap == NULL) croak(0, "'pcap_open_live' call failed : %s", ebuf) ;

    err = pcap_lookupnet (device, &localnet, &netmask, ebuf) ;
    if (err < 0) croak(0, "'pcap_lookupnet' call failed : %s", ebuf) ;

    p = pgm_buffer ;
    va_start(args, program_fmt) ;
    p += vsprintf (pgm_buffer, program_fmt, args) ;
    va_end(args) ;

    err = pcap_compile (pcap, &program, pgm_buffer, TRUE, netmask) ;
    if (err) croak(0, "'pcap_compile' call failed on program string = "
                      "\"%s\": %s", pgm_buffer, pcap_geterr(pcap)) ;

    err = pcap_setfilter (pcap, &program) ;
    if (err) croak(0, "'pcap_setfilter' call failed, program string = "
                      "\"%s\": %s", pgm_buffer, pcap_geterr(pcap)) ;

    datalink = pcap_datalink(pcap) ;

    if (datalink < 0) croak(0, "'pcap_datalink' call failed: %s",
                            pcap_geterr(pcap)) ;

    if ( (datalink < 0)
      || (datalink > 120)
      || (datalink_header_lengths[datalink] < 0))
    {
        croak(0,"Unknown header type from 'pcap_datalink' call: %d", datalink);
    }

    *returned_pcap = pcap ;

    if (first_call && G_dump_headers) {
        first_call = FALSE ;
        p = "-UNKNOWN-" ;
	if ( (datalink > 0) && (datalink < 20)) {
            p = datalink_names_1 [datalink] ;
	} else if ( (datalink > 103) && (datalink < 121)) {
            p = datalink_names_2 [datalink - 104] ;
	} else if (datalink == 50) {
            p = "PPP over serial with HDLC encapsulation" ;
	} else if (datalink == 51) {
            p = "PPP over Ethernet" ;
	}
        printf ("*** pcap sensed the %s interface link as type %d (%s),"
                " with link header length = %d bytes ***\n",
                device, datalink, p, datalink_header_lengths[datalink]) ;
    }

    hdr_len = G_link_header_length ;
    if (hdr_len == -1) {
        hdr_len =  datalink_header_lengths[datalink] ;
    }

    return hdr_len ;
}



char *run_script (char *script, char *fmt, ...)
{
    FILE         *f ;
    va_list      args ;
    char         *p ; 
    char         cmd_buffer[_POSIX_PATH_MAX + 64] ; 
    static char  return_buffer[_POSIX_PATH_MAX + 64] ; 

    strncpy (cmd_buffer, script, _POSIX_PATH_MAX) ;
    p = cmd_buffer + strlen(cmd_buffer) ;

    va_start(args, fmt) ;
    p += vsprintf (p, fmt, args) ;
    va_end(args) ;

    DEBUG "run script: '%s'", cmd_buffer) ;
    f = popen (cmd_buffer, "r") ;
    if (f == NULL) {
        croak (errno, "Can't run script '%s'", script) ;
    }

    p = fgets (return_buffer, sizeof(return_buffer)-2, f) ;
    if (p == NULL) {
        croak (errno, "Bad (or no) output from script %s", script) ;
    }
    fclose (f) ;

    p = strrchr(return_buffer, '\n') ;
    if (p) *p = 0 ;
    DEBUG "output from script: '%s'", return_buffer) ;
    if (return_buffer[0] != '0') {
        char  ebuffer[_POSIX_PATH_MAX + 64] ; 
        char  *p1, *p2, *p3 ;
        int   level ;
        strncpy (ebuffer, return_buffer, sizeof(ebuffer)) ;
        p3 = ebuffer ;
        p1 = token (&p3, " \t") ;
        if (p1 == NULL) {
            croak (0, "Bad output from script %s : \"%s\"",
                   script, return_buffer) ;
        }
        p2 = token (&p3, " \t") ;
        if (p2 == NULL) {
            croak (0, "Bad output from script %s : \"%s\"",
                   script, return_buffer) ;
        }
        errno = atoi(p1) ;
        level = atoi(p2) ;
        err_log ("doormand", LOG_NOMARK, level,
                 "script'%s' returned \"%s\"; Exiting.",
                  cmd_buffer, return_buffer) ;
        if (level < LOG_WARNING) {
            if (G_pidfile_is_ours) unlink(G_pidfile) ;
            exit (1) ;
        }
    }

    return return_buffer ;

}



//
// A rather grotty macro to run an 'lsof' command, & search
// the output for a specific TCP connection. Included
// in a possibly misguided attempt to make the code
// more readable.
//

#define LSOF()\
sprintf (cmd, "lsof -Pn -iTCP@%s:%s", interface_ip_str, dport_string) ;\
\
f = popen (cmd, "r") ;\
if (f == NULL) {\
    croak (errno, "Can't execute '%s'; exiting.", cmd) ;\
}\
\
fgets(buffer, 254, f) ;   /* throw away the first line. */ \
while (fgets(buffer, 254, f)) {\
    p2 = buffer ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    dname = p1 ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    pid = p1 ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    uname = p1 ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    if ((p1 = token (&p2, " :")) == NULL) continue ;\
    local_ip = inet_addr(p1) ;\
    if ((p1 = token (&p2, "-")) == NULL) continue ;\
    local_port = atoi(p1) ;\
    if ((p1 = token (&p2, "->:")) == NULL) continue ;\
    aptr = p1 ;\
    remote_ip = inet_addr(p1) ;\
    if ((p1 = token (&p2, " ")) == NULL) continue ;\
    pptr = p1 ;\
    remote_port = atoi(p1) ;\
    if ((p1 = token (&p2, " ()")) == NULL) continue ;\
    status = p1 ;\
\
    if ((saddr == remote_ip) &&\
        (daddr == local_ip) &&\
        (sport == remote_port) &&\
        (dport == local_port) && \
        (strcmp(status, "ESTABLISHED") == 0))\
    {\
        connected = TRUE ;\
        break ;\
    }\
}\
pclose(f) ;




void manage_firewall (char               *device,
                      int                hdr_len, 
                      char               *guest,
                      char               *src_addr,
                      char               *dport_string)
{
    char                interface_ip_str[32] ;
    pcap_t              *cap ;
    struct pcap_pkthdr  packet_hdr ;   
    struct ip           *ip ;
    struct tcphdr       *tcp ;
    int                 err, i, ip_hl, connected=0 ;
    uint16_t            sport, dport ;
    uint32_t            saddr, daddr ;
    char                sport_string[32] ; 
    unsigned char       *p ;
    char                cmd[256] ;
    char                buffer[256] ;
    FILE                *f ;
    char                *pid="", *dname="", *aptr="", *pptr="" ;
    char                *uname, *status ;
    char                *p1, *p2 ;
    uint32_t            local_ip, remote_ip, local_port, remote_port ;


    G_fw_broad_rule[0] = 0 ;
    G_fw_narrow_rule[0] = 0 ;

    err = get_interface_address (device, interface_ip_str,
                                 sizeof(interface_ip_str));
    if (err) {
        croak (errno,"Can't get interface address of %s", device) ;
    }


    daddr = inet_addr (interface_ip_str) ;
    saddr = inet_addr (src_addr) ;

    snprintf (cmd, 254, "tcp and dst port %s and src %s and dst %s",
              dport_string, src_addr, interface_ip_str) ;
    DEBUG "open a secondary pcap: '%s'", cmd) ;
    hdr_len = open_a_pcap (device, 0, &cap, cmd) ;

    // set broad firewall rule
    sprintf (G_fw_broad_rule, " %s %s 0 %s %s",
             device, src_addr, interface_ip_str, dport_string) ;
    run_script (G_fw_add, G_fw_broad_rule) ;

    G_waiting_for_syn_packet = TRUE ;
    alarm (G_waitfor) ;              // set timer while we wait for SYN pkt.

    for (;;) {

        p = (unsigned char*)pcap_next (cap, &packet_hdr) ;
        if (p == NULL) {
            WARNX "manage_firewall got null from 'pcap_next': %s  Exiting.",
                   pcap_geterr(G_cap)) ;
            exit (1) ;
        }

        ip = (struct ip*)(p + hdr_len) ;
        ip_hl = ip->ip_hl * 4 ;
        tcp = (void*)ip + ip_hl ;

        if ( ((tcp->th_flags & TH_ACK) == 0) && (tcp->th_flags & TH_SYN) ) {
            alarm (0) ;
            G_waiting_for_syn_packet = FALSE ;

            sport = ntohs(tcp->th_sport) ;
            dport = ntohs(tcp->th_dport) ;
            sprintf (sport_string, "%d", sport) ;

            DEBUG "Initial SYN packet detected, %s@%s:%s -> %d",
                   guest, src_addr, sport_string, dport);

            pcap_close (cap) ;

            // set narrow firewall rule

            sprintf (G_fw_narrow_rule, " %s %s %s %s %s",
                     device, src_addr, sport_string,
                     interface_ip_str, dport_string);
                     
            run_script (G_fw_add, G_fw_narrow_rule) ;

            // delete broad firewall rule

            run_script (G_fw_del, G_fw_broad_rule) ;
            G_fw_broad_rule[0] = 0 ;
  
            // wait no more G_conn_delay_1 usecs for TCP handshake to complete

            for (i=0;i<G_conn_delay_1; i+=100000) {
                connected = FALSE ;
                LSOF()               // search output of 'lsof' command
                if (connected) break ;
                usleep (100000) ;
            }

            if (connected) {
                INFO "connection established,  %s@%s:%s -> %s(pid %s)",
                     guest, aptr, pptr, dname, pid) ;
            } else {
                WARN "connection attempt time-out,  %s@%s -> %s",
                     guest, src_addr, dport_string) ;
                break ;
            }

            // then wait for connection to be broken.

            for (;;) {
                connected = FALSE ;
                LSOF()                      // search output of 'lsof' command
                if ( ! connected) break ;
                if (getppid() == 1) break ; // break if our parent has died.
                sleep (G_conn_delay_2) ;
            }

            if (connected) {
                WARN "Quitting because parent has died. "
                     "Connection: '%s(pid %s) (%s@%s:%s)' is cut off.",
                     dname, pid, guest, aptr, pptr) ;
            } else {
                INFO "%s(pid %s) (%s@%s:%s) has stopped running.",
                     dname, pid, guest, aptr, pptr) ;
            }

            break ;
        }

    }

    // delete narrow firewall rule
    run_script (G_fw_del, G_fw_narrow_rule) ;

    pcap_close (cap) ;

    exit (0) ;

}



//
//    Given a 16-byte MD5 hash, calculate it's
//    index into the hash-archive file
//
int aindex (struct archive_record *p, int hash_archive_size)
{
    ulong  *u = (ulong*)p ;
    int    hindex ;

    hindex = u[0] + u[1] + u[2] + u [3] ;
    hindex = (hindex & 0x7fffffff) % hash_archive_size ;

    return hindex ;
}




int main (int argc, char *argv[])
{
    struct pcap_pkthdr     packet_hdr ;   
    unsigned char         *p ;
    struct ip             *ip ;
    struct udphdr         *udp ;
    struct config_block    cfg ;
    struct stat            fs ;
    struct archive_record *hash_archive, *new_hash_archive, *old_hash_archive ;
    ulong                  hash_archive_size ;
    ulong                  old_hash_archive_size ;
    ulong                  new_hash_archive_size ;
    ulong                  hindex ;

    char     device[IFNAMSIZ + 2] ;
    char     *daemon_string, *secret ;
    ushort   *services ;
    uint32_t *iplist ;
    char     *guest, *offered_secret, *tag ;
    char     *cfg_name ;
    char     stored_plaintext_secret[128] ;
    char     config_file_pathname[_POSIX_PATH_MAX] ;
    char     *ebuf ;
    char     c ;
    int      daemonize, err, hdr_len, len, port, nbytes ;
    int      i, upper, lower, cmp ;
    int      nIPs, nServices ;
    int      fail_limit, fail_delay ;
    uint32_t mask, masked_srcaddr=0 ;
    uint32_t netdown_count ;
    char     *buffer ;
    char     interface_ip[32] ;
    char     guestlist_name[256] ;
    uint8_t  *u ;
    uint8_t  offered_hash[MD5_DIGEST_LENGTH] ;
    void     **guest_list ;
    int      nGuests = 0 ;
    FILE     *f ;


    _err_file = stderr ;

    G_errlog = stderr ;  // XXX
    G_reconfigure = FALSE ;
    G_waiting_for_syn_packet = FALSE ;
    G_pidfile[0] = 0 ;
    G_pidfile_is_ours = FALSE ;

    errno = 0 ;
    daemon_string = NULL ;
    guest_list = NULL ;

    signal (SIGCHLD, sigchild) ;
    signal (SIGALRM, sigalarm) ;
    signal (SIGHUP, sighup) ;
    signal (SIGTERM, shutitdown) ;
    signal (SIGSTOP, shutitdown) ;
    signal (SIGQUIT, shutitdown) ;
    signal (SIGINT, shutitdown) ;

    ebuf = malloc (1024) ;
    if (ebuf == NULL) croak (errno, "malloc failed") ;

    buffer = malloc (BUFFERLEN + 16) ;
    if (buffer == NULL) croak (errno, "malloc failed") ;


    //             ------------------------
    //             -  parse command line  -
    //             ------------------------

    cfg_name = "/usr/local/etc/doormand/doormand.cf" ;
#ifdef CONFIG_DIR
    strncpy (config_file_pathname, CONFIG_DIR, _POSIX_PATH_MAX) ;
    strncat (config_file_pathname, "/doormand.cf", _POSIX_PATH_MAX) ;
    cfg_name = config_file_pathname ;
#endif

    daemonize = TRUE ;
    G_dump_headers = FALSE ;

    while ((c = getopt(argc, argv, "?DXhvf:p:")) != -1) {
        switch (c) {
            case 'D':
                daemonize = FALSE ;
                break ;
            case 'X':
                G_dump_headers = TRUE ;
                break ;
            case 'f':
                cfg_name = optarg ;
                break ;
            case 'h':
                usage (0) ;
                exit (0) ;
                break ;
            case 'p':
                strncpy (G_pidfile, optarg, _POSIX_PATH_MAX) ;
                break ;
            case 'v':
                printf ("Doorman daemon %s  %s %s\n",
                         VERSION, __DATE__, __TIME__) ;
                printf ("%s\n\n", DOORMAN_URL) ;
                exit (0) ;
                break ;
            case '?':
            default:
                usage ('\a') ;
                exit (1) ;
                break ;
        }
    }

    if (cfg_name == NULL) {
        usage ('\a') ;
        exit (1) ;
    }

    //             ---------------
    //             -  daemonize  -
    //             ---------------

    if (daemonize) {
        err = daemon (FALSE, FALSE) ;
        if (err) croak(errno, "Can't become a daemon") ;
    }

    //             ----------------------
    //             -  read config file  -
    //             ----------------------

reconfigure:

    err = cfg_open (cfg_name, &cfg) ;
    if (err) croak(errno, "Can't open configuration file '%s'", cfg_name) ;

    if (daemonize) {
        p = cfg_first_ascii_value (&cfg, "logfile") ;
        if (p == NULL) {
            p = DEFAULT_LOGFILE ;
        }

        err = err_openlog (p, "debug") ;
        if (err) croak (errno, "Can't open logfile '%s'", p) ;

        p = cfg_first_ascii_value (&cfg, "loglevel") ;
        if (p) {
            err = err_set_loglevel(p) ;
            if (err) {
                croak(0, "Illegal value (%s) for loglevel in %s.", p, cfg_name);
            }
        }
    } else {
        err = err_set_loglevel("debug") ;
    }

// --- interface

    p = cfg_first_ascii_value (&cfg, "interface") ;
    if (p == NULL)croak(0,"Can't find 'interface' record in %s",cfg_name);
    strncpy (device, p, IFNAMSIZ) ;

// --- pidfile

    if (daemonize) {
        if (G_pidfile[0] == 0) {
            p = cfg_first_ascii_value (&cfg, "pidfile") ;
            if (p == NULL) {
                p = DEFAULT_PIDFILE ;
            }
            strncpy (G_pidfile, p, _POSIX_PATH_MAX) ;
        }

        if (G_pidfile_is_ours == FALSE) {
            if (stat(G_pidfile, &fs) == 0) {
                croak (0, "Found an old pidfile at %s . Remove it and run again.",
                       G_pidfile) ;
            }

            f = fopen (G_pidfile, "w") ;
            if (f == NULL) croak(errno, "Can't open pidfile %s.", G_pidfile) ;
            fprintf (f, "%d\n", getpid()) ;
            fclose(f) ;
            G_pidfile_is_ours = TRUE ;
        }
    }

// --- port

    p =  cfg_first_ascii_value (&cfg, "port") ;
    if (p) {
        port = atoi(p) ;
        if ((port < 1) || (port > 65535)) {
            croak(0, "Illegal port number (%s) in %s.", p, cfg_name) ;
        }
    } else {
        port = DEFAULT_PORT ;
    }

// --- waitfor

    p = cfg_first_ascii_value (&cfg, "waitfor") ;
    if (p) {
        G_waitfor = atoi(p) ;
        if (G_waitfor < 1) {
            croak(0,"Illegal value for 'waitfor' (%s) in %s.", p, cfg_name) ;
        }
    } else {
        G_waitfor = DEFAULT_WAITFOR ;
    }

// --- connection_delay_1

    p = cfg_first_ascii_value (&cfg, "connection-delay-1") ;
    if (p == NULL)   p = cfg_first_ascii_value (&cfg, "connection_delay_1") ;
    if (p) {
        G_conn_delay_1 = atoi(p) ;
        if (G_waitfor < 1) {
            croak(0,"Illegal value for 'connection-delay-1' (%s) in %s.",
                  p, cfg_name) ;
        }
    } else {
        G_conn_delay_1 = DEFAULT_CONNECTION_DELAY_1 ;
    }

// --- connection_delay_2

    p = cfg_first_ascii_value (&cfg, "connection-delay-2") ;
    if (p == NULL)   p = cfg_first_ascii_value (&cfg, "connection_delay_2") ;
    if (p) {
        G_conn_delay_2 = atoi(p) ;
        if (G_waitfor < 1) {
            croak(0,"Illegal value for 'connection-delay-2' (%s) in %s.",
                  p, cfg_name) ;
        }
    } else {
        G_conn_delay_2 = DEFAULT_CONNECTION_DELAY_2 ;
    }

// --- Link-level header length

    G_link_header_length = -1 ;

    p = cfg_first_ascii_value (&cfg, "link-header-length") ;
    if (p) {
        errno = 0 ;
        G_link_header_length = strtoul (p, NULL, 10) ;
        if (errno) {
            croak(errno, "Illegal value for 'link_header_length' (%s) in %s\n",
                  p, cfg_name) ;
        }
    }

// --- fail-limit

    p = cfg_first_ascii_value (&cfg, "fail-limit") ;
    if (p) {
        fail_limit = atoi(p) ;
        if (fail_limit < 1) {
            croak(0,"Illegal value for 'fail-limit' (%s) in %s.", p, cfg_name);
        }
    } else {
        fail_limit = DEFAULT_FAIL_LIMIT ;
    }

// --- fail-delay

    p = cfg_first_ascii_value (&cfg, "fail-delay") ;
    if (p) {
        fail_delay = atoi(p) ;
        if (fail_delay < 1) {
            croak(0,"Illegal value for 'fail-delay' (%s) in %s.", p, cfg_name);
        }
    } else {
        fail_delay = DEFAULT_FAIL_DELAY ;
    }

// --- guestlist

    p = cfg_first_ascii_value (&cfg, "guestlist") ;
    if (p) {
        strncpy (guestlist_name, p, 254) ;
    } else {
        strncpy (guestlist_name, DEFAULT_GUESTLIST, 254) ;
    }
    if (daemonize) {
        err = stat (guestlist_name, &fs) ;
        if (err) {
            croak (errno, "%s", p) ;
        }
        if (fs.st_uid != 0) croak(0, "%s must be owned by root.", p) ;
        if ((fs.st_mode & S_IFREG) == 0) {
            croak(0, "%s must be a regular file.", p) ;
        }
        if (fs.st_mode & (S_IRWXG | S_IRWXO)) {
            croak(0, "%s must be readable and writeable only by root.", p) ;
        }
    }

// --- firewall-add

    p = cfg_first_ascii_value (&cfg, "firewall-add") ;
    if (p) {
        strncpy (G_fw_add, p, _POSIX_PATH_MAX) ;
        if (daemonize) {
            err = stat (G_fw_add, &fs) ;
            if (err) {
                croak (errno, "%s", p) ;
            }
            if (fs.st_uid != 0) croak(0, "%s must be owned by root.", p) ;
            if ((fs.st_mode & S_IFREG) == 0) {
                croak(0, "%s must be a regular file.", p) ;
            }
            if (fs.st_mode & (S_ISUID | S_ISGID | S_IWOTH | S_IXOTH)) {
                croak(0,"%s must be writable and executable only by root.", p);
            }
        }
    } else {
        croak (0, "No 'firewall-add' record found in %s", cfg_name) ;
    }

// --- firewall-del

    p = cfg_first_ascii_value (&cfg, "firewall-del") ;
    if (p) {
        strncpy (G_fw_del, p, _POSIX_PATH_MAX) ;
        if (daemonize) {
            err = stat (G_fw_del, &fs) ;
            if (err) {
                croak (errno, "%s", p) ;
            }
            if (fs.st_uid != 0) croak(0, "%s must be owned by root.", p) ;
            if ((fs.st_mode & S_IFREG) == 0) {
                croak(0, "%s must be a regular file.", p) ;
            }
            if (fs.st_mode & (S_ISUID | S_ISGID | S_IWOTH | S_IXOTH)) {
                croak(0,"%s must be writable and executable only by root.", p);
            }
        }
    } else {
        croak (0, "No 'firewall-del' record found in %s", cfg_name) ;
    }

// --- size of hash archive

    hash_archive = NULL ;   // (Just to shut the compiler up...)
    hash_archive_size = 0 ;

    p = cfg_first_ascii_value (&cfg, "hash-archive-size") ;
    if (p) {
        new_hash_archive_size = atoi(p) ;
        if (new_hash_archive_size < 1000) {
            croak (0,
            "Illegal value for 'hash-archive-size': %s is < 1000\n", p) ;
        }
    } else {
        new_hash_archive_size = 100000 ;
    }

// --- hash archive file

    p = cfg_first_ascii_value (&cfg, "hash-archive") ;
    if (p == NULL) croak (0, "No 'hash-archive' record found in %s", cfg_name);

    err = stat (p, &fs) ;    // If the hash archive doesn't exist, create it.
    if ((err == ENOENT) || (fs.st_size < (1000*ARCHIVE_RECLEN))) {
        int n ;
        nbytes = new_hash_archive_size * ARCHIVE_RECLEN ;
        hash_archive = calloc (nbytes, 1) ;
        if (hash_archive == NULL) croak (errno, "calloc failed") ;
        G_hash_fd = open (p, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR) ;
        if (G_hash_fd == -1) {
            croak(errno, "Can't create new hash-archive file %s\n", p) ;
        }
        n = write (G_hash_fd, hash_archive, nbytes) ;
        if (n < nbytes) {
            croak(errno, "Can't write to new hash-archive file %s\n", p) ;
        }
        close (G_hash_fd) ;
        free (hash_archive) ;
        old_hash_archive_size = new_hash_archive_size ;
    }

    G_hash_fd = open (p, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR) ;
    if (G_hash_fd == -1) {
        croak(errno, "Can't open hash-archive file %s\n", p) ;
    }

    err = fstat (G_hash_fd, &fs) ;
    if (err) {
        croak(errno, "Can't 'fstat' hash-archive file %s\n", p) ;
    }

    lseek (G_hash_fd, fs.st_size, SEEK_SET) ;

    old_hash_archive = mmap (NULL, fs.st_size, PROT_READ|PROT_WRITE,
                             MAP_SHARED, G_hash_fd, 0) ;
    if (old_hash_archive == (void*)MAP_FAILED) {
        croak(errno, "Can't mmap hash-archive file %s\n", p) ;
    }

    old_hash_archive_size = fs.st_size / ARCHIVE_RECLEN ;

    if (new_hash_archive_size == old_hash_archive_size) {
        hash_archive_size = old_hash_archive_size ;  // No change in file size.
        hash_archive = old_hash_archive ;
//printf ("hash_archive_size = %d   fs.st_size = %d\n", hash_archive_size, fs.st_size) ;
    } else {                                         // File size has changed
//printf ("***** File size has changed. \n") ;
        new_hash_archive = calloc (new_hash_archive_size, ARCHIVE_RECLEN) ;
        if (new_hash_archive == NULL) croak(errno, "calloc call failed.") ;

        if (old_hash_archive_size) {                // Did file exist before?
            char zero_buffer[ARCHIVE_RECLEN] ;      // Yes; copy old contents.
            memset (zero_buffer, 0, ARCHIVE_RECLEN) ;

            for (i=0; i<old_hash_archive_size; i++) {
                if (memcmp(&new_hash_archive[i], zero_buffer, ARCHIVE_RECLEN)) {
                    hindex = aindex(&old_hash_archive[i],new_hash_archive_size);
                    new_hash_archive[hindex] = hash_archive[i] ;
                }
            }
        }

        munmap (old_hash_archive, old_hash_archive_size*ARCHIVE_RECLEN) ;
        close (G_hash_fd) ;
        err = unlink(p) ;
        if (err) croak(errno, "Can't delete hash-archive file %s\n", p) ;

        G_hash_fd = open (p, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR) ;
        if (G_hash_fd == -1) {
            croak(errno, "Can't open new hash-archive file %s\n", p) ;
        }

        nbytes = new_hash_archive_size * ARCHIVE_RECLEN ;
        write (G_hash_fd, new_hash_archive, nbytes) ;

        free (new_hash_archive) ;

        hash_archive_size = new_hash_archive_size ;
        hash_archive = mmap (NULL, nbytes, PROT_READ|PROT_WRITE, MAP_SHARED,
                             G_hash_fd, 0) ;
        if (hash_archive == (void*)MAP_FAILED) {
            croak(errno, "Can't mmap hash-archive file %s\n", p) ;
        }
    }


    cfg_close (&cfg) ;

    //          ----------------------------------
    //          -  finished reading config file; -
    //          -  set up guest-list table       -
    //          ----------------------------------

    if (G_reconfigure) {               // free old guest list allocations
        for (i=0; i<nGuests; i++) {
            p = guest_list[i] + strlen(guest_list[i]) ;
            memset (p, 0, strlen(p)) ; // clear 'secret' field first
            free ((void*)guest_list[i]) ;
        }
        free (guest_list) ;
    }

    nGuests = prepare_guestlist (guestlist_name, &guest_list) ;


    //             ----------------------
    //             -  set up main pcap  -
    //             ----------------------

    err = get_interface_address (device, interface_ip, sizeof(interface_ip)) ;
    if (err) {
        croak (errno, "Can't get interface address of %s", device) ;
    }

    hdr_len = open_a_pcap (device, 0, &G_cap, "udp and port %d and dst %s",
                           port, interface_ip) ;

    if (G_reconfigure) {
        G_reconfigure = FALSE ;
        NOTICE "reconfigured.") ;
    } else {
        NOTICE "Doorman %s starting; listening on %s %s, UDP port %d",
	        VERSION, device, interface_ip, port) ;
    }


/* ===================================*=================================== */
/*                                                                         */
/*                          l o o p  f o r e v e r                         */
/*                                                                         */
/* ===================================*=================================== */



    for (;;) {

        int             i, nomatch, ip_hl, ip_len, ip_off ;
        char            *payload, *service ;
        unsigned char   t[16] ; // temp. buffer for error logging
        char            hash_buff1[128], hash_buff2[128] ;
        struct in_addr  src_addr ;
        char            src_addr_buff[16] ;

        errno = 0 ;
        netdown_count = 0 ;

        p = (unsigned char *)pcap_next (G_cap, &packet_hdr) ;
        if (G_reconfigure) {
            if (daemonize) err_closelog() ;
            goto reconfigure ;
        }

        if (p == NULL) {
            if ((errno==0) || (errno==ENETDOWN) || (errno==EAGAIN)) {
                DEBUGX "pcap_next returned 'null' : %s", pcap_geterr(G_cap)) ;
                netdown_count += 1 ;
                if (netdown_count > 10) {
                    croak (errno, "main got too many null from 'pcap_next'(1): \"%s\"",
                                   pcap_geterr(G_cap)) ;
                }
                continue ;
            }
            croak (errno, "main got null from 'pcap_next'(2): \"%s\"",
                           pcap_geterr(G_cap)) ;
        }

        len = packet_hdr.caplen ;
        if (len > (BUFFERLEN - 2)) continue ;

        if (G_dump_headers) {
            int n = len ;
            if (n > 128) n = 128 ;
            xdump (p, n) ;
        }

        memcpy (buffer, p, len) ;
        buffer[len] = 0 ;
        if (buffer[len-1]=='\n') buffer[len-1] = 0;
        p = buffer + hdr_len ;

        ip = (struct ip*)p ;
        ip_hl = ip->ip_hl * 4  ;
        ip_len = ntohs(ip->ip_len) ;
        ip_off = ntohs(ip->ip_off) ;

        if (ip_len > (MAX_GROUPNAME_LENGTH + MD5_HEXLENGTH + 27)) continue ;
        if (ip_len < (MD5_HEXLENGTH + 24)) continue ;
        if (ip_hl != 20) continue ;          // options are kinda suspicious.
        if (ip_off & IP_OFFMASK) continue ;  // fragments are -right out-.
        if (ip->ip_off & IP_MF) continue ;   //   "               "

        udp = (struct udphdr*) (p + ip_hl) ;
        payload = (unsigned char*)udp + sizeof(struct udphdr) ;
        memcpy (t, payload, 16) ;
//printf ("strlen(payload) = %d;  payload = '%s'\n", strlen(payload), payload) ;

        service = token (&payload, " ") ;
        if (service == NULL) continue ;
        guest = token (&payload, " ") ;
        if (service == NULL) continue ;
        tag = token (&payload, " ") ;
        if (tag == NULL) continue ;
        offered_secret = token (&payload, " ") ;
        if (service == NULL) continue ;
//printf ("service=%s  guest=%s  tag=%s  offered_secret=%s\n",
//service, guest, tag, offered_secret) ;
        src_addr = ip->ip_src ;
        strncpy (src_addr_buff, inet_ntoa(src_addr), sizeof(src_addr_buff)) ;

        if (  (strlen(service) > 5) ||
              (strlen(guest) > MAX_GROUPNAME_LENGTH)  ||
              (strlen(tag) > 10)  ||
              (strlen(offered_secret) != MD5_HEXLENGTH)  )
        {
            WARN "Bad packet from %s \""
                 "%2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x "
                 "%2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x %2.2x ..\"",
                  src_addr_buff,
                  t[0], t[1], t[2], t[3], t[4], t[5], t[6], t[7],
                  t[8], t[9], t[10], t[11], t[12], t[13], t[14], t[15]) ;
            continue ;
        }

        INFO "knock from %s : %s %s %s %s",
              src_addr_buff, service, guest, tag, offered_secret) ;

       // Do a binary search for the guest in the guest-list
       // (Algorithm courtesy D.E. Knuth :)

        lower = 0 ;
        upper = nGuests -1 ;
        i = 0 ;      // (just to keep the compiler quiet)
        cmp = 0 ;    //  ditto

        for (;;) {
            if (upper < lower) break ;
            i = (lower + upper) / 2 ;
            cmp = strcmp (guest, guest_list[i]) ;
            if (cmp == 0) break ;
            if (cmp < 0) {
                upper = i - 1 ;
            } else {
                lower = i + 1 ;
            }
        }

        if (cmp) {
            WARN "Unknown guest '%s'", guest) ;
            continue ;
        }

        // guest is in the list; break out all fields in the entry.

        p = guest_list[i] ;

        p += strlen(p) + 1 ;
        secret = p ;
        strncpy (stored_plaintext_secret, secret, MAX_SECRET_LENGTH) ;

        p += strlen(p) + 1 ;
        nServices = *(ushort*)p ;
        
        p += sizeof(ushort) ;
        services = (ushort*)p ;
        
        p += nServices * sizeof(ushort) ;
        nIPs =  *(ushort*)p ;
        iplist = (void*)p + sizeof(ushort) ;

        // check the requested service (port-number)

        port = atoi (service) ;
        for (i=0; i<nServices; i++) {
            if (port == services[i]) break ;
        }

        if (i == nServices) {
            WARN "Guest %s at %s not registered for port %s.",
                  guest, src_addr_buff, service) ;
            continue ;
        }

        // port-number is in the list; 
        // check the source address.

        for (i=0; i<nIPs; i++) {
            uint32_t  masked_listaddr ;
            mask = *(iplist + 1 + 2*i) ;
            masked_srcaddr = src_addr.s_addr & mask ;
            masked_listaddr = *(iplist + 2*i) ;
            if (masked_listaddr == masked_srcaddr) break ;
        }

        if (i == nIPs) {
            WARN "Guest %s is not registered for address %s.",
                  guest, src_addr_buff) ;
            continue ;
        }

        // IP address is in the list;
        // check the hashed secret.

         u = offered_hash ;
         for (i=0; i<16; i++) {
             *(u+i) = hex2byte (offered_secret + 2*i) ;
         }

        sprintf (hash_buff1, "%d %s %s",  port, guest, tag) ;

        hmac_md5 (stored_plaintext_secret, strlen(stored_plaintext_secret),
                   hash_buff1, strlen(hash_buff1), hash_buff2) ;

        nomatch = memcmp (hash_buff2, offered_hash, MD5_DIGEST_LENGTH) ;
        if (nomatch) {
            WARN "Guest %s at %s used incorrect secret.", guest, src_addr_buff);
            continue ;
        }

        // secret is ok;
        // check that packet tag & hash are not being replayed.

        hindex = aindex ((struct archive_record*)hash_buff2, hash_archive_size);

        nomatch = memcmp (&hash_archive[hindex], hash_buff2, MD5_DIGEST_LENGTH);
        if (nomatch) { // "no match" == good; save hash & time it was received.
            memcpy (&hash_archive[hindex], hash_buff2, MD5_DIGEST_LENGTH) ;
            time ((time_t*)(&hash_archive[hindex].time)) ;
        } else {       // A match is bad news. It's almost certain someone is
                       // trying to re-use a knock. Only BAD people do this.
            char time_buffer[64] ;
            struct tm *tm_time ;

            tm_time = gmtime ((time_t*)&hash_archive[hindex].time) ;
            strftime (time_buffer, 62, "%Y-%m-%d %H:%M:%S %Z", tm_time) ;
            WARN "PROBABLE REPLAY ATTEMPT from %s: port=%s guest=%s "
                 "tag=%s hash=%s; original timestamp=%s",
                 src_addr_buff, service, guest, tag,
                 offered_secret, time_buffer) ;
            continue ;
        }

//---------------------------------------------------
//           All checks have been passed.
//                 Let the guest in.
//---------------------------------------------------

        DEBUG "knock from %s was valid.", src_addr_buff) ;
        if (fork()) continue ;

        G_pidfile_is_ours = FALSE ;
        manage_firewall (device, hdr_len, guest, src_addr_buff, service) ;
        exit (0) ;

    }

}

