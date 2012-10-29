/*****************************************************************************

    File: "utilities.h"

    Copyright (C) 2002-2003, Bruce Ward

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
//   JBW | Oct.8 2003 | Initial version
// --------------------------------------------------------------------------



#ifndef SRC_UTILITIES_H
#define SRC_UTILITIES_H 1


#ifndef u_char
#  define u_char unsigned char
#endif

u_char hex2byte (char *p) ;


/***** Debugging  *****/

char *btohex (char *p, char c) ;
char *itohex (char *p, int n) ;
void xxdump (FILE* f, void *v, int len, int aflag) ;
void xdump (void *data, int len) ;



/***** Error logging *****/

#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERROR   3
#define LOG_WARNING 4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7

#define LOG_NOERR  0x10
#define LOG_MARK   __FILE__, __LINE__
#define LOG_NOMARK NULL, 0

#define LOG    err_log("doormand",LOG_NOMARK,
#define EMERG  err_log("doormand",LOG_NOMARK,LOG_NOERR|LOG_EMERG,
#define EMERGX err_log("doormand",LOG_MARK,LOG_EMERG,
#ifndef WIN32
#define ERROR  err_log("doormand",LOG_NOMARK,LOG_NOERR|LOG_ERROR,
#define ERRORX err_log("doormand",LOG_MARK,LOG_ERROR,
#endif
#define WARN   err_log("doormand",LOG_NOMARK,LOG_NOERR|LOG_WARNING,
#define WARNX  err_log("doormand",LOG_MARK,LOG_WARNING,
#define NOTICE err_log("doormand",LOG_NOMARK,LOG_NOERR|LOG_NOTICE,
#define INFO   err_log("doormand",LOG_NOMARK,LOG_NOERR|LOG_INFO,
#define DEBUG  err_log("doormand",LOG_NOMARK,LOG_NOERR|LOG_DEBUG,
#define DEBUGX err_log("doormand",LOG_MARK,LOG_DEBUG,


FILE *_err_file ;


void err_log (char         *lable,
              char         *file,
              int          line,
              unsigned int level,
              char         *fmt, ...) ;


void err_set_errfile (FILE *f) ;
int  err_loglevel (void) ;
int  err_set_loglevel (void *level) ;
int  err_openlog (char *name, char *levelname) ;
int  err_closelog (void) ;



/***** Configuration *****/

typedef struct config_block {
    FILE *f ;
    char buffer[130] ;
} config_block ;

char *token (char **buffer, char *delimiters) ;
int cfg_open (char *file, struct config_block *cfg) ;
int cfg_close (struct config_block *cfg) ;
int cfg_rewind (struct config_block *cfg) ;
char *cfg_first_ascii_value (struct config_block *cfg, char *key) ;
char *cfg_next_ascii_value (struct config_block *cfg, char *key) ;




/***** md5 replacement *****/

// (we assume that only windows wiil be utterly without md5)
#ifdef WIN32

/*
 ***********************************************************************
 ** md5.h -- header file for implementation of MD5                    **
 ** RSA Data Security, Inc. MD5 Message-Digest Algorithm              **
 ** Created: 2/17/90 RLR                                              **
 ** Revised: 12/27/90 SRD,AJ,BSK,JT Reference C version               **
 ** Revised (for MD5): RLR 4/27/91                                    **
 **   -- G modified to have y&~z instead of y&z                       **
 **   -- FF, GG, HH modified to add in last register done             **
 **   -- Access pattern: round 2 works mod 5, round 3 works mod 3     **
 **   -- distinct additive constant for each step                     **
 **   -- round 4 added, working mod 7                                 **
 ***********************************************************************
 */

/*
 * Edited 7 May 93 by CP to change the interface to match that
 * of the MD5 routines in RSAREF.  Due to this alteration, this
 * code is "derived from the RSA Data Security, Inc. MD5 Message-
 * Digest Algorithm".  (See below.)  Also added argument names
 * to the prototypes.
 */

/*
 ***********************************************************************
 ** Copyright (C) 1990, RSA Data Security, Inc. All rights reserved.  **
 **                                                                   **
 ** License to copy and use this software is granted provided that    **
 ** it is identified as the "RSA Data Security, Inc. MD5 Message-     **
 ** Digest Algorithm" in all material mentioning or referencing this  **
 ** software or this function.                                        **
 **                                                                   **
 ** License is also granted to make and use derivative works          **
 ** provided that such works are identified as "derived from the RSA  **
 ** Data Security, Inc. MD5 Message-Digest Algorithm" in all          **
 ** material mentioning or referencing the derived work.              **
 **                                                                   **
 ** RSA Data Security, Inc. makes no representations concerning       **
 ** either the merchantability of this software or the suitability    **
 ** of this software for any particular purpose.  It is provided "as  **
 ** is" without express or implied warranty of any kind.              **
 **                                                                   **
 ** These notices must be retained in any copies of any part of this  **
 ** documentation and/or software.                                    **
 ***********************************************************************
 */

/* typedef a 32-bit type */
#ifdef __alpha
typedef unsigned int UINT4;
#else
typedef unsigned long int UINT4;
#endif

/* Data structure for MD5 (Message-Digest) computation */
typedef struct
  {
    UINT4 buf[4];        /* scratch buffer */
    UINT4 i[2];            /* number of _bits_ handled mod 2^64 */
    unsigned char in[64];    /* input buffer */
  }

MD5_CTX;

void MD5Init (MD5_CTX * mdContext);
void MD5Update (MD5_CTX * mdContext, unsigned char *bug, unsigned int len);
void MD5Final (unsigned char digest[16], MD5_CTX * mdContext);
void Transform (UINT4 * buf, UINT4 * in);

#endif   /* WIN32 */



/***** hmac_md5 replacement *****/

#ifndef HAVE_HMAC_MD5_H

#define HMAC_MD5_SIZE 16

#ifndef caddr_t
#  define caddr_t unsigned char*
#endif


void hmac_md5 (
    unsigned char*  textr,       /* pointer to data stream */
    int             text_len,    /* length of data stream */
    unsigned char*  key,         /* pointer to authentication key */
    int             key_len,     /* length of authentication key */
    caddr_t         digest       /* caller digest to be filled in */
) ;

#endif // HAVE_HMAC_MD5_H



/***** getopt replacement *****/

#ifdef WIN32


#ifndef _GETOPT_H_
#define _GETOPT_H_ 1

#ifdef __cplusplus
extern          "C" {
#endif

    extern int      getopt(int, char *const *, const char *);
    extern char    *optarg;
    extern int      optind, opterr, optopt, optreset;

#ifdef __cplusplus
}
#endif
#endif

#endif  /* WIN32 */




/***** daemon replacement *****/

#ifndef HAVE_DAEMON
int daemon(int nochdir, int noclose) ;
#endif  /* HAVE_DAEMON */



#ifdef WIN32

struct timezone {
    int tz_minuteswest; /* minutes W of Greenwich */
    int tz_dsttime;     /* type of dst correction */
};

#endif


#endif  /* ! SRC_UTILITIES_H */


