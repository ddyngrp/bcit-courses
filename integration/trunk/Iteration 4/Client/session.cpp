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
#include "n_serialize.h"


int main(int argc, char *argv[])
{
	SDL_Surface * screen;
	int r, numImagesInSet = 15;
	int tcpSockFd, udpSockFd;
	unsigned char recvbuf[MAXLEN];
	char playerBuf[1024];
	char line[MAXLEN];
	unsigned char ** inMap;
	DPlaya *allPlayers[8];
	//allPlayers[0] = new DPlaya();
	//allPlayers[1] = new DPlaya();
	int i;
	SDL_Surface *imageSet;
	int numClients;
	
	if(!sdl_init(&screen))
		printf("Init Failed\n");

	//allocate the DPlaya array
	for(i = 0; i < 8; i++)
	{
		allPlayers[i] = new DPlaya();
	}
	
	//open the imageset
	imageSet = load_image("Map/img/tileset.png");
	SDL_Surface *background = load_image("Map/img/snowback.png");
	r = SDL_BlitSurface(background,0,screen,0);
	inMap = genRandomMap(17,18);
	printf("Initial map:\n");
	for(int i = 0; i < 17; i++)
	{
		for(int j = 0 ; j < 18; j++)
		{
			inMap[i][j] = 1;
			printf("%d ",inMap[i][j]);
		}
		printf("\n");
	}
	user_map *map = new user_map(inMap, imageSet, numImagesInSet, background, 17,18);
	map->draw_map(screen);
	SDL_Flip(screen);
	sleep(2);

	if (argc != 2)
	{
	    fprintf(stdout, "Usage: [Server IP]\n");
		exit(1);
	}

	//set up control channel
	tcpSockFd = connection_setup(argv[1]);

	// Get the initial Map, copy it to our map, and print it out as we go
	if ((r = recv(tcpSockFd, recvbuf, MAXLEN, 0)) == -1)
	{
		perror("recv call() failed.");
		exit(2);
	}
	printf("Got server's map\n");

	for(int i = 0; i < 17; i++){
		for(int j = 0 ; j < 18; j++){
			inMap[i][j] = recvbuf[17*i + j];
			printf("%3d",inMap[i][j]);
		}
		printf("\n");
	}
	map->update_map(inMap,17,18);
	sleep(1);
	map->draw_map(screen);
	SDL_Flip(screen);
	
	if ((r = recv(tcpSockFd, playerBuf, 1024, 0)) == -1)
	{
		perror("recv call() failed.");
		exit(3);
	}
	numClients = atoi(playerBuf);
	printf("%d clients connected\n\n\n\n\n", numClients);
	

	for(int i = 0; i < numClients; i++)
	{
		memset(playerBuf, 0, 1024);
		if ((r = recv(tcpSockFd, playerBuf, 1024, 0)) == -1)
		{
			perror("recv call() failed.");
			exit(3);
		}
		
		unserialize_player(playerBuf, allPlayers[i]);
		allPlayers[i]->setImage(allPlayers[i]->getImgName());
		allPlayers[i]->refresh(screen);
		SDL_Flip(screen);
		printf("Initial connection - PlayerID =%d  X=%d  Y= %d socket=%d\n",
				allPlayers[i]->getDPlayaID(), allPlayers[i]->getX(), allPlayers[i]->getX(), allPlayers[i]->getSock());
	}


	
	//udpSockFd = start_udp_client(argv[1]);


	// Creates an extra process: one reads the socket, and one gets messages from stdin
	// Note: the tcpSockFd should be the UDP connection once is established
	fork_off(tcpSockFd, udpSockFd, allPlayers, map, screen);


	return 0;
}


