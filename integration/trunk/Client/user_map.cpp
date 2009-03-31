#include "user_map.h"

user_map::~user_map()
{
	delete[] _map;
	SDL_FreeSurface(_image_set);
}

//note: Strong Exception Safety! If invalid data is found, _map will contain old data!
bool user_map::update_map(unsigned char new_map[17][18], const int height, const int width) 
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

bool user_map::update_grid(const int gridx, const int gridy, const int newval){
	if (gridx >= _width)
		return false;
	if (gridy >= _height)
		return false;
	if (newval >= _numImages)
		return false;

	_map[gridy][gridx] = newval;
	return true;	
}

bool user_map::draw_map(SDL_Surface *screen)
{
	SDL_Rect srcTemp, destTemp;

	srcTemp.x = 0;
	srcTemp.w = srcTemp.h = BLOCK_SIZE;
	destTemp.w = srcTemp.h = BLOCK_SIZE;

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
				return false;
		}
	}

	SDL_Flip(screen);	

	return true;
}

