/*****************************************************************************

    File: "constants.h"

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
//   JBW | Oct.8  2003 | Initial version
//   JBW | Jul 29 2004 | Changed DEFAULT_PORT from 1033 to 1001
// --------------------------------------------------------------------------



#ifndef _DOORMAN_CONSTANTS_H
#define _DOORMAN_CONSTANTS_H 1


#define MD5_HEXLENGTH 32

#define MAX_SECRET_LENGTH 64
#define MAX_GROUPNAME_LENGTH 32

#define BUFFERLEN 4096
#define SNAPLEN 256

#define DEFAULT_PORT 1001
#define DEFAULT_WAITFOR 10
#define DEFAULT_CONNECTION_DELAY_1 500000
#define DEFAULT_CONNECTION_DELAY_2 5
#define DEFAULT_FAIL_LIMIT 3
#define DEFAULT_FAIL_DELAY 60
#define DEFAULT_GUESTLIST "/etc/dd_guestlist"
#define DEFAULT_LOGFILE "/var/log/doorman"
#define DEFAULT_PIDFILE "/var/run/doorman.pid"
#define DEFAULT_UNIXCLIENT_CONFIGFILE ".knockcf"
#define DEFAULT_WINDOWSCLIENT_CONFIGFILE "C:\\knock.cfg"

#define DOORMAN_URL "http://doorman.sourceforge.net"

#undef TRUE
#undef FALSE
#define TRUE 1
#define FALSE 0

#endif /* _DOORMAN_CONSTANTS_H */


