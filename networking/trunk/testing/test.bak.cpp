#include <stdio.h>
#include <stdlib.h>

#include "network.h"
#include "globals.h"
#include "DPlaya.h"

extern DPlaya *player_array[MAX_PLAYERS];

int add_player(unsigned long ip_netformat);

int main(int argc, char *argv[]) {
	for(int a = 0; a < MAX_PLAYERS; a++) {
		add_player(a);
	}
	
	for(int a = 0; a < MAX_PLAYERS; a++) {
		printf("%d %d\n", player_array[a]->getX(), player_array[a]->getY());
	}
	
	return 0;
}

int add_player(unsigned long ip_netformat) {
	int a;
	
	for(a = 0; a < MAX_PLAYERS; a++) {
		if(player_array[a] == 0) {
			break;
		}
	}
	
	if(a >= MAX_PLAYERS) {
		return (-1);
	}
	
	printf("in add_player %d\n", a);
	
	player_array[a] = new DPlaya();
	
	player_array[a]->setX(a);
	player_array[a]->setY(a);
	player_array[a]->setID(a);
	
	return 0;
}
