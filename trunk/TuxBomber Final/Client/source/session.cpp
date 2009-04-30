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
#include "../headers/mainHeader.h"
int connection_setup(char * servIp);
int start(int argc, char *argv[], SDL_Surface *screen, OkCancel* exitMenu) {
	int r, numImagesInSet = 15;
	int tcpSockFd, udpSockFd;
	unsigned char recvbuf[MAXLEN];
	char playerBuf[1024];
	unsigned char ** inMap;
	DPlaya *allPlayers[4];
	allPlayers[0] = new DPlaya();
	allPlayers[1] = new DPlaya();
	allPlayers[2] = new DPlaya();
	allPlayers[3] = new DPlaya();
	SDL_Surface *imageSet;
	struct sockaddr_in server;
	int numClients;
	struct ip_mreq mcast;
	if (argc == 3) {
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT - 200, 32,
				SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	} else {
		screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT - 200, 32,
				SDL_SWSURFACE | SDL_DOUBLEBUF);
	}

	//open the imageset
	imageSet = load_image(IMG_SET);
	SDL_Surface *background = load_image(BACKGROUND_IMG);

	r = SDL_BlitSurface(background, 0, screen, 0);
	inMap = genRandomMap(17, 18);
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 18; j++) {
			inMap[i][j] = 2;
		}

	}
	user_map *map = new user_map(inMap, imageSet, numImagesInSet, background,
			17, 18);
	map->draw_map(screen);
	SDL_Flip(screen);
	sleep(2);
	/// Negotiate connection with server
	tcpSockFd = connection_setup(argv[1]);

	// Get the initial Map and list of Players
	if ((r = recv(tcpSockFd, recvbuf, MAXLEN, 0)) == -1) {
		perror("recv call() failed.");
		return 2;
	}

	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 18; j++) {
			inMap[i][j] = recvbuf[17* i + j];

		}
	}

	map->update_map(inMap, 17, 18);
	sleep(1);
	map->draw_map(screen);
	SDL_Flip(screen);

	if ((r = recv(tcpSockFd, playerBuf, 1024, 0)) == -1) {
		perror("recv call() failed.");
		return (3);
	}
	numClients = atoi(playerBuf);

	for (int i = 0; i < numClients; i++) {
		memset(playerBuf, 0, 1024);
		if ((r = recv(tcpSockFd, playerBuf, 1024, 0)) == -1) {
			perror("recv call() failed.");
			return (3);
		}

		unserialize_player(playerBuf, allPlayers[i]);
		allPlayers[i]->setImage(allPlayers[i]->getImgName());
		allPlayers[i]->refresh(screen);
		SDL_Flip(screen);
		printf("Initial connection - PlayerID =%d  X=%d  Y= %d FileName= %s\n",
		allPlayers[i]->getDPlayaID(), allPlayers[i]->getX(),
		allPlayers[i]->getY(), allPlayers[i]->getImgName());
	}

	udpSockFd = start_udp_client(argv[1]);

	struct addrinfo hints, *results;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;

	mcast.imr_multiaddr.s_addr = inet_addr(MCAST_GROUP);
	mcast.imr_interface.s_addr = htonl(INADDR_ANY);

	if (setsockopt(udpSockFd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*) &mcast,
			sizeof(mcast)) < 0) {
		perror("Setsockop failed");
	}
	if (getaddrinfo(argv[1], PORT, &hints, &results) == -1) {
		perror("something bad happened");
		return (1);

	}
	memcpy(&server, (struct sockaddr_in *) results->ai_addr, sizeof(server));

	// Creates an extra process: one reads the socket, and one gets messages from stdin
	// Note: the tcpSockFd should be the UDP connection once is established
	fork_off(tcpSockFd, udpSockFd, &server, allPlayers, map, screen);
	
	// Free resources
	SDL_FreeSurface(imageSet);
	SDL_FreeSurface(background);
	map->user_map::~user_map();
	for (int i = 0; i < 4; i++){
		allPlayers[i]->DPlaya::~DPlaya();
	}


	return 0;
}

