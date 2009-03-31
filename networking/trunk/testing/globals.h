#ifndef GLOBAL_H
#define GLOBAL_H

#include "DPlaya.h"

#define MAX_PLAYERS 8

unsigned char 	grid[15][15];
static DPlaya 	*player_array[MAX_PLAYERS];
unsigned char 	player_count = 0;
bool			game_running = false;

#endif
