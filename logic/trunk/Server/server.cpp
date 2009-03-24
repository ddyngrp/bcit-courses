/* need to add alive bool to player class */
/* also it occurs to me that graphics are going need to implement some sort
   of gui with a start button or something on the server and a list of players
   or sth dunno they can figure it out */
/* these need to go somewhere global so that networking can use them too */
unsigned char grid[15][15];
Player player_array[8];
unsigned char player_count = 0;
bool game_running = false;

void move_player(const int, const int);
void plant_bomb(const int);
void player_quit(const int);
void player_join(void);

void start_fuse(const int, const int);

void
move_player(const int index, const int direction)
{
char packet;
	
	switch(direction)
	{
	case MOVE_UP:
		if(player_array[index].collision(direction) == false)
			break;
		
		player_array[index].y_ -= UNITS_PER_MOVE;	
		packet = make_packet(TYPE_MOVE, player_array[index].id_, MOVE_UP);
		// send packet to all clients
		break;
		
	case MOVE_DOWN:
		if(player_array[index].collision(direction) == false)
			break;
			
		player_array[index].y_ += UNITS_PER_MOVE;
		packet = make_packet(TYPE_MOVE, player_array[index].id_, MOVE_DOWN);
		// send packet to all clients
		break;
		
	case MOVE_LEFT:
		if(player_array[index].collision(direction) == false)
			break;
			
		player_array[index].x_ -= UNITS_PER_MOVE;
		packet = make_packet(TYPE_MOVE, player_array[index].id_, MOVE_LEFT);
		// send packet to all clients
		break;
		
	case MOVE_RIGHT:
		if(player_array[index].collision(direction) == false)
			break;
			
		player_array[index].x_ += UNITS_PER_MOVE;
		packet = make_packet(TYPE_MOVE, player_array[index].id_, MOVE_RIGHT);
		// send packet to all clients
		break;
	}
}
void
plant_bomb(const int index)
{
char packet;
int x;
int y;
	
	if(player_array[index].canPlant() == false)
		return;
	x = player_array[index].x_;
	y = player_array[index].y_;

	grid[x][y] = GRID_BOMB;
	player_array[index].droppedBombs_--;
	start_fuse(x,y);
	packet = make_packet(TYPE_PLANT, player_array[index].id_, 0);
	// send packet to all clients
}

void
start_fuse(const int x, const int y)
{
	return;	
}

bool
add_player(void)
{
char packet;
char packet2;

	if (player_count == MAX_PLAYERS)
		return false;
	packet = make_packet(TYPE_JOIN, player_count, 0);
	// send packet to all clients	
	player_count++;
	return true;
}

Player
getPlayer(const int id)
{
	int i;
	for (i = 0; i < num_players; ++i) {
		if (player_array[i].DPlayaID_ == id)
			return &(player_array[i]);
	}
	return NULL;
}

void
explode_bomb(const int x, const int y, const int id, const int len)
{
char up_len, down_len, right_len, left_len;	
int j, k;

		for (j = x, k = 0; j > 0 && k < len; --j, ++k) {
			if (check_block(x,j))
				break;
			kill_if_here(x,j);
		}
		up_len = k;
		for (j = x, k = 0; j < 15 && k < len; ++j, ++k) {
			if (check_block(x,j))
				break;
			kill_if_here(x,j);
		}
		down_len = k;
		for (j = x, k = 0; j > 0 && k < len; --j, ++k) {
			if (check_block(j,y))
				break;
			kill_if_here(j,y);
		}
		left_len = k;
		for (j = x, k = 0; j < 15 && k < len; ++j, ++k) {
			if (check_block(j,y))
				break;
			kill_if_here(j,y);
		}
		right_len = k;
		
}

void
kill_if_here(const int x, const int y)
{
int i;
	
	for (i = 0; i < MAX_PLAYERS; ++i) {
		if (player_array[i].x_ == x && player_array[i].y_ == y) {
			player_array[i].alive_ = 0;
			// send out player dead msg
		}
	}
}

bool
check_block(const int x, const int y)
{
	
}
