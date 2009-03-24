#ifndef SERVER_H

#include <cstdio>
#include "s_player.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

/* s_movement.cpp */
void   	move_player(const int, const int);

/* s_player.cpp */
bool   	addPlayer(const int);
DPlaya* getPlayer(const int);

/* s_bomb.cpp */
void   	plant_bomb(const int);
void   	explode_bomb(const int, const int);
void   	start_fuse(void);

/* s_explosion.cpp */
void   	kill_if_here(const int, const int);
bool   	check_block(const int, const int);
void 	destroy_block(const int, const int);

struct fire {
	int up;
	int down;
	int left;
	int right;
	int x;
	int y;
};

#define SERVER_H
#endif
