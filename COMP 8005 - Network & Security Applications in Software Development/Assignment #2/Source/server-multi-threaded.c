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

void *servlet(void *ptr)
{
	Thread *thread = (Thread *)ptr;
	u_char buf[MAX_IOSIZE];
	int fd, client = 0, rlen = 0, wlen;
	
	while (1) {
		fd = thread->client_fd[client];
		
		if (fd != 0) {
			rlen = read(fd, buf, sizeof(buf));
			
			if (rlen == 0) {
				printf("Client disconnected from socket %d.\n", fd);
				thread->client_count--;
				thread->client_fd[client] = 0;
				close(fd);
			}
			else if (rlen > 0) {
				while ((wlen = write(fd, buf, rlen)) < 0)
					warn("write");
				
				/* update client info */
				cli_stats[thread->stats_pos[client]].requests++;

				if (wlen > 0)
					cli_stats[thread->stats_pos[client]].sent_data += wlen;
			}
		}
		
		if (client == MAX_CLIENTS_PER_THREAD -1)
			client = 0;
		else
			client++;
		
		/* exit the thread if no clients */
		if (thread->client_count == 0) {
			thread->thread_id = 0;
			printf("Terminating thread %d\n", thread->current_thread);
			break;
		}
	}
	return NULL;
}

void on_accept(int fd)
{
	int client_fd, thread_num, client_num, sock_buf_size;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	
	/* accept the new connection. */
	client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd == -1) {
		warn("accept failed");
		return;
	}
	
	/* set to non-blocking */
	/* if (fcntl (client_fd, F_SETFL, O_NONBLOCK | fcntl (client_fd, F_GETFL, 0)) == -1)
		err(1, "fnctl"); */
	
	/* increase the buffer size */
	sock_buf_size = MAX_IOSIZE * 2;
	setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &sock_buf_size, sizeof(sock_buf_size));
	setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &sock_buf_size, sizeof(sock_buf_size));
	
	
	/* setup thread conditions */
	if ((thread_num = first_free_thread()) == -1)
		perror("No more free threads.");
	
	if ((client_num = first_free_client(thread_num)) == -1)
		perror("Thread has no room for more clients.");
	
	threads[thread_num].current_thread = thread_num;
	threads[thread_num].client_fd[client_num] = client_fd;
	threads[thread_num].stats_pos[client_num] = cli_pos;
	
	/* add client info */
	memcpy(cli_stats[cli_pos].address,
		   inet_ntoa(client_addr.sin_addr),
		   strlen(inet_ntoa(client_addr.sin_addr)));
	cli_stats[cli_pos].port = client_addr.sin_port;
	cli_stats[cli_pos].requests = 0;
	cli_stats[cli_pos].sent_data = 0;
	cli_pos++;
	
	/* create a new thread if needed */
	if (threads[thread_num].thread_id == 0) {
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
		if (threads[thread_num].client_fd[i] == 0)
			return i;
	
	return -1;
}

void terminate(int sig)
{
	FILE *file;
	int i, k;

	/* kill all threads & terminate connections */
	for (i = 0; i < MAX_THREADS; i++) {
		for (k = 0; k < MAX_CLIENTS_PER_THREAD; k++) {
			if (threads[i].client_fd[k] != 0)
				close(threads[i].client_fd[k]);
		}
		threads[i].client_count = 0;
	}

	/* write data to file */
	file = fopen(STATS_FILE, "w");
	if (file == NULL)
		err(1, "fopen failed");
	
	if (cli_pos == 0) {
		fprintf(file, "%s", "No data stored.\n");
	}

	for (i = 0; i < cli_pos; i++) {
		fprintf(file, "%s, %d, %lu, %lu\n", cli_stats[i].address, cli_stats[i].port, 
				cli_stats[i].requests, cli_stats[i].sent_data);
	}
	
	fclose(file);
	
	printf("\nStatistics written to %s, program terminated.\n", STATS_FILE);
	
	exit(0);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in listen_addr;
	int listen_fd, i, k, reuseaddr_on = 1;
	
	/* cleanup and write data when CTRL+C is pressed */
	(void)signal(SIGINT, terminate);
	
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
		threads[i].thread_id = 0;
		threads[i].current_thread = 0;
		threads[i].client_count = 0;
		for (k = 0; k < MAX_CLIENTS_PER_THREAD; k++) {
			threads[i].client_fd[k] = 0;
		}
	}
	
	/* accept is blocking, so we loop forever */
	while (1)
		on_accept(listen_fd);
	
	return 0;
}