/*
 * Funcs.cpp
 *
 *  Created on: 24-Mar-2009
 *      Author: d3vil
 */

#include "mainHeader.h"

//initialises the libraries, as well as the screen.
//sets screen size and window caption.
bool init_everything(SDL_Surface* screen)
{
	printf("Init everything Started");
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
    	printf("Init everything Failed\n");
        return false;
    }
    printf("...");
    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE | SDL_DOUBLEBUF );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
    	printf("Init SCREEN Failed\n");
        return false;
    }
    printf("...");
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
    	printf("Init TTF Failed\n");
        return false;
    }
    printf("...");
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
    	printf("Init AUDIO Failed\n");
    	return false;
    }
    printf("...");
    //Set the window caption
    SDL_WM_SetCaption( "Tux Bomber", NULL );
    printf("...");
	SDL_ShowCursor(SDL_ENABLE);
    //If everything initialized fine
	printf("Init everything Done\n");
    return true;
}

SDL_Surface *load_image( std::string filename )
{
	printf("Loading Image: %s \n", filename.c_str());
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    printf("...");
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
    	printf("Optimizing Image: %s \n", filename.c_str());
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
            printf("Optimizing Image: %s Done \n", filename.c_str());
        }else{
        	printf("Optimizing Image: %s Failed \n", filename.c_str());
        }
    }

    //Return the optimized surface
    return optimizedImage;
}



bool optimizeImg( SDL_Surface ** img )
{
	printf("Optimizing Image: \n");
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    if( img != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(*img);

        //If the surface was optimized
        if( optimizedImage != NULL )
        {

            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
            //Free the old surface
            //SDL_FreeSurface(img);
            *img = new SDL_Surface((SDL_Surface&) *optimizedImage);
            printf("Optimizing Image: Done \n");
        }else{
           	printf("Optimizing Image: Failed \n");
        }

    }


    return false;
}

//blits two images together, with the source being pasted on the destination starting at x,y
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	printf("Blitting Surface!");
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
    printf("Blitting Surface Done!");
}


