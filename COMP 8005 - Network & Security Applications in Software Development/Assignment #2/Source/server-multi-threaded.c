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

/**
 * This function will be called by libevent when the client socket is
 * ready for reading.
 */
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
				/* Client disconnected, remove the read event and the
				 * free the client structure. */
				printf("Client disconnected from socket %d.\n", fd);
				thread->client_count--;
				thread->clients[client] = 0;
				close(fd);
			}
			else if (len > 0)
				wlen = write(fd, buf, len);
		}
		
		if (client == MAX_CLIENTS_PER_THREAD -1)
			client = 0;
		else
			client++;
		
		/* exit the thread if no clients */
		if (thread->client_count == 0) {
			break;
		}
		usleep(100);
	}
	return NULL;
}

/**
 * This function will be called by libevent when there is a connection
 * ready to be accepted.
 */
void on_accept(int fd)
{
	int client_fd, thread_num, client_num;
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
	
	if (threads[thread_num].client_count == 0) {
		printf("Creating thread %d\n", thread_num);
		pthread_create(&threads[thread_num].thread_id,
					   NULL, &servlet, (void *)&threads[thread_num]);
	}
	
	threads[thread_num].client_count++;
	
	printf("Accepted connection from %s on socket %d\n",
		   inet_ntoa(client_addr.sin_addr), client_fd);
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

int main(int argc, char **argv)
{
	int listen_fd, i, k;
	struct sockaddr_in listen_addr;
	int reuseaddr_on = 1;
	
	/* Create our listening socket. This is largely boiler plate
	 * code that I'll abstract away in the future. */
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
		err(1, "listen failed");
	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on, 
				   sizeof(reuseaddr_on)) == -1)
		err(1, "setsockopt failed");
	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = INADDR_ANY;
	listen_addr.sin_port = htons(SERVER_PORT);
	if (bind(listen_fd, (struct sockaddr *)&listen_addr,
			 sizeof(listen_addr)) < 0)
		err(1, "bind failed");
	if (listen(listen_fd, 5) < 0)
		err(1, "listen failed");
	
	/* initialize thread struct */
	for (i = 0; i < MAX_THREADS; i++) {
		threads[i].client_count = 0;
		for (k = 0; k < MAX_CLIENTS_PER_THREAD; k++)
			threads[i].clients[k] = 0;
	}
	
	while (1)
		on_accept(listen_fd);
	
	return 0;
}