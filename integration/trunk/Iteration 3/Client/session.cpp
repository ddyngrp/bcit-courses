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
	allPlayers[0] = new DPlaya();
	allPlayers[1] = new DPlaya();
	SDL_Surface *imageSet;
	if(!sdl_init(&screen))
	{
		printf("Init Failed\n");
	}

	//open the imageset
	imageSet = load_image("Map/img/tileset.png");
	SDL_Surface *background = load_image("Map/img/snowback.png");

	r = SDL_BlitSurface(background,0,screen,0);
	inMap = genRandomMap(17,18);
	printf("map\n");
	for(int i = 0; i < 17; i++){
			for(int j = 0 ; j < 18; j++){
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

   //TODO take out comment
	/// Negotiate connection with server
	tcpSockFd = connection_setup(argv[1]);

	/// wait until the user types "ready," will change once we have the menus
	/*while(fgets(line, MAXLEN, stdin) != NULL)
	{
		if(!strcmp(line, "ready\n"))
		{
			r = send(tcpSockFd, "ready", MAXLEN, 0);
			break;
		}
	}*/
			printf("got here!\n");
	// Get the initial Map and list of Players
	if ((r = recv(tcpSockFd, recvbuf, MAXLEN, 0)) == -1)
	{
		perror("recv call() failed.");
		exit(2);
	}
	printf("got here! rith r = %d\n",r);


	//memcpy(*inMap, recvbuf, (17 * 18));
	printf("2nd map\n");

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
	unserialize_player(playerBuf, allPlayers[0]);
	allPlayers[0]->setImage(allPlayers[0]->getImgName());
	allPlayers[0]->refresh(screen);
	SDL_Flip(screen);
	
	if ((r = recv(tcpSockFd, playerBuf, 1024, 0)) == -1)
	{
		perror("recv call() failed.");
		exit(3);
	}

	unserialize_player(playerBuf, allPlayers[1]);
	allPlayers[1]->setImage(allPlayers[1]->getImgName());
	allPlayers[1]->refresh(screen);
	printf("PlayerID =%d  X=%d  Y= %d socket=%d",allPlayers[1]->getDPlayaID(), allPlayers[1]->getX(), allPlayers[1]->getX(), allPlayers[1]->getSock());
	SDL_Flip(screen);


	
	udpSockFd = start_udp_client(argv[1]);


	// Creates an extra process: one reads the socket, and one gets messages from stdin
	// Note: the tcpSockFd should be the UDP connection once is established
	fork_off(tcpSockFd, udpSockFd, allPlayers, map, screen);


	return 0;
}


