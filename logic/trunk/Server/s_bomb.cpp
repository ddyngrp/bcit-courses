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
	return;	
}

void
recieve_packet(char b, int index)
{
	if (b == 0)
		move_player(index, CS_UP);
	else if (b == 1)
		move_player(index, CS_DOWN);
	else if (b == 2)
		move_player(index, CS_LEFT);
	else if (b == 3)
		move_player(index, CS_RIGHT);
	else if (b == 4)
		plant_bomb(index);
	else if (b == 5)
		player_quit(index);
}

//send_player_class()
//send_map()
