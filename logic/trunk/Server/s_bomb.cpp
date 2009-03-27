#include "server.h"

void
plant_bomb(const int index)
{
char packet;
int x;
int y;
	
	if(player_array[index].canPlant() == false)
		return;
	x = player_array[index].x_;
	y = player_array[index].y_;

	grid[x][y] = GRID_BOMB;
	player_array[index].numBombs_--;
	start_fuse(x,y);
	send_player_class(player_array[index]);
}

void
start_fuse(const int x, const int y)
{
	p_thread_t pt;
	struct coords c;
	
	c.x = x;
	c.y = y;

	if (pthread_create(&pt, NULL, countdown, (void *)&c) != 0) {
		perror("pthread_create() failed");
		return;
	}
}
void
countdown(void *param)
{
	struct coords c;
	c = (struct coords *)param;

	/* finish this muddafukka */	
}


