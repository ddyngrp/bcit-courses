#ifndef USER_MAP_H

#include <unistd.h>
#include <iostream>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define BLOCK_SIZE 35
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

class user_map
{
	public:
	//note: we need to add some more error checking (width/height > 0, etc) and throw exceptions
	user_map(unsigned char **map, SDL_Surface *&image_set, const int &numImages, 
				  const int &height,const int &width):
				 _numImages(numImages), _width(width), _height(height)
	{ 
		//memcpy(_image_set, *image_set, sizeof( SDL_Surface));
		_image_set = image_set;
		//_image_set = SDL_ConvertSurface(image_set, NULL, NULL);
		_map = new unsigned char*[_width];
	
		for(int i = 0; i < _height; i++)
			_map[i] = new unsigned char[_width];
	
		if(!(update_map(map, height, width)));
			//throw something
			//there's no way to return false on a ctor
	}
			 
	~user_map();
	
	bool draw_map(SDL_Surface *screen);
	
	bool update_map(unsigned char **new_map,const int height, const int width);
	void set_images(SDL_Surface *new_image, const int numImages);

	unsigned char** get_map(){ return (unsigned char**)_map;}

	private:
	unsigned char **_map;
	SDL_Surface *_image_set; //0 is indestructable, 1 is walkable, 2 is destructable
	int _numImages;
	int _width;
	int _height;
	
};

#define USER_MAP_H
#endif
