#include "DPlaya.h"
#include "globals.h"

unsigned char 	grid[15][15];
DPlaya 	*player_array[MAX_PLAYERS];
unsigned char 	player_count = 0;
bool			game_running = false;
