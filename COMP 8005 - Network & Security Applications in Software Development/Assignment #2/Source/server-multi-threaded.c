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
	LLIST **tmp;
	
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
			else if (len > 0) {
				wlen = write(fd, buf, len);
				
				/* update the requests and data for the client & lock access */
				pthread_mutex_lock(&linked_list_mutex);
				tmp = list_search(&conn_track, thread->unique_id[client]);
				(*tmp)->srv_req++;
				(*tmp)->srv_data += wlen;
				pthread_mutex_unlock(&linked_list_mutex);
				list_print(conn_track);
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
	
	/* assign a unique ID for each new client & create list entry */
	threads[thread_num].unique_id[client_num] = random_id();
	
	/* lock access to list */
	pthread_mutex_lock(&linked_list_mutex);
	list_add(&conn_track, threads[thread_num].unique_id[client_num]);
	memcpy(conn_track->hostname, inet_ntoa(client_addr.sin_addr),
		   strlen(inet_ntoa(client_addr.sin_addr)));
	conn_track->srv_req = 0;
	conn_track->srv_data = 0;
	pthread_mutex_unlock(&linked_list_mutex);
	
	if (threads[thread_num].client_count == 0) {
		printf("Creating thread %d\n", thread_num);
		pthread_create(&threads[thread_num].thread_id,
					   NULL, &servlet, (void *)&threads[thread_num]);
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

unsigned int random_id()
{
	/* Simple "srand()" seed: just use "time()" */
	unsigned int iseed = (unsigned int)time(NULL);
	srand (iseed);
	
	return rand();
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
		for (k = 0; k < MAX_CLIENTS_PER_THREAD; k++) {
			threads[i].clients[k] = 0;
			threads[i].unique_id[k] = 0;
		}
	}
	
	/* accept is blocking, so we loop forever */
	while (1)
		on_accept(listen_fd);
	
	return 0;
}