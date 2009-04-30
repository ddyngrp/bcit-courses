#ifndef USER_MAP
#define USER_MAP

#include "mainHeader.h"

class user_map
{
	public:

/*------------------------------------------------------------------------------
-- METHOD:		user_map
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:	Tajinder Thind & Clay Sayer
--
-- INTERFACE:	user_map(unsigned char **map, SDL_Surface *&image_set,
--					const int &numImages, SDL_Surface * background,
--					const int &height,const int &width):
--					_numImages(numImages), _width(width), _height(height)
--
-- RETURNS:
--
-- NOTES:
-- Constructor for user map.
------------------------------------------------------------------------------*/
	user_map(unsigned char **map, SDL_Surface *&image_set,
				const int &numImages, SDL_Surface * background,
				const int &height,const int &width):
				 _numImages(numImages), _width(width), _height(height)
	{
		//memcpy(_image_set, *image_set, sizeof( SDL_Surface));
		_image_set = image_set;
		//_image_set = SDL_ConvertSurface(image_set, NULL, NULL);
		_map = new unsigned char*[_width];

		for(int i = 0; i < _height; i++)
			_map[i] = new unsigned char[_width];

		update_map(map, height, width);
			//throw something
			//there's no way to return false on a ctor
		_background = background;
	}

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
	~user_map();

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
	bool update_map(unsigned char **new_map,const int height, const int width);

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
-- 									const int newval)
--
-- RETURNS:		bool.
--
-- NOTES:
-- Update a specific value in the _map 2D array in index [gridx][gridy] with
-- newval. Return true of the method successfuly updated the value in the
-- specified index or false if their is an error.
------------------------------------------------------------------------------*/
	bool update_grid(const int gridx, const int gridy, const int newval);

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
	bool draw_map(SDL_Surface *screen);

/*------------------------------------------------------------------------------
-- METHOD:		get_map
--
-- DATE:		March 16, 2009
--
-- REVISIONS:
--
-- DESIGNER:
--
-- PROGRAMMER:	Tajinder Thind, Clay Sayer
--
-- INTERFACE:	unsigned char** get_map()
--
-- RETURNS:		unsigned char**
--
-- NOTES:
-- Returns the _map data member.
----------------------------------------------------------------------*/
	unsigned char** get_map(){ return (unsigned char**)_map;}

	private:
	unsigned char **_map;
	SDL_Surface *_image_set;
	int _numImages;
	int _width;
	int _height;
	SDL_Surface * _background;

};

#endif

