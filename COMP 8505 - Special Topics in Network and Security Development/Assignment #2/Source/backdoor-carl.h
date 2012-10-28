/*-----------------------------------------------------------------------------
 * backdoor-carl.h - Linux backdoor client (remote server control)
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

#ifndef BACKDOOR_CARL_H
#define BACKDOOR_CARL_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include <getopt.h>
#include <pcap.h>

#define __FAVOR_BSD	/* use BSD-style headers */
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* error codes */
#define ERROR_NONE		 0
#define ERROR_GENERAL	-1
#define ERROR_OPTS		-3
#define	ERROR_OPTS_HELP	-4

/* defaults */
#define	TRUE			1
#define FALSE			0
#define USER_ROOT		0

struct cli_vars {
	char *server_ip;
	char *command;
} cli_vars;

/* function prototypes */
void print_settings(char *);
void print_usage(char *, int);
int parse_options(int, char **);

#endif
