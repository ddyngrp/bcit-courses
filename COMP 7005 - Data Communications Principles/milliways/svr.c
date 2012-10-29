/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	tcp_svr.c -   A simple echo server using TCP
--
--	PROGRAM:		tsvr.exe
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:			January 23, 2001
--
--	REVISIONS:	(Date and Description)
--
--				January 2005 - Aman Abdulla
--				Modified the read loop to use fgets.
--				While loop is based on the buffer length 
--
--				October 2005 - Sachiko Nakano
--				Combined TCP & UDP server programs into one common server application.
--				users can select the protocol mode using command-line swicthes				
--
--	DESIGNERS:		Aman Abdulla
--
--	PROGRAMMERS:	Aman Abdulla
--					Sachiko Nakano
--
--	NOTES:
--	The program will accept TCP connections from client machines.
-- The program will read data from the client socket and simply echo it back.
---------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "helper.h"

int do_tcp( const int );
int do_udp( const int );

int main (int argc, char **argv)
{
	int port = SERVER_TCP_PORT;
	int protocol = -1;
	int sock_fd = -1;
	struct sockaddr_in server;
	char *prot_str = "TCP";

	if ( ( protocol = get_param_svr( argv, &port ) ) < 0 )
	{
		exit(1);
	}
	
	if ( protocol == UDP )
	{
		prot_str = "UDP";
	}

	printf( "%s server is starting ", prot_str );
	do_sleep( DELAY );

	if ( ( sock_fd = init_server( protocol, &server, port ) ) < 0 )
	{
		exit(1);
	}

	if ( protocol == TCP )
	{
		if ( do_tcp( sock_fd ) < 0 )
		{
			exit(1);
		}
	}
	else	// UDP
	{
		if ( do_udp( sock_fd ) < 0 )
		{
			exit(1);
		}
	}

	close( sock_fd );
	exit(0);
}

int do_tcp( const int base_sock )
{
	int new_sd = -1;
	struct sockaddr_in client;
	char buf[BUFLEN];
	unsigned clnt_len = sizeof( struct sockaddr_in );
	int rcvd = -1;

	/* marks socket as accepting connections (listening)
           setting the maximum number of listen queue */
	if ( listen( base_sock, 5 ) == -1 )
	{
		perror( "can't listen for connections" );
		return -1;
	} 

	printf( "now server is listening\n" );

	while ( 1 )
	{
		/* extracts the first connection on the pending connection
		   queue and creates a new socket of the same type */
		if ( ( new_sd = accept( base_sock, 
		(struct sockaddr *)&client, &clnt_len ) ) == -1 )
		{
			perror( "can't accept client" );
			return -1;
		}

		printf( "\naccepted a connection from %s\n", inet_ntoa( client.sin_addr ) );
		printf( "new socket created: socket file descripter = %d\n", new_sd );

		if ( ( rcvd = recv( new_sd, buf, BUFLEN, 0 ) ) == -1 )
		{
			perror( "can't receive message" );
			return -1;
		} 
		printf ( "received %d bytes from host %s\n", rcvd, inet_ntoa(client.sin_addr) );
		printf( "msg: %s\n", buf );
		sleep( DELAY );
		printf( "echoing the message " );
		do_sleep( DELAY );

		send( new_sd, buf, BUFLEN, 0 );
		close( new_sd );
	}
}

int do_udp( const int sock_fd )
{
	int rcvd = -1;
	struct sockaddr_in client;
	char buf[BUFLEN];
	unsigned clnt_len = sizeof( struct sockaddr_in );

	while ( 1 )
	{
		if ( ( rcvd = recvfrom( sock_fd, buf, BUFLEN, 0, 
		(struct sockaddr *)&client, &clnt_len)) < 0)
		{
			perror ("recvfrom error");
			exit(1);
		}

		printf ( "received %d bytes from host %s\n", rcvd, inet_ntoa(client.sin_addr) );
		printf( "msg: %s\n", buf );
		sleep( DELAY );
		printf( "echoing the message " );
		do_sleep( DELAY );

		if ( sendto( sock_fd, buf, rcvd, 0, 
		(struct sockaddr *)&client, clnt_len ) != rcvd )
		{
			perror ("sendto error");
			exit(1);
		}
	}
}

int init_server( const int protocol, struct sockaddr_in *svr_ptr, const int port )
{
    int sock_fd;

    if ( ( sock_fd = create_socket( protocol ) ) < 0 )
    {
        return -1;
    }
    bzero( (char *)svr_ptr, sizeof( *svr_ptr ) );
    svr_ptr->sin_family = AF_INET;
    svr_ptr->sin_port = htons(port);
    svr_ptr->sin_addr.s_addr = htonl(INADDR_ANY); 

    if ( bind( sock_fd, (struct sockaddr *)svr_ptr, sizeof( *svr_ptr ) ) == -1 )
    {
        perror("can't bind name to socket");
        return -1;
    }

    printf( "bound socket %d to port %d\n", sock_fd, port );
    sleep( DELAY );
    return sock_fd;
}

