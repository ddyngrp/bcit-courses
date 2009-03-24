#include "UserMap.h"

#define TOTAL_TILES 306

int** genRandomMap(int rowNum, int colNum)
{
	int tile,row;
	//generate random map
	int sTime;
	long lTime;
	int **map;
	//int map[rowNum][colNum];
	int i;
	lTime = time(NULL);
	sTime = (unsigned)lTime/2;
	srand(sTime);

	//map = (int **)malloc(sizeof(int) * (rowNum * colNum));
	//map = new int[rowNum][colNum];

	map = (int**)malloc(rowNum * sizeof(int *));
	for(i = 0; i < rowNum; i++)
		map[i] = (int*)malloc(colNum * sizeof(int));


	for(tile = 0, row = -1  ;tile < 306; tile++ )
	{
		// Places indestructables along left side.
		if(tile % 18 == 0)
		{
			row++;
			map[row][tile%18] = 0 ;
			continue;
		}
		// Places indestructables along the right side.
		if(tile % 18 == 16 || tile % 18 == 17 )
		{
			map[row][tile % 18] = 0;
			continue;
		}

		// Places indestructables along top and bottom.
		if((tile < 18 || tile > TOTAL_TILES -19))
		{
			map[row][tile%18] = 0;
			continue;
		}
		// Place indestructables at every second row and second column
		if( row % 2 == 0 && tile % 2 == 0)
		{
			map[row][tile%18] = 0;
			continue;
		}
		// Places either emprow or destructable in every open location.
		map[row][tile%18] = (rand()%2 + 1);
	}

	return map;
}
