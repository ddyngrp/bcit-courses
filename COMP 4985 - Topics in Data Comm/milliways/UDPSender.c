/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	UDPSender.c -   A simple program to send a UDP datagram to a
--												UDP receiver.
--
--	PROGRAM:		udptx.exe
--
--	FUNCTIONS:		Winsock 2 API
--
--	DATE:			January 6, 2008
--
--	REVISIONS:		(Date and Description)
--
--	DESIGNERS:		Aman Abdulla
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--     This simple  program  will  open a UDP socket and send a user specified 
--	   datagram to a host at the specified IP address and UDP port.  
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <winsock2.h>

#define PORT 7000

int main(int argc, char **argv)
{
	int i, nBufSize, err;
	SOCKET sock;
	char *buf, *buf_ptr;
  	struct sockaddr_in sin ;
	WSADATA stWSAData;
	WORD wVersionRequested = MAKEWORD (2,2);

	if (argc != 4)
	{
		printf("Usage: sender <Remote-Address> <Packet-Size> <Port>\n");
		printf ("		Enter the Remote Address in dotted IP format\n");
		printf ("		Packet size is in Bytes\n");
		exit(1) ;
	}
	else
	{
		//printf("%s %s %s\n", argv[0], argv[1], argv[2]) ;
		nBufSize = atoi(argv[2]) ;
		printf("Buffer size is %d\n", nBufSize) ;
	}

	buf = (char*)malloc(nBufSize) ;

	for (i = 0; i < nBufSize; i++)
		buf[i] = 'a';

	// Initialize the DLL with version Winsock 2.2
	WSAStartup(wVersionRequested, &stWSAData ) ;

	// Open a connectionless, unreliable socket (Datagrams)
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
		exit(2);

	buf_ptr = buf;

   // Set the socket options such that the send buffer size is set at the
   // application layer
	if (err = setsockopt( sock, SOL_SOCKET, SO_SNDBUF, buf_ptr, sizeof(buf)) != 0)
	{
		printf ("Error in setsockopt!\n");
		exit (3);
	}
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;	 // Specify the Internet (TCP/IP) Address family
	sin.sin_port = htons(atoi(argv[3])); // Convert to network byte order

	// Ensure that the IP string is a legitimate address (dotted decimal)
	if ((sin.sin_addr.s_addr = inet_addr(argv[1])) == INADDR_NONE)
	{
		printf( "Invalid IP address\n");
		exit(3);
	}
	printf( "IP Address & Socket Okay\n" );
	printf( "Socket is %d\n", sock ) ;
	printf("We have ignition!\n") ;

	// Transmit data through an unconnected (UDP) socket
	if (sendto(sock, buf, nBufSize, 0, (struct sockaddr *)&sin, sizeof( sin )) <= 0)
	{
		perror ("sendto error");
		exit (1);
	}

 	// Close the socket
	closesocket(sock);

   // Cleanup after yourself
   WSACleanup();
   exit(0);
}

