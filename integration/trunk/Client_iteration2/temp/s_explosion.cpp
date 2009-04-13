#include "s_server.h"

extern DPlaya 		   *player_array[8];
extern unsigned char 	grid[17][18];

void
explode_bomb(const int x, const int y, const int len)
{
struct fire f;
int j, k;

	f.x = x;
	f.y = y;

	for (j = y, k = 0; j > 0 && k < len; --j, ++k) {
		if (block_here(x,j)) 
			break;
		kill_if_here(x,j);
	}
	f.up = k-1;	
	for (j = y, k = 0; j < 17 && k < len; ++j, ++k) {
		if (block_here(x,j))
			break;
		kill_if_here(x,j);
	}
	f.down = k-1;
	for (j = x, k = 0; j > 0 && k < len; --j, ++k) {
		if (block_here(j,y))
			break;
		kill_if_here(j,y);
	}
	f.left = k-1;
	for (j = x, k = 0; j < 18 && k < len; ++j, ++k) {
		if (block_here(j,y))
			break;
		kill_if_here(j,y);
	}
	f.right = k-1;

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

	grid[f.y][f.x] = GRID_CENTER;
	for (i = (f.y - 1); i > (f.y - f.up); --i) // goes till it == 1
		grid[i][f.x] = GRID_VT;			
	grid[i][f.x] = GRID_TOP;
	for (i = (f.y + 1); i < (f.y + f.down); ++i)
		grid[i][f.x] = GRID_VT;
	grid[i][f.x] = GRID_BOTTOM;
	for (i = (f.x - 1); i > (f.x - f.left); --i)
		grid[f.y][i] = GRID_HZ;
	grid[f.y][i] = GRID_LEFT;
	for (i = (f.x + 1); i < (f.x + f.right); ++i)
		grid[f.y][i] = GRID_HZ;
	grid[f.y][i] = GRID_RIGHT;
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
	if (grid[y][x] == GRID_UBLOCK)
		return true;
	else if (grid[y][x] == GRID_DBLOCK) {
		destroy_block(y,x);
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
	
	i = 3; /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX: takign out ofr now implement plz */
	if (i == 0)
		grid[y][x] = GRID_POWUP_NUM;
	else if (i == 1)
		grid[y][x] = GRID_POWUP_RAD;
	else if (i == 2)
		grid[y][x] = GRID_POWUP_SPIKE;
	else
		grid[y][x] = GRID_EMPTY;
}
