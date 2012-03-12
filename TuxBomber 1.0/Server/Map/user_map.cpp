#include "user_map.h"

/*------------------------------------------------------------------------------
-- METHOD:		~user_map
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	
--
-- PROGRAMMER:	Tajinder Thind & Clay Sayer
--
-- INTERFACE:	user_map::~user_map()
--
-- RETURNS:
--
-- NOTES:
-- Destructor for user_map. Deletes map and free's the SDL_Surface data members.
------------------------------------------------------------------------------*/
user_map::~user_map()
{
	delete[] _map;
	SDL_FreeSurface(_image_set);
	SDL_FreeSurface(_background);
}

/*------------------------------------------------------------------------------
-- METHOD:		update_map
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	
--
-- PROGRAMMER:	Tajinder Thind & Clay Sayer
--
-- INTERFACE:	bool user_map::update_map(unsigned char **new_map, 
--						const int height, const int width) 
--
-- RETURNS:		bool.
--
-- NOTES:
-- Change the object datamember _map to a new map. Height and width must be the 
-- same as the current demensions of the current map data member. Returns false 
-- if the dimensions of the new map are not the same as current map or if any of
-- the values in the array are not valid.
------------------------------------------------------------------------------*/
bool user_map::update_map(unsigned char **new_map, const int height, 
							const int width) 
{
	int i, j;
	if ((height != _height) || (width != _width))
		 return false;

	for (i = 0; i < _height; i++)
	{
		for (j = 0; j < _width; j++)
		{
			//checks that the new value is within the bounds
			if((new_map[i][j] > _numImages) || (new_map[i][j] < 0))
				return false;
		}
	}

	for (i = 0; i < _height; i++)
		for (j = 0; j < _width; j++)
			_map[i][j] = new_map[i][j];

	return true;
}

/*------------------------------------------------------------------------------
-- METHOD:		update_grid
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	
--
-- PROGRAMMER:	Henry Berrisford
--
-- INTERFACE:	bool user_map::update_grid(const int gridx, const int gridy, 
--											const int newval)
--
-- RETURNS:		bool.
--
-- NOTES:		
-- Update a specific value in the _map 2D array in index [gridx][gridy] with 
-- newval. Return true of the method successfuly updated the value in the 
-- specified index or false if their is an error.
------------------------------------------------------------------------------*/
bool user_map::update_grid(const int gridx, const int gridy, const int newval)
{
	if (gridx >= _width)
		return false;
	if (gridy >= _height)
		return false;
	if (newval >= _numImages)
		return false;

	_map[gridy][gridx] = newval;
	return true;	
}

/*------------------------------------------------------------------------------
-- METHOD:		draw_map
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:	
--
-- PROGRAMMER:	Tajinder Thind, Clay Sayer, Alin Albu
--
-- INTERFACE:	bool user_map::draw_map(SDL_Surface *screen)
--
-- RETURNS:		bool.
--
-- NOTES:
-- Draws the map on the specified SDL_Surface (screen). Returns true if the 
-- method completed successfuly. False if it failed. Don't forget to call 
-- 'SDL_Flip(SDL_Surface)' to display the map on the screen ;-)
------------------------------------------------------------------------------*/
bool user_map::draw_map(SDL_Surface *screen)
{
	SDL_Rect srcTemp, destTemp;

	srcTemp.x = 0;
	srcTemp.w = srcTemp.h = BLOCK_SIZE;
	destTemp.w = srcTemp.h = BLOCK_SIZE;

	if(SDL_BlitSurface(_background, 0 , screen, 0))
	{
			return false;
	}		
	for(int i = 0; i < _height; i++)
	{
		//sets which row we're going to draw
		destTemp.y = BLOCK_SIZE * i;
		for(int j = 0; j < _width; j++)
		{
			//select which image to display from image set
			srcTemp.y = BLOCK_SIZE * _map[i][j];
			//sets which column we're going to draw
			destTemp.x = BLOCK_SIZE * j;
			
			if(SDL_BlitSurface(_image_set, &srcTemp, screen, &destTemp))
			{
				return false;
			}
		}
	}	

	return true;
}
