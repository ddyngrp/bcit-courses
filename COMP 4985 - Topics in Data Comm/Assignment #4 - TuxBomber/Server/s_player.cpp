#include "s_player.h"
#include <cmath>

#define MOVESPEED 5

extern int playerCount;

void DPlaya::refresh(SDL_Surface * screen)
{
	if (this->getAlive() == false)
		return;
	SDL_Rect  position;
	position.x = this->getX();
	position.y = this->getY();

	SDL_BlitSurface( this->getImage(), NULL, screen, &position );
}

void DPlaya::paint(DPlaya &player, int newX , int newY, SDL_Surface* screen)
{
	player.setX(newX);
	player.setY(newY);
	refresh(screen);
}

bool DPlaya::canPlant()
{	
	if(droppedBombs_ >= numBombs_) 
		return false;
	else if (alive_ == false)
		return false;
	else
		droppedBombs_++;
	return true;
}

bool DPlaya::move(unsigned char map[17][18], int direction)
{
	int yt,yb,xl,xr;
	
	if(direction == 0)
		y_ += -MOVESPEED;
	else if(direction == 1)
		y_ += MOVESPEED;
	else if(direction == 2)
		x_ += -MOVESPEED;
	else if(direction == 3)
		x_ += MOVESPEED;
	
	yt= y_ + 10;
	yb= y_ + 30;
	
	xl= x_ + 8;
	xr= x_ + 27;
	if (map[yt/35][xl/35] > 7 || map[yb/35][xr/35] > 7
	    || map[yb/35][xl/35] > 7 || map[yt/35][xr/35] > 7) {
		this->killPlayer();
		playerCount--;
		return true;
	}
	//Move the Player up or down
    if(map[yt/35][xl/35] != 2 || map[yb/35][xr/35] != 2
	|| map[yb/35][xl/35] != 2 || map[yt/35][xr/35] != 2)
    {
		if(direction == 0) {
			y_ -= -MOVESPEED;
			if (map[yb / 35][(x_ + 17)/35] == 3 && map[(yb/35) - 1 ][(x_ + 17)/35] == 2) {
				y_+= -MOVESPEED;
				return true;
			}
		}
		else if(direction == 1) {
			y_ -= MOVESPEED;
			if (map[yt/35][(x_ + 17)/35] == 3 && map[(yt/35) + 1][(x_ + 17)/35] == 2) {
				y_ += MOVESPEED;
				return true;
			}
		}
		else if(direction == 2) {
			x_ += MOVESPEED;
			if (map[(y_+ 17)/35][xr/35] == 3 && map[(y_+ 17)/35][(xr/35) - 1] == 2 ) {
				x_ -= MOVESPEED;
				return true;
			}
			if (map[(y_+ 17)/35][xr/35] > 7) {
				this->killPlayer();
				return true;
			}
		}
		else if(direction == 3) {
			x_ -= MOVESPEED;
			if (map[(y_+ 17)/35][xl/35] == 3 && map[(y_+ 17)/35][(xl/35) + 1] == 2 ) {
				x_ += MOVESPEED;
				return true;
			}
			if(map[(y_+ 17)/35][xl/35] > 7) {
				this->killPlayer();
				return true;
			}
		}
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

