#include "server.h"

void
recieve_packet(char b, int index)
{
	if (b == 0)
		move_player(index, CS_UP);
	else if (b == 1)
		move_player(index, CS_DOWN);
	else if (b == 2)
		move_player(index, CS_LEFT);
	else if (b == 3)
		move_player(index, CS_RIGHT);
	else if (b == 4)
		plant_bomb(index);
	else if (b == 5)
		player_quit(index);
}
