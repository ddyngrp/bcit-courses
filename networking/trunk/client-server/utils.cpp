#include "utils.h"
#include "globals.h"

extern DPlaya *player_array[MAX_PLAYERS];
extern unsigned char player_count;

int add_player(unsigned long ip_netformat) {
	int pos;
	
	for(pos = 0; pos < MAX_PLAYERS; pos++) {
		if(player_array[pos] == 0) {
			break;
		}
	}
	
	if(pos >= MAX_PLAYERS) {
		return (-1);
	}
	
	//printf("in add_player %d\n", pos);
	
	player_array[pos] = new DPlaya();
	
	player_array[pos]->setX(pos);
	player_array[pos]->setY(pos);
	player_array[pos]->setID(pos);
	
	return pos;
}