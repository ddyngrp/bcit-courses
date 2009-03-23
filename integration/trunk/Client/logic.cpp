/*---------------------------------------------------------------------------------------------
--      SOURCE FILE:	logic.cpp - Main processor of what the client needs to do, may have
--									some overlap with the network and graphics processing.
--            
--      PROGRAM:        TuxBomber 
--
--      FUNCTIONS:      void fork_off(int sockfd)
--                      void handle_input()      
--
--      REVISIONS:      
--
--      DESIGNER:       Jaymz Boilard
--      PROGRAMMER:		Jaymz Boilard
---------------------------------------------------------------------------------------------*/
#include "graphics.h"
#include "logic.h"
SDL_Surface *screen  = NULL;

/*---------------------------------------------------------------------------------------------
--      FUNCTION: 		fork_off
--
--      REVISIONS:      
--
--      DESIGNER:       Jaymz Boilard
--      PROGRAMMER:     Jaymz Boilard
--
--      INTERFACE:      void fork_off(int sockfd, int makeRecord)
--
--      RETURNS:        void
--
--      NOTES:          Initializes the screen & forks off a process: one gets input from the
--						user by calling handle_input(), and the other listens to the socket for
--						commands incoming from the server & will call the functions needed to
--						redraw the map based on that.
---------------------------------------------------------------------------------------------*/
void fork_off(int sockfd)
{
	struct in_addr in;
	pid_t pid;
	char sendbuf[MAXLEN], recvbuf[MAXLEN], buf[MAXLEN];
	int r;
	struct sockaddr_in clientInfo;
	socklen_t clientLen;	
	unsigned int len;
	struct sigaction sa;
	SDL_Event event;
	bool quit = false;
	
	/* TODO NETWORK: any of this stuff needed? Remove whatever's no longer necessary*/
	clientLen = sizeof(clientInfo);
	len = sizeof(clientInfo);
	getsockname(sockfd,(struct sockaddr *)&clientInfo,&len);
	memset(&in,0,sizeof(in));
	in.s_addr = clientInfo.sin_addr.s_addr;
    /* TODO END */
    
    
	
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
			    handle_input(event);

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
			if ((r = recv(sockfd, recvbuf, MAXLEN, 0)) == -1)
			{
				perror("recv call() failed.");
				continue;
			}
			//recvbuf[r] = '\0';
			
			if (recbuf[0] == TYPE_MOVE)
			{
				redrawMap();
			}
			else if (recvbuf[0] == PLAYERMOVE)
			{

            }		
			
			
		}
	}
}

/*---------------------------------------------------------------------------------------------
--      FUNCTION: 		handle_input
--
--      REVISIONS:      
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
void handle_input(SDL_Event event)
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: /* TODO network: send corresponding messages through the network.  defs.h has the values of each key */ break;
            case SDLK_DOWN: 						 	    break;
            case SDLK_LEFT: 							    break;
            case SDLK_RIGHT:							    break;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: /* send corresponding messages through the network */	 break;
            case SDLK_DOWN:									 break;
            case SDLK_LEFT: 								 break;
            case SDLK_RIGHT:								 break;
        }
    }
}

