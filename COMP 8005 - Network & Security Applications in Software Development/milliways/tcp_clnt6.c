/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		tcp_clnt.c - A simple TCP client program.
--
--	PROGRAM:		tcpc6 	[gcc -Wall -o tcpc6 tcp_clnt6.c]
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:			February 27, 2008
--
--	REVISIONS:		(Date and Description)
--	
--
--	DESIGNER:		Aman Abdulla
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--	The program will establish a TCP connection to a default or user-specifed 
--	server (IPv6 address).
-- 	After the connection has been established the user will be
-- 	prompted for data. The data string is then sent to the server and the
-- 	response (echo) back from the server is displayed.
--	In order for this to work you will have to set up a site-level 
-- 	IPv6 address as follows:                                       
--      	ifconfig eth0 inet6 add fec0:0:0:1:20c:f1ff:fee3:4679/64       
-- 	Test the NIC setip as follows:                                                    
--      	ping6 fec0::1:20c:f1ff:fee3:4679     
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

#define SERVER_TCP_PORT 7000	// Default port
#define BUFLEN	80		//Buffer length
#define TRUE	1
#define FALSE 	0
#define QUEUE 	5
#define MAXSTR	100
#define DEFAULT_HOST "fec0::1:20c:f1ff:fee3:4679"

// Function Prototypes
static void SystemFatal(const char* );

int main (int argc, char **argv)
{
	int n, bytes_to_read;
	int sd, server_port, ret;
	char  *host, *bp, rbuf[BUFLEN], sbuf[BUFLEN];
	struct sockaddr_in6 client, client2; 
  	char ip6str[INET6_ADDRSTRLEN];
	
	switch (argc)
	{
		case 1:
			host = DEFAULT_HOST;	//Default host name
			server_port = SERVER_TCP_PORT;	//Default port
		break;
		case 2:
			host =	argv[1];	// Host name
			server_port = SERVER_TCP_PORT; //use default port
		break;
		case 3:
			host =	argv[1];
			server_port = atoi(argv[2]);	// User specified port
		break;
		default:
			printf ("Using default host: %s  port: %d\n", DEFAULT_HOST, SERVER_TCP_PORT);
	}
		
	memset (&client2, 0, sizeof(client2)); 

	client2.sin6_family = AF_INET6;
	ret = inet_pton (AF_INET6,host,&(client2.sin6_addr));	

	client2.sin6_port = htons (server_port);

	printf ("\nSend the string \"server-halt\" to shut the server down\n");
	printf ("\nConnecting to %s = %s (err=%d)\n", host, inet_ntop(AF_INET6,&client.sin6_addr,ip6str,sizeof(ip6str)),ret);
	printf ("Same as %s\n",inet_ntop(AF_INET6,&client2.sin6_addr,ip6str,sizeof(ip6str)));

	// Create the socket
	if ((sd = socket (AF_INET6, SOCK_STREAM,0)) == -1)
		SystemFatal ("Cannot create socket");
   	
	
	// Connecting to the server
	if (connect (sd,(void *)&client2, sizeof(client2)) == -1)
		SystemFatal ("Can't connect to server");
   	
	printf("\nTransmit: ");
	fgets (sbuf, BUFLEN, stdin);

	// Transmit data through the socket
	send (sd, sbuf, BUFLEN, 0);

	printf("Receive: ");
	bp = rbuf;
	bytes_to_read = BUFLEN;

	// client makes repeated calls to recv until no more data is expected to arrive.
	n = 0;
	while ((n = recv (sd, bp, bytes_to_read, 0)) < BUFLEN)
	{
		bp += n;
		bytes_to_read -= n;
	}
	printf ("%s\n", rbuf);
	fflush(stdout);
	close (sd);
	return (0);
}

// Prints the error stored in errno and aborts the program.
static void SystemFatal(const char* message)
{
    perror (message);
    exit (EXIT_FAILURE);
}