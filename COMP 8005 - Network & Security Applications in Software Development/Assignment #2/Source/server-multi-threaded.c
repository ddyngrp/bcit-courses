/*-----------------------------------------------------------------------------
 * server-multi-threaded.c
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * server-multi-threaded.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * server-multi-threaded.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "server-multi-threaded.h"
#include "linked-list.h"

void *servlet(void *ptr)
{
	Thread *thread = (Thread *)ptr;
	u_char buf[4096];
	int fd, client = 0, len, wlen;
	
	while (1) {
		fd = thread->clients[client];
		
		if (fd != 0) {
			len = read(fd, buf, sizeof(buf));
			if (len == 0) {
				printf("Client disconnected from socket %d.\n", fd);
				thread->client_count--;
				thread->clients[client] = 0;
				close(fd);
			}
			else if (len > 0) {
				wlen = write(fd, buf, len);
				
				/* update statistics */
			}
		}
		
		if (client == MAX_CLIENTS_PER_THREAD -1)
			client = 0;
		else
			client++;
		
		/* exit the thread if no clients */
		if (thread->client_count == 0) {
			break;
		}
		usleep(1);
	}
	return NULL;
}

void on_accept(int fd)
{
	int client_fd, thread_num, client_num, i;
	struct sockaddr_in client_addr;
	
	socklen_t client_len = sizeof(client_addr);
	
	/* accept the new connection. */
	client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd == -1) {
		warn("accept failed");
		return;
	}
	
	/* set to non-blocking */
	fcntl(client_fd, F_SETFL, O_NONBLOCK);
	
	/* setup thread conditions */
	if ((thread_num = first_free_thread()) == -1)
		perror("No more free threads.");
	
	if ((client_num = first_free_client(thread_num)) == -1)
		perror("Thread has no room for more clients.");
	
	threads[thread_num].thread_num = thread_num;
	threads[thread_num].clients[client_num] = client_fd;
	
	/* store initial client data */
	
	/* prefork THREADS_PREFORK threads at a time */
	if (threads[thread_num].thread_id == 0) {
		for (i = thread_num; i < thread_num + THREADS_PREFORK; i++) {
			printf("Creating thread %d\n", i);
			pthread_create(&threads[i].thread_id,
						   NULL, &servlet, (void *)&threads[i]);
		}
	}
	
	threads[thread_num].client_count++;
	
	printf("Accepted connection from %s on socket %d\n",
		   inet_ntoa(client_addr.sin_addr), client_fd);

	fflush(stdout);
}

int first_free_thread()
{
	int i;
	
	for (i = 0; i < MAX_THREADS; i++)
		if (threads[i].client_count < MAX_CLIENTS_PER_THREAD)
			return i;
	
	return -1;
}

int first_free_client(int thread_num)
{
	int i;
	
	for (i = 0; i < MAX_CLIENTS_PER_THREAD; i++)
		if (threads[thread_num].clients[i] == 0)
			return i;
	
	return -1;
}

void terminate(int sig)
{
	int i, k;
	char *fileName = "./server-data.csv";

	/* kill all threads & terminate connections */
	for (i = 0; i < MAX_THREADS; i++) {
		for (k = 0; k < MAX_CLIENTS_PER_THREAD; k++) {
			if (threads[i].clients[k] != 0)
				close(threads[i].clients[k]);
		}
		threads[i].client_count = 0;
	}
	
	/* write collected data to file */
	list_write(conn_track, fileName);
	
	printf("\nData written to %s, program terminated.\n", fileName);
	
	exit(0);
}

int main(int argc, char **argv)
{
	struct sockaddr_in listen_addr;
	int listen_fd, i, k, reuseaddr_on = 1;
	
	/* cleanup and write data CTRL+C is pressed */
	(void)signal(SIGINT, terminate);
	
	/* set the initial list to empty */
	conn_track = NULL;
	
	/* create listening socket */
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
		err(1, "listen failed");
	
	/* reuse the socket address */
	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on, 
				   sizeof(reuseaddr_on)) == -1)
		err(1, "setsockopt failed");
	
	/* set to listen on all addresses */
	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = INADDR_ANY;
	listen_addr.sin_port = htons(SERVER_PORT);
	
	/* bind the socket */
	if (bind(listen_fd, (struct sockaddr *)&listen_addr,
			 sizeof(listen_addr)) < 0)
		err(1, "bind failed");
	
	/* listen for new connections */
	if (listen(listen_fd, 5) < 0)
		err(1, "listen failed");
	
	/* initialize thread struct */
	for (i = 0; i < MAX_THREADS; i++) {
		threads[i].client_count = 0;
		threads[i].thread_id = 0;
		for (k = 0; k < MAX_CLIENTS_PER_THREAD; k++) {
			threads[i].clients[k] = 0;
			threads[i].client_port[k] = 0;
		}
	}
	
	/* accept is blocking, so we loop forever */
	while (1)
		on_accept(listen_fd);
	
	return 0;
}