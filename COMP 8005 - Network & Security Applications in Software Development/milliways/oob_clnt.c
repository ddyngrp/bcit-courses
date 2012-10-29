/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		tcp_clnt.c - A simple TCP client program.
--
--	PROGRAM:		tclnt.exe
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
--	The program will establish a TCP connection to a user specifed server.
-- 	The server can be specified using a fully qualified domain name or and
--	IP address. After the connection has been established the user will be
-- 	prompted for date. The string is then sent to the server and the
-- 	response (echo) back from the server is displayed.
--	A single character is also sent as urgent data.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>

#define SERVER_TCP_PORT		7000	// Default port
#define BUFLEN			256  // Buffer length

int main (int argc, char **argv)
{
	int n, bytes_to_read;
	int sd, port;
	struct hostent	*hp;
	struct sockaddr_in server;
	char  *host, *bp, rbuf[BUFLEN], sbuf[BUFLEN], **pptr;
	char str[16];

	switch(argc)
	{
		case 2:
			host =	argv[1];	// Host name
			port =	SERVER_TCP_PORT;
		break;
		case 3:
			host =	argv[1];
			port =	atoi(argv[2]);	// User specified port
		break;
		default:
			fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
			exit(1);
	}

	// Create the socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Cannot create socket");
		exit(1);
	}
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr, "Unknown server address\n");
		exit(1);
	}
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	// Connecting to the server
	if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		fprintf(stderr, "Can't connect to server\n");
		perror("connect");
		exit(1);
	}
	printf("Connected:    Server Name: %s\n", hp->h_name);
	pptr = hp->h_addr_list;
	printf("\t\tIP Address: %s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)));
	printf("Transmit:\n");
	fgets(sbuf, BUFLEN, stdin); // get user's text

	// Transmit OOB data through the socket
	send(sd, "9", 1, MSG_OOB); 
	
	// Transmit client input
	send (sd, sbuf, BUFLEN, 0);
	send (sd, "\n", 1, 0);
	
	send(sd, "9", 1, MSG_OOB); 
	printf("Receive:\n");
	bp = rbuf;
	bytes_to_read = BUFLEN;

	// client makes repeated calls to recv until no more data is expected to arrive.
	while ((n = recv (sd, bp, bytes_to_read, 0)) > 0)
	{
		bp += n;
		bytes_to_read -= n;
		if ((strncmp(bp, "\n", 0)) == 0)
		{
			break;
		}
	}
	printf ("%s\n", rbuf);
	close (sd);
	return (0);
}
