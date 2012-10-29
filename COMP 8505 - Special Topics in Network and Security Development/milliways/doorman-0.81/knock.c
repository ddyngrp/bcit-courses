/*****************************************************************************

    File: "knock.c"

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
//   JBW | v0.1   | Oct  8 2003 | Initial version
//   JBW | v0.5   | Jun 19 2004 | Added 'secret' prompt if secret is otherwise
//                              | missing
//                              | Fixed a few bugs
//   JBW | v0.5.1 | Jul 3  2004 | Removed use of address mask bits
//   JBW | v0.6   | Jul 13 2004 | Removed use of 'gettimeofday' replacement fn.
//                              | for Windows.
//   JBW | v0.8   | Jul 28 2004 | Added '-r' option; changed authentication
//                              | method 
// --------------------------------------------------------------------------




#ifdef WIN32
   typedef unsigned int uint32_t ;
#  define  vsnprintf _vsnprintf
#  define  snprintf  _snprintf
#  define  write     _write
#  include "config_win.h"
#  include <io.h>
#  include <conio.h>
#  include <winsock.h>
#  include <sys/timeb.h>
#else
#  include "config.h"
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <sys/stat.h>
#  include <sys/param.h>
#  include <sys/user.h>
#  include <sys/time.h>
#  include <sys/times.h>
#  include <unistd.h>
#  include <netinet/in.h>
#  include <arpa/inet.h>
#  include <netdb.h>
#endif

#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef WIN32
#  ifdef HAVE_MD5GLOBAL_H
#    include <md5global.h>
#  endif
#
#  ifdef HAVE_MD5_H
#    include <md5.h>
#  else
#    ifdef HAVE_OPENSSL_MD5_H
#      include <openssl/md5.h>
#    endif
#  endif
#
#  ifdef HAVE_HMAC_MD5_H
#    include <hmac-md5.h>
#  endif
#endif

#ifndef in_addr_t
#  define in_addr_t u_int
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

#ifndef INADDR_NONE
#  define INADDR_NONE (0xffffffff)
#endif

#include "constants.h"
#include "utilities.h"


char secret[MAX_SECRET_LENGTH+2] ;


void usage(char c)
{

#ifdef WIN32
   char *filename = "C:\\knock.cfg" ; 
#else
   char *filename = "~/.knockcf" ; 
#endif

   fprintf (stderr, "\n%cPortknocker client %s\n", c, VERSION) ;
   fprintf (stderr, "Usage :\n") ;
   fprintf (stderr, "  knock [-h] [-v] [-p port] [-g groupid] \\\n");
   fprintf (stderr, "        [-s secret] [-r \"program arg1 arg2... \"]  "
                    "host service\n\n");
   fprintf (stderr, "    -h             print this message and quit.\n") ;
   fprintf (stderr, "    -v             print version number the and "
                     "quit.\n");
   fprintf (stderr, "    -g groupid     use this group-name.\n") ;
   fprintf (stderr, "    -p port        knock on this port.\n") ;
   fprintf (stderr, "    -s secret      use this secret.\n") ;
   fprintf (stderr, "    -r \"program arg1 arg2..\"   run this program after");
   fprintf (stderr, " sending the knock.\n") ;
   fprintf (stderr, "    host           IP address or name of the"
                    " remote server\n") ;
   fprintf (stderr, "    service        port number or name of the service"
                    " requested\n\n") ;
   fprintf (stderr, "  -g, -p, -r, and -s override the corresponding "
                    "values in %s\n\n", filename);
}



void die (int err, char *fmt, ...)
{
    char     buffer [256] ;
    char     *p ;
    va_list  args ;

    memset (secret, 0, MAX_SECRET_LENGTH+2) ;

    p = buffer ;
    va_start(args, fmt) ;
    p += vsprintf (p, fmt, args) ;
    va_end(args) ;

    if (err) sprintf (p, " : %s", strerror(err)) ;
    strcat (p, "\a\n") ;
    fputs (buffer, stderr) ;

    exit (1) ;
}



int main (int argc, char *argv[])
{
#ifdef WIN32
    WORD                 wVersionRequested;
    WSADATA              wsaData;
    struct _timeb        timebuffer ;
//    OSVERSIONINFO        versioninfo ;
#else
    struct stat          status ;
    struct timeval       tod ;
#endif
    uint32_t             uaddr ;
    unsigned char        *u ;
    struct sockaddr_in   addr ;
    struct servent       *servent ;
    struct hostent       *hostent ;
    struct config_block  cfg ;
    int       sock, err, port_number, service_number ;
#ifdef WIN32
    int       windoze = 1 ;
#else
    int       windoze = 0 ;
#endif
    uint32_t  random_number ;
    char      c ;
    int       n ;
    char      *p, *p1, *p2, *host, *port, *service ;
    char      group[MAX_GROUPNAME_LENGTH+2] ;
    char      cfg_name[512] ;
    char      buffer[256], command[256] ;
    char      hash_buff1[128], hash_buff2[128] ;


    port_number = DEFAULT_PORT ;
    port = NULL ;
    group[0] = 0 ;
    secret[0] = 0 ;
    command[0] = 0 ;

//                 ----------------------
//                 -  read config file  -
//                 ----------------------

#ifdef WIN32
    strcpy (cfg_name, DEFAULT_WINDOWSCLIENT_CONFIGFILE) ;
#else
    sprintf (cfg_name, "%s/" DEFAULT_UNIXCLIENT_CONFIGFILE, getenv("HOME")); 
#endif

    err = cfg_open (cfg_name, &cfg) ;
    if (err) {
        fprintf (stderr, "\aWarning: can't open configuration file '%s'\n",
                 cfg_name);
    } else {

#ifndef WIN32
        err = stat (cfg_name, &status) ;
        if (err) {
            die (errno, "Can't get status of config file '%s'.", cfg_name) ;
        }
        if ( (status.st_mode & (S_IRWXG | S_IRWXO)) ) {
            die (0, "'%s' must not be readable or writeable by anyone but "
                    "the owner.", cfg_name) ;
        }
#endif

        p =  cfg_first_ascii_value (&cfg, "group") ;
        if (p) strncpy (group, p, MAX_GROUPNAME_LENGTH) ;

        p =  cfg_first_ascii_value (&cfg, "secret") ;
        if (p) strncpy (secret, p, MAX_SECRET_LENGTH) ;

        p =  cfg_first_ascii_value (&cfg, "run") ;
        if ( p && ((*p == '\'') || (*p == '"')) ) p++ ;
        if (p) strncpy (command, p, sizeof(command)-2) ;

        p =  cfg_first_ascii_value (&cfg, "port") ;
        if (p) {
            port_number = atoi(p) ;
            if ((port_number < 1) || (port_number > 65535)) {
                die(0, "Illegal port number (%s) in %s.", p, cfg_name) ;
            }
        } else {
            port_number = DEFAULT_PORT ;
        }
        
        cfg_close (&cfg) ;
    
    }

//                 ----------------------
//                 -   parse cmd line   -
//                 ----------------------


    while ((c = getopt(argc, argv, "?g:hp:r:s:v")) != -1) {

        switch (c) {
            case 'g':
                strncpy (group, optarg, MAX_GROUPNAME_LENGTH) ;
                break ;
            case 'h':
                usage(0) ;
                memset (secret, 0, MAX_SECRET_LENGTH+2) ;
                exit (0) ;
                break ;
            case 'p':
                port_number = atoi(optarg) ;
                if ((port_number < 1) || (port_number > 65534)) {
                    fprintf(stderr, "\aInvalid port number, '-p %s'\n", optarg);
                    goto error_exit ;
                }
                break ;
            case 'r':
                if (  (strcmp(optarg,"0")==0)
		   || (strcmp(optarg,"x")==0)
		   || (strcmp(optarg,"X")==0) )
		{
                    command[0] = 0 ;
                } else {
                    strncpy (command, optarg, sizeof(command)-2) ;
                }
                break ;
            case 's':
                strncpy (secret, optarg, MAX_SECRET_LENGTH) ;
                break ;
            case 'v':
                printf ("Port knocking client %s  %s %s\n",
                         VERSION, __DATE__, __TIME__) ;
                printf ("%s\n\n", DOORMAN_URL) ;
                memset (secret, 0, MAX_SECRET_LENGTH+2) ;
                exit (0) ;
                break ;
            case '?':
            default:
                usage('\a') ;
                goto error_exit ;
                break ;
        }
    }

    if ((argc - optind) < 2) {
        usage('\a') ;
        goto error_exit ;
    }

    if (secret[0] == 0) {
#ifdef WIN32
        int i ;
        printf ("Enter secret: ") ;
        p = secret ;
        for (i=0; i<MAX_SECRET_LENGTH; i++) {
            c = _getch() ;
            if (c == 3) {
                fprintf (stderr, "\n** Interrupted **\n") ;
                goto error_exit ;
            }
            if (c == '\b') {
                i -= 2 ;
                if (i < -1) {
                    i = -1 ;
                    putchar('\a') ;
                }
                continue ;
            }
            if (c == '\r') break ;

            secret[i] = c ;
        }
        secret[i] = 0 ;
#else
        p = getpass("Enter secret: ") ;
        strncpy (secret, p, MAX_SECRET_LENGTH) ;
        memset (p, 0, strlen(p)) ;
#endif
    }


#ifdef WIN32
    wVersionRequested = MAKEWORD(2,0) ;
    err = WSAStartup (wVersionRequested, &wsaData ) ;
    if (err) {
        fprintf (stderr, "\aNeed Winsock version 2.\n") ;
        goto error_exit ;
    }
#endif

    host = argv[argc-2] ;
    service = argv[argc-1] ;

    service_number = atoi (service) ;
    if (service_number > 65534) {
        fprintf (stderr, "\aInvalid port number, %s\n", service) ;
        goto error_exit ;
    }
    if (service_number == 0) {
        if (windoze && ((strcmp(service, "SSH")==0) ||  // Older windozes don't
                        (strcmp(service, "ssh")==0))) { // know about ssh.
            service_number = 22 ;                      
        } else {
            servent = getservbyname (service, NULL) ;
            if (servent == NULL) {
                fprintf (stderr, "\aNo such service, %s\n", service) ;
                goto error_exit ;
            }
            service_number = ntohs (servent->s_port) ;
        }
    }

    sock = socket (AF_INET, SOCK_DGRAM, 0) ;
    if (sock <0) die (errno, "Can't create a socket") ;

    uaddr = inet_addr (host) ;
    if (uaddr == INADDR_NONE) {
        hostent = gethostbyname (host) ;
        if (hostent == NULL) {
            fprintf (stderr, "\aCan't find host '%s'\n", host) ;
            goto error_exit ;
        }
        uaddr = *(in_addr_t*)*hostent->h_addr_list ;
    }

    addr.sin_family = AF_INET ;
    addr.sin_addr.s_addr = uaddr ;
    addr.sin_port = htons ((unsigned short)port_number) ;

    err = connect (sock, (struct sockaddr*)&addr, sizeof(addr)) ;
    if (err) die (errno, "Can't connect to '%s'", host) ;

#ifdef WIN32
    _ftime (&timebuffer) ;
    random_number = timebuffer.time ;
    random_number += timebuffer.millitm ;
    srand (random_number) ;
    random_number = rand() ;
    random_number += rand() << 16 ;
    random_number += rand() << 17 ;
#else
    gettimeofday (&tod, NULL) ;
    random_number = tod.tv_sec ;
    random_number += tod.tv_usec ;
    srand (random_number) ;
    random_number = rand() ;
#endif

    sprintf (hash_buff1, "%d %s %10.10u", service_number, group, random_number) ;

    hmac_md5 (secret, strlen(secret),
              hash_buff1, strlen(hash_buff1), hash_buff2) ;
    memset (secret, 0, MAX_SECRET_LENGTH+2) ;

    u = (unsigned char*)hash_buff2 ;
    snprintf (buffer, 80, "%d %s %10.10u "
                          "%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x"
                          "%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x",
                          service_number, group, random_number,
                          u[0],u[1],u[2],u[3],u[4],u[5],u[6],u[7],
                          u[8],u[9],u[10],u[11],u[12],u[13],u[14],u[15]) ;


    send (sock, buffer, strlen(buffer), 0) ;

    if (command[0]) {

        p1 = command ;       // substitute for host marker '%H%'
        n = strlen (host) ;
        for (;;) {
            p2 = strstr (p1, "%H%") ;
            if (p2 == NULL) break ;
            if ( (((p2+n)-command) + (strlen(p2+3)+1)) > sizeof(command) ) {
                fprintf (stderr, "'-r' command is too long.\n") ;
                exit(1) ;
            }
            memmove (p2+n, p2+3, strlen(p2+3)+1) ;
            memmove (p2, host, n) ;
            p1 += n ;
        }

        p1 = command ;       // substitute for service (port) marker '%P%'
        n = strlen (service) ;
        for (;;) {
            p2 = strstr (p1, "%P%") ;
            if (p2 == NULL) break ;
            if ( (((p2+n)-command) + (strlen(p2+3)+1)) > sizeof(command) ) {
                fprintf (stderr, "'-r' command is too long.\n") ;
                exit(1) ;
            }
            memmove (p2+n, p2+3, strlen(p2+3)+1) ;
            memmove (p2, service, n) ;
            p1 += n ;
        }

#ifdef WIN32
        Sleep (100) ;
#else
        usleep (100000) ;    // pause for 0.1 seconds
#endif
        err = system (command) ;
        if (err) {
            exit (1) ;       // depend on the shell to complain of any errors.
        }
    }

    exit (0) ;


error_exit:

    memset (secret, 0, MAX_SECRET_LENGTH+2) ;
    exit (1) ;

}


