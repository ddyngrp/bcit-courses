/*
 * DPlaya.h
 *
 *  Created on: Mar 19, 2009
 *      Author: root
 */

#ifndef DPLAYA_H_
#define DPLAYA_H_
#include "headerMain.h"

class DPlaya {
public:
	DPlaya(){ x_ = 0,  y_ = 0 , w_= 35, h_ = 35, image_ = IMG_Load("default.png");}

	DPlaya(const int x, const int y, const int w, const int h , const std::string pic){
				 x_ = x,  y_ = y, w_ = w, h_ = h, image_ = IMG_Load((char*)&pic);}

	DPlaya(const DPlaya& old){ x_ = old.x_, y_ = old.y_, image_ = old.image_, w_ = old.w_, h_ = old.h_;}

	virtual ~DPlaya(){};

	void paint(DPlaya player, int x, int y, SDL_Surface* screen);
	void refresh(SDL_Surface * screen);
	void dropBomb();
	void explodeBomb(int i);
	bool canPlant(){return (numBombs_ < 5);}

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

#endif /* DPLAYA_H_ */
