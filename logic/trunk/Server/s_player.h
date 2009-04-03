#ifndef S_PLAYER_H
#define S_PLAYER_H
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "funcs.h"

class DPlaya {
public:
	DPlaya() : x_(0), y_(0), w_(35), h_(35), DPlayaID_(-1), alive_(false), image_(IMG_Load("default.png")){}
	DPlaya(const int x, const int y, const int w, const int h, char* pic) :
				 x_(x),  y_(y), w_(w), h_(h), image_(IMG_Load(pic)){}
	DPlaya(const DPlaya& old):x_(old.x_), y_(old.y_), w_(old.w_), h_(old.h_), image_(old.image_){}

	virtual ~DPlaya(){};

	//functions
	void paint(DPlaya DPlaya, int x, int y, SDL_Surface *screen);
	void refresh(SDL_Surface *screen);
	void dropBomb();
	void explodeBomb(int i);
	bool canPlant(){return (numBombs_ < 5);}
	void move(unsigned char map[17][18], int direction);

	//getters
	int getX(){return x_;}
	int getY(){return y_;}
	int getNumBombs(){return numBombs_;}
	int getDroppedBombs(){return droppedBombs_;}
	int getDPlayaID(){return DPlayaID_;}
	bool getAlive(){return alive_;}
	SDL_Surface* getImage() {return image_;}
	int getBombPower() { return bombPower_; }

	//setters
	void setX(int x){x_ = x;}
	void setY(int y){y_ = y;}
	void setImage(char* pic){image_ = load_image(pic);}
	void setNumBombs(int numBombs){numBombs_ = numBombs;}
	void setDroppedBombs(int droppedBombs){droppedBombs_ = droppedBombs;}
	void killPlayer(){alive_ = false;}
	void spawnPlayer(){alive_ = true;}
	void setID(int id){DPlayaID_ = id;}
	/*To add the drop bomb */


private:
int x_, y_, w_,h_, numBombs_, droppedBombs_;
int DPlayaID_;
int bombPower_;
bool alive_;
//Bomb bombs[5]; //TODO bomb init !

SDL_Surface* image_;

};

#endif




