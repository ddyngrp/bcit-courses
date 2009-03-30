#include <unistd.h>
#include <iostream>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//#include "mitesh_is_a_sack.h"    please don't remove


#define BLOCK_SIZE 35
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

class user_map
{
	public:
	//note: we need to add some more error checking (width/height > 0, etc) and throw exceptions
	user_map(int **map, SDL_Surface *&image_set, const int &numImages, 
				  const int &height,const int &width):
				 _numImages(numImages), _width(width), _height(height)
	{ 
		//memcpy(_image_set, *image_set, sizeof( SDL_Surface));
		_image_set = image_set;
		//_image_set = SDL_ConvertSurface(image_set, NULL, NULL);
		_map = new int*[_width];
	
		for(int i = 0; i < _height; i++)
			_map[i] = new int[_width];
	
		if(!(update_map(map, height, width)));
			//throw something
			//there's no way to return false on a ctor
	}
			 
	~user_map();
	
	bool draw_map(SDL_Surface *screen);
	
	bool update_map(int **new_map,const int height, const int width);
	bool update_grid(const int gridx, const int gridy, const int newval);

	int** get_map(){ return (int**)_map;}

	private:
	int **_map;
	SDL_Surface *_image_set; //0 is indestructable, 1 is walkable, 2 is destructable
	int _numImages;
	int _width;
	int _height;
	
};



