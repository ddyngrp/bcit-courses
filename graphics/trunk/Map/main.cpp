#include "user_map.h"
#include "init.h"
#include "statusbar.h"

SDL_Surface *screen;

using namespace std;

/*------------------------------------------------------------------------------
-- METHOD:		sdl_init
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	
--
-- PROGRAMMER:	Alin Albu
--
-- INTERFACE:	void sdl_init()
--
-- RETURNS:
--
-- NOTES:
-- Initialize the screen SDL_Surface.
------------------------------------------------------------------------------*/
void sdl_init()
{
    SDL_Init( SDL_INIT_EVERYTHING );

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        //turn video on
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);
    
    //video settings
    screen = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 16, SDL_DOUBLEBUF);

    if (screen == NULL)
    {
        printf("Unable to set video mode: %s\n", SDL_GetError());
        exit(2);
    }

    SDL_WM_SetCaption( "Tux Bomber", NULL ); 
}

/*------------------------------------------------------------------------------
-- METHOD:		sdl_init
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	
--
-- PROGRAMMER:	Tajinder Thind
--
-- INTERFACE:	int main()
--
-- RETURNS:		int
--
-- NOTES:
-- This program tests the map class.
------------------------------------------------------------------------------*/
int main()
{
	unsigned char **map;
	
	sdl_init();
	
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0x00,0xFF,0xFF));
	SDL_Surface *image_set = load_image( "tileset.png" );
	SDL_Surface *background = load_image("snowback.png");

	int numImages = 15;
	int width = 18;
	int height = 17;
	
	map = genRandomMap(height,width);

	//Stuff added from HUD MAIN
	SDL_Surface *tux[8];
	string playerList[8] = {"player 1", "player 2", "player 3", "player 4",
			  "player 5", "player 6", "player 7", "player 8"};
			  
    SDL_Color textColor = { 255,0, 0 };
    
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
        return false;
    
    tux[0] 		= load_image("tux.gif");
    tux[1] 		= load_image("tux.gif");
    tux[2] 		= load_image("tux.gif");
    tux[3] 		= load_image("tux.gif");
    tux[4] 		= load_image("tux.gif");
    tux[5] 		= load_image("tux.gif");
    tux[6] 		= load_image("tux.gif");
    tux[7] 		= load_image("tux.gif");
    
    //HUD members end here
    
	for( int i = 0 , j = -1 ; i < 306; i++)
	{
		if (i %18 == 0 )
		{
			printf("\n");
			j++;
		}
		printf(" %d",map[j][i%18]);
	}
	
	printf("\n");
	fflush(stdout);
	

	user_map uMap(map,image_set,numImages, background,height,width);

	uMap.draw_map(screen);
	
	if(!draw_status_bar(playerList,tux,screen,textColor))
		return 1;
	
	SDL_Flip(screen);
	sleep(5);

	uMap.update_grid(15,15,12);
	uMap.draw_map(screen);
	SDL_Flip(screen);
	sleep(1);
	
	//uMap.~user_map();
	
	
	return 0;
}
/*
int main( int argc, char* args[] )
{
	SDL_Surface *background = NULL;
	SDL_Surface *screen = NULL;
	SDL_Surface *tux[8];
    
    string playerList[8] = {"player 1", "player 2", "player 3", "player 4",
			  "player 5", "player 6", "player 7", "player 8"};
    SDL_Color textColor = { 255,0, 0 };
    //The event structure
	SDL_Event event;

	//The font that's going to be used
	TTF_Font *font = NULL;

    //Quit flag
    bool quit = false;

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;
 
    //If there was an error in setting up the screen
    if((screen = SDL_SetVideoMode( 600,200, 32, SDL_SWSURFACE )) == NULL )
        return false;

    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
        return false;

    //Set the window caption
    SDL_WM_SetCaption( "TTF Test", NULL );

    tux[0] 		= load_image("tux.gif");
    tux[1] 		= load_image("tux.gif");
    tux[2] 		= load_image("tux.gif");
    tux[3] 		= load_image("tux.gif");
    tux[4] 		= load_image("tux.gif");
    tux[5] 		= load_image("tux.gif");
    tux[6] 		= load_image("tux.gif");
    tux[7] 		= load_image("tux.gif");

   
    //If there was a problem in loading the background
    if((background = load_image(BACKGROUND_IMG)) == NULL )
        return false;

    apply_surface(0, 0, background, screen);

	
	if(!draw_status_bar(playerList,tux,screen,textColor))
		return 1;
	
    //Update the screen
    if( SDL_Flip( screen ) == -1 )
        return 1;

    //While the user hasn't quit
    while( quit == false )
    {
        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }
    }
	SDL_FreeSurface( background );

    //Close the font that was used
    TTF_CloseFont( font );

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
    
    //Free surfaces and font then quit SDL_ttf and SDL
    //clean_up();

    return 0;
}
*/
