/*
 * main.cpp
 * Uploads and runs the game menu.
 *
 *  Created on: 24-Mar-2009
 *      Author: d3vil aka Alin Albu
 */
//TODO proper comments

#include "mainHeader.h"
#include "MainMenu2.h"
#include "OkCancel.h"

int main( int argc, char* args[] )
{
    //fullscreen flag
	int i, width, height;
	int mmresult, ocresult; //MainMenu result and OkCancel menu result
	bool fulls = false, exitGame = false;
	Uint32 countStart,fps;
    SDL_Event event;
    //filenames for options in main menu
    std::string mainOpts[MainMenu2::num_options_]={"img/MainBackgroundv3.png","img/ExitBackgroundv3.png",
													"img/SelPlayerBackgroundv3.png","img/StartBackgroundv3.png"
														,"img/OPTBackgroundv3.png"};
    //filenames for OkCnacel exit menu
    std::string exitOpts[OkCancel::num_options_] = {"img/OK_CANCEL_EXIT.xcf","img/OK_EXIT.xcf","img/CANCEL_EXIT.xcf"};
    SDL_Surface *screen;

    //init SDL
    if (!init_everything(screen)){return 1;}
    //set the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32,	SDL_SWSURFACE | SDL_DOUBLEBUF);
    printf("Done init all Loading main...\n");

    //create main menu and exit dialog
    MainMenu2 main(mainOpts, "sound/mc.ogg","sound/click.wav", screen);
    OkCancel  exitMenu(exitOpts, "sound/click.wav", screen);

	mmresult = 0;
	ocresult = 0;
	exitGame = false;

	while(!exitGame)
	{
		mmresult = main.start(event);
		switch (mmresult)
		{
		case 0: //error
			exitGame = true;
			break;
		case 1:
			//load ok_cancel dialog
			fps = 50;
			height = exitMenu.getBackground(0)->h;
			for(i = 0 ; i < fps; i++)
			{
				countStart = SDL_GetTicks();
				if(SDL_GetTicks() - countStart < 500 / fps)
						SDL_Delay((500/fps) - (SDL_GetTicks() - countStart));
				main.move(0,0);
				exitMenu.move(0, ((250 + height)* i/(int)fps) - height);
				SDL_Flip(screen);
				countStart = SDL_GetTicks();
			}
			main.move(0,0);
			ocresult = exitMenu.start(event);
			switch (ocresult)
			{
			case 1:
				exitGame = true;
				break;
			case 2:
				for(i = 0 ; i < fps; i++)
				{
					countStart = SDL_GetTicks();
					if(SDL_GetTicks() - countStart < 500 / fps)
							SDL_Delay((500/fps) - (SDL_GetTicks() - countStart));
					main.move(0,0);
					exitMenu.move(0, ((250 + height)* (fps - i)/(int)fps) - height);
					SDL_Flip(screen);
					countStart = SDL_GetTicks();
				}
				exitGame = false;
				break;
			}
		case 2:
			//load player options
		case 3:
			//load start game
		case 4:
			//load game options
			break;
		case 'f': //full screen
			fulls = !fulls;
			screen = fulls?SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32,	SDL_SWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN):
							SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32,	SDL_SWSURFACE | SDL_DOUBLEBUF );
			break;
		}
	}

	printf("Done all\n");
   return 0;
}
