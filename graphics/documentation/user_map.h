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


user_map::user_map(const int &map[][],const SDL_image &image_set,const int numImages, 
			 const int width, const int height):
			 _numImages(numImages), _width(width), _height(height)
{ 
	_image_set = SDL_ConvertSurface(image_set);

	if(!(this.update_map(map, width, height)))
		//throw something
		//there's no way to return false on a ctor
}

user_map::~user_map()
{
	SDL_FreeSurface(_image_set);
}

//note: Strong Exception Safety! If invalid data is found, _map will contain old data!
bool user_map::update_map(const int new_map[][], const int height, const int width) 
{
	int i, j;
	int temp[_width][_height];
	if ((height != _height) || (width != _width))
		 return false;

	for(i = 0; i < _width; i++)
		for(j = 0; j < _width; j++)
			temp[i][j] = _map[i][j];

	for (i = 0; i < _width; i++)
	{
		for (j = 0; j < _height; j++)
		{
			//checks that the new value is within the bounds
			if(new_map[i][j] > _numImages || new_map[i][j] < 0)
				return false;
			temp[i][j] = new_map[i][j];
		}
	}
	_map = temp;
	return true;
}

bool user_map::draw_map(SDL_Surface *screen)
{
	SDL_Rect srcTemp, destTemp;

	srcTemp.x = 0;
	srcTemp.w = srcTemp.h = BLOCK_SIZE;
	destTemp.w = srcTemp.h = BLOCK_SIZE;

	for(int i = 0; i < _width; i++)
	{
		//sets which row we're going to draw
		destTemp.y = BLOCK_SIZE * i;
		for(int j = 0; j < _height; j++)
		{
			//select which image to display from image set
			srcTemp.y = BLOCK_SIZE * _map[i][j];
			//sets which column we're going to draw
			destTemp.x = BLOCK_SIZE * j;
			
			if(SDL_BlitSurface(_image_set, &srcTemp, screen, &destTemp))
				return false;
		}
	}
	return true;
}
