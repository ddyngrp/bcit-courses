#include "user_map.h"
#include "init.h"

SDL_Surface *screen;

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
	SDL_Flip(screen);
	sleep(5);

	uMap.update_grid(15,15,12);
	uMap.draw_map(screen);
	SDL_Flip(screen);
	sleep(1);
	
	uMap.~user_map();
	
	
	return 0;
}


