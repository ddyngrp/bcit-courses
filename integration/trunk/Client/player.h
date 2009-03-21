#ifndef PLAYER_H
#define PLAYER_H

#include "graphics.h"

class Player 
{
public:
	Player() : x_(0), y_(0), w_(35), h_(35), image_(load_image("center.xcf")){}
	Player(const int x, const int y, const int w, const int h , char *pic) :
				 x_(x),  y_(y), w_(w), h_(h), image_(load_image(pic)){}
	Player(const Player& old):x_(old.x_), y_(old.y_), image_(old.image_),
						w_(old.w_), h_(old.h_){}
	void paint(Player player, int x, int y, SDL_Surface*);
	void refresh(SDL_Surface*);
	void dropBomb();
	void explodeBomb(int i);
	void handle_input(); 

	//getters 
	int getX(){return x_;}
	int getY(){return y_;}
	int getNumBombs(){return numBombs_;}
	int getDroppedBombs(){return droppedBombs_;}
	SDL_Surface* getImage() {return image_;}
	
	//setters
	void setX(int x){x_ = x;}
	void setY(int y){y_ = y;}
	void setImage(SDL_Surface* pic){image_ = pic;}
	void setNumBombs(int numBombs){numBombs_ = numBombs;}
	void setDroppedBombs(int droppedBombs){droppedBombs_ = droppedBombs;}
	/*To add the drop bomb */


private:
int x_, y_, w_,h_, numBombs_, droppedBombs_;
//Bomb bombs[5]; //TODO bomb init !
SDL_Surface* image_;
};
#endif

