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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/param.h>
#include <netdb.h>

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

#define MAX_CONNECT_ERRORS	10		/* times to retry connecting */
#define USLEEP_TIME			100		/* backoff time in µseconds */

/* boolean values */
#define TRUE	1
#define FALSE	0

/* error codes */
#define OPTS_HELP			0
#define OPTS_ERROR			1
#define ERROR_RESOLVE		2
#define ERROR_CONN_ERR		3
#define	ERROR_CONN_REFUSED	4

/* option defaults */
#define TV_TEST		0
#define TV_REPEAT	10
#define TV_LENGTH	32
#define TV_SERVER	"localhost"
#define TV_PORT		9000
#define TV_FILE		"./client_stats.csv"

#define MAX_IOSIZE	81920

/* ASCII options */
#define MIN_CHAR	32
#define MAX_CHAR	126

typedef struct 
{
	int connect_test;	/* enable connection testing mode */
	int repeat;			/* number of times send test string
						 * or run connection test */
	int	string_length;	/* length of string to send */
	char *server;		/* server host or address */
	int port;			/* server port */
	char *string_test;	/* the test string being sent */
	char *output_file;	/* where to save statistics */
} TestVars;

TestVars test_vars;

int server_connect(struct in_addr const *paddr, int port);
int init_test(void);
void terminate(int sig);
void print_usage(char *command, int err);
void print_settings(int argc);

#endif
