#include "server.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream> 

void
plant_bomb(const int index)
{
char packet;
int x;
int y;
	
	if(player_array[index].canPlant() == false)
		return;
	x = player_array[index].getX();
	y = player_array[index].getY();

	grid[x][y] = GRID_NORMBOMB;
	player_array[index]->setNumBombs(player_array[index]->getNumBombs()++);
	start_fuse(x,y, player_array[index]->bombPower_);
	send_player_class(player_array[index]);
}

void
start_fuse(const int x, const int y, const int len)
{
	p_thread_t pt;
	struct coords c;
	
	c.x = x;
	c.y = y;
	c.len = len;

	if (pthread_create(&pt, NULL, countdown, (void *)&c) != 0) {
		perror("pthread_create() failed");
		return;
	}
}

void
countdown(void *param)
{
	Uint32 start = 0;
	bool running = false;
	struct coords *c;

	c = (struct coords *)param;
	start = SDL_GetTicks();

	sleep(3);
	explode_bomb(c->x, c->y, c->len);	
}
