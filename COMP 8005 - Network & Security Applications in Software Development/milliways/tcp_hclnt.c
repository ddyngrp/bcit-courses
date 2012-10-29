/*-----------------------------------------------------------------------------------
--	SOURCE FILE:	tcp_hclnt.c -   A simple TCP client example that illustrates 
--					how to detect a loss of connection with a server.
--
--	PROGRAM:			hclnt.exe
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:				March 13, 2001
--
--	REVISIONS:		Date and Description)
--
--	DESIGNERS:     Aman Abdulla
--
--	PROGRAMMERS:	Aman Abdulla
--
--	NOTES:
--	The program will establish a TCP connection to a user specifed server. The
--	client sends off an initial data packet. After that it will block on select and
--	wait for messages (data) or  periodic "heartbeats" to indicate that the other
--	side is still connected.
--
--	If select unblocks due to a timeout and no packet has been received it will
--	start sending out #1 "heartbeats" periodically and continue waiting to wait
--	for responses. If there is no response it sends a #2 heartbeat and then
--	#3 after which it will assume a disconnection and terminate.
------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "hbeat.h"


#define SERVER_TCP_PORT		7000	// Default port

int main (int argc, char **argv)
{
	int i, j, n, ns, nready, bytes_read, bytes_to_read, heartbeats = 0;
	int sd, port, data_size = BUFLEN;
	struct hostent	*hp;
	struct sockaddr_in server;
	msg_t 	msg, bmsg, resp, *mp, *rp, *bm;
	char  *host, **pptr, *bp, rbuf[sizeof(msg)], str[16], *hmsg;
	struct 	timeval tv;
	fd_set 	allset, rset;

	switch(argc)
	{
		case 2:
			host =	argv[1];	// Host name
			port =	SERVER_TCP_PORT;
		break;
		case 3:
			host =	argv[1];
			port =	atoi(argv[2]);	// User specified port
		break;
		default:
			fprintf(stderr, "Usage: %s host [port]\n", argv[0]);
			exit(1);
	}

	// Create the socket
	if ((sd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Cannot create socket");
		exit(1);
	}
	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr, "Unknown server address\n");
		exit(1);
	}
	bcopy(hp->h_addr, (char *)&server.sin_addr, hp->h_length);

	// Connecting to the server
	if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		fprintf(stderr, "Can't connect to server\n");
		perror("connect");
		exit(1);
	}
	printf("Connected:    Server Name: %s\n", hp->h_name);
	pptr = hp->h_addr_list;
	printf("\t\tIP Address: %s\n", inet_ntop(hp->h_addrtype, *pptr, str, sizeof(str)));
	printf("Transmitting data....:\n");

	// data packet
	for (i = 0; i < 10; i++)
	{
		j = (i < 26) ? i : i % 26;
		msg.data[i] = 'a' + j;
		//msg.data[i] = 'a';
	}
	msg.data[i+1] = '\0';
	msg.type = MSG_DATA;
	mp = &msg;

	// Transmit data through the socket
	if ((ns = send (sd, mp, sizeof(msg), 0)) < 0)
	{
		perror ("Data Send error:");
		exit(1);
	}


	// Set up the socket descriptors for select
	tv.tv_sec = T0;
	tv.tv_usec = 0;
	FD_ZERO (&allset);
	FD_SET (sd, &allset);

	for (;;)
	{
		 rset = allset;  // create a set of all valid read sockets

		// wait for something to happen on the newly connected socket
		bytes_read =0;
		if ((nready = select (sd+1, &rset, NULL, NULL, &tv)) < 0)
		{
			perror ("select error: ");
			exit(1);
		}

	              if (nready == 0)	// timer has expired
		{
			if (++heartbeats > 3)
			{
				printf ("Connection broken!\n");
				exit (1);
			}
			printf ("Sending heartbeat #%d\n", heartbeats);
			bm = &bmsg;
			bm->type = MSG_HEARTBEAT;
			hmsg = "I am still alive!";
			strcpy (bm->data, hmsg);
			if ((ns = send (sd, bm, sizeof (bmsg), 0)) < 0)
			{
				perror ("Heartbeat send error: \n");
				exit(1);
			}
			tv.tv_sec = T1;
			continue;
		}

		if (FD_ISSET(sd, &rset))
  		{
         			bytes_to_read = sizeof (msg);
         			bp = rbuf;
         			mp = (msg_t *)rbuf;

			// client makes repeated calls to recv until no more data is expected to arrive.
			while (((n = recv (sd, bp, bytes_to_read, 0)) < bytes_to_read) && (n != 0))
			{
				bytes_read = n;
				bp += n;
				bytes_to_read -= n;
			}

			if ((bytes_read == 0) && (n == 0)) // connection closed by server
            {
				printf(" Server:  %s closed connection\n", inet_ntoa(server.sin_addr));
				close (sd);
				exit(1);
    		}
			if (n < 0)
			{
				perror ("recv error: ");
				exit(1);
			}

			// Process received message
			switch (mp->type)
			{
				case MSG_ACK:
					printf ("Received ACK\n");
				break;

				case MSG_DATA:	// Incoming data
					//printf ("Message type: %d\n", mp->type);
					printf ("Received: Type : %d, Message: %s\n", mp->type, mp->data);
					fflush(stdout);

					// Reply with ACK
					resp.type = MSG_ACK;
					rp = &resp;
					if ((ns = send (sd, rp, sizeof (resp), 0)) < 0)
					{
						perror ("ACK send error: ");
						exit(1);
					}
				break;

				case MSG_HEARTBEAT:
					// echo it back
					/*if ((ns = send (sd, mp, sizeof(rmsg), 0)) < 0)
					{
						perror ("Echo error: ");
						exit(1);
					}         	*/
				break;
				default:
					printf ("Unknown Message Type: %d\n", (mp->type));
			}
		}
	              heartbeats = 0;
		tv.tv_sec = T0;
	 }

	close (sd);
	return (0);
}
