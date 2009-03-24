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

	//SDL_BlitSurface( this->getImage(), NULL, screen, &position );
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
/*
 * Will move the player up, down left, or right
 * If xDir is set to -1 will move left, 0 will not move and one will move right
 * If yDir is set to -1 will move up, 0 will not move and one will move down
 */
void DPlaya::move(int xDir, int yDir, int map[][18])
{
	int yt; // Player box top y coordinate
	int yb; // Player box bottom y coordinate
	int xl; // Player box left x coordinate
	int xr; // Player box right x coordinate
	int step = 7; // How big is one step?

	x_ += step * xDir;
	y_ += step * yDir;

	yt= y_ + 15;
	yb= y_ + 25;

	xl= x_ + 10;
	xr= x_ + 25;

	/*//For debugging only ... if uncommented will print in terminal
	printf("xl = %d\nxr = %d\nyt = %d\nyb= %d \n", xl/35, xr/35, yt/35 ,yb/35);
	printf("map: map[xl/35][yt/35], %d\n", map[xl/35][yt/35]);
	printf("map: map[xr/35][yb/35], %d\n", map[xr/35][yb/35]);
	printf("map: map[xl/35][yb/35], %d\n", map[xl/35][yb/35]);
	printf("map: map[xr/35][yt/35], %d\n", map[xr/35][yt/35]);
	printf("*******\n");
	*/

    //Move the Player up or down
    if(map[xl/35][yt/35] != 0 || map[xr/35][yb/35] != 0
    	|| map[xl/35][yb/35] != 0 || map[xr/35][yt/35] != 0 )
    {
    	y_ -= step * xDir;
    	x_ -= step * yDir;
	}
}
