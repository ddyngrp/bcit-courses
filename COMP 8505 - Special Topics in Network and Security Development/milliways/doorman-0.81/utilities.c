/*****************************************************************************

    File: "utilities.c"

    Copyright (C) 2002-2003  Bruce Ward

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
//   JBW | Oct  8 2003 | Initial version
//   JBW | Jul 23 2004 | Bugfix by Leonid Shalupov to make sure hostname
//                     | is null terminated in fn. 'err_log'
// --------------------------------------------------------------------------



#include <sys/types.h>
#ifdef WIN32
#  include <wtypes.h>
#  include <winbase.h>
#  include <winsock.h>
#else
#  include "config.h"
#  include <unistd.h>
#  include <sys/time.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "utilities.h"






u_char hex2byte (char *p)
{
    static u_char n[256] = {
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 1, 2, 3,  4, 5, 6, 7,  8, 9, 0, 0,  0, 0, 0, 0,

	    0,10,11,12, 13,14,15, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0,10,11,12, 13,14,15, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,

	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 1, 2, 3,  4, 5, 6, 7,  8, 9, 0, 0,  0, 0, 0, 0,

	    0,10,11,12, 13,14,15, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0,10,11,12, 13,14,15, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	    0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0
	} ;


	return  (n[(int)*p]<<4) | (n[(int)*(p+1)]) ;
}





/*************************** Debugging hexdump ****************************/



static char *hexchar = "0123456789abcdef" ;

char *btohex (char *p, char c)
{
    *p++ = hexchar[(c>>4)&0x0f] ;
    *p++ = hexchar[c&0x0f] ;

    return p ;
}


char *itohex (char *p, int n)
{
    *p++ = hexchar[(n>>28)&0x0f] ;
    *p++ = hexchar[(n>>24)&0x0f] ;
    *p++ = hexchar[(n>>20)&0x0f] ;
    *p++ = hexchar[(n>>16)&0x0f] ;
    *p++ = hexchar[(n>>12)&0x0f] ;
    *p++ = hexchar[(n>>8)&0x0f] ;
    *p++ = hexchar[(n>>4)&0x0f] ;
    *p++ = hexchar[n&0x0f] ;

    return p ;
}



void xxdump (FILE* f, void *v, int len, int aflag)
{
    int      i, line, last ;
    char     buffer[80] ;
    char     c ;
    u_char   *base, *data, *p ;

    data = v ;
    base = 0 ;
    if (aflag) {
        base = data ;
    }
/*
    buffer = malloc(80) ;
    if (buffer == NULL) {
        fprintf (f, "**malloc failed in 'xxdump'\n") ;
        return ;
    }
*/
    for (line=0; line<len; line += 16) {
        memset (buffer, 0x20, 80) ;
        p = itohex (buffer, ((unsigned long)base)+line) ;
        *p++ = ' ' ;
        *p++ = ':' ;
        last = line + 16 ;
        if (last > len) last = len ;
        for (i=line; i<last; i++) {
            if ((i %4) == 0) *p++ = ' ' ;
            p = btohex (p, data[i]) ;
            *p++ = ' ' ;
        }
        p = buffer + 63 ;
        for  (i=line; i<last; i++) {
            c = data[i] & 0x7f ;
            if (c < 0x20)  c = '.' ;
            if (c == 0x7f) c = '.' ;
            *p++ = c ;
        }
        *p++ = '\n' ;
        *p = 0 ;
        fputs (buffer, f) ;
    }
    fputs ("\n", f) ;
    fflush (f) ;
 //   free (buffer) ;
}



void xdump (void *data, int len)
{
    xxdump (stdout, data, len, 0) ;
}




/***************************** Error logging ******************************/


#ifndef WIN32



static const char *log_prioritynames[] = {
    "emerg", "alert", "crit", "error", "warn", "notice", "info", "debug", NULL
} ;

int  _err_loglevel ;
FILE *_err_file ;



void err_set_errfile (FILE *f)
{
    if (f) {
        _err_file = stderr ;
    } else {
        _err_file = f ;
    }
}



int err_set_loglevel (void *level)
{
    int   i, err ;
    
    err = -1 ;

    if ((unsigned long)level <= LOG_DEBUG) {
        _err_loglevel = abs((long)level) ;
        err = 0 ;
    } else {
        for (i=0; log_prioritynames[i]; i++) {
            if (strcasecmp(level,log_prioritynames[i]) == 0) {
                _err_loglevel = i ;
                err = 0 ;
                break ;
            }
        }
    }
    return err ;
}



int err_openlog (char *filename, char *levelname)
{
    int  level ;

    for (level=0; log_prioritynames[level]; level++) {
        if (strcasecmp(levelname, log_prioritynames[level])==0) break ;
    }
    
    if (log_prioritynames[level] == NULL) {
        errno = EINVAL ;
        return errno ;
    }
    
    _err_loglevel = level ;
    _err_file = fopen (filename, "a") ;
    if (_err_file == NULL) {
        _err_loglevel = -1 ;
        return errno ;
    }
    return 0 ;
}



int err_closelog (void)
{
    return fclose (_err_file) ;
}



int err_loglevel (void)
{
    return _err_loglevel ;
}




#define BSIZE 256

void err_log (char         *lable,
              char         *file,
              int          line,
              unsigned int level,
              char         *fmt, ...)
{
    time_t       t ;
    struct tm    *lt ;
    char         *t_fmt = "%b %e %H:%M:%S "  ;
    unsigned int n, log_errno ;
    va_list      ap ;
    char         buffer[BSIZE+10] ;

    if (_err_loglevel < 0) return ;

    if (level & LOG_NOERR) {
        log_errno = 0 ;
    } else {
        log_errno = 1 ;
    } ;

    level = level & 0x07 ;
    if (level > _err_loglevel) return ;

    t = time(NULL) ;
    lt = localtime (&t) ;

    strftime (buffer, 17, t_fmt, lt) ;                   /* time */

    buffer[32] = 0 ;   // L.S. : make sure it's terminated!
    gethostname(buffer+16, 16) ;                         /* hostname */

    strcat (buffer, " ") ;
    n = strlen (buffer) ;

    if (lable) {                                         /* lable */
        strncat (buffer, lable, BSIZE-n) ;
    } else {
        strncat (buffer, "<null>", BSIZE-n) ;
    }
    
    n = strlen (buffer) ;

    n += snprintf (buffer+n, BSIZE-n, "[%d]: %s: ",      /* pid & level */
                   (int)getpid(), log_prioritynames[level]) ;

    if (file) {
        n += sprintf (buffer+n, "%s line %d  ", file, line) ;
    }

    if (log_errno) {                                     /* error string */
        n += snprintf (buffer+n, BSIZE-n, "(%s) ", strerror(errno)) ;
    }

    va_start (ap, fmt) ;                                 /* all the rest */
    n += vsnprintf (buffer+n, BSIZE-n, fmt, ap) ;
    va_end (ap) ;

    buffer[n] = '\n' ;
    buffer[n+1] = 0 ;
    fputs (buffer, _err_file) ;
    fflush (_err_file) ;
}


#endif   /*  ifndef WIN32  */





/************************ Configuration functions ***************************/


int cfg_open (char *file, struct config_block *cfg)
{
    cfg->f = fopen (file, "r") ;
    if (cfg->f) {
        return 0 ;
    } else {
        return errno ;
    }
}



int cfg_close (struct config_block *cfg)
{
    return fclose (cfg->f) ;
}



int cfg_rewind (struct config_block *cfg)
{
    return fseek (cfg->f, 0L, SEEK_SET) ;
}



char *token (char **buffer, char *delimiters)
{
    int i ;
    char darray[256] ;
    char *p1, *p2 ;
    
    memset (darray, 0, 256) ;
    for (i=0; delimiters[i]; i++) darray[(unsigned char)delimiters[i]] = 1 ;
    darray[0] = 1 ;  // null is always a delimiter.

    for (p1=*buffer; *p1; p1++) {  // find first non-delimiter
        if (darray[(unsigned char)*p1] == 0) break ;
    }

    if (*p1 == 0) {
        *buffer = p1 ;
        return NULL ;
    }

    for (p2=p1; *p2; p2++) {
        if (darray[(unsigned char)*p2]) break ;
    }

    *buffer = p2 ;
    if (*p2) {
        *p2 = 0 ;
        *buffer += 1 ;
    }
    
    return p1 ;

}



char *cfg_next_ascii_value (struct config_block *cfg, char *key)
{
    char  *p1, *p2, *p3 ;

    while (fgets(cfg->buffer, 128, cfg->f)) {
        p1 = strchr (cfg->buffer, '#') ;
        if (p1) *p1 = 0 ;
        p3 = cfg->buffer ;
        p1 = token (&p3, " \t\n") ;
        if (p1 == NULL) continue ;

        p2 = strchr (p3, '"') ;
        if (p2) {
            p3 = strrchr (p3, '"') ;
            if (p3) *p3 = 0 ;
        } else {
            p2 = token (&p3, " \t\n") ;
        }

        if (p2 == NULL) {
            continue ;
        }
#ifdef WIN32
        if (strcmp(p1, key) == 0) {  // winDoze uSers wiLl haVta
#else                                // paY attEntIon To cAse. 
        if (strcasecmp(p1, key) == 0) {
#endif
            return p2 ;
        }
    }

    return NULL ;
}



char *cfg_first_ascii_value (struct config_block *cfg, char *key)
{
    int  err ;

    err = fseek (cfg->f, 0L, SEEK_SET) ;
    if (err) return NULL ;

    return cfg_next_ascii_value (cfg, key) ;
}


