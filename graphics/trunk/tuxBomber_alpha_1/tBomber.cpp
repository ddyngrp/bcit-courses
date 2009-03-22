/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.
The code was modified by Alin Albu to meet the requirements of the Tux Bomer game.*/

//The headers
#include "MainHeader.h"

//bombs location index
SDL_Rect bombs[TOTAL_TILES];

//The surfaces
SDL_Surface *player = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *tileSheet = NULL;
SDL_Surface *background = NULL; 
SDL_Surface *bomb = NULL;

//Sprite from the tile sheet
SDL_Rect clips[TILE_SPRITES];

//The event structure
SDL_Event event;

//loads the images
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

//shows images on screen
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

//collision detection
bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB+5 || topA >= bottomB-15 || rightA <= leftB+5 || leftA >= rightB-5 )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Tux Bomber", NULL );

    //If everything initialized fine
    return true;
}

//load all files -- should be generalized a good prototype would be:
// bool load_files(SDL_Surface * image[], const string path[] )
bool load_files()
{
    //Load the Player image
    player = load_image( "batmanTuxSmal.gif" );

    //If there was a problem in loading the player
    if( player == NULL )
    {
        return false;
    }

    //Load the tile sheet
    tileSheet = load_image( "empty.xcf" );

    //If there was a problem in loading the tiles
    if( tileSheet == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

//should be generalized also
void clean_up( Tile *tiles[] )
{
    //Free the surfaces
    SDL_FreeSurface( player );
    SDL_FreeSurface( tileSheet );

    //Free the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        delete tiles[ t ];
    }

    //Quit SDL
    SDL_Quit();
}

// Cut tiles from the picture empty.xcf, faster loading one image than three.
void clip_tiles()
{
    //Clip the sprite sheet
    clips[ICECUBE].x = 0;
    clips[ICECUBE].y = 0;
    clips[ICECUBE].w = TILE_WIDTH;
    clips[ICECUBE].h = TILE_HEIGHT;

    clips[SNOWMAN].x = 0;
    clips[SNOWMAN].y = 35;
    clips[SNOWMAN].w = TILE_WIDTH;
    clips[SNOWMAN].h = TILE_HEIGHT;

    clips[EMPTYSPACE ].x = 0;
    clips[EMPTYSPACE ].y = 70;
    clips[EMPTYSPACE ].w = TILE_WIDTH;
    clips[EMPTYSPACE ].h = TILE_HEIGHT;

}


//draw tiles on the screen based on the map
//to do: generalize
bool set_tiles( Tile *tiles[] )
{
    //The tile offsets
    int x = FIELD_X_OFFSET, y = FIELD_Y_OFFSET;

    //Open the map
    std::ifstream map( "lazyBack.map" );

    //If the map couldn't be loaded
    if( map == NULL )
    {
        return false;
    }

    //Initialize the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //Determines what kind of tile will be made
        int tileType = -1;

        //Read tile from map file
        map >> tileType;

        //If the was a problem in reading the map
        if( map.fail() == true )
        {
            //Stop loading map
        map.close();
        return false;
        }

        //If the number is a valid tile number
        if( ( tileType >= 0 ) && ( tileType < TILE_SPRITES ) )
        {
            tiles[ t ] = new Tile( x, y, tileType );
        }
        //If we don't recognize the tile type
        else
        {
            //Stop loading map
            map.close();
            return false;
        }

        //Move to next tile spot
        x += TILE_WIDTH;

        //If we've gone too far
        if( x >= FIELD_WIDTH )
        {
            //Move back
            x = 0;

            //Move to the next row
            y += TILE_HEIGHT;
        }
    }

    //Close the file
    map.close();
    //If the map was loaded fine
    return true;
}

//check collision with blocks
bool touches_wall( SDL_Rect box, Tile *tiles[] )
{
    //Go through the tiles
    for( int t = 0; t < TOTAL_TILES; t++ )
    {
        //If the tile is a wall type tile
        if( tiles[ t ]->get_type() == ICECUBE || tiles[ t ]->get_type() == SNOWMAN  )
        {
            //If the collision box touches the wall tile
            if( check_collision( box, tiles[ t ]->get_box() ) == true )
            {
                return true;
            }
        }
    }

    //If no wall tiles were touched
    return false;
}

Tile::Tile( int x, int y, int tileType )
{
    //Get the offsets
    box.x = x;
    box.y = y;

    //Set the collision box
    box.w = TILE_WIDTH;
    box.h = TILE_HEIGHT;

    //Get the tile type
    type = tileType;
}

void Tile::show()
{
    apply_surface( box.x, box.y, tileSheet, screen, &clips[ type ] );
}

int Tile::get_type()
{
    return type;
}

SDL_Rect Tile::get_box()
{
    return box;
}

Player::Player()
{
    //Initialize the offsets
    box.x = FIELD_X_OFFSET + PLAYER_X_POS;
    box.y = FIELD_Y_OFFSET + PLAYER_Y_POS;
    box.w = TUX_WIDTH;
    box.h = TUX_HEIGHT;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;
}

void Player::handle_input()
{
     //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= TUX_HEIGHT / 7; break;
            case SDLK_DOWN: yVel += TUX_HEIGHT / 7; break;
            case SDLK_LEFT: xVel -= TUX_WIDTH / 7; break;

            case SDLK_SPACE: 
            	bombs[BOMBS].x = TILE_WIDTH*(int)((box.x+ TILE_WIDTH/2 -xVel)/TILE_WIDTH);
            	bombs[BOMBS].y = TILE_HEIGHT*(int)((box.y+TILE_HEIGHT/2 -yVel)/TILE_HEIGHT); 
            	apply_surface(bombs[BOMBS].x ,bombs[BOMBS].y , bomb, screen );
            	
            	if(++BOMBS == TOTAL_TILES)
            		BOMBS = 0;
            	break;

            case SDLK_RIGHT: xVel += TUX_WIDTH / 7; break;
            //escape will kill the game
            case SDLK_ESCAPE: quit=true;break;
            //refreshes the map from the file : lazyBack.map 
            //to test this modify the values in the map and press 'r'
            case SDLK_r: set_tiles(tiles);break;
            default:break;
            
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += TUX_HEIGHT / 7; break;
            
            case SDLK_DOWN: yVel -= TUX_HEIGHT / 7; break;
            case SDLK_LEFT: xVel += TUX_WIDTH / 7; break;
            case SDLK_SPACE: break;
            case SDLK_RIGHT: xVel -= TUX_WIDTH / 7; break;
            default:break;
        }
    }
}

void Player::move( Tile *tiles[] )
{
    //Move the Player left or right
    box.x += xVel;

    //If the Player went too far to the left or right or touched a wall
    if( ( box.x < TILE_WIDTH + FIELD_X_OFFSET ) || ( box.x + TUX_WIDTH > FIELD_WIDTH + FIELD_X_OFFSET- TILE_WIDTH) || touches_wall( box, tiles ) )
    {
        //move back
        box.x -= xVel;
    }

    //Move the Player up or down
    box.y += yVel;

    //If the Player went too far up or down or touched a wall
    if( ( box.y < TILE_HEIGHT + FIELD_Y_OFFSET) || ( box.y + TUX_HEIGHT > FIELD_HEIGHT + FIELD_Y_OFFSET- TILE_HEIGHT ) || touches_wall( box, tiles ) )
    {
        //move back
        box.y -= yVel;
    }
}

void Player::show()
{
    //Show the Player
    apply_surface( box.x, box.y, player, screen );
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main( int argc, char* args[] )
{
    
    //The Player
    Player myPlayer;
    //generate random map	
    std::ofstream genmap( "lazy.map" );
    int sTime;
    long lTime;
    lTime = time(NULL);
    sTime = (unsigned)lTime/2;
    srand(sTime);
    //If the map couldn't be loaded
    if( genmap == NULL )
    {
        return false;
    }

    
    //Initialize the tiles
    for( int tx = 0, ty = -1; tx < TOTAL_TILES; tx++ )
    {
	// Place empty spaces at player location, 2 locations right, and one down.
	if(tx==20 || tx ==21 || tx ==37 ||tx==19 )
	{
		genmap<< "01" <<' ';
    		continue;
    	}
	// Places indestructables along left side.
    	if(tx%18==0)
    	{
    		if(++ty!=0)
    		    genmap<<'\n';
    		genmap<< "00" <<' ';
    		continue; 
    	}
    	// Places indestructables along the right side.
    	if(tx%18==16 || tx%18==17 )
    	{
    		genmap<< "00" <<' ';
    		continue; 
    	} 
    	// Places indestructables along top and bottom.
    	if((tx < 18 || tx > TOTAL_TILES -19))
    	{
    		genmap<< "00" <<' ';
    		continue;
    	}
    	// Place indestructables at every second row and second column
    	if( ty%2 == 0 && tx%2 == 0)
    	{
    		genmap<< "00" <<' ';
    		continue;
    	}
    	// Places either empty or destructable in every open location.
    	genmap<<'0'<<(rand()%2 + 1) <<' ';	
    }
    

    genmap.close();
    //The frame rate regulator
    Timer fps;

    //Initialize
    if( init() == false )
    {
        return 1;
    }
    background = load_image( "snowback.png" );
    bomb = load_image("tuxBommb2.xcf"); 
    apply_surface( FIELD_X_OFFSET, FIELD_Y_OFFSET, background, screen );
    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Clip the tile sheet
    clip_tiles();

    //Set the tiles
    if( set_tiles( tiles ) == false )
    {
        return 1;
    }

    //While the user hasn't quit
    while( quit == false )
    {
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //Handle events for the Player
            myPlayer.handle_input();

            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }

        //Move the Player
        myPlayer.move( tiles );

        
	apply_surface( FIELD_X_OFFSET, FIELD_Y_OFFSET, background, screen );
	
        //Show the tiles
        for( int t = 0; t < TOTAL_TILES; t++ )
        {
            tiles[ t ]->show();
        }

        //Show the Player on the screen
        myPlayer.show();
	for (int i =0; i < BOMBS; i++)
	{
		if(bombs[i].x != 0)
		    {
		    	apply_surface( bombs[i].x,bombs[i].y, bomb, screen );
		    }
	}
        //Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;
        }

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

    //Clean up
    clean_up( tiles );

    return 0;
}
