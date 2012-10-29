/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		tcp_clnt.c - A simple TCP client program.
--
--	PROGRAM:			tclnt.exe
--
--	FUNCTIONS:			Winsock 2 API
--
--	DATE:				January 11, 2006
--
--	REVISIONS:			(Date and Description)
--
--						Oct. 1, 2007 (A. Abdulla):
--						
--						Changed the read loop to better handle the 
--						blocking recv call. 
--
--	DESIGNERS:			Aman Abdulla
--
--	PROGRAMMERS:		Aman Abdulla
--
--	NOTES:
--	The program will establish a TCP connection to a user specifed server.
--  The server can be specified using a fully qualified domain name or and
--	IP address. After the connection has been established the user will be
--  prompted for date. The date string is then sent to the server and the
--  response (echo) back from the server is displayed.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <winsock2.h>
#include <errno.h>
//#include <string.h>
//#include <memory.h>

#define SERVER_TCP_PORT			7000	// Default port
#define BUFSIZE					255		// Buffer length

int main (int argc, char **argv)
{
	int n, ns, bytes_to_read;
	int port, err;
	SOCKET sd;
	struct hostent	*hp;
	struct sockaddr_in server;
	char  *host, *bp, rbuf[BUFSIZE], sbuf[BUFSIZE], **pptr;
	WSADATA WSAData;
	WORD wVersionRequested;

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

	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &WSAData );
	if ( err != 0 ) //No usable DLL
	{
		printf ("DLL not found!\n");
		exit(1);
	}

	// Create the socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Cannot create socket");
		exit(1);
	}

	// Initialize and set up the address structure
	memset((char *)&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr, "Unknown server address\n");
		exit(1);
	}

	// Copy the server address
	memcpy((char *)&server.sin_addr, hp->h_addr, hp->h_length);

	// Connecting to the server
	if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		fprintf(stderr, "Can't connect to server\n");
		perror("connect");
		exit(1);
	}
	printf("Connected:    Server Name: %s\n", hp->h_name);
	pptr = hp->h_addr_list;
	printf("\t\tIP Address: %s\n", inet_ntoa(server.sin_addr));
	printf("Transmiting:\n");
	memset((char *)sbuf, 0, sizeof(sbuf));
	gets(sbuf); // get user's text

	// Transmit data through the socket
	ns = send (sd, sbuf, BUFSIZE, 0);
	printf("Receive:\n");
	bp = rbuf;
	bytes_to_read = BUFSIZE;

	// client makes repeated calls to recv until no more data is expected to arrive.
	while ((n = recv (sd, bp, bytes_to_read, 0)) < BUFSIZE)
	{
		bp += n;
		bytes_to_read -= n;
		if (n == 0)
			break;
	}
	printf ("%s\n", rbuf);
	closesocket (sd);
	WSACleanup();
	exit(0);
}
