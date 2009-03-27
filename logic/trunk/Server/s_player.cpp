#include "s_player.h"
#include "server.h"

void DPlaya::refresh(SDL_Surface * screen)
{
	SDL_Rect  position;
	position.x = this->getX();
	position.y = this->getY();

	//SDL_BlitSurface( this->getImage(), NULL, screen, &position );
}

void DPlaya::paint(DPlaya player, int newX, int newY, SDL_Surface* screen)
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

	//bombs[i] = new Bomb();
	this->droppedBombs_++;
}

void DPlaya::explodeBomb(int i)
{
	//bombs[i] = 0;
	this->droppedBombs_--;
}


void
add_player(unsigned long ip)
{
	if (player_count == MAX_PLAYERS)
		return;
	player_array[player_count].connected_ = true;
	player_array[player_count].ip_ = ip;
	return player_count++;
}

DPlaya *
getPlayer(const int id)
{
int i;

	for (i = 0; i < num_players; ++i) 
		if (player_array[i].DPlayaID_ == id)
			return &(player_array[i]);
	return NULL;
}
