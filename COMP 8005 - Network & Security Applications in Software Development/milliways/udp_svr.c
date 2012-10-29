// A simple echo server using UCP 

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>

#define SERVER_UDP_PORT 	8000	// Default port
#define MAXLEN			65000	//Buffer length
#define TRUE			1
 
int main (int argc, char **argv)
{
	int	sd, client_len, port, n;
	char	buf[MAXLEN];
	struct	sockaddr_in server, client;

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

	// Create a datagram socket
	if ((sd = socket (AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror ("Can't create a socket"); 
		exit(1);
	}

	// Bind an address to the socket
	bzero((char *)&server, sizeof(server)); 
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
		printf ("From host: %s\n", inet_ntoa (client.sin_addr));
	}
	close(sd);
	return(0);
}
