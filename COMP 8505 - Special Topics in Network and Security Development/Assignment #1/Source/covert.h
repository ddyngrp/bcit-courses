/*-----------------------------------------------------------------------------
 * covert.h - Covert communication over TCP/IP
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <getopt.h>

#define __FAVOR_BSD		/* use BSD-style headers */
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* error codes */
#define	ERROR_NONE		0
#define ERROR_GENERAL	-1
#define ERROR_NOTROOT	-3
#define	ERROR_FILE		-4
#define ERROR_SOCKET	-5
#define ERROR_SEND		-6
#define ERROR_READ		-7
#define OPTIONS_ERROR	-8
#define OPTIONS_HELP	-9

/* misc definitions */
#define USER_ROOT	0
#define	MODE_SERVER	1
#define	MODE_CLIENT	2
#define DELAY_USEC	10000
#define	BUFFER_SIZE	4	/* 32 bits */
#define BUFFER_RECV	128

/* true false */
#define TRUE	1
#define FALSE	0

struct conn_info {
	int mode_server;
	char *dest_ip;
	unsigned int dest_port;
	unsigned int th_win;
	char *file_name;
} conn_info;

void print_settings(char *);
void print_usage(char *, int);
int parse_options(int, const char **);
int file_io(char *, char *recv_buff);
void packet_forge(unsigned int);
void packet_decode();
unsigned short in_cksum(unsigned short *, int);
unsigned short in_cksum_tcp(int, int, unsigned short *, int);
char *ip_to_string(struct in_addr);
