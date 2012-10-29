/*---------------------------------------------------------------------------------------
--	SOURCE FILE:		tcp_svr6.c -   A simple IPv6 echo server using TCP
--
--	PROGRAM:		tcps6	[gcc -Wall -o tcps6 tcp_svr6.c]
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:			February 27, 2008
--
--	REVISIONS:		(Date and Description)
--
--				
--
--	DESIGNER:		Aman Abdulla
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--	The program will accept TCP connections from IPv6 client addreses.
-- 	The program will read data from the client socket and simply echo it back.
--
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

#define SERVER_TCP_PORT "7000"	// Default port
#define BUFLEN	80		//Buffer length
#define TRUE	1
#define FALSE 	0
#define QUEUE 	5
#define MAXSTR	100

// Function Prototypes
static void SystemFatal(const char* );

int main (int argc, char **argv)
{
	int	n, bytes_to_read, ret, yes = 1;
	int	sd, new_sd, client_len;
	char	*bp, buf[BUFLEN];
	struct sockaddr_in6 client; 
	struct addrinfo query,*response,*ap;
  	struct linger cflinger;
	char hostname[MAXSTR], service[MAXSTR];
	static const char *server_port = SERVER_TCP_PORT;
		
	// Initialize cflinger - this option will ensure that the connection "close" will block until all the data is delivered
	cflinger.l_onoff = 1; // non zero will block close 
	cflinger.l_linger = 60; // until timeout


	switch(argc)
	{
		case 1:
			server_port = SERVER_TCP_PORT;	// Use the default port
		break;
		case 2:
			server_port = argv[1];	// Get user specified port
		break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
	}


	// Get the the address info from the NIC
	bzero (&query,sizeof(struct addrinfo));

	query.ai_flags = AI_PASSIVE;	// Passive Open
	query.ai_family = AF_UNSPEC;	// Either IPv4 or IPv6 
	query.ai_socktype = SOCK_STREAM;
	
	if ((ret = getaddrinfo (NULL, server_port, &query, &response)) != 0)
	{
		printf("%s",gai_strerror(ret));
		exit (1);
	}
	
	sd = -1;
	for (ap = response ; ap != NULL; ap=ap->ai_next)
  	{
   		if ((sd = socket (ap->ai_family,ap->ai_socktype,ap->ai_protocol)) == -1)
      			continue;
      		
   		if (setsockopt (sd, SOL_SOCKET, SO_REUSEADDR, (char *) &yes, sizeof (int)) == -1)
      			SystemFatal("setsockopt");
		   
   		if (setsockopt (sd, SOL_SOCKET, SO_LINGER, (char *) &cflinger, sizeof (struct linger)) == -1)
      			SystemFatal("setsockopt");
   
   		if (bind(sd,ap->ai_addr,ap->ai_addrlen) == 0)
      			break; // success 
      		   
   		close(sd);
   		sd = -1;
		SystemFatal("bind");
   	}

	freeaddrinfo(response);

	if (sd < 0)
		SystemFatal ("Cannot bind the open socket");
   	 
	
	// Listen for connections
	// queue up to 5 connect requests
	if (listen (sd, QUEUE) == -1)
   		SystemFatal("listen");

	while (TRUE)
	{
		bzero (hostname, MAXSTR);
  		bzero (service, MAXSTR);

		client_len= sizeof (client);
		if ((new_sd = accept (sd, (struct sockaddr *)&client, &client_len)) == -1)
      			SystemFatal("accept");		

		if (getnameinfo ((struct sockaddr *)&client, client_len, hostname, MAXSTR, service, MAXSTR, 0) != 0)
			SystemFatal("getnameinfo");     		

  		printf ("Remote Address: (%s) on Remote Port (%s)\n", hostname, service);
  
		bp = buf;
		bytes_to_read = BUFLEN;
		while ((n = recv (new_sd, bp, bytes_to_read, 0)) < BUFLEN)
		{
			bp += n;
			bytes_to_read -= n;
		}
		
		if (strncmp("server-halt", buf, 11) == 0)
		{
			printf ("sending:%s\n", buf);
			send (new_sd, buf, BUFLEN, 0);
			close (new_sd);
                	break;
		}
		else
		{
			printf ("sending:%s\n", buf);
			send (new_sd, buf, BUFLEN, 0);
			close (new_sd);
		}
	}
	
	close (sd);
	printf ("Server shutting down...\n");
	return (0);
}

// Prints the error stored in errno and aborts the program.
static void SystemFatal(const char* message)
{
    perror (message);
    exit (EXIT_FAILURE);
}