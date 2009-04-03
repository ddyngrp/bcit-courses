#include "server.h"

extern DPlaya 		   *player_array[8];
extern unsigned char 	grid[17][18];

void
explode_bomb(const int x, const int y, const int len)
{
struct fire f;
int j, k;

	f.x = x;
	f.y = y;

	for (j = x, k = 0; j > 1 && k < len; --j, ++k) {
		if (block_here(x,j)) 
			break;
		kill_if_here(x,j);
	}
	f.up = k;	
	for (j = x, k = 0; j < 16 && k < len; ++j, ++k) {
		if (block_here(x,j))
			break;
		kill_if_here(x,j);
	}
	f.down = k;
	for (j = x, k = 0; j > 1 && k < len; --j, ++k) {
		if (block_here(j,y))
			break;
		kill_if_here(j,y);
	}
	f.left = k;
	for (j = x, k = 0; j < 16 && k < len; ++j, ++k) {
		if (block_here(j,y))
			break;
		kill_if_here(j,y);
	}
	f.right = k;
	fire_to_map(f);
	send_map(grid);
}

/* network will make this -- need in order to compile properly */
void
send_map(const unsigned char grid[17][18])
{
	return;
}
/* network will make this -- need in order to compile properly */
void
send_player_class(DPlaya *player)
{
	return;
}

void
fire_to_map(struct fire f)
{
int i;

	grid[f.x][f.y] = GRID_CENTER;
	for (i = (f.y - 1); i < (f.up - f.y + 1); --i)
		grid[f.x][i] = GRID_HZ;
	grid[f.x][i] = GRID_TOP;
	for (i = (f.y + 1); i > (f.down + f.y - 1); ++i)
		grid[f.x][i] = GRID_HZ;
	grid[f.x][i] = GRID_BOTTOM;
	for (i = (f.x - 1); i < (f.left - f.x + 1); --i)
		grid[i][f.y] = GRID_VT;
	grid[i][f.y] = GRID_LEFT;
	for (i = (f.x + 1); i > (f.right + f.x - 1); ++i)
		grid[i][f.y] = GRID_VT;
	grid[i][f.y] = GRID_RIGHT;
}

void
kill_if_here(const int x, const int y)
{
int i;
	
	for (i = 0; i < MAX_PLAYERS; ++i) 
		if (player_array[i]->getX() == x && player_array[i]->getY() == y) {
			player_array[i]->killPlayer();
			send_player_class(player_array[i]);
		}
}



bool
block_here(const int x, const int y)
{
	if (grid[x][y] == GRID_UBLOCK)
		return true;
	else if (grid[x][y] == GRID_DBLOCK) {
		destroy_block(x,y);
		return true;
	}
	return false;
}

/* each powerup has a 1/9 chance of spawning.  6/9 chance
   of no powerup spawning. */
void
destroy_block(const int x, const int y)
{
int i;
	
	i = rand() * 9;
	if (i == 0)
		grid[x][y] = GRID_POWUP_NUM;
	else if (i == 1)
		grid[x][y] = GRID_POWUP_RAD;
	else if (i == 2)
		grid[x][y] = GRID_POWUP_SPIKE;
	else
		grid[x][y] = GRID_EMPTY;
}
