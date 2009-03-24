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
#include "user_map.h"

static user_map map;

int main(int argc, char *argv[])
{
	int c;
	int makeRecord = 0;
	int sockfd;
	int r;
	char recvbuf[MAXLEN];
	DPlaya allPlayers[8];


	if (argc != 2) 
	{
	    fprintf(stderr, "Usage: [Server IP]\n");
		return 1;
	}

	/* Negotiate connection with server */
	sockfd = connection_setup(argv[1]);
	
	/* wait until the user types "ready," will change once we have the menus */
	while(fgets(line, MAXLEN, stdin) != NULL)
	{
		if(!strcmp(line, "ready"))
		{
			send(sockfd, "ready", 6, 0)
			break;
		}
	}
	
	/* Get the initial Map and list of Players */
	if ((r = recv(sockfd, recvbuf, MAXLEN, 0)) == -1)
	{
		perror("recv call() failed.");
		continue;
	}
	memcpy(&map, recvbuf, r);
	if ((r = recv(sockfd, recvbuf, MAXLEN, 0)) == -1)
	{
		perror("recv call() failed.");
		continue;
	}
	memcpy(&allPlayers, recvbuf, r);

	close(sockfd);
	/* TODO Network: Create the UDP socket */
	
	
	/* TODO GRAPHICS: make sure this works.  Note: this will go earlier once we have menus working */
	/* Screen Initializers start */
	SDL_Init( SDL_INIT_EVERYTHING );

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {//turn video on
		printf("Unable to initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);
	screen = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 16, SDL_SWSURFACE );//video settings  //SDL_DOUBLEBUF instead of SDL_SWSURFACE?
	if (screen == NULL) {
		printf("Unable to set video mode: %s\n", SDL_GetError());
		exit(2);
	}
    /* Screen initializers end */
    
    
	
	/* Creates an extra process: one reads the socket, and one gets messages from stdin */
	/* Note: the sockfd should be the UDP connection once is established */
	fork_off(sockfd, allPlayers);

	return 0;
}

