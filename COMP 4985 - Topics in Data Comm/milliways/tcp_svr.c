/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		tcp_svr.c -   A simple echo server using TCP
--
--	PROGRAM:			tsvr.exe
--
--	FUNCTIONS:			Winsock 2 API
--
--	DATE:				January 6, 2008
--
--	REVISIONS:			(Date and Description)
--
--	DESIGNERS:			Aman Abdulla
--
--	PROGRAMMERS:		Aman Abdulla
--
--	NOTES:
--	The program will accept TCP connections from client machines.
--  The program will read data from the client socket and simply echo it back.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <winsock2.h>
#include <errno.h>

#define SERVER_TCP_PORT 7000	// Default port
#define BUFSIZE	255				//Buffer length
#define TRUE	1
 
int main (int argc, char **argv)
{
	int	n, ns, bytes_to_read;
	int	client_len, port, err;
	SOCKET sd, new_sd;
	struct	sockaddr_in server, client;
	char	*bp, buf[BUFSIZE];
	WSADATA WSAData;
	WORD wVersionRequested;
	
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

	wVersionRequested = MAKEWORD( 2, 2 ); 
	err = WSAStartup( wVersionRequested, &WSAData );
	if ( err != 0 ) //No useable DLL
	{
		printf ("DLL not found!\n");
		exit(1);
	}

	// Create a stream socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

	// Initialize and set up the address structure
	memset((char *)&server, 0, sizeof(struct sockaddr_in)); 
	server.sin_family = AF_INET;
	server.sin_port = htons(port); 
	server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client
	
	// Bind an address to the socket
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't bind name to socket");
		exit(1);
	}

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

		printf(" Remote Address:  %s\n", inet_ntoa(client.sin_addr));
		bp = buf;
		bytes_to_read = BUFSIZE;
		while ((n = recv (new_sd, bp, bytes_to_read, 0)) < BUFSIZE)
		{
			bp += n;
			bytes_to_read -= n;
			if (n == 0)
				break;
		}
		
		ns = send (new_sd, buf, BUFSIZE, 0);
		closesocket (new_sd);
	}
	closesocket(sd);
	WSACleanup();
	exit(0);
}

