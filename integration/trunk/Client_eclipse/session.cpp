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
#include "Map/user_map.h"
#include "defs.h"
SDL_Surface * screen;

int main(int argc, char *argv[])
{
	int c, r, numImagesInSet = 15;
	int makeRecord = 0;
	int tcpSockFd, udpSockFd;
	char recvbuf[MAXLEN], line[MAXLEN];
	unsigned char ** inMap;
	DPlaya allPlayers[8];
	SDL_Surface *imageSet;
	if(!sdl_init(&screen))
	{
		printf("OH SHIT");
	}

	//open the imageset
	imageSet = load_image("Map/img/tileset.png");
	SDL_Surface *background = load_image("Map/img/snowback.png");

	r = SDL_BlitSurface(background,0,screen,0);


	//memset(inMap, GRID_UBLOCK, 289); //fill the map with blocks

	inMap = genRandomMap(17,18);

	user_map *map = new user_map(inMap, imageSet, numImagesInSet, background, 17,18);
	//map.update_map(inMap, 17, 18);   //initial map
	map->draw_map(screen);
	SDL_Flip(screen);
	sleep(2);

	if (argc != 2)
	{
	    fprintf(stdout, "Usage: [Server IP]\n");
		exit(1);
	}

/* TODO take out comment
	/// Negotiate connection with server
	tcpSockFd = connection_setup(argv[1]);

	/// wait until the user types "ready," will change once we have the menus
	while(fgets(line, MAXLEN, stdin) != NULL)
	{
		if(!strcmp(line, "ready"))
		{
			send(tcpSockFd, "ready", 6, 0);
			break;
		}
	}

	// Get the initial Map and list of Players
	if ((r = recv(tcpSockFd, recvbuf, MAXLEN, 0)) == -1)
	{
		perror("recv call() failed.");
		exit(2);
	}
	memcpy(&inMap, recvbuf, r);
	if ((r = recv(tcpSockFd, recvbuf, MAXLEN, 0)) == -1)
	{
		perror("recv call() failed.");
		exit(3);
	}
	memcpy(&allPlayers, recvbuf, r);
	//close(tcpSockFd);

	udpSockFd = start_udp_client(argv[1]);


	// Creates an extra process: one reads the socket, and one gets messages from stdin
	// Note: the tcpSockFd should be the UDP connection once is established
	fork_off(tcpSockFd, udpSockFd, allPlayers); */


	return 0;
}


