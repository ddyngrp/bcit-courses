// A simple UCP client program allows the user to specify a server by its domain name.

#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>

#define SERVER_UDP_PORT		8000	// Default port
#define MAXLEN				65000    // Maximum Buffer length
#define DEFLEN				64	// Default Length

/*----------- Function Prototypes ------------------------*/
long delay (struct timeval t1, struct timeval t2);

int main (int argc, char **argv)
{
	int	data_size = DEFLEN, port = SERVER_UDP_PORT;
	int	i, j, sd, server_len;
	char *pname, *host, rbuf[MAXLEN], sbuf[MAXLEN];
	struct	hostent	*hp;
	struct	sockaddr_in server, client;
	struct  timeval start, end;

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

	// Create a datagram socket
	if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
	{
		perror ("Can't create a socket\n");
		exit(1);
	}

	// Store server's information
	bzero((char *)&server, sizeof(server)); 
	server.sin_family = AF_INET; 
	server.sin_port = htons(port);

	if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr,"Can't get server's IP address\n");
		exit(1);
	}
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	// Bind local address to the socket 
	bzero((char *)&client, sizeof(client)); 
	client.sin_family = AF_INET; 
	client.sin_port = htons(0);
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if (bind(sd, (struct sockaddr *)&client, sizeof(client)) == -1)
	{
		perror ("Can't bind name to socket");
		exit(1);
	}

	if (data_size > MAXLEN)
	{
		fprintf(stderr, "Data is too big\n");
		exit(1);
	}
	
	// data	is a, b, c, ..., z, a, b,...
	for (i = 0; i < data_size; i++)
	{
		j = (i < 26) ? i : i % 26;
		sbuf[i] = "a" + j;
	}

	gettimeofday(&start, NULL); // start delay measure

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

	gettimeofday (&end, NULL); // end delay measure
	printf ("Round-trip delay = %ld ms.\n", delay(start, end));

	if (strncmp(sbuf, rbuf, data_size) != 0) 
		printf("Data is corrupted\n");

	close(sd);
	return(0);
}

// Compute the delay between tl and t2 in milliseconds 
long delay (struct timeval t1, struct timeval t2)
{
	long d;

	d = (t2.tv_sec - t1.tv_sec) * 1000;
	d += ((t2.tv_usec - t1.tv_usec + 500) / 1000);
	return(d);
}
