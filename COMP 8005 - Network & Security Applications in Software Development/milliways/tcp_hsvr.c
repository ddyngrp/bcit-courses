/*------------------------------------------------------------------------------------
--	SOURCE FILE:	tcp_hsvr.c -   A simple TCP server example that illustrates how 
--								   to detect a loss of connection with a client.
--
--	PROGRAM:			hsvr.exe
--
--	FUNCTIONS:		Berkeley Socket API
--
--	DATE:				March 13, 2001
--
--	REVISIONS:		(Date and Description)
--
--	DESIGNER:		Aman Abdulla
--
--	PROGRAMMER:		Aman Abdulla
--
--	NOTES:
--	The program will accept TCP connections from client machines. After that it will
--	wait for messages (data) or periodic "heartbeats" to indicate that the client is
--	still connected. When a data message is received the contents are printed out
--	together with the message type. It responds with an ACK to  a data type. If it
--	receives a heartbeat it simply echoes it back.
--
--	If select unblocks due to a timeout and no heartbeat is received it will increment
--	the missed heratbeat counter and continue waiting to wait for two more heartbeats
--	after it will assume a disconnection and terminate if no heartbeats are
--	forthcoming.
-------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "hbeat.h"

int main (int argc, char **argv)
{
	int	nr, ns, bytes_to_read, bytes_read, nready, miss_beats = 0;
	int	sd, new_sd, client_len, port, beats = 0;
	struct	sockaddr_in server, client;
	struct 	timeval tv;
	fd_set 	allset, rset;
	msg_t 	msg, resp, *mp, *rp;
	char     buf[sizeof(msg)], *bp, *hmsg;

	switch(argc)
	{
		case 1:
			port = SERVER_TCP_PORT;	// Use the default port
		break;
		case 2:
			port = atoi(argv[1]);	// Get user specified port
		break;
		default:
			fprintf(stderr, "Usage: %s [port]\n", argv[0]);
			exit(1);
	}

	// Create a stream socket
	if ((sd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror ("Can't create a socket");
		exit(1);
	}

	bzero((char *)&server, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		perror("Can't bind name to socket");
		exit(1);
	}

	// Listen for connections
	// queue up to 5 connect requests
	listen(sd, 5);

    // Wait for connections
   client_len= sizeof(client);
   if ((new_sd = accept (sd, (struct sockaddr *)&client, &client_len)) == -1)
	{
		fprintf(stderr, "Can't accept client\n");
		exit(1);
	}
	printf(" Remote Address:  %s\n", inet_ntoa(client.sin_addr));

	// Set up the socket descriptors for select
	tv.tv_sec = T0 + T1;
	tv.tv_usec = 0;
	FD_ZERO (&allset);
	FD_SET (new_sd, &allset);

	for (;;)
	{
		rset = allset;               // structure assignment

		// wait for something to happen on the newly connected socket
		bytes_read = 0;
		if ((nready = select (new_sd+1, &rset, NULL, NULL, &tv)) < 0)
		{
			perror ("select error: \n");
			exit(1);
		}

		if (nready == 0)	// timer has expired
		{
			if (++miss_beats > 3)
			{
				printf ("Connection broken!\n");
				exit (1);
			}
			printf ("Missed heartbeat #%d\n", miss_beats);
			tv.tv_sec = T1;
			continue;
		}

		if (FD_ISSET(new_sd, &rset))
  		{
			bytes_to_read = sizeof (msg);
         	bp = buf;
         	mp = (msg_t *)buf;

			while (((nr = recv (new_sd, bp, bytes_to_read, 0)) < bytes_to_read) && (nr != 0))
			{
				bytes_read = nr;
				bp += nr;
				bytes_to_read -= nr;
			}

			if (nr < 0)
			{
				perror ("recv error: ");
				exit(1);
			}
			if ((bytes_read == 0) && (nr == 0)) // connection closed by client
            {
				printf(" Remote Address:  %s closed connection\n", inet_ntoa(client.sin_addr));
				close (new_sd);
				exit(1);
			}

		}

		miss_beats = 0;
		tv.tv_sec = T0 + T1;

		// Process the received message
		switch (mp->type)
		{
			case MSG_ACK:
				printf ("received ACK\n");
			break;

			case MSG_DATA:	// Incoming data
				//printf ("Message type: %d\n", mp->type);
				printf ("Received: Type: %d, Message: %s\n", mp->type, mp->data);
				fflush(stdout);
				// Reply with ACK
				resp.type = MSG_ACK;
				rp = &resp;
				if ((ns = send (new_sd, rp, sizeof (resp), 0)) < 0)
				{
					perror ("ACK send error: ");
					exit(1);
				}
			break;
			case MSG_HEARTBEAT:
				// echo it back
				printf ("Received Heartbeat: %d Message : %s\n", beats++, mp->data);
				mp->type = MSG_DATA;
				hmsg = "Server is alive!";
				strcpy (mp->data, hmsg);
				if ((ns = send (new_sd, mp, sizeof(msg), 0)) < 0)
				{
					perror ("Echo error: ");
					exit(1);
				}
			break;
			default:
				printf ("Unknown Message Type: %d\n", mp->type);
		}
	}
	close (new_sd);
	close(sd);
	return(0);
}

