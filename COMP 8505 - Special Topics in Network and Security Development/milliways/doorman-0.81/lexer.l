/*****************************************************************************

    File: "lexer.l"

    Copyright (C) 2004  Bruce Ward

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

/* -------------------------------------------------------------------------*/
/*   JBW | June 24 2004 | Initial version                                   */
/* -------------------------------------------------------------------------*/

/*
    'prepare_guestlist()' reads the guest-list file, and creates a guest-list
    structure as shown below.   The pointer guest_list points to a vector of
    pointers, each of which points to a guest record.

    Each guest record is the catenation of port & address info for that 'guest':
    < guestname + secret +
                #-of-ports + port1 + port2 ... +
                #-of-IPaddresses + addr1+mask1 + addr2+mask2 ... >

    guest_list ->  guest1 ----------.
                   guest2 --> etc   |
                     :              |
                   guestn --> etc   |
                                    |
                                    |
   .--------------------------------'
   |                                  short short       short
   |                                    |    |            |
   `-----> guestname <00> secret <00> nPorts p1 p2 .. pn nIPS IP1 mask1 IP2 mask2 .. IPn maskn
                      |           |                            |    |
                   null byte    null byte                    long  long

*/


%{
    #include <sys/types.h>
    #include <stdlib.h>
    #include <string.h>
    #include <netdb.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include "utilities.h"

    #ifndef TRUE
    #  define TRUE (1)
    #endif

    #ifndef FALSE
    #  define FALSE (0)
    #endif

    #ifndef INADDR_NONE
    #  define INADDR_NONE 0xffffffff
    #endif

    #ifndef in_addr_t
    #  define in_addr_t u_int
    #endif

    #define YY_NO_UNPUT

    int     phase ;
    int     fatal ;
    int     lineno = 1 ;
    int     i, n ;
    void    **guest_list, *guestPtr, *next ;
    int     nGuests ;
    u_short    *nPortsPtr, *portPtr, *nIPsPtr ;
    in_addr_t  *IPPtr ;
    
    in_addr_t  ip, mask ;

    in_addr_t ipmasks[33] = {
        0x00000000, 0x80000000, 0xc0000000, 0xe0000000,
        0xf0000000, 0xf8000000, 0xfc000000, 0xfe000000,
        0xff000000, 0xff800000, 0xffc00000, 0xffe00000,
        0xfff00000, 0xfff80000, 0xfffc0000, 0xfffe0000,
        0xffff0000, 0xffff8000, 0xffffc000, 0xffffe000,
        0xfffff000, 0xfffff800, 0xfffffc00, 0xfffffe00,
        0xffffff00, 0xffffff80, 0xffffffc0, 0xffffffe0,
        0xfffffff0, 0xfffffff8, 0xfffffffc, 0xfffffffe,
        0xffffffff
    } ;


    void syntax (void)
    {
        char *p ;
//printf ("PHASE = %d\n", phase) ;
        switch (phase) {
            case 0:
                p = "group name" ;
                break ;
            case 1:
                p = "secret" ;
                break ;
            case 2:
                p = "port or service name" ;
                break ;
            case 3:
                p = "port or hostname/address" ;
                break ;
            case 4:
                p = "hostname or IP address" ;
                break ;
            default:
                p = "**internal lexer error; this should never be seen**" ;
                break ;
        }
        EMERG "Expected a %s, but found \"%s\" on line %d of guest list.",
               p, yytext, lineno) ;
        fatal = TRUE ;
    }


    void new_group(char *s)
    {
        u_int   len ;

        if (guest_list == NULL) {
            guest_list = malloc (sizeof(void*)) ;
            if (guest_list == NULL) {
                EMERGX "malloc call failed") ;
                exit(1) ;
            }
            nGuests = 1 ;
        } else {
            nGuests++ ;
            guest_list = realloc(guest_list, nGuests*sizeof(void*)) ;
            if (guest_list == NULL) {
                EMERGX "realloc call failed") ;
                exit(1) ;
            }
        }

        len = strlen(s) + 1 ;
        guestPtr = malloc(len) ;
        if (guestPtr == NULL) {
            EMERGX "malloc call failed") ;
            exit(1) ;
        }
        strcpy (guestPtr, s) ;

        guest_list[nGuests-1] = guestPtr ;
        nPortsPtr = NULL ;
        portPtr = NULL ;
        nIPsPtr = NULL ;
        IPPtr = NULL ;
        next = guestPtr + len ;

    }


    void realloc_guest(int added)
    {
        u_long    offset_to_next ;
        u_long    offset_to_nPortsPtr, offset_to_portPtr ;
        u_long    offset_to_nIPsPtr, offset_to_IPPtr ;

        offset_to_next = next - guestPtr ;
        offset_to_nPortsPtr = (void*)nPortsPtr - guestPtr ;
        offset_to_portPtr = (void*)portPtr - guestPtr ;
        offset_to_nIPsPtr = (void*)nIPsPtr - guestPtr ;
        offset_to_IPPtr = (void*)IPPtr - guestPtr ;
//printf ("guestPtr=    0x%12.12x  next=0x%12.12x   offset_to_next=%d   added=%d   offset_to_next+added=%d  offset_to_IPPtr=%d\n", guestPtr, next, offset_to_next, added, offset_to_next+added, offset_to_IPPtr) ;
        guestPtr = realloc(guestPtr,  offset_to_next + added) ;
        if (guestPtr == NULL) {
            EMERGX "realloc call failed") ;
            exit(1) ;
        }
        guest_list[nGuests-1] = guestPtr ;
        next = guestPtr + offset_to_next + added ;
//printf ("new guestPtr=0x%12.12x  new next=0x%12.12x\n", guestPtr, next) ;

        if (nPortsPtr) nPortsPtr = guestPtr + offset_to_nPortsPtr ;
        if (portPtr) portPtr = guestPtr + offset_to_portPtr ;
        if (nIPsPtr) nIPsPtr = guestPtr + offset_to_nIPsPtr ;
        if (IPPtr) IPPtr = guestPtr + offset_to_IPPtr ;
    }


    void store_secret (char *s)
    {
        int  offset_to_secret ;

        offset_to_secret = next - guestPtr ;
        realloc_guest (strlen(s) + 1) ;
        strcpy (guestPtr+offset_to_secret, s) ;

    }


    void store_port (u_short port) 
    {
        if (phase == 2) {
            nPortsPtr = next ;
            realloc_guest (sizeof(u_short)) ;
            *nPortsPtr = 0 ;
            portPtr = next ;
        }
        realloc_guest (sizeof(u_short)) ;

        (*nPortsPtr)++ ;
        *(portPtr++) = port ;
    }


    void store_IP (in_addr_t addr, in_addr_t mask)
    {
        int  n ;
        void *p ;
        if (phase == 3) {
//printf ("store_IP phase 3\n") ;
            n = sizeof(short) ;
            realloc_guest (n) ;
            p =  next - n ;
            *(u_short*)p = 0 ;
            nIPsPtr = next - sizeof(u_short) ;
            IPPtr = next ;
        }
        realloc_guest (2*sizeof(in_addr_t)) ;

        (*nIPsPtr)++ ;
//printf ("IPPtr=       0x%12.12x\n", IPPtr) ;
        *(IPPtr++) = addr ;
//printf ("IPPtr=       0x%12.12x\n", IPPtr) ;
        *(IPPtr++) = htonl(mask) ;
    }


%}


NAME [a-zA-Z0-9\!\@\#\$\%\^\&\*\(\)\-\_\=\+\|\\\?\/\\,<\>\[\]\{\}\"\'\:\;]+


%%


\n { lineno += 1 ; }

#.*

[ \t]*

^{NAME}/\.  {
    EMERG "Guest list line %d: group name contains a period", lineno) ;
    exit(1) ;
} 



^{NAME}  {                                                    /* groupname */
//printf ("phase %d;  groupname  %s\n", phase, yytext) ;
    if ((phase == 0) || phase == 4) {
        new_group (yytext) ;
    } else {
        syntax() ;
    }
    phase = 1 ;
}



[0-9]+ {                                            /* portnumber or secret */
//printf ("phase %d;  portnumber or secret  %s\n", phase, yytext) ;
    switch (phase) {
        u_short port ;
        case 1:   /* secret */
            store_secret(yytext) ;
            phase = 2 ;
            break ;
        case 2:   /* portnumber */
        case 3:
            port = (u_short)atoi(yytext) ;
            if ((port < 1) || (port > 65534)) {
                EMERG "Bad port number \"%s\" on line %d of guest list",
                       yytext, lineno) ;
                fatal = TRUE ;
            }
            store_port(port) ;
            phase = 3 ;
            break ;
        default:
            syntax() ;
            fatal = TRUE ;
            break ;
    }
}



[a-zA-Z][a-zA-Z0-9]+ {                             /* servicename or secret */
//printf ("phase %d;  servicename or secret  %s\n", phase, yytext) ;
    switch (phase) {
        struct servent *p ;
	int port ;
        case 1:   /* secret */
            store_secret(yytext) ;
            phase = 2 ;
            break ;
        case 2:   /* service name */
        case 3:
            p = getservbyname (yytext, NULL) ;
            if (p == NULL) {
                EMERG "Bad service name \"%s\" on line %d of guest list",
                       yytext, lineno) ;
                fatal = TRUE ;
            } else {
                  port = ntohs ((short)p->s_port) ;
//printf("          portnumber for %s = %d\n", yytext, port) ;
                store_port((short)port) ;
            }
        phase = 3 ;
            break ;
        default:
            syntax() ;
            break ;
    }
}    



{NAME}/\. {                                     /* something odd with a "." */
//printf ("phase %d;  odd thing with a '.' in it:  %s\n", phase, yytext) ;
    switch (phase) {
        case 0:
            EMERG "Guest list line %d: \"%s\" guest name(?) must begin in "
                  "column 1", lineno, yytext) ;
        break ;
    case 4:
            EMERG "Guest list line %d: \"%s\" illegal address",
                  lineno, yytext) ;
        break ;
        case 1:
            EMERG "Guest list line %d:  \"%s\" secret contains a period",
                  lineno, yytext) ;
        break ;
    case 2:
            EMERG "Guest list line %d:  \"%s\" illegal port port or service "
                  "name", lineno, yytext) ;
        break ;
    case 3:
            EMERG "Guest list line %d:  \"%s\" illegal port port or service "
                  "name", lineno, yytext) ;
        break ;
        default:
            EMERG "Guest list line %d:  \"%s\" **internal lexer error**",
                  lineno, yytext) ;
        break ;
    }
    exit(1) ;
}



{NAME} {                                                         /* secret */
//printf ("phase %d;  secret  %s\n", phase, yytext) ;
    if (phase == 1) {
        store_secret(yytext) ;
        phase = 2 ;
    } else {
        syntax() ;
    }
}



[0-9]+\.[0-9]+\.[0-9]+\.[0-9]+  {                             /* IP address */
//printf ("phase %d;  IP address  %s\n", phase, yytext) ;
    if ((phase < 3) || (phase > 4)) {
        syntax() ;
    } else {
        ip = inet_addr (yytext) ;
        if (ip == INADDR_NONE) {
            EMERG "Illegal IP addressd \"%s\" in guestlist line %d\n",
                  yytext, lineno) ;
            fatal = TRUE ;
        }
        store_IP (ip, inet_addr("255.255.255.255")) ;
        phase = 4 ;
    }
}



[0-9]+\.([0-9]+\.[0-9]+\.[0-9]+\/[0-9]+)+  {           /* masked IP address */
//printf ("phase %d;  masked IP address  %s\n", phase, yytext) ;
    char  *p, *p2 ;
    if ((phase < 3) || (phase > 4)) {
        syntax() ;
    } else {
        p2 = yytext ;
        p = token (&p2, "/") ;
        ip = inet_addr (yytext) ;
        if (ip == INADDR_NONE) {
            EMERG "Illegal IP address \"%s\" in guestlist line %d\n",
                  yytext, lineno) ;
            fatal = TRUE ;
        } else {
            n = atoi (p2) ;
            if ((n < 0) || (n > 32)) {
                EMERG "No. of bits \"%s\" out of range 0-32 in guestlist "
                      "line %d\n", p2, lineno) ;
                fatal = TRUE ;
            } else {
                store_IP (ip, ipmasks[n]) ;
            }
        }
        phase = 4 ;
    }
}



[a-zA-Z0-9\-]+\.([a-zA-Z0-9\-]+\.)*[a-zA-Z0-9\-]+  {                  /* hostname */
//printf ("phase %d;  hostname  %s\n", phase, yytext) ;
    struct hostent *h ;
    if ((phase < 3) || (phase > 4)) {
        syntax() ;
    } else {
        h = gethostbyname (yytext) ;
        if (h == NULL) {
            EMERG "Unknown host \"%s\" in guestlist line %d\n",
                  yytext, lineno) ;
            fatal = TRUE ;
        } else {
            store_IP (*(in_addr_t*)*h->h_addr_list,
                       inet_addr("255.255.255.255")) ;
        }
        phase = 4 ;
    }
}



[a-zA-Z0-9\-]+\.([a-zA-Z0-9\-]+\.)*[a-zA-Z0-9\-]+\/[0-9]+  {   /* masked hostname */
//printf ("phase %d;  masked hostname  %s\n", phase, yytext) ;
    struct hostent *h ;
    char  *p, *p2 ;
    if ((phase < 3) || (phase > 4)) {
        syntax() ;
    } else {
        p2 = yytext ;
        p = token (&p2, "/") ;
        h = gethostbyname (yytext) ;
        if (h == NULL) {
            EMERG "Unknown host \"%s\" in guestlist line %d\n",
                   yytext, lineno) ;
            fatal = TRUE ;
        } else {
            n = atoi (p2) ;
            if ((n < 0) || (n > 32)) {
                EMERG "No. of bits \"%s\" out of range 0-32 in guestlist "
                      "line %d\n", p2, lineno) ;
                fatal = TRUE ;
            } else {
                store_IP (*(in_addr_t*)*h->h_addr_list, ipmasks[n]) ;
            }
        }
        phase = 4 ;
    }
}



%%



/* ----------------------------------------------------- */



#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

int compare (char **s1, char **s2)
{
    return strcmp(*s1, *s2) ;
}



int prepare_guestlist (char *filename, void ***returned_guest_list)
{

     FILE *f ;

     f = freopen (filename, "r", stdin) ;
     if (f == NULL) {
        EMERGX "Can't open guest list \"%s\"", filename) ;
        exit(1) ;
    }

    guest_list = NULL ;
    phase = 0 ;
    fatal = FALSE ;

    yylex() ;

    if (fatal) exit(1) ;
    if (phase != 4) {
        EMERG "Unexpected end-of-file in guest list \"%s\"\n", filename) ;
        exit(1) ;
    }

    qsort (guest_list, nGuests, sizeof(void*), (void*)compare) ;

    *returned_guest_list = guest_list ;

    return nGuests ;
}

