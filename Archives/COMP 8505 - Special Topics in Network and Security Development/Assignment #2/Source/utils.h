/*-----------------------------------------------------------------------------
 * utils.h - Linux backdoor utilities
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <err.h>

#define __FAVOR_BSD	/* use BSD-style headers */
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* error codes */
#define ERROR_NONE		 0
#define ERROR_SOCKET	-1
#define ERROR_SEND		-2
#define ERROR_NOTROOT	-3

/* function prototypes */
unsigned short in_cksum(unsigned short *, int);
unsigned short in_cksum_tcp(int, int, unsigned short *, int);
char *xor(char *);
void packet_forge(char *, char *, char *);
int set_root(void);

#endif
