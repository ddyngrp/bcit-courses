#include <stdio.h>
#include <stdlib.h>
#include "s_player.h"

#define MAX_PLAYERS 8

extern DPlaya *player_array[MAX_PLAYERS];
extern unsigned char player_count;

int add_player(unsigned long ip_netformat);
int get_player_loc(unsigned long ip_netformat);
int get_first_avail();
