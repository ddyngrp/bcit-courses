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

bool DPlaya::move(int** map, int direction)
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
   /* 
    printf("xl = %d\nxr = %d\nyt = %d\nyb= %d \n", xl/35, xr/35, yt/35 ,yb/35);
	printf("map: map[xl/35][yt/35], %d\n", map[xl/35][yt/35]);
	printf("map: map[xr/35][yb/35], %d\n", map[xr/35][yb/35]);
	printf("map: map[xl/35][yb/35], %d\n", map[xl/35][yb/35]);
	printf("map: map[xr/35][yt/35], %d\n", map[xr/35][yt/35]);
	printf("*******\n");*/
		
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
