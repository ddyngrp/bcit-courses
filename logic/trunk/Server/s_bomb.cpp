#include "s_server.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>

extern DPlaya 		   *player_array[8];
extern unsigned char 	grid[17][18];

void
plant_bomb(const int index)
{
int x;
int y;
int nBombs;
	
	if(player_array[index]->canPlant() == false)
		return;
	x = player_array[index]->getX();
	y = player_array[index]->getY();

	nBombs = player_array[index]->getNumBombs();
	nBombs++;

	grid[x][y] = GRID_NORMBOMB;
	player_array[index]->setNumBombs(nBombs);
	start_fuse(x,y, player_array[index]->getBombPower());
	send_player_class(player_array[index]);
}

void
start_fuse(const int x, const int y, const int len)
{
pthread_t pt;
struct coords c;
	
	c.x = x;
	c.y = y;
	c.len = len;

	if (pthread_create(&pt, NULL, countdown, (void *)&c) != 0) {
		perror("pthread_create() failed");
		return;
	}
}

void *
countdown(void *param)
{
struct coords *c;

	c = (struct coords *)param;

	sleep(3);
	explode_bomb(c->x, c->y, c->len);

	return NULL;
}
