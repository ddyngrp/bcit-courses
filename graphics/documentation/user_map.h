#define indestructable_image 0
#define walkable_image 1
#define destructable_image 2

class user_map
{
	public:
	user_map();
	user_map(user_map &map);
	~user_map();
	
	draw_map();
	
	update_map(int new_map[][]);
	
	set_images(SDL_image *new_image);
	
	private:
	int map[][];
	SDL_image *image_set; //0 is indestructable, 1 is walkable, 2 is destructable
	
}
