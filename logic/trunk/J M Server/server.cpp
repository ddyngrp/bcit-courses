#define UMOVE 10
#define GRID_EMPTY 0
#define GRID_BOMB 1

unsigned char grid[15][15];
Player pArray[8];

int main(void)
{
	// Init shizzle
	
	for( ; ; )
	{
		// call receive function
	}
}

void move_player(int pIndex, const char direction)
{
	char packet = 0;
	
	switch(direction)
	{
	case 0:
		if(!pArray[pIndex].collision(direction))
			break;
		
		pArray[pIndex].y_ -= UMOVE;	
			
		packet += pArray[pIndex].playerid_;
		packet << 2;
		
		// send packet to network function
		break;
		
	case 1:
		if(!pArray[pIndex].collision(direction))
			break;
			
		pArray[pIndex].y_ += UMOVE;
		
		packet += pArray[pIndex].playerid_;
		packet << 2;
		
		// send packet to network function
		break;
		
	case 2:
		if(!pArray[pIndex].collision(direction))
			break;
			
		pArray[pIndex].x_ -= UMOVE;
		
		packet += pArray[pIndex].playerid_;
		packet << 2;
		
		// send packet to network function
		break;
		
	case 3:
		if(!pArray[pIndex].collision(direction))
			break;
			
		pArray[pIndex].x_ += UMOVE;
		
		packet += pArray[pIndex].playerid_;
		packet << 2;
		
		// send packet to network function
		break;
	}
}

void plant_bomb(int pIndex)
{
	char packet = 0;
	char temp = 0;
	
	if(!pArray[pIndex].canPlant)
		return;
		
	grid[pArray[pIndex].x_][pArray[pIndex].y_] = GRID_BOMB;
	
	pArray[pIndex].availableBombs--;
	
	start_fuse(pArray[pIndex].x_, pArray[pIndex].y_);
	
	temp = 2;
	packet += temp << 5;
	
	temp = pArray[pIndex].playerid_;
	packet += temp << 2;
	
	// send packet to network
}

