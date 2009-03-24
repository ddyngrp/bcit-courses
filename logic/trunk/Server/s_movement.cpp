#include "server.h"

void
move_player(const int index, const int direction)
{
	switch(direction)
	{
	case MOVE_UP:
		if(player_array[index].collision(direction) == false)
			break;
		player_array[index].y_ -= UNITS_PER_MOVE;
		update_player(player_array[index]);
		break;
		
	case MOVE_DOWN:
		if(player_array[index].collision(direction) == false)
			break;
		player_array[index].y_ += UNITS_PER_MOVE;
		update_player(player_array[index]);
		break;
		
	case MOVE_LEFT:
		if(player_array[index].collision(direction) == false)
			break;
		player_array[index].x_ -= UNITS_PER_MOVE;
		update_player(player_array[index]);
		break;
		
	case MOVE_RIGHT:
		if(player_array[index].collision(direction) == false)
			break;
		player_array[index].x_ += UNITS_PER_MOVE;
		update_player(player_array[index]);
		break;
	}
}
