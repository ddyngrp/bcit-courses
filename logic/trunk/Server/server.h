#ifndef SERVER_H
#define SERVER_H

#include <cstdio>
#include "s_player.h"
#include "defs.h"
#include "headerMain.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "user_map.h"
#include "funcs.h"

/* s_movement.cpp */
void   	move_player(const int, const int);

/* s_player.cpp */
bool   	addPlayer(const int);
DPlaya* getPlayer(const int);

/* s_network.cpp */
void recieve_packet(const char, const int);

/* s_bomb.cpp */
void   	plant_bomb(const int);
void   	explode_bomb(const int, const int, const int);
void   	start_fuse(void);
void    fire_to_map(struct fire);

/* s_explosion.cpp */
void   	kill_if_here(const int, const int);
bool   	block_here(const int, const int);
void 	destroy_block(const int, const int);

struct fire {
	int left, right, up, down;
	int x,y;
};

struct coords {
	int x,y;
};

unsigned char 		grid[15][15];
DPlaya 			player_array[MAX_PLAYERS];
unsigned char 		player_count = 0;
bool 			game_running = false;

#endif
