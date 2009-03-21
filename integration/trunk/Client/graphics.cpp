/*---------------------------------------------------------------------------------------------
--      SOURCE FILE:	graphics.cpp - Taken from the online code samples and modified them
--									   to not use any global variables.  Also has Colby's
--									   fire-drawing functions.  Someone from Graphics who
--									   understands these functions better should fill out the
--									   headers.
--            
--      PROGRAM:        TuxBomber 
--
--      FUNCTIONS:      void server_main()
--                      int new_client(int nfds, int listener, fd_set * all_fds)       
--
--      REVISIONS:      
--
--      DESIGNER:     Jaymz Boilard, Colby Last & Lazy Foo Productions 
--      PROGRAMMER:	  Jaymz Boilard, Colby Last & Lazy Foo Productions
---------------------------------------------------------------------------------------------*/
#include "player.h"
#include "graphics.h"
extern SDL_Surface *screen;
using namespace std;

//loads the images
SDL_Surface *load_image(string filename)
{
	SDL_Surface* loadedImage = NULL; 
	SDL_Surface* optimizedImage = NULL;
	char a[64];

	loadedImage = IMG_Load(filename.c_str());

	if( loadedImage != NULL )
	{ 
		printf("here: %s", filename.c_str());
		fflush(stdout);
		optimizedImage = SDL_DisplayFormat( loadedImage ); 

		SDL_FreeSurface( loadedImage ); 

		if( optimizedImage != NULL )
		{
			//Color key surface
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
		}
	} 

	return optimizedImage;
}

/*---------------------------------------------------------------------------------------------
--      FUNCTION: 		draw_fire
--
--      REVISIONS:      
--
--      DESIGNER:       Colby Last
--      PROGRAMMER:     Colby Last
--
--      INTERFACE:      bool draw_fire(fire f, SDL_Surface * screen)
--
--      RETURNS:        void
--
--      NOTES:          I don't know what this does, the garphics team will have to fill out 
--						this header.
---------------------------------------------------------------------------------------------*/
bool draw_fire(fire f, SDL_Surface * screen)
{
	SDL_Surface *imgCenter;
	SDL_Surface *imgVertical;
	SDL_Surface *imgHorizontal;
	SDL_Surface *imgLeftEnd;
	SDL_Surface *imgRightEnd;
	SDL_Surface *imgTopEnd;
	SDL_Surface *imgBottomEnd;
	SDL_Surface *temp;

	char fName[50] = "center.xcf\0";

	imgCenter = load_image(fName);
	SDL_Rect dest;

	apply_surface((f.center.x*TILE), (f.center.y*TILE), imgCenter, screen);
	return true;
}

//shows images on screen
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    SDL_Rect* clip = NULL;
    //Holds offsets
    SDL_Rect offset;
    SDL_Rect src;
    src.w = TILE;
    src.h = TILE;
    src.x = 0;
    src.y = 0;

    //Get offsets
    offset.x = x;
    offset.y = y;
    offset.w = TILE;
    offset.h = TILE;

    //Blit
    SDL_BlitSurface( source, &src, destination, &offset );
}

void DrawMap(int map[11][17], SDL_Surface *wall2, SDL_Surface *screen)
{
	int i, j;

	for(i = 0; i < GRIDSIZE; i++)
	{
		for(j = 0; j < GRIDSIZE; j++)
		{
			if(map[i][j] == WALL)
			apply_surface( i * TILE, j * TILE, wall2, screen);			
		}
	}
}

bool init(SDL_Surface *screen)
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )        return false;

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Move the Player", NULL );

    //If everything initialized fine
    return true;
}

