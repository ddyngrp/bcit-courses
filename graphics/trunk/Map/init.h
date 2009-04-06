#ifndef INIT_H
#define INIT_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
/*----------------------------------------------------------------------
-- METHOD:		genRandomMap
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	Alin Albu
--
-- PROGRAMMER:	Alin Albu
--
-- INTERFACE:	unsigned char** genRandomMap(int rowNum, int colNum)
--
-- RETURNS:		void.
--
-- NOTES:
-- Generates a random map contained within a 2D array with sizes
-- specified by rowNum and colNum which are number of rows and columns
-- respectivly. 
----------------------------------------------------------------------*/
unsigned char** genRandomMap(int rowNum, int colNum);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
void sdl_init(SDL_Surface * screen);
/*----------------------------------------------------------------------
-- METHOD:		load_image
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	Alin Albu
--
-- PROGRAMMER:	Alin Albu
--
-- INTERFACE:	SDL_Surface *load_image( std::string filename )
--
-- RETURNS:		SDL_Surface *
--
-- NOTES:
-- Load an image into an SDL_Surface and then optimize and set 
-- transparancy.
----------------------------------------------------------------------*/
SDL_Surface *load_image( std::string filename );



#endif
