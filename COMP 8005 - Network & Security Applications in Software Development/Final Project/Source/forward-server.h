/*-----------------------------------------------------------------------------
 * forward-server.h
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * forward-server.h is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * forward-server.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#ifndef FORWARD_SERVER_H
#define FORWARD_SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>

#include <getopt.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h> 
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <stddef.h>

/* using libev instead of libevent */
#ifdef __linux__
	#include <libev/ev.h> /* header location on linux */
#elif __APPLE__
	#include <ev.h> /* header location on OS X */
#endif

/* defaults */
#define IO_BUFFER	65536
#define TRUE		1
#define FALSE		0
#define FILENAME	"./forward.conf"
#define PID_FILE	"/tmp/forward.pid"

/* error codes */
#define ERROR_NONE	0
#define ERROR		-1

struct client {
	int fd_in;		/* inbound socket */
	int fd_out;		/* outbound socket */
	ev_io ev_read;
	ev_io ev_read_out;
};

/* creating a dynamic array of sorts */
typedef struct {
	int local_port;
	char *remote_ip;
	int remote_port;
	ev_io ev_accept;
} FORWARD;

int setnonblock(int);
static void read_client_cb(struct ev_loop *, struct ev_io *, int);
static void read_remote_cb(struct ev_loop *, struct ev_io *, int);
static void accept_cb(struct ev_loop *, struct ev_io *, int);
struct sockaddr_in peer_info(int);
struct sockaddr_in local_info(int);
void read_config(void);
void forward_add(FORWARD);
void print_forward_info(void);
void terminate(int);
void pid_file(void);

FORWARD *forward_info = NULL;
int num_elements = 0;	/* elements in array */
int num_allocated = 0;	/* size of array */
ev_io ev_accept;

#endif