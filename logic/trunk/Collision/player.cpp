#include "player.h"

//Player::Player(const Player& old): x_(old.x_), y_(old.y_), image_(old.image_),
					//	w_(old.w_), h_(old.h_){}
						
void Player::paint(Player player, int newX , int newY, SDL_Surface* screen)
{
	player.setX(newX);
	player.setY(newY);
	refresh(screen);
}
void Player::refresh(SDL_Surface * screen)
{
	SDL_Rect  position;
	position.x = getX();
	position.y = getY();
	
	SDL_BlitSurface(getImage(), NULL, screen, &position );	
}

void Player::dropBomb()
{
	int i;
	for(i = 0; i < numBombs_; i++)
	{
		if(bombs[i] == 0)
		break;
	}
	
	bombs[i] = new Bomb();
	droppedBombs_++;
}

void Player::explodeBomb(int i)
{
	bombs[i] = 0;
	droppedBombs_--;
}

//Player::Player(const int x, const int y, const int w, const int h , const string pic) :
//				 x_(x),  y_(y), w_(w), h_(h),
//					image_(loadImage(pic)){}
					
int collision (int direction){
	switch (direction){
	case 0: // up
		// check all gridspaces up to see if collision happens
			//all players bombs,
		// Check map, all blocks
		//was the player able to move to that space?
	case 1: // down
	case 2: // left
	case 3: // right
	}
	
}
			
bool checkCollisionLeft (playerArray){
	int i;
	int j;

	for(i = 0; i != sizeof(playerarray); i++){
		if(playerArray[i].gridSpace == this.gridspace - 1) // minus one gridspace left.
			return false;
		for(j = 0; j != sizeof(playerarray[i].bombs); j++){
			if(playerarray[i].bomb[j].gridspace == this.gridpsace - 1) 
				return false;
		}
	}	
}

int checkCollisionright (playerArray){
	int i;
	int j;

	for(i = 0; i != sizeof(playerarray); i++){
		if(playerArray[i].gridSpace == this.gridspace + 1) // plus one gridspace right.
			return false;
		for(j = 0; j != sizeof(playerarray[i].bombs); j++){
			if(playerarray[i].bomb[j].gridspace == this.gridpsace + 1) 
				return false;
		}
	}	
}

int checkCollisionUp (playerArray){
	int i;
	int j;

	for(i = 0; i != sizeof(playerarray); i++){
		if(playerArray[i].gridSpace == this.gridspace - 1) // minus one gridspace up.
			return false;
		for(j = 0; j != sizeof(playerarray[i].bombs); j++){
			if(playerarray[i].bomb[j].gridspace == this.gridpsace - 1) 
				return false;
		}
	}	
}

int checkCollisionDown (playerArray){
	int i;
	int j;

	for(i = 0; i != sizeof(playerarray); i++){
		if(playerArray[i].gridSpace == this.gridspace + 1) // plus one gridspace down.
			return false;
		for(j = 0; j != sizeof(playerarray[i].bombs); j++){
			if(playerarray[i].bomb[j].gridspace == this.gridpsace + 1) 
				return false;
		}
	}	
}












}
