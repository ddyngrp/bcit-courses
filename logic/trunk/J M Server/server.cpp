/* need to add alive bool to player class */
/* also it occurs to me that graphics are going need to implement some sort
   of gui with a start button or something on the server and a list of players
   or sth dunno they can figure it out */
/* these need to go somewhere global so that networking can use them too */
unsigned char grid[15][15];
Player player_array[8];
unsigned char player_count = 0;
bool game_running = false; /* this needs to be changed in main as we go
			      from pre-game to game to pre-game etc */

void move_player(const int, const int);
void plant_bomb(const int);
void player_quit(const int);
void player_join(void);

void start_fuse(const int, const int);

/* this should be somewhere global so that everyone can use it */
void make_packet(char, char, char);

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

void
add_player(void)
{
char packet;
char packet2;

	if (player_count == MAX_PLAYERS)
		return;
	packet2 = make_packet(TYPE_ADDYOU, player_count, 0);
	// send packet to _ONLY_ the player who joined
	packet = make_packet(TYPE_JOIN, player_count, 0);
	// send packet to all clients	
	player_count++;
	init_player(player_count);
}

void
player_quit(const int id)
{
char packet;
    
	packet = make_packet(TYPE_QUIT, id, 0);
	// send packet to all clients
	player_array[id].alive = false;
	player_count--;
}

char
make_packet(char type, char id, char options)
{
char packet = 0;

	packet += type >> 5;
	packet += id >> 2;
	packet += options;
	return packet;
}
/* i guess we could add players as the game is running if we want to, we
   would have to add some logic so they dont spawn on a block or whatever */
void
init_player(const int id)
{
	if (game_running == false)		
		return;
	player_array[id].x_ = rand() * 15;
	player_array[id].y_ = rand() * 15;
	player_array[id].alive = true;
}
