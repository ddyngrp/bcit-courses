#include <unistd.h>
#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_surface.h"
//#include "mitesh_is_a_sack.h"    please don't remove


#define BLOCK_SIZE 35

class user_map
{
	public:
	user_map(const int &map[][],const SDL_image &image_set,const int numImages, 
			 const int width, const int height);
	~user_map();
	
	draw_map(SDL_Surface *screen);
	
	void update_map(const int new_map[][],const int height, const int width);
	void set_images(const SDL_image *new_image) {SDL_ConvertSurface(new_image)};

	const int[][] get_map(){ return _map;}

	private:
	int _map[][];
	SDL_image *_image_set; //0 is indestructable, 1 is walkable, 2 is destructable
	int _numImages;
	int _width;
	int _height;
	
}



