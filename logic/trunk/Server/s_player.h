/*
 * DPlaya.h
 *
 *  Created on: Mar 19, 2009
 *      Author: root
 */

#ifndef DPLAYA_H_
#define DPLAYA_H_
#include "headerMain.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_thread.h" 
#include "Map/user_map.h"
#include "Map/init.h"

class DPlaya {
public:
	/*DPlaya(){ x_ = 0,  y_ = 0 , w_= 35, h_ = 35, image_ = IMG_Load("default.png");}

	DPlaya(const int x, const int y, const int w, const int h , const std::string pic){
				 x_ = x,  y_ = y, w_ = w, h_ = h, image_ = IMG_Load((char*)&pic);}

	DPlaya(const DPlaya& old){ x_ = old.x_, y_ = old.y_, image_ = old.image_, w_ = old.w_, h_ = old.h_;}*/
	DPlaya() : x_(0), y_(0), w_(35), h_(35), xVel(0), yVel(0), bombPower(2), DPlayaID_(-1), alive_(false), image_(IMG_Load("default.png")){}
	DPlaya(const int x, const int y, const int w, const int h, char* pic) :
				 x_(x),  y_(y), w_(w), h_(h), image_(IMG_Load(pic)){}
	DPlaya(const DPlaya& old):x_(old.x_), y_(old.y_), w_(old.w_), h_(old.h_), image_(old.image_) {}

	virtual ~DPlaya(){};   

	//functions
	void paint(DPlaya DPlaya, int x, int y, SDL_Surface* screen);
	void refresh(SDL_Surface * screen);
	bool canPlant();
	bool move(unsigned char mapGrid[17][18], int direction);
	void explode();

	//getters
	int getX(){return x_;}
	int getY(){return y_;}
	int getNumBombs(){return numBombs_;}
	int getDroppedBombs(){return droppedBombs_;}
	int getDPlayaID(){return DPlayaID_;}
	bool getAlive(){return alive_;}
	int getBombPower(){return bombPower_;}
	SDL_Surface* getImage() {return image_;}

	//setters
	void setX(int x){x_ = x;}
	void setY(int y){y_ = y;}
	void setImage(const char* pic){image_ = load_image(pic);}
	void setNumBombs(int numBombs){numBombs_ = numBombs;}
	void setDroppedBombs(int droppedBombs){droppedBombs_ = droppedBombs;}
	void killPlayer(){alive_ = false;}
	void spawnPlayer(){alive_ = true;}
	void setID(int id){DPlayaID_ = id;}
	void setName(char *name){strcpy(name_, name);}
	void setColor(char color){color_ = color;}

	/*To add the drop bomb */


private:
int x_, y_, w_,h_, numBombs_, droppedBombs_, xVel, yVel;
int bombPower;
int DPlayaID_;
int bombPower_;
bool alive_;
char name_[256];
char color_;

SDL_Surface* image_;

};
#endif /* DPLAYA_H_ */
