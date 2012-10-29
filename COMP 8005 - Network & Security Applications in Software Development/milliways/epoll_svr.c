/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		epoll_svr.c -   A simple echo server using the epoll API
--
--	PROGRAM:		epolls
--				gcc -Wall -ggdb -o epolls epoll_svr.c  
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:			February 2, 2008
--
--	REVISIONS:		(Date and Description)
--
--	DESIGNERS:		Design based on various code snippets found on C10K links
--				Modified and improved: Aman Abdulla - February 2008
--
--	PROGRAMMERS:		Aman Abdulla
--
--	NOTES:
--	The program will accept TCP connections from client machines.
-- 	The program will read data from the client socket and simply echo it back.
--	Design is a simple, single-threaded server using non-blocking, edge-triggered
--	I/O to handle simultaneous inbound connections. 
--	Test with accompanying client application: epoll_clnt.c
---------------------------------------------------------------------------------------*/

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define TRUE 		1
#define FALSE 		0
#define EPOLL_QUEUE_LEN	256
#define BUFLEN		80
#define SERVER_PORT	7000

//Globals
int fd_server;

// Function prototypes
static void SystemFatal (const char* message);
static int ClearSocket (int fd);
void close_fd (int);

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
				close(events[i].data.fd);
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
				close (events[i].data.fd);
	    		}
		}
    	}
	close(fd_server);
	exit (EXIT_SUCCESS);
}


static int ClearSocket (int fd) 
{
	int	n, bytes_to_read;
	char	*bp, buf[BUFLEN];

	while (TRUE)
	{
		
		bp = buf;
		bytes_to_read = BUFLEN;
		while ((n = recv (fd, bp, bytes_to_read, 0)) < BUFLEN)
		{
			bp += n;
			bytes_to_read -= n;
		}
		printf ("sending:%s\n", buf);

		send (fd, buf, BUFLEN, 0);
		close (fd);
		return TRUE;
	}
	close(fd);
	return(0);

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
