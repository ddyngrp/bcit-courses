#ifndef BOMB_H
#define BOMB_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "server.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream> 

class Bomb
{
public:
	explicit Bomb() : isActive_(false), bombID_(-1), x_(0), y_(0), power_(0) {}
	virtual ~Bomb();
	
	int getBombID(){return bombID_;}
	int getX(){return x_;}
	int getY(){return y_;}
	
	void setBombID(int id){bombID_ = id;}
	void setX(int x){x_ = x;}
	void setY(int y){y_ = y;}
	void setPower(int power){power_ = power;}

	void startFuse(){isActive_ = true;} //TODO timer
	void countdown(void* param);
	void detonate();
	
private:
	int x_, y_;
	bool isActive_;
	int bombID_;
	int power_;
};

#endif
