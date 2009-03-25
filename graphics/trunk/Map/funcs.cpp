#include "user_map.h"

#define TOTAL_TILES 306

int** genRandomMap(int rowNum, int colNum)
{
	int tile,row;
	
	int sTime;
	long lTime;
	int **map;
	int i;
	lTime = time(NULL);
	sTime = (unsigned)lTime/2;
	srand(sTime);

	//Initialize map	
	map = (int**)malloc(rowNum * sizeof(int *));

	for(i = 0; i < rowNum; i++)
		map[i] = (int*)malloc(colNum * sizeof(int));

	//generate random map
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
	
	//Clear spaces for player start positions
	map[1][1] = map[1][2] = map[2][1] = 2; //Player 1 (top left)
	map[1][colNum - 3] = map[1][colNum - 4] = map[2][colNum - 3] = 2; //Player 2(Top right)
	map[rowNum - 2][1] = map[rowNum - 2][2] = map[rowNum - 3][1] = 2; //Player 3(Bot Left)
	map[rowNum - 2][colNum - 3] = map[rowNum - 3][colNum - 3] 
		= map[rowNum - 2][colNum - 4] = 2; //Player 4(Bot right)
	
	return map;
}

SDL_Surface *load_image( std::string filename )
{
	SDL_RWops *rwop;
	rwop=SDL_RWFromFile(filename.c_str(), "rb");
	
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
	
	if(IMG_isGIF(rwop))
		loadedImage = IMG_LoadGIF_RW(rwop);
    else
        //Load the image
    	loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

