/*---------------------------------------------------------------------------------------------
--      SOURCE FILE:	session.c - Main entry to a new session, takes in the server IP
--									for args.
--            
--      PROGRAM:        TuxBomber
--
--      FUNCTIONS:      int main(int argc, char *argv[])           
--
--      DATE:           March 18, 2009
--
--      DESIGNER:       Jaymz Boilard
--      PROGRAMMER:		Jaymz Boilard
---------------------------------------------------------------------------------------------*/
#include "logic.h"
#include "network.h"

int main(int argc, char *argv[])
{
	int c;
	int makeRecord = 0;
	int sockfd;

	if (argc != 1) 
	{
	    fprintf(stderr, "Usage: [Server IP]\n");
		return 1;
	}

	/* Negotiate connection with server */
	sockfd = connection_setup(argv[1]);
	
	/* Creates an extra process: one reads the socket, and one gets messages from stdin */
	fork_off(sockfd);

	return 0;
}

