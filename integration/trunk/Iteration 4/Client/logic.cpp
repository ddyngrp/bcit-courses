/*---------------------------------------------------------------------------------------------
 --      SOURCE FILE:	logic.cpp - Main processor of what the client needs to do, may have
 --									some overlap with the network and graphics processing.
 --
 --      PROGRAM:        TuxBomber
 --
 --      FUNCTIONS:      void fork_off(int tcpSockFd)
 --                      void handle_input()
 --
 --      REVISIONS:
 --
 --      DESIGNER:       Jaymz Boilard
 --      PROGRAMMER:		Jaymz Boilard
 ---------------------------------------------------------------------------------------------*/
#include "logic.h"
#include "Map/user_map.h"
#include "defs.h"
#include "n_serialize.h"
#include <signal.h>
/*---------------------------------------------------------------------------------------------
 --      FUNCTION: 		fork_off
 --
 --      REVISIONS:
 --
 --      DESIGNER:       Jaymz Boilard
 --      PROGRAMMER:     Jaymz Boilard
 --
 --      INTERFACE:      void fork_off(int tcpSockFd, int makeRecord)
 --
 --      RETURNS:        void
 --
 --      NOTES:         Initializes the screen & forks off a process: one gets input from the
 --						user by calling handle_input(), and the other listens to the socket for
 --						commands incoming from the server & will call the functions needed to
 --						redraw the map based on that.
 ---------------------------------------------------------------------------------------------*/
void fork_off(int tcpSockFd, int udpSockFd, DPlaya * allPlayers[8], user_map *map, SDL_Surface *screen)
{
	pid_t pid;
	char recvbuf[1024];
	int r;
	SDL_Event event;
	bool quit = false;
	DPlaya *tmpPlaya = new DPlaya();
	unsigned char **inMap;
	int i;
	Uint32 then, now;
	if ((pid = fork()) < 0) {
		perror("Fork");
		exit(1);
	} else if (pid != 0) {
		SDL_Event event;
		while (quit == false) {
			/* While we have a user event to handle */
			while (SDL_PollEvent(&event)) {
				//Handle events for the square
				if (event.type == SDL_KEYDOWN) {
					handle_input(tcpSockFd, udpSockFd, event.key.keysym.sym);
					printf("keyDown\n");
					then = SDL_GetTicks();
				}

				//If the user has Xed out the window
				if (event.type == SDL_QUIT) //Quit the program
					quit = true;

			}
			now = SDL_GetTicks();
			if((now - then) < 50){
				continue;
			}else{
				then = SDL_GetTicks();
			}



			if (SDL_GetKeyState(NULL)[SDLK_UP]
					&& !SDL_GetKeyState(NULL)[SDLK_DOWN]) {
				handle_input(tcpSockFd, udpSockFd, SDLK_UP);


			}
			if (SDL_GetKeyState(NULL)[SDLK_DOWN]
					&& !SDL_GetKeyState(NULL)[SDLK_UP]) {
				handle_input(tcpSockFd, udpSockFd, SDLK_DOWN);

			}

			if ( SDL_GetKeyState(NULL)[SDLK_LEFT]
					&& !SDL_GetKeyState(NULL)[SDLK_RIGHT]) {
				handle_input(tcpSockFd, udpSockFd, SDLK_LEFT);

			}

			if (SDL_GetKeyState(NULL)[SDLK_RIGHT]
					&& !SDL_GetKeyState(NULL)[SDLK_LEFT]) {
				handle_input(tcpSockFd, udpSockFd, SDLK_RIGHT);

			}

			//for rapid fire

			SDL_ClearError();
		}
		kill(pid, SIGKILL);
	}else {
		while (1) {
			//memset(recvbuf, 0, 1024);
			printf("PlayerID =%d  X=%d  Y= %d socket=%d\n",allPlayers[0]->getDPlayaID(), allPlayers[0]->getX(), allPlayers[0]->getX(), allPlayers[0]->getSock());

			/* receive data here and redraw map based on it */
			if ((r = recv(tcpSockFd, recvbuf, 1024, 0)) == -1) {
				perror("recv call() failed.");
				continue;
			}
			//printf("%d\n", r);

			unserialize_player(recvbuf, tmpPlaya);
			//unserialize_player(recvbuf, allPlayers[tmpPlaya->getDPlayaID()]);
			allPlayers[tmpPlaya->getDPlayaID()]->setX( (tmpPlaya->getX()) );
			allPlayers[tmpPlaya->getDPlayaID()]->setY( (tmpPlaya->getY()) );
			//allPlayers[tmpPlaya->getDPlayaID()]->setImage(allPlayers[tmpPlaya->getDPlayaID()]->getImgName());
			//printf("%d", allPlayers[tmpPlaya->getDPlayaID()]->getX());
			map->draw_map(screen);
			for(i = 0; i < 4;i++)
			{
				allPlayers[i]->refresh(screen);
			}
			SDL_Flip(screen);

		}
	}
}


/*---------------------------------------------------------------------------------------------
 --      FUNCTION: 		handle_input
 --
 --      REVISIONS:      April 2 - Changed sendto() to send() for the SDLK_ESCAPE since it's TCP
 --
 --      DESIGNER:       Jaymz Boilard
 --      PROGRAMMER:     Jaymz Boilard
 --
 --      INTERFACE:      void handle_input()
 --
 --      RETURNS:        void
 --
 --      NOTES:          Initializes the screen & forks off a process: one gets input from the
 --						user by calling handle_input(), and the other listens to the socket for
 --						commands incoming from the server & will call the functions needed to
 --						redraw the map based on that.
 ---------------------------------------------------------------------------------------------*/
void handle_input(int tcpSockFd, int udpSockFd, int Key) {
	char outBuf[2];
	struct sockaddr_in server;
	socklen_t servLen;
	
	/* If the user ends, we want to tell the server through the control channel */
	/*if (Key == SDLK_ESCAPE) {
		if (send(tcpSockFd, outBuf, strlen(outBuf), 0) == -1)
			perror("sendto failure");
		exit(1);unserialize_player(recvbuf, allPlayers[0]);
	}*/
	if(Key == SDLK_DOWN)
		outBuf[0] = '1';
	else if(Key == SDLK_UP)
		outBuf[0] = '0';
	else if(Key == SDLK_RIGHT)
		outBuf[0] = '3';
	else if(Key == SDLK_LEFT)
		outBuf[0] = '2';
	else if(Key == SDLK_SPACE)
	{
	}
	outBuf[1] = '\0';
	if(send(tcpSockFd, outBuf, strlen(outBuf), 0) == -1)
	{
		perror("send failed");
	}
	/* Regular keystrokes we can send through UDP */
		/*if (sendto(udpSockFd, outBuf, strlen(outBuf), 0,(struct sockaddr *) &server, sizeof(servLen)) == -1) {
			perror("sendto failure");
			exit(1);
		}*/
}

