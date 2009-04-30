#include "s_server.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include <sstream>

extern DPlaya 		   *player_array[8];
extern unsigned char 	grid[17][18];
extern int              fd;
extern struct sockaddr_in addr;


void
plant_bomb(const int index)
{
int x;
int y;
int droppedBombs;
char outBuf[1024];
	
	if(player_array[index]->canPlant() == false) {
		return;
	}

	x = ((player_array[index]->getX()) + 35/2) / 35;
	y = ((player_array[index]->getY()) + 35/2) / 35;
	droppedBombs = player_array[index]->getDroppedBombs();
	player_array[index]->setDroppedBombs(droppedBombs);
	grid[y][x] = GRID_NORMBOMB;
	
	for(int i = 0; i < 17; i++)
    for(int j = 0; j < 18; j++)
        outBuf[17 * i + j] = grid[i][j];
	        
	if(sendto(fd, outBuf, sizeof(outBuf), 0, (struct sockaddr *)&addr, sizeof(addr)) == -1) //need to multicast it
        perror("sendto");
	start_fuse(x,y, player_array[index]->getBombPower(), index);

}

void
start_fuse(const int x, const int y, const int len, const int index)
{
pthread_t pt;
struct coords *c;
	c = (struct coords *)malloc(sizeof(struct coords));
	c->x     = x;
	c->y 	= y;
	c->len 	= len;
	c->id    = index;

	if (pthread_create(&pt, NULL, countdown, (void *)c) != 0) {
		perror("pthread_create() failed");
		return;
	}
}

//TODO: Modified by Max and Matt C, added bomb decrementing. Tested, works as intended.
void *
countdown(void *param)
{
struct coords *c;
struct fire f;

	c = (struct coords *)param;
	sleep(3);
	f = explode_bomb(c->x, c->y, c->len);
	player_array[c->id]->explode();
	sleep(1);
	unexplode_bomb(f);
	return NULL;
}
