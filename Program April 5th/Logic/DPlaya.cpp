/*
 * DPlaya.cpp
 *
 *  Created on: Mar 19, 2009
 *      Author: root
 */

#include "DPlaya.h"
#include <cmath>


void DPlaya::refresh(SDL_Surface * screen)
{
	SDL_Rect  position;
	position.x = this->getX();
	position.y = this->getY();

	SDL_BlitSurface( this->getImage(), NULL, screen, &position );
}

void DPlaya::paint(DPlaya player, int newX , int newY, SDL_Surface* screen)
{
	player.setX(newX);
	player.setY(newY);
	refresh(screen);
}

bool DPlaya::canPlant()
{	
	if(droppedBombs_ >= numBombs_)
		return false;
	else
		droppedBombs_++;
	return true;
}

bool DPlaya::move(unsigned char** map, int direction)
{
	int yt,yb,xl,xr;
	
	if(direction == 0)
		y_ += -3;
	else if(direction == 1)
		y_ += 3;
	else if(direction == 2)
		x_ += -3;
	else if(direction == 3)
		x_ += 3;
	
	yt= y_ + 10;
	yb= y_ + 30;
	
	xl= x_ + 8;
	xr= x_ + 27;
		
    //Move the Player up or down
    if(map[yt/35][xl/35] != 2 || map[yb/35][xr/35] != 2
	|| map[yb/35][xl/35] != 2 || map[yt/35][xr/35] != 2)
    {
		if(direction == 0)
			y_ -= -3;
		else if(direction == 1)
			y_ -= 3;
		else if(direction == 2)
			x_ -= -3;
		else if(direction == 3)
			x_ -= 3;
			
		return false;
    }
    return true;
		
}

void DPlaya::explode()
{
	if(droppedBombs_ == 0)
		return;
	droppedBombs_--;
}
