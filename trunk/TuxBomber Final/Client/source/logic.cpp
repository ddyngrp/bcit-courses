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
#include "../headers/mainHeader.h"
#ifdef errprint
#define errprint(x) do { fprintf(stderr,x); } while(0);
#else
#define errprint(x)
#endif

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
void fork_off(int tcpSockFd, int udpSockFd, struct sockaddr_in *server,
		DPlaya * allPlayers[8], user_map *map, SDL_Surface *screen) {
	pid_t pid;
	char recvbuf[1024];
	int r;
	bool quit = false;
	DPlaya *tmpPlaya = new DPlaya();
	int i;
	Uint32 then, now;
	unsigned char **inMap;

	inMap = genRandomMap(17, 18);
	if ((pid = fork()) < 0) {
		perror("Fork");
		return;
	} else if (pid != 0) {
		SDL_Event event;

		while (quit == false) {
			/* While we have a user event to handle */
			while (SDL_PollEvent(&event)) {
				//Handle events for the square
				if (event.type == SDL_KEYDOWN) {
					handle_input(tcpSockFd, udpSockFd, server,event.key.keysym.sym);
					then = SDL_GetTicks();
				}

				//If the user has Xed out the window
				if (event.type == SDL_QUIT) //Quit the program
					quit = true;

			}
			now = SDL_GetTicks();
			if ((now - then) < 75) {
				continue;
			} else {
				then = SDL_GetTicks();
			}

			if (SDL_GetKeyState(NULL)[SDLK_UP]
					&& !SDL_GetKeyState(NULL)[SDLK_DOWN]) {
				handle_input(tcpSockFd, udpSockFd, server, SDLK_UP);

			}
			if (SDL_GetKeyState(NULL)[SDLK_DOWN]
					&& !SDL_GetKeyState(NULL)[SDLK_UP]) {
				handle_input(tcpSockFd, udpSockFd, server, SDLK_DOWN);

			}

			if (SDL_GetKeyState(NULL)[SDLK_LEFT]
					&& !SDL_GetKeyState(NULL)[SDLK_RIGHT]) {
				handle_input(tcpSockFd, udpSockFd, server, SDLK_LEFT);

			}

			if (SDL_GetKeyState(NULL)[SDLK_RIGHT]
					&& !SDL_GetKeyState(NULL)[SDLK_LEFT]) {
				handle_input(tcpSockFd, udpSockFd, server, SDLK_RIGHT);

			}

			//for rapid fire
			SDL_ClearError();
		}
		exit(0);
	} else {
		socklen_t servsize = sizeof(server);
		SDL_Flip(screen);
		while (1) {
			//SDL_Flip(screen);
			/* receive data here and redraw map based on it */
			if ((r = recvfrom(udpSockFd, recvbuf, 1024, 0,
					(struct sockaddr *) server, &servsize)) == -1) {
				perror("recv call() failed Logic.cpp.");
				close(udpSockFd);
				return;
			}
			if (recvbuf[0] == 'G') {
				// GAME OVER, CLOSE SOCKETS
				shutdown(udpSockFd, 2);
				close(udpSockFd);
				shutdown(tcpSockFd, 2);
				close(tcpSockFd);
				return;
			}

			if (recvbuf[0] == 'P' && recvbuf[1] == 'P') {
				unserialize_player(recvbuf + 2, tmpPlaya);

				allPlayers[tmpPlaya->getDPlayaID()]->setX((tmpPlaya->getX()));
				allPlayers[tmpPlaya->getDPlayaID()]->setY((tmpPlaya->getY()));

				map->draw_map(screen);

				fflush(stdout);
				for (i = 0; i < 4; i++) /* XXX */
				{
					if (allPlayers[i]->getX() == 0)
						continue;
					allPlayers[i]->refresh(screen);
				}
				SDL_Flip(screen);
			} else {
				for (i = 0; i < 17; i++)
					for (int j = 0; j < 18; j++)
						inMap[i][j] = recvbuf[17* i + j];

				map->update_map(inMap, 17, 18);
				map->draw_map(screen);
				for (i = 0; i < 4; i++) {
					if (allPlayers[i]->getX() == 0)
						continue;
					allPlayers[i]->refresh(screen);
				}
				SDL_Flip(screen);
			}
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
void handle_input(int tcpSockFd, int udpSockFd, struct sockaddr_in *server,int Key) {
	char outBuf[2];

	if (Key == SDLK_DOWN)
		outBuf[0] = '1';
	else if (Key == SDLK_UP)
		outBuf[0] = '0';
	else if (Key == SDLK_RIGHT)
		outBuf[0] = '3';
	else if (Key == SDLK_LEFT)
		outBuf[0] = '2';
	else if (Key == SDLK_SPACE) {
		outBuf[0] = '4';
	}
	outBuf[1] = '\0';

	if (sendto(udpSockFd, outBuf, 2, 0, (struct sockaddr *) server,
			sizeof(*server)) == -1) {

		exit(0);
		perror("send failed");
	}

}

