#include "server.h"

void
add_player(unsigned long ip)
{
	if (player_count == MAX_PLAYERS)
		return;
	player_array[player_count].connected_ = true;
	player_array[player_count].ip_ = ip;
	
	return player_count++;
}
