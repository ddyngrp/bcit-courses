/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	clnt.c - A simple TCP/UDP client program.
--
--	PROGRAM:		clnt.exe
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
--				Combined TCP & UDP client programs into one common client application.
--				users can select the protocol mode using command-line swicthes				--
--
--	DESIGNERS:		Aman Abdulla
--
--	PROGRAMMERS:	Aman Abdulla
--					Sachiko Nakano
--
--	NOTES:
--	The program will establish a TCP connection to a user specifed server.
-- The server can be specified using a fully qualified domain name or and
--	IP address. After the connection has been established the user will be
-- prompted for date. The date string is then sent to the server and the
-- response (echo) back from the server is displayed.
---------------------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "helper.h"

#define HOST_SIZE 32

int set_server_info( struct sockaddr_in*, const char*, const int );
int do_udp( const int, const struct sockaddr_in* );
int do_tcp( const int, const struct sockaddr_in* );

int main ( int argc, char *argv[] )
{
	int protocol = -1;
	int port = SERVER_TCP_PORT;
	char host[HOST_SIZE] = "localhost";
	int sock_fd;
	struct sockaddr_in server;
	char *prot_str = "TCP";

	if( ( protocol = get_param_clnt( argv, &port, host, HOST_SIZE ) ) < 0 )
		exit(1);

	if ( protocol == UDP )
		prot_str = "UDP";

	printf( "%s client is starting ", prot_str );
	do_sleep( DELAY );

	if ( ( sock_fd = create_socket( protocol ) ) < 0 )
		exit(1);

	if ( set_server_info( &server, host, port ) < 0 )
		exit(1);

	if ( protocol == TCP )
	{
		if ( do_tcp( sock_fd, &server ) < 0 )
		{
			exit(1);
		}
	}
	else	// UDP
	{
		if ( do_udp( sock_fd, &server ) < 0 )
		{
			exit(1);
		}
	}

	close( sock_fd );
	return (0);
}

int set_server_info( struct sockaddr_in *svr_ptr, const char *host, const int port )
{
	struct hostent *svr_info;
	char **svr_addr_list;
	char *svr_addr;
	char str[INET_ADDRSTRLEN];	// size = 16

	bzero( (char *)svr_ptr, sizeof( struct sockaddr_in ) );
	// TO DO: convert to memset
	svr_ptr->sin_family = AF_INET;
	svr_ptr->sin_port = htons( port );

	/* retrieves the server information */
	if ( ( svr_info = gethostbyname( host ) ) == NULL )
	{
		herror("failed to retrieve the server information");
		//TO Do: herror obsolute? how to print h_errno
		return -1;
	}

	bcopy( svr_info->h_addr, (char *)&svr_ptr->sin_addr, svr_info->h_length );

	svr_addr_list = svr_info->h_addr_list;
	printf( "server information retrieved: %s %s\n", svr_info->h_name,
                inet_ntop( svr_info->h_addrtype, *svr_addr_list, str, sizeof( str ) ) );
	sleep( DELAY );
}

int do_udp( const int sckt, const struct sockaddr_in *svr_ptr )
{
	unsigned svr_len = sizeof( *svr_ptr );
	struct	sockaddr_in client;
	char snd_buf[BUFLEN], rcv_buf[BUFLEN];

	bzero( (char *)&client, sizeof(client) ); 
	client.sin_family = AF_INET; 

	/* 0 - chooses an unused port at random */
	client.sin_port = htons( 0 );

	/* INADDR_ANY - uses the IP address of the machine */
	client.sin_addr.s_addr = htonl( INADDR_ANY );
	
	/* binds local address to the socket */
	if ( bind( sckt, (struct sockaddr *)&client, sizeof(client) ) == -1 )
	{
		perror ( "can't bind name to socket" );
		return -1;
	}

	/* prints out the port # bound to the socket */ 
	unsigned len = sizeof(client);
	getsockname( sckt, (struct sockaddr *)&client, &len );
	printf( "bound socket %d to port %d\n", sckt, client.sin_port );

	printf( "message: " );
	fgets( snd_buf, BUFLEN, stdin );

	printf( "sending the message to the server " );
	do_sleep( DELAY );

	/* transmits data. since no connection is established, 
 	   destination must be specified.	
	   -1 indicates only locally-detected errors. 
	   non -1 does not guarantee delivery of the message. */
	if ( sendto( sckt, snd_buf, BUFLEN, 0, 
	(struct sockaddr *)svr_ptr, svr_len ) == -1)
	{
		perror( "sendto failure" );
		return -1;
	}

	/* receives data. since no connection is established, 
 	   source must be specified. */	
	if ( recvfrom( sckt, rcv_buf, 
             BUFLEN, 
             0, 
             (struct sockaddr *)&svr_ptr, 
             &svr_len ) == -1 ) 
	{
		perror ( "recvfrom error" );
		return -1;
	}

	printf( "received: %s", rcv_buf );

	if ( strncmp( snd_buf, rcv_buf, BUFLEN ) != 0 )
	{
		printf( "data is corrupted\n" );
	}
	printf("data did not get corrupted\n");
	return 0;
}

int do_tcp( const int sckt, const struct sockaddr_in *svr_ptr )
{
	char snd_buf[BUFLEN], rcv_buf[BUFLEN];

	// Connecting to the server
	if ( connect( sckt, (struct sockaddr *)svr_ptr, sizeof( *svr_ptr ) ) == -1 )
	{
		perror( "can't connect to the server" );
		return -1;
	}

	printf( "connected to the server\n" );
	sleep( DELAY );

	printf( "message: " );
	fgets( snd_buf, BUFLEN, stdin );

	/* this is just to demonstrate the flow */
	printf( "sending the message to the server " );
	do_sleep( DELAY );

	/* transmit data on the socket to server's port */
	send( sckt, snd_buf, BUFLEN, 0 );

	/* retrieves message from socket */
	if ( recv( sckt, rcv_buf, BUFLEN, 0 ) == -1 )
	{
		perror( "can't receive message" );
		return -1;
	} 
	printf( "received: %s", rcv_buf );
	return 0;
}


