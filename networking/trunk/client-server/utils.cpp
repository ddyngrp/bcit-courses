#include "utils.h"
#include "globals.h"

extern DPlaya *player_array[MAX_PLAYERS];
extern unsigned char player_count;

int add_player(unsigned long ip_netformat) {
	int pos = get_player_loc(ip_netformat);
	
/*	for(pos = 0; pos < MAX_PLAYERS; pos++) {
		if(player_array[pos] == 0) {
			break;
		}
	}*/
	
	if(pos < 0 || pos >= MAX_PLAYERS) {
		return (-1);
	}
	
	player_array[pos] = new DPlaya();
	
	player_array[pos]->setX(pos);
	player_array[pos]->setY(pos);
	player_array[pos]->setID(pos);
	
	return pos;
}

int get_player_loc(unsigned long ip_netformat) {
	int pos, first_avail = -1;
	
	for(pos = 0; pos < MAX_PLAYERS; pos++) {
		if(player_array[pos] != NULL) { /* if there's a player at pos */
			if(player_array[pos]->get_ip_netformat() == ip_netformat) { /* if this player's IP is the same as the IP we're searching for */
				return pos;
			}
		} else if(first_avail == -1) { /* no player at pos and first avail hasn't been set yet */
			first_avail = pos; /* the first available position (if it's needed) */
		}
	}
	
	return first_avail;
}

