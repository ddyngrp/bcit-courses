
// **********************************************************The Player Class***********************************************************************

Class DPlaya 
{
public:
	DPlaya() : this.x_ = 0,  this.y_ = 0 , this.w_= 35, this.h_ = 35,
					 this.image_ = loadImage(“default.png”){}

	Dplaya(const int x, const int y, const int w, const int h , const string pic) :
				 this.x_ = x,  this.y_ = y, this_w_ = w, this.h_ = h,
					, this.image_ = loadImage(pic){}

	DPlaya(const DPlaya& old_playa): this.x_(old.x), this.y_( old.y), this.image_(old.image),
						w_(w), h_(h){}

	void paint(DPlaya player, int x, int y);
	void refresh();

	//getters 
	int getX(){return this.x_}
	int getY(){return this.y_}
	SDL_Surface* getImage() {return this.image}
	
	//setters
	void setX(itn x){this.x_ = x}
	void set(int y){this.y_ = y}
	void setImage(const SDL_Surface* pic){this.image_ = pic}

	/*To add the drop bomb */


private:
int x_, y_, w_,h_;
SDL_Surface* image_;
}


Dplaya::paint(DPlaya player, int newX , int newY, SDL_Surface* screen)
{
	player.setX(newX);
	player.setY(newY);
	refresh(screen);
}
Dplaya::refresh(SDL_Surface * screen)
{
	SDL_Rect  position;
	position.x = this.getX();
	position.Y = this.getY();
	
	SDL_BlitSurface( this.getImage(), NULL, screen, &positiont );	
}


/* *****************************************************This is the end of the Player Class *******************************************************/

//This method will apply to all players it will be the interface for the server

void draw_players(STL Container, SDL_Surface* screen)
{
	for each player in Container do:
	    player.refresh(screen);
}
