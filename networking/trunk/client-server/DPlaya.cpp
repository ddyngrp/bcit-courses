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

/*void DPlaya::dropBomb()
{
	struct coords c;
	if(droppedBombs >= numBombs)
		return;
	for(int i = 0; i < numBombs_; i++)
	{
		if(bombs[i].getBombID() != -1)
			break;
	}

	bombs[i].setX(x_);
	bombs[i].setY(y_);
	bombs[i].setID(i);

	c.x = x_;
	c.y = y_;
	c.len = bombPower_;
	c.id = i;
	
	droppedBombs++;

	bombs[i].startFuse();	

	if (pthread_create(&pt, NULL, countdown, (void *)&c) != 0) {
		perror("pthread_create() failed");
		return;
	}
}

void DPlaya::countdown()
{
	struct coords *c;

	c = (struct coords *)param;

	sleep(3);
	bombs[c->id].detonate();
	droppedBombs--;
}*/


/* 
	Note: map[][] = 2
		  changed to '2' since the real map is now holding chars, 
		  change it back if you need to re-test this, but remember
		  that the final version is using chars.
*/
bool DPlaya::move(unsigned char map[15][15], int direction)
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
    if(map[yt/35][xl/35] != '2' || map[yb/35][xr/35] != '2'
	|| map[yb/35][xl/35] != '2' || map[yt/35][xr/35] != '2')
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
