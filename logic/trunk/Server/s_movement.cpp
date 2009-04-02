#include "server.h"
/* 
	Note: Grid is a global map, do we need to extern it or is it
		defined in a header file?
*/
//extern user_map grid;

void
move_player(const int index, const int direction)
{
	player_array[index]->move(grid, direction);
}
