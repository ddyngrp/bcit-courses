/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		udp_svr.c -   A simple echo server using UDP
--
--	PROGRAM:			usvr.exe
--
--	FUNCTIONS:			winsock2 API
--
--	DATE:				January 6, 2008
--
--	REVISIONS:			(Date and Description)
--
--	DESIGNERS:
--
--	PROGRAMMERS:		Aman Abdulla
--
--	NOTES:
--	The program will accept UDP packets from client machines.
-- The program will read data from the client socket and simply echo it back.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <winsock2.h>


#define SERVER_UDP_PORT 		8000	// Default port
#define MAXLEN					65000	//Buffer length
#define TRUE					1

int main (int argc, char **argv)
{
	int	client_len, port, n;
	SOCKET sd;
	char	buf[MAXLEN];
	struct	sockaddr_in server, client;
	WSADATA stWSAData;
	WORD wVersionRequested = MAKEWORD (2,2);
  	
	switch(argc)
	{
		case 1:
			port = SERVER_UDP_PORT;	// Default port
		break;
		case 2:
			port = atoi(argv[1]);	//User specified port
		break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
   	}

	// Initialize the DLL with version Winsock 2.2
	WSAStartup(wVersionRequested, &stWSAData ) ;

	// Create a datagram socket
	if ((sd = socket (PF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

	// Bind an address to the socket
	memset ((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror ("Can't bind name to socket");
		exit(1);
	}

	while (TRUE)
	{
		client_len = sizeof(client);
		if ((n = recvfrom (sd, buf, MAXLEN, 0, (struct sockaddr *)&client, &client_len)) < 0)
		{
			perror ("recvfrom error");
			exit(1);
		}
		if (sendto (sd, buf, n, 0,(struct sockaddr *)&client, client_len) != n)
		{
			perror ("sendto error");
			exit(1);
		}
		printf ("Received %d bytes\t", n);
		printf ("From host: %s\n", inet_ntoa(client.sin_addr));
	}
	closesocket(sd);
	WSACleanup();
	exit(0);
}
