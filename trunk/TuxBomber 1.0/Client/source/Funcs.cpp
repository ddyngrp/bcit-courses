
#include "../headers/mainHeader.h"



/*------------------------------------------------------------------------------------------------------------------
--       FUNCTION: 		    	init_everything
--
--       DATE:                  April 15, 2009
--
--       DESIGNER:              Alin Albu
--
--       PROGRAMMER: 		    Alin Albu
--
--       INTERFACE:                 bool init_everything(SDL_Surface* screen)
--
--	 RETURNS:		    true if SDLinitialization succeeds, false otherwise
--
--       NOTES:
--       initialises the libraries, as well as the screen and sets screen size and window caption.
----------------------------------------------------------------------------------------------------------------------*/
bool init_everything(SDL_Surface **screen) {
	printf("Init everything Started");
	//Initialize all SDL subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		printf("Init everything Failed\n");
		return false;
	}
	printf("...");
	//Set up the screen
	*screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_DOUBLEBUF);
	//If there was an error in setting up the screen
	if (*screen == NULL) {
		printf("Init SCREEN Failed\n");
		return false;
	}
	printf("...");
	//Initialize SDL_ttf
	if (TTF_Init() == -1) {
		printf("Init TTF Failed\n");
		return false;
	}
	printf("...");
	//Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		printf("Init AUDIO Failed\n");
		return false;
	}
	printf("...");
	//Set the window caption
	SDL_WM_SetCaption("Tux Bomber", NULL);
	printf("...");
	SDL_ShowCursor(SDL_ENABLE);
	//If everything initialized fine
	printf("Init everything Done\n");
	return true;
}

/*------------------------------------------------------------------------------------------------------------------
--       FUNCTION: 		    load_image
--
--       DATE:                      April 15, 2009
--
--       DESIGNER:                  Alin Albu
--
--       PROGRAMMER: 		    Alin Albu
--
--       INTERFACE:                 SDL_Surface *load_image( std::string filename )
--
--	 RETURNS:		    a pinter to the loaded optimized surface
--
--       NOTES:
--       Takes in a filename of a picture and loads the image, after the image is loaded
		 it will be optimized (background colour RGB{0, 0xFF, 0xFF} is removed).
----------------------------------------------------------------------------------------------------------------------*/

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    printf("...");
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;
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
            printf("Optimizing Image: %s Done \n", filename.c_str());
        }else{
        	printf("Optimizing Image: %s Failed \n", filename.c_str());
        }
    }

    //Return the optimized surface
    return optimizedImage;
}


/*------------------------------------------------------------------------------------------------------------------
--       FUNCTION: 		    optimizeImg
--
--       DATE:                      April 15, 2009
--
--       DESIGNER:                  Alin Albu
--
--       PROGRAMMER: 		    Alin Albu
--
--       INTERFACE:                 bool optimizeImg( SDL_Surface ** img )
--
--	 RETURNS:		    true if succeeds, false otherwise
--
--       NOTES:
--       Converts the image to a new format by removing the colour RGB{0, 0xFF, 0xFF}
		from the surface.
----------------------------------------------------------------------------------------------------------------------*/
bool optimizeImg( SDL_Surface ** img )
{
    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    if( img != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat(*img);

        //If the surface was optimized
        if( optimizedImage != NULL )
        {

            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
            //Free the old surface
            //SDL_FreeSurface(img);
            *img = new SDL_Surface((SDL_Surface&) *optimizedImage);
            printf("Optimizing Image: Done \n");
        }else{
           	printf("Optimizing Image: Failed \n");
        }

    }


    return false;
}

/*------------------------------------------------------------------------------------------------------------------
--       FUNCTION: 		    apply_surface
--
--       DATE:                      April 15, 2009
--
--       DESIGNER:                  Alin Albu
--
--       PROGRAMMER: 		    Alin Albu
--
--       INTERFACE:                 void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
--
--	 RETURNS:		    void
--
--       NOTES:
--       blits two images together, with the source being pasted on the destination starting at x,y
----------------------------------------------------------------------------------------------------------------------*/
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, 0, destination, &offset );
}

/*------------------------------------------------------------------------------------------------------------------
--       FUNCTION: 		    getMenuItems
--
--       DATE:                      April 15, 2009
--
--       DESIGNER:                  Alin Albu
--
--       PROGRAMMER: 		    Alin Albu
--
--       INTERFACE:              void getMenuItems(std::string menu[], FILE* fp, const char * type, int size)
--
--		 RETURNS:		    void
--
--       NOTES:
--       retrieves the path for the menu items/backgrounds from the file pointed by *fp
		 it only looks in the secion "type" and assigns only "size" number of paths.
		 The file to retrieve paths from is config.txb
----------------------------------------------------------------------------------------------------------------------*/

void getMenuItems(std::string menu[], FILE* fp, const char * type, int size) {
	static char *line =(char*) malloc(30);
	size_t len = 0 ;
	int i = 0;
	int ret = 0;

	while((ret = getline(&line, &len, fp)) != -1) {
		if(!strcmp(line, type)){
			break;
		}
	}
	if(ret == -1)
		return ;
	while(getline(&line, &len, fp) != -1) {
		if(!strcmp(line, "done"))
			break;
		line = strtok(line,"\n");
		if(i == size)
			return;
		menu[i]="";
		menu[i++].append(line);

	}
}


/******************************************************************************
 *  Function:    serialize_player
 *
 *  Date:        March 30, 2009
 *
 *  Revisions:
 *
 *  Designer:    David Young
 *  Programmer:  David Young
 *
 *  Interface:   serialize_player(DPlaya *player, char *buf, int buflen)
 *                          DPlaya *player: Pointer to the DPlaya object to be serialized
 *                  char *buf: buffer to put the serialized form of the player into
 *                                      int buflen: the length of buf
 *
 *  Returns:     0 on success or (-1) on failure.
 *
 *  Description: Serialize player's data members into buf to be passed across the network.
 *
 *****************************************************************************/
int serialize_player(DPlaya *player, char *buf, size_t buflen) {
        if(buflen < sizeof(DPlaya)) {
                return -1;
        }

        memcpy(buf, player, sizeof(DPlaya));
        return 0;
}

/******************************************************************************
 *  Function:    unserialize_player
 *
 *  Date:        March 30, 2009
 *
 *  Revisions:
 *
 *  Designer:    David Young
 *  Programmer:  David Young
 *
 *  Interface:   unserialize_player(char *buf, DPlaya *player)
 *                                      char *buf: buffer to get the serialized form of the player from
 *                          DPlaya *player: Pointer to the DPlaya object to fill
 *
 *  Returns:     0 on success or (-1) on failure.
 *
 *  Description: Unserialize the info in buf and put it into player.
 *
 *****************************************************************************/
int unserialize_player(char *buf, DPlaya *player) {
        memcpy(player, buf, sizeof(DPlaya));
        return 0;
}



/*----------------------------------------------------------------------
 -- METHOD:		genRandomMap
 --
 -- DATE:		March 16, 2009
 --
 -- REVISIONS:
 --
 -- DESIGNER:	Alin Albu
 --
 -- PROGRAMMER:	Alin Albu
 --
 -- INTERFACE:	unsigned char** genRandomMap(int rowNum, int colNum)
 --
 -- RETURNS:		void.
 --
 -- NOTES:
 -- Generates a random map contained within a 2D array with sizes
 -- specified by rowNum and colNum which are number of rows and columns
 -- respectivly.
 ----------------------------------------------------------------------*/
	unsigned char** genRandomMap(int rowNum, int colNum) {
	int tile, row;

	int sTime;
	long lTime;
	unsigned char **map;
	int i;
	lTime = time(NULL);
	sTime = (unsigned) lTime / 2;
	srand(sTime);

	//Initialize map
	map = (unsigned char**) malloc(rowNum * sizeof(unsigned char *));

	for (i = 0; i < rowNum; i++)
		map[i] = (unsigned char*) malloc(colNum * sizeof(unsigned char));

	//generate random map
	for (tile = 0, row = -1; tile < 306; tile++) {
		// Places indestructables along left side.
		if (tile % 18 == 0) {
			row++;
			map[row][tile % 18] = 0;
			continue;
		}
		// Places indestructables along the right side.
		if (tile % 18 == 16 || tile % 18 == 17) {
			map[row][tile % 18] = 0;
			continue;
		}

		// Places indestructables along top and bottom.
		if ((tile < 18 || tile > TOTAL_TILES - 19)) {
			map[row][tile % 18] = 0;
			continue;
		}
		// Place indestructables at every second row and second column
		if (row % 2 == 0 && tile % 2 == 0) {
			map[row][tile % 18] = 0;
			continue;
		}
		// Places either emprow or destructable in every open location.
		map[row][tile % 18] = (rand() % 2 + 1);
	}

	//Clear spaces for player start positions

	//Player 1 (top left)
	map[1][1] = map[1][2] = map[2][1] = 2;

	//Player 2(Top right)
	map[1][colNum - 3] = map[1][colNum - 4] = map[2][colNum - 3] = 2;

	//Player 3(Bot Left)
	map[rowNum - 2][1] = map[rowNum - 2][2] = map[rowNum - 3][1] = 2;

	//Player 4(Bot right)
	map[rowNum - 2][colNum - 3] = map[rowNum - 3][colNum - 3]
			= map[rowNum - 2][colNum - 4] = 2;

	return map;
}
