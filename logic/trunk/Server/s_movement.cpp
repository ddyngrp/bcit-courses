#include "server.h"

void
move_player(const int index, const int direction)
{
	player_array[index]->move(grid, direction);
}
