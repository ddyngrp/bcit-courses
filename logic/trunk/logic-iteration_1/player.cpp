#include "Player.h"

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
					

