#include "s_server.h"

extern DPlaya 				*player_array[8];
extern unsigned char 		grid[17][18];
extern int           		fd;
extern int                  expectedClients;
extern struct sockaddr_in 	addr;
extern int                  playerCount;

/*
Calculates the length of a bomb explosion in each direction.
Destroys any block or kills any player in the path of the
explosion.  Returns a structure containing the lengths of the fire,
so that we can re-draw the map after the fire expires.

Matt Woodske
Jerrod Hudson
*/
struct fire
explode_bomb(const int x, const int y, const int len)
{
struct fire f;
int j, k;
char outBuf[1024];
	
	f.x = x;
	f.y = y;
	
	for (j = y - 1, k = 0; j > 0 && k < len; --j, ++k) {
		int ret = block_here(x,j);
		if (ret == 0) {
			k++;
			break;
		}
		if (ret == 1)
			break;
		kill_if_here(x,j);
	}
	f.up = k;	
	for (j = y + 1, k = 0; j < 17 && k < len; ++j, ++k) {
		int ret = block_here(x,j);
		if (ret == 0) {
			k++;
			break;
		}
		if (ret == 1)
			break;
		kill_if_here(x,j);
	}
	f.down = k;
	for (j = x - 1, k = 0; j > 0 && k < len; --j, ++k) {
		int ret = block_here(j,y);
		if (ret == 0) {
			k++;
			break;
		}
		if (ret == 1)
			break;
		kill_if_here(j,y);
	}
	f.left = k;
	for (j = x + 1, k = 0; j < 18 && k < len; ++j, ++k) {
		int ret = block_here(j,y);
		if (ret == 0) {
			k++;
			break;
		}
		if (ret == 1)
			break;
		kill_if_here(j,y);
	}
	f.right = k;

	fire_to_map(f);
	
	for(int i = 0; i < 17; i++)
	    for(int j = 0; j < 18; j++)
	        outBuf[17 * i + j] = grid[i][j];
	        
	if(sendto(fd, outBuf, sizeof(outBuf), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) //need to multicast it
        perror("sendto");
	
	return f;
}

void send_player_class(DPlaya* player) { return; }
void send_map(const unsigned char map[17][18]) { return; }
/*
Each loop writes horizontal or vertical bars of fire to the map,
and the i value after the loop will be the position of the tips
of the fire in each direction.

Matt Woodske
Jerrod Hudson
*/ 
void
fire_to_map(struct fire f)
{
int i;
int j;
char outBuf[1024];

	grid[f.y][f.x] = GRID_CENTER;
	
	if (f.up != 0) {
		for (i = (f.y - 1), j = 0; j < f.up - 1; --i, ++j) 
			grid[i][f.x] = GRID_VT;			
		grid[i][f.x] = GRID_TOP;
	}

	if (f.down != 0) {
		for (i = (f.y + 1), j = 0; j < f.down - 1; ++i, ++j)
			grid[i][f.x] = GRID_VT;
		grid[i][f.x] = GRID_BOTTOM;
	}

	if (f.left != 0) {
		for (i = (f.x - 1), j = 0; j < f.left - 1; --i, ++j)
			grid[f.y][i] = GRID_HZ;
		grid[f.y][i] = GRID_LEFT;
	}

	if (f.right != 0) {
		for (i = (f.x + 1), j = 0; j < f.right - 1; ++i, ++j)
			grid[f.y][i] = GRID_HZ;
		grid[f.y][i] = GRID_RIGHT;
	}
		
	for (int k = 0; k < GRID_HEIGHT; ++k)
		for (int n = 0; n < GRID_WIDTH; ++n)
			outBuf[k * GRID_HEIGHT + n] = grid[k][n];

    if(sendto(fd, outBuf, sizeof(outBuf), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) //need to multicast it
        perror("sendto");
}
/*
Kills any player that is on the coordinates specified and sends an update
of the player class to each client.

Matt Woodske
Jerrod Hudson
*/
void
kill_if_here(const int x, const int y)
{
int i;
int tempx, tempy;
char outBuf[1024];

for (i = 0; i < expectedClients; ++i)  {
	tempx = (player_array[i]->getX() + 17) / 35;
	tempy = (player_array[i]->getY() + 17) / 35;
	
	outBuf[0] = 'P';
	outBuf[1] = 'P';
	
	if (tempx == x && tempy == y) {
		player_array[i]->killPlayer();
		memcpy(outBuf+2, player_array[i], 1024);
		
		if(sendto(fd, outBuf, sizeof(outBuf), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) //need to multicast it
	        perror("sendto");
	        
	    playerCount--;
	}
    
}
}

/*
Returns 0 if it is a destructable block, 1 if it is indestructable, 2 otherwise.
If the block is destructable, a function is called to destroy it.

Matt Woodske
Jerrod Hudson
*/
int
block_here(const int x, const int y)
{
if (grid[y][x] == GRID_DBLOCK) {
	destroy_block(x,y);
	return 0;
}
	
if (grid[y][x] == GRID_UBLOCK)
	return 1;
else
	return 2;
}

/*
Each powerup has a one-third chance of spawning a powerup.

NOTE: Powerups are not implemented.
*/
void
destroy_block(const int x, const int y)
{
int i;

i = 3;

if 	(i == 0) 		grid[y][x] = GRID_POWUP_NUM;
else if (i == 1) 	grid[y][x] = GRID_POWUP_RAD;
else if (i == 2)	grid[y][x] = GRID_POWUP_SPIKE;
else				grid[y][x] = GRID_EMPTY;

}

/*
Draws empty spaces on all grid spaces that contained fire, as specified by the
fire struct.

Matt Woodske
Jerrod Hudson
*/
void
unexplode_bomb(struct fire f)
{
int i;
int j;
char outBuf[1024];

grid[f.y][f.x] = GRID_EMPTY;
	
	if (f.up != 0) 
		for (i = (f.y - 1), j = 0; j < f.up; --i, ++j) 
			grid[i][f.x] = GRID_EMPTY;			

	if (f.down != 0) 
		for (i = (f.y + 1), j = 0; j < f.down; ++i, ++j)
			grid[i][f.x] = GRID_EMPTY;

	if (f.left != 0) 
		for (i = (f.x - 1), j = 0; j < f.left; --i, ++j)
			grid[f.y][i] = GRID_EMPTY;

	if (f.right != 0) 
		for (i = (f.x + 1), j = 0; j < f.right; ++i, ++j)
			grid[f.y][i] = GRID_EMPTY;
		
	for (int k = 0; k < 17; ++k)
		for (int n = 0; n < 18; ++n) 
			outBuf[k * 17 + n] = grid[k][n];

    if(sendto(fd, outBuf, sizeof(outBuf), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) //need to multicast it
        perror("sendto");
}

