#ifndef SERVER_H
#define SERVER_H

#include <cstdio>
#include "s_player.h"
#include "s_defs.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Map/user_map.h"
#include "Map/init.h"
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <ctype.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/sem.h>
#include <signal.h>

/* s_player.cpp */
bool   	addPlayer(const int);

/* s_network.cpp */
void recieve_packet(const char, const int);

/* s_bomb.cpp */
void   	plant_bomb(const int);
struct fire explode_bomb(const int x, const int y, const int len);
void    start_fuse(const int x, const int y, const int len, const int index);
void    fire_to_map(struct fire);
void    *countdown(void *);
void    unexplode_bomb(struct fire);

/* s_explosion.cpp */
void   	kill_if_here(const int, const int);
int     block_here(const int x, const int y);
void 	destroy_block(const int, const int);
void 	send_player_class(DPlaya *player);
void	send_map(const unsigned char grid[17][18]);

/* s_init.cpp */
bool	initialize_server(struct server_info *);

struct fire {
	int left, right, up, down;
	int x,y;
};

struct coords {
	int x,y;
	int len;
    	int id; 
};

struct server_info
{
	unsigned char 		grid[GRID_HEIGHT][GRID_WIDTH];
	DPlaya 			    *player_array;
	unsigned char 		player_count;
	bool 			    game_running;
};

#endif
