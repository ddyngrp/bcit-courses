/*
 * DPlaya.h
 *
 *  Created on: Mar 19, 2009
 *      Author: root
 *
 *	Revisions:
 *		April 8, 2009 - David Young
 *			Added ip_netformat_ field and getters/setters.
 *			Fixed misc bugs.
 */

#ifndef DPLAYA_H_
#define DPLAYA_H_
#include "headerMain.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_thread.h" 
#include "Map/user_map.h"
#include "funcs.h"

class DPlaya {
public:
	/*DPlaya(){ x_ = 0,  y_ = 0 , w_= 35, h_ = 35, image_ = IMG_Load("default.png");}

	DPlaya(const int x, const int y, const int w, const int h , const std::string pic){
				 x_ = x,  y_ = y, w_ = w, h_ = h, image_ = IMG_Load((char*)&pic);}

	DPlaya(const DPlaya& old){ x_ = old.x_, y_ = old.y_, image_ = old.image_, w_ = old.w_, h_ = old.h_;}*/
	DPlaya() : x_(0), y_(0), w_(35), h_(35), xVel(0), yVel(0), DPlayaID_(-1), alive_(false), image_(IMG_Load("default.png")){}
	DPlaya(const int x, const int y, const int w, const int h, char* pic) :
				 x_(x),  y_(y), w_(w), h_(h), image_(IMG_Load(pic)){}
	DPlaya(const DPlaya& old):x_(old.x_), y_(old.y_), w_(old.w_), h_(old.h_),
				image_(old.image_){}

	virtual ~DPlaya(){};   

	//functions
	void paint(DPlaya DPlaya, int x, int y, SDL_Surface* screen);
	void refresh(SDL_Surface * screen);
	void dropBomb();
	bool canPlant(){return (numBombs_ < 5);}
	bool move(unsigned char map[15][15], int direction);

	//getters
	int getX(){return x_;}
	int getY(){return y_;}
	int getNumBombs(){return numBombs_;}
	int getDroppedBombs(){return droppedBombs_;}
	int getDPlayaID(){return DPlayaID_;}
	bool getAlive(){return alive_;}
	SDL_Surface* getImage() {return image_;}
	unsigned long get_ip_netformat(){return ip_netformat_;}

	//setters
	void setX(int x){x_ = x;}
	void setY(int y){y_ = y;}
	void setImage(const char* pic){image_ = load_image(pic);}
	void setNumBombs(int numBombs){numBombs_ = numBombs;}
	void setDroppedBombs(int droppedBombs){droppedBombs_ = droppedBombs;}
	void killPlayer(){alive_ = false;}
	void spawnPlayer(){alive_ = true;}
	void setID(int id){DPlayaID_ = id;}
	void setName(const char *name){strcpy(name_, name);}
	void setColor(char color){color_ = color;}
	void set_ip_netformat(unsigned long ip) {ip_netformat_ = ip;}

	/*To add the drop bomb */


private:
	int x_, y_, w_,h_, numBombs_, droppedBombs_, xVel, yVel;
	int DPlayaID_;
	int bombPower_;
	unsigned long ip_netformat_;
	bool alive_;
	char name_[256];
	char color_;
	//Bomb bombs[5]; //TODO bomb init !

	SDL_Surface* image_;

};

#endif /* DPLAYA_H_ */
