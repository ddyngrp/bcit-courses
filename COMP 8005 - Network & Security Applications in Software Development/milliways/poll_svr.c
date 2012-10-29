/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		poll_svr.c -   A simple multiplexed echo server using TCP
--
--	PROGRAM:			poll.exe
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:				February 18, 2001
--
--	REVISIONS:			(Date and Description)
--
--	DESIGNERS:			Based on Richard Stevens Example, p165-166
--					Modified & redesigned: Aman Abdulla: February 16, 2001
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--	The program will accept TCP connections from multiple client machines.
-- 	The program will read data from each client socket and simply echo it back.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <limits.h>		// for OPEN_MAX

#define SERVER_TCP_PORT 7000	// Default port
#define BUFLEN	256			//Buffer length
#define TRUE	1
#define LISTENQ	5
#define MAXLINE 4096

int main (int argc, char **argv)
{
	int i, maxi, nready, bytes_to_read;
	int listen_sd, new_sd, sockfd, client_len, port, maxfd, client[FD_SETSIZE];
	struct sockaddr_in server, client_addr;
	char *bp, buf[BUFLEN];
  	ssize_t n;
  	socklen_t clilen;
  	struct pollfd client[OPEN_MAX];

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
	if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

	// Bind an address to the socket
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

	if (bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't bind name to socket");
		exit(1);
	}

	// Listen for connections
	// queue up to LISTENQ connect requests
	listen(listen_sd, LISTENQ);

	client[0].fd = listen_sd;	// initialize
   client[0].events =  POLLRDNORM;

	for (i = 0; i < OPEN_MAX; i++)
           	client[i].fd = -1;             // -1 indicates available entry
	maxi = 0;	// max index into client[] array

	while (TRUE)
	{
   	nready = poll(client, maxi + 1, INFTIM);

      	if (client[0].revents & POLLRDNORM)   // new client connection
         {
				client_len = sizeof(client_addr);
				if ((new_sd = accept(listen_sd, (struct sockaddr *) &client_addr, &client_len)) == -1)
				{
					fprintf(stderr, "Can't accept client\n");
					exit(1);
				}
            printf(" Remote Address:  %s\n", inet_ntoa(client_addr.sin_addr));

            for (i = 0; i < OPEN_MAX; i++)
				if (client[i].fd < 0)
            {
					client[i].fd = new_sd;	// save descriptor
					break;
            }
				if (i == OPEN_MAX)
     			{
					printf ("Too many clients\n");
            	exit(1);
            }

				client[i].events = POLLPDNORM;

				if (i > maxi)
					maxi = i;	// new max index in client[] array

				if (--nready <= 0)
					continue;	// no more readable descriptors
     		 }

			for (i = 1; i <= maxi; i++)		// check all clients for data
     	   {
         	if ((sockfd = client[i].fd) < 0)
					continue;

			if (client[i].revents & (POLLPDNOPM | POLLFRR))
         {
  				bp = buf;
				bytes_to_read = BUFLEN;
				while ((n = read(sockfd, bp, bytes_to_read)) > 0)
				{
					bp += n;
					bytes_to_read -= n;
				}
				write(sockfd, buf, BUFLEN);   // echo to client

				if (errno == ECONNRESET) // connection closed by client
            {
					printf(" Remote Address:  %s reset connection\n", inet_ntoa(client_addr.sin_addr));
					close(sockfd);
					client[i].fd = -1;
         	}
            else if (n == 0)
            {
               printf(" Remote Address:  %s closed connection\n", inet_ntoa(client_addr.sin_addr));
					close(sockfd);
					client[i].fd = -1;
            }

				if (--nready <= 0)
            					break;        // no more readable descriptors
			}
      }
   }
	return(0);
}

