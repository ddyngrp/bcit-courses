/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	udp_clnt.c - A simple UDP client program.
--
--	PROGRAM:		uclnt.exe
--
--	FUNCTIONS:		Winsock 2 API
--
--	DATE:			January 6, 2008
--
--	REVISIONS:		(Date and Description)
--
--	DESIGNERS:
--
--	PROGRAMMERS:	Aman Abdulla
--
--	NOTES:
--	The program will send a UDP packet to a user specifed server.
--  The server can be specified using a fully qualified domain name or and
--	IP address. The packet is time stamped and then sent to the server. The
--  response (echo) is also time stamped and the delay is displayed.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <winsock2.h>
#include <errno.h>
#include <string.h>


#define SERVER_UDP_PORT		8000	// Default port
#define MAXLEN				65000   // Maximum Buffer length
#define DEFLEN				64		// Default Length

/*----------- Function Prototypes ------------------------*/
long delay (SYSTEMTIME t1, SYSTEMTIME t2);

int main (int argc, char **argv)
{
	int	data_size = DEFLEN, port = SERVER_UDP_PORT;
	int	i, j, server_len, client_len;
	SOCKET sd;
	char *pname, *host, rbuf[MAXLEN], sbuf[MAXLEN];
	struct	hostent	*hp;
	struct	sockaddr_in server, client;
	SYSTEMTIME stStartTime, stEndTime;
	WSADATA stWSAData;
	WORD wVersionRequested = MAKEWORD (2,2);

	pname = argv[0];
	argc--;
	argv++;
	if (argc > 0 && (strcmp(*argv, "-s") == 0))
	{
		if (--argc > 0 && (data_size = atoi(*++argv)))
		{
			argc--;
			argv++;
		}
		else
		{
			fprintf (stderr,"Usage: %s [-s packet size] host [port]\n", pname);
			exit(1);
		}
	}
	if (argc > 0)
	{
		host = *argv;
			if (--argc > 0)
				port = atoi(*++argv);
	}
	else
	{
		fprintf(stderr, "Usage:	%s [-s packet size] host [port]\n", pname);
		exit(1);
	}

	// Initialize the DLL with version Winsock 2.2
	WSAStartup(wVersionRequested, &stWSAData ) ;

	// Create a datagram socket
	if ((sd = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror ("Can't create a socket\n");
		exit(1);
	}

	// Store server's information
	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr,"Can't get server's IP address\n");
		exit(1);
	}
	//strcpy((char *)&server.sin_addr, hp->h_addr);
	memcpy((char *)&server.sin_addr, hp->h_addr, hp->h_length);

	// Bind local address to the socket
	memset((char *)&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(0);  // bind to any available port
	client.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(sd, (struct sockaddr *)&client, sizeof(client)) == -1)
	{
		perror ("Can't bind name to socket");
		exit(1);
	}
	// Find out what port was assigned and print it
	client_len = sizeof(client);
	if (getsockname (sd, (struct sockaddr *)&client, &client_len) < 0)
	{
		perror ("getsockname: \n");
		exit(1);
	}
	printf ("Port aasigned is %d\n", ntohs(client.sin_port));
	
	if (data_size > MAXLEN)
	{
		fprintf(stderr, "Data is too big\n");
		exit(1);
	}

	// data	is a, b, c, ..., z, a, b,...
	for (i = 0; i < data_size; i++)
	{
		j = (i < 26) ? i : i % 26;
		sbuf[i] = 'a' + j;
	}

	// Get the start time
	GetSystemTime(&stStartTime);

	// transmit data
	server_len = sizeof(server);
	if (sendto (sd, sbuf, data_size, 0, (struct sockaddr *)&server, server_len) == -1)
	{
		perror("sendto failure");
		exit(1);
	}

	// receive data
	if (recvfrom (sd, rbuf, MAXLEN, 0, (struct sockaddr *)&server, &server_len) < 0)
	{
		perror (" recvfrom error");
		exit(1);
	}

	//Get the end time and calculate the delay measure
	GetSystemTime(&stEndTime);
	printf ("Round-trip delay = %ld ms.\n", delay(stStartTime, stEndTime));

	if (strncmp(sbuf, rbuf, data_size) != 0)
		printf("Data is corrupted\n");

	closesocket(sd);
	WSACleanup();
	exit(0);
}

// Compute the delay between tl and t2 in milliseconds
long delay (SYSTEMTIME t1, SYSTEMTIME t2)
{
	long d;

	d = (t2.wSecond - t1.wSecond) * 1000;
	d += (t2.wMilliseconds - t1.wMilliseconds);
	return(d);
}
