/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		tcp_svr.c -   A simple echo server using TCP
--
--	PROGRAM:		tsvr.exe
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:			January 23, 2001
--
--	REVISIONS:		(Date and Description)
--
--				February 10, 2006
--				Added OOB code
--
--	DESIGNERS:		Aman Abdulla
--
--	PROGRAMMERS:		Aman Abdulla
--
--	NOTES:
--	The program will accept TCP connections from client machines.
-- 	The program will read data from the client socket and simply echo it back.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>

#define SERVER_TCP_PORT 7000		// Default port
#define BUFLEN	256			//Buffer length
#define TRUE	1

void sig_urg(int);	// Urgent signal handler
int new_sd;

int main (int argc, char **argv)
{
	int	n, bytes_to_read;
	int	sd, client_len, port;
	struct	sockaddr_in server, client;
	char	*bp, buf[BUFLEN];

	switch(argc)
	{
		case 1:
			port = SERVER_TCP_PORT;	// Use the default port
		break;
		case 2:
			port = atoi(argv[1]);	// Get user specified port
		break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
	}

	// Create a stream socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

	// Bind an address to the socket
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't bind name to socket");
		exit(1);
	}

	// associate the signal handler with the SIGURG signal
	signal(SIGURG, sig_urg); 

	// Listen for connections
	// queue up to 5 connect requests
	listen(sd, 5);

	while (TRUE)
	{
		client_len= sizeof(client);
		if ((new_sd = accept (sd, (struct sockaddr *)&client, &client_len)) == -1)
		{
			fprintf(stderr, "Can't accept client\n");
			exit(1);
		}
		
		fcntl(new_sd, F_SETOWN, getpid());	//set PID to recieve SIGURG to current process
		printf(" Remote Address:  %s\n", inet_ntoa(client.sin_addr));
		bp = buf;
		bytes_to_read = BUFLEN;
		while ((n = recv (new_sd, bp, bytes_to_read, 0)) > 0)
		{
			
			bp += n;
			bytes_to_read -= n;
			if ((strncmp(bp, "\n", 1)) == 0)
			{
				break;
			}
		}
		send (new_sd, buf, BUFLEN, 0);
		close (new_sd);
	}
	close(sd);
	return(0);
}

void sig_urg(int signo)
{
	int n;
	char buff[100];

	printf("SIGURG received\n");
	n = recv(new_sd, buff, sizeof(buff) - 1, MSG_OOB);
	buff[n] = 0;
	printf("read %d OOB byte: %c\n", n, buff[0]);
}
