/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

void draw_status_bar(std::string players[],SDL_Surface *tux[],SDL_Surface *background,SDL_Surface *screen,TTF_Font *font ,SDL_Color textColor );

using namespace std;


SDL_Surface *load_image( std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optiSDL_Surface *background = NULL;
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

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
    if((background = load_image( "background1.jpg" )) == NULL )
        return false;

    //If there was an error in loading the font
    if((font = TTF_OpenFont( "ActionIs.ttf", 25)) == NULL )
        return false;

    apply_surface( 0, 0, background, screen );

	
	draw_status_bar(playerList,tux,background,screen,font,textColor);	
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


void draw_status_bar(std::string players[],SDL_Surface *tux[],SDL_Surface *background,SDL_Surface *screen,TTF_Font *font ,SDL_Color textColor )
{
	SDL_Surface *message;
	int x =30,y=1;
	for(int i =0; i < 8; i++)
	{	
		if(i % 2 == 0 && i != 0)
		{
			x += 150;
			y = 1;	
		}
		message = TTF_RenderText_Solid( font,players[i].c_str() , textColor);
		apply_surface(x,y ,message, screen );
		apply_surface(x-30,y,tux[i],screen);
		y *= 50;
	}
	
	    SDL_FreeSurface( message );
}
