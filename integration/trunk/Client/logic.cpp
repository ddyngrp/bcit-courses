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
#include "graphics.h"
#include "logic.h"
#include "DPlaya.h"
#include "user_map.h"
#include "defs.h"
SDL_Surface *screen  = NULL;
extern user_map map;

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
--      NOTES:          Initializes the screen & forks off a process: one gets input from the
--						user by calling handle_input(), and the other listens to the socket for
--						commands incoming from the server & will call the functions needed to
--						redraw the map based on that.
---------------------------------------------------------------------------------------------*/
void fork_off(int tcpSockFd, int udpSockFd, DPlaya allPlayers[])
{
	pid_t pid;
	char sendbuf[MAXLEN], recvbuf[MAXLEN], buf[MAXLEN];
	int r;
	SDL_Event event;
	bool quit = false;
	DPlaya  tmpPlaya;
	unsigned char inMap[17][18];
	
	if((pid = fork()) < 0)
	{
    	perror("Fork");
    	exit(1);
    }
	else if (pid == 0)
	{
	    while( quit == false )
    	{
			/* While we have a user event to handle */
			while( SDL_PollEvent( &event ) )
			{
			    //Handle events for the square
			    handle_input(tcpSockFd, udpSockFd, event);

			    //If the user has Xed out the window
			    if( event.type == SDL_QUIT )
			    {
			        //Quit the program
			        quit = true;
			    }
			}
		}
		
	}
	else
	{
		while(1)
		{
			/* receive data here and redraw map based on it */
			if ((r = recv(tcpSockFd, recvbuf, MAXLEN, 0)) == -1)
			{
				perror("recv call() failed.");
				continue;
			}
			//recvbuf[r] = '\0';
			//memcpy(inMap, recvbuf, sizeof(inMap));
			
			if (recvbuf[0] == TYPE_MOVE)
			{
				//Change the string back into a class
				memcpy((void*)&tmpPlaya, recvbuf + 1, sizeof(DPlaya));
				//We may need to change the id when we create the variable because it may be different.
				allPlayers[tmpPlaya.getDPlayaID()] = tmpPlaya;
				//redrawMap();
			}
			else if (recvbuf[0] == TYPE_EXPLODE)
			{
				memcpy(inMap, recvbuf + 1, sizeof(map));
				map.update_map(inMap, 17, 18);
				map.draw_map(screen);
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
void handle_input(int tcpSockFd, int udpSockFd, SDL_Event event)
{
	char * outBuf;
    struct sockaddr_in server;
    socklen_t servLen;        


    //If a key was released
    if( event.type == SDL_KEYDOWN )
    {
        /* If the user ends, we want to tell the server through the control channel */
		if(event.key.keysym.sym == SDLK_ESCAPE)
		{
			if (send(tcpSockFd,outBuf,strlen(outBuf),0,(struct sockaddr *)&server, sizeof(servLen))==-1)
		        perror("sendto failure");
			exit(1);
		}
			
		/* Regular keystrokes we can send through UDP */
		memcpy(outBuf, (void *)event.key.keysym.sym, sizeof(outBuf));
		if (sendto(udpSockFd,outBuf,strlen(outBuf),0,(struct sockaddr *)&server, sizeof(servLen))==-1)
		{
            perror("sendto failure");
            exit(1);
        }
    }
}

