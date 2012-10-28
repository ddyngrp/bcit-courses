/*-----------------------------------------------------------------------------
 * server-multi-threaded.h
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * server-multi-threaded.h is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 * 
 * server-multi-threaded.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#ifndef SERVER_MULTI_THREADED_H
#define SERVER_MULTI_THREADED_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
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

#include <pthread.h>

#define SERVER_PORT				9000	/* port number to listen on */
#define MAX_THREADS				300
#define MAX_CLIENTS_PER_THREAD	200
#define MAX_IOSIZE				65536
#define USLEEP_TIME				1

#define STATS_FILE	"./server_stats.csv"

typedef struct 
{
	pthread_t thread_id;					/* the serving thread's id */
	int current_thread;						/* current thread number */
	int client_count;						/* number of clients being served */
	int client_fd[MAX_CLIENTS_PER_THREAD];	/* socket descriptors for each client */
	int stats_pos[MAX_CLIENTS_PER_THREAD];	/* where to locate the client info */
} Thread;

typedef struct
{
	char address[17];			/* client's address */
	int port;					/* remote port for client */
	unsigned long requests;		/* total requests generated */
	unsigned long sent_data;	/* total data sent to */
} ClientStats;

Thread threads[MAX_THREADS];
ClientStats cli_stats[MAX_THREADS * MAX_CLIENTS_PER_THREAD];

static int cli_pos = 0;

void *servlet(void *ptr);
void on_accept(int fd);
int first_free_thread(void);
int first_free_client(int thread_num);
void terminate(int sig);
#endif
