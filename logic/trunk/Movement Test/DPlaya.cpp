/*
 * DPlaya.cpp
 *
 *  Created on: Mar 19, 2009
 *      Author: root
 */

#include "DPlaya.h"


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

void DPlaya::dropBomb()
{
	int i;
	for(i = 0; i < this->numBombs_; i++)
	{
		//if(this->bombs[i] == 0)
		break;
	}

	//bombs[i].setX(this.x_);
	//bombs[i].setY(this.y_);
	//bombs[i].startFuse();
	//map.setCoords(this.x, this.y, 3); TODO not yet implemented by graphics
	this->droppedBombs_++;
}

void DPlaya::explodeBomb(int i)
{
	//bombs[i].detonate();
	this->droppedBombs_--;
}

void DPlaya::move(user_map mapGrid, int direction)
{
	int yt,yb,xl,xr;
	int xVel = 0;
	int yVel = 0;
	int **map;
	map = mapGrid.get_map();
	if(direction == 0)
		yVel = -10;
	else if(direction == 1)
		yVel = 10;
	else if(direction == 2)
		xVel = -10;
	else if(direction == 3)
		xVel = 10;

	x_ += xVel;
	y_ += yVel;
	 
	yt= y_ + 15;
	yb= y_ + 25;
	
	xl= x_ + 10;
	xr= x_ + 25;
       
    //Move the Player up or down
    if(map[xl/35][yt/35] != 0 || map[xr/35][yb/35] != 0 
    	|| map[xl/35][yb/35] != 0 || map[xr/35][yt/35] != 0 )
    {
    	y_ -= yVel;
    	x_ -= xVel;
    }
}
