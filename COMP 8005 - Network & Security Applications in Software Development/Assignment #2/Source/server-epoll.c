/*-----------------------------------------------------------------------------
 * server-epoll.c
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * server-epoll.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * server-epoll.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "server-epoll.h"

int get_local_Port(int socket_fd)
{
	struct sockaddr_in addr;
	socklen_t addr_len = sizeof(addr);
	
	/* get the local port */
	if (getsockname(socket_fd, (struct sockaddr *)&addr, &addr_len) == ERROR)
		err(1, "getsockname");
	
	return addr.sin_port;
}

unsigned long time_usec(void)
{
	/* for time in µsec */
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL) == ERROR)
		err(1, "gettimeofday");
	
	return tv.tv_usec + (tv.tv_sec * 1000000L);
}

int set_nonblocking(int socket_fd)
{
	int flags;
	
	flags = fcntl(socket_fd, F_GETFL);
	if (flags < 0)
		return flags;
	
	flags |= O_NONBLOCK;
	if (fcntl(socket_fd, F_SETFL, flags) < 0)
		return ERROR;
	
	return ERROR_NONE;
}

int main (int argc, char* argv[]) 
{
	int i, arg; 
	int num_fds, fd_new, epoll_fd;
	static struct epoll_event events[EPOLL_QUEUE_LEN], event;
	int port = SERVER_PORT;
	struct sockaddr_in addr, remote_addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	struct sigaction act;
	
	// set up the signal handler to close the server socket when CTRL-c is received
	act.sa_handler = close_fd;
	act.sa_flags = 0;
	if ((sigemptyset (&act.sa_mask) == -1 || sigaction (SIGINT, &act, NULL) == -1))
	{
		perror ("Failed to set SIGINT handler");
		exit (EXIT_FAILURE);
	}
	
	// Create the listening socket
	fd_server = socket (AF_INET, SOCK_STREAM, 0);
	if (fd_server == -1) 
		SystemFatal("socket");
	
	// set SO_REUSEADDR so port can be resused imemediately after exit, i.e., after CTRL-c
	arg = 1;
	if (setsockopt (fd_server, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1) 
		SystemFatal("setsockopt");
	
	// Make the server listening socket non-blocking
	if (fcntl (fd_server, F_SETFL, O_NONBLOCK | fcntl (fd_server, F_GETFL, 0)) == -1) 
		SystemFatal("fcntl");
	
	// Bind to the specified listening port
	memset (&addr, 0, sizeof (struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	if (bind (fd_server, (struct sockaddr*) &addr, sizeof(addr)) == -1) 
		SystemFatal("bind");
	
	// Listen for fd_news; SOMAXCONN is 128 by default
	if (listen (fd_server, SOMAXCONN) == -1) 
		SystemFatal("listen");
	
	// Create the epoll file descriptor
	epoll_fd = epoll_create(EPOLL_QUEUE_LEN);
	if (epoll_fd == -1) 
		SystemFatal("epoll_create");
	
	// Add the server socket to the epoll event loop
	event.events = EPOLLIN | EPOLLERR | EPOLLHUP | EPOLLET;
	event.data.fd = fd_server;
	if (epoll_ctl (epoll_fd, EPOLL_CTL_ADD, fd_server, &event) == -1) 
		SystemFatal("epoll_ctl");
	
	// Execute the epoll event loop
	while (TRUE) 
	{
		//struct epoll_event events[MAX_EVENTS];
		num_fds = epoll_wait (epoll_fd, events, EPOLL_QUEUE_LEN, -1);
		if (num_fds < 0) 
			SystemFatal ("Error in epoll_wait!");
		
		for (i = 0; i < num_fds; i++) 
		{
			// Case 1: Error condition
			if (events[i].events & (EPOLLHUP | EPOLLERR)) 
			{
				fputs("epoll: EPOLLERR", stderr);
				//close(events[i].data.fd);
				continue;
			}
			assert (events[i].events & EPOLLIN);
			
			// Case 2: Server is receiving a connection request
			if (events[i].data.fd == fd_server) 
			{
				//socklen_t addr_size = sizeof(remote_addr);
				fd_new = accept (fd_server, (struct sockaddr*) &remote_addr, &addr_size);
				if (fd_new == -1) 
				{
					if (errno != EAGAIN && errno != EWOULDBLOCK) 
					{
						perror("accept");
					}
					continue;
				}
				
				// Make the fd_new non-blocking
				if (fcntl (fd_new, F_SETFL, O_NONBLOCK | fcntl(fd_new, F_GETFL, 0)) == -1) 
					SystemFatal("fcntl");
				
				// Add the new socket descriptor to the epoll loop
				event.data.fd = fd_new;
				if (epoll_ctl (epoll_fd, EPOLL_CTL_ADD, fd_new, &event) == -1) 
					SystemFatal ("epoll_ctl");
				
				printf(" Remote Address:  %s\n", inet_ntoa(remote_addr.sin_addr));
				continue;
			}
			
			// Case 3: One of the sockets has read data
			if (!ClearSocket(events[i].data.fd)) 
			{
				// epoll will remove the fd from its set
				// automatically when the fd is closed
				//close (events[i].data.fd);
			}
		}
	}
	close(fd_server);
	exit (EXIT_SUCCESS);
}


static int ClearSocket (int fd) 
{
	int	n, bytes_to_read;
	char	*bp, buf[BUFLEN * 2];
	
	bp = buf;
	bytes_to_read = BUFLEN;
	n = recv (fd, bp, bytes_to_read, 0);
	
	if (send (fd, buf, strlen(buf), 0) == 0) {
		close(fd);
	}

	return TRUE;
}

// Prints the error stored in errno and aborts the program.
static void SystemFatal(const char* message) 
{
    perror (message);
    exit (EXIT_FAILURE);
}

// close fd
void close_fd (int signo)
{
	close(fd_server);
	exit (EXIT_SUCCESS);
}