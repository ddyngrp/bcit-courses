/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	UDPReceiver.c -   A simple program to receive a UDP datagram from a
--												UDP sender.
--
--	PROGRAM:		udprx.exe
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
--     This simple  program  will  open a passive UDP socket and wait for datagrams
--     to arrive on the specified UDP port. It will print the size of the received
--     datagram and the IP address of the source host. 
---------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <winsock2.h>

#define BUFSIZE  100000
#define PORT	7000

/*---- Function Prototypes -----------------------*/
SOCKET passiveUDP(unsigned short);

/*--- Globals --------------*/
char buf[BUFSIZE];

int main(int argc, char **argv)
{
	int nbytes, err;
	SOCKET sock;
  	struct sockaddr_in sin;
	char *buf_ptr;
	int sin_len;

	
	if (argc != 2)
	{
   		printf("Usage: %s <Port>\n", argv[0]);
		exit (1);
	}

	// Create a socket to read from
  	sock = passiveUDP(atoi(argv[1]));

  	buf_ptr = buf;

	// Set the options such that the recieve buffer size is set at the
	// application layer
  	if (err = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, buf_ptr, sizeof(buf)) !=0)
	{
		printf ("Error in setsockopt!\n");
		exit (1);
	}
	printf("setsockopt returns: %d\n", err) ;
  	printf("Socket: %d\n", sock);
	printf ("Waiting for data ......\n");
   
  	sin_len = sizeof(sin);

	// Receive data from an unconneted (UDP) socket
	// Note that this function will block until data arrives at the socket!
  	
	if ((nbytes = recvfrom (sock, buf, BUFSIZE, 0, (struct sockaddr *)&sin, &sin_len)) < 0)
	{
		perror ("recvfrom error");
		exit(1);
	}

	printf ("Received %d bytes\t", nbytes);
	printf ("From host: %s\n", inet_ntoa (sin.sin_addr));
	
	// Cleanup after yourself
	WSACleanup();
	exit(0);
}

/*-------- Function for creating a Passive UDP socket ---------*/
SOCKET passiveUDP(unsigned short portnumber)
{
	SOCKET s;
  	struct sockaddr_in  sin;
  	
	WSADATA stWSAData;
	WORD wVersionRequested = MAKEWORD (2,2);
  	
	// Initialize the DLL with version Winsock 2.2
	WSAStartup(wVersionRequested, &stWSAData ) ;
	  	
	if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
   		exit(1);

  	memset(&sin, 0, sizeof(sin));
  	sin.sin_family = AF_INET;
  	sin.sin_addr.s_addr = INADDR_ANY; // Stack assigns the local IP address
  	sin.sin_port = htons(portnumber);

	// Name the local socket with values in sin structure
  	if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) < 0)
   		exit(2);

  	return s;
}