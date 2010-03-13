/*-----------------------------------------------------------------------------
 * client.h
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * client.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * client.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include <sys/socket.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/epoll.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <time.h>
#include <signal.h>
#include <getopt.h>

#include <event.h>
#include <evutil.h>

#include <pthread.h>

#define MAX_CONNECT_ERRORS	10		/* times to retry connecting */
#define USLEEP_TIME			100		/* backoff time in µseconds */

/* boolean values */
#define TRUE	1
#define FALSE	0

/* error codes */
#define	ERROR			-1
#define ERROR_NONE		0
#define ERROR_OPTS		1

/* option defaults */
#define TV_TEST		0
#define TV_REPEAT	10
#define TV_CONNS	10
#define TV_LENGTH	32
#define TV_SERVER	"localhost"
#define TV_PORT		9000
#define TV_FILE		"./client_stats.csv"

#define MAX_IOSIZE	65536	/* maximum packet size to send */
#define MAX_CONNS	50000	/* maximum number of connections */
#define EVENT_TIMER	10000	/* event timer in µseconds */

/* ASCII options */
#define MIN_CHAR	32
#define MAX_CHAR	126

typedef struct 
{
	int connect_test;	/* enable connection testing mode */
	int repeat;			/* number of times send test string
						 * or run connection test */
	int conns;			/* number of simultaneous connections */
	int	string_length;	/* length of string to send */
	char *server;		/* server host or address */
	int port;			/* server port */
	char *string_test;	/* the test string being sent */
	char *output_file;	/* where to save statistics */
} TestVars;

typedef struct
{
	int	fd_server;				/* socket descriptor for the server */
	unsigned long time;			/* current system time in µsec */
	int local_port;				/* local port used to connect to server */
	int requests;				/* total number of requests sent */
	unsigned long sent_data;	/* total amount of data sent */
	int delay;					/* delay in server response */
} ServerStats;

TestVars test_vars;
ServerStats srv_stats[MAX_CONNS];

void *ev_timer(void *ptr);
static void timeout_cb(int fd, short event, void *arg);
int client_init(void);
int client_start(void);
int get_socket(int connection);
unsigned long time_usec(void);
int set_nonblocking(int socket_fd);
int write_stats(void);
void print_usage(char *command, int err);
void print_settings(int argc);

#endif
