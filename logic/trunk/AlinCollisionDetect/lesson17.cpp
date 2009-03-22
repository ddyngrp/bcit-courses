/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.*/

//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include "SDL/SDL_thread.h" 

#define WALL 1
#define GRIDSIZE 17
#define PLAYER1 2
#define BOMB1 3
#define PBOMB 4

//Screen attributes
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 20;

//The attributes of the Player
const int SQUARE_WIDTH = 20;
const int SQUARE_HEIGHT = 20;

//The surfaces
SDL_Surface *square  = NULL;
SDL_Surface *bomb    = NULL;
SDL_Surface *screen  = NULL;
SDL_Surface *wall2   = NULL;

//The event structure
SDL_Event event;
SDL_Thread *bombThread= NULL;
//The wall
SDL_Rect wall;

int map[17][17];
int prevX, prevY;
class Bomb
{
    private:
    SDL_Rect bombSquare;
    
    
    public:
    Bomb();
    
    void setRect(int, int);
    
    int getRectX(){return bombSquare.x;};
    
    int getRectY(){return bombSquare.y;};
    
    void explode();
    
    void placeBomb();
};

//The Player
class Player
{
    private:
    //The collision box of the Player
    SDL_Rect box;
    Bomb myBomb[5];
    int isPlanted[6];
    int bombCount;

    //The velocity of the Player
    int xVel, yVel;
    
    public:
    //Initializes the variables
    Player();

    //Takes key presses and adjusts the Player's velocity
    void handle_input();

    //Moves the Player
    void move();

    //Shows the Player on the screen
    void show();
    
    void plantBomb();
    
    void removeBomb(){bombCount--;};
    
    void setBombStatus(int bombNo, bool status);
    
    bool getBombStatus(int bombNo){return isPlanted[bombNo];};
};

//The timer
class Timer
{
    public:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

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
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void InitMap()
{
	int i, j;

	for(i = 0; i < GRIDSIZE; i++)
	{
		for(j = 0; j < GRIDSIZE; j++)
		{
			map[i][j] = 0; 
		} 
	}
	for(i = 0; i < GRIDSIZE; i++)
	{
		map[0][i]  = WALL;
		map[i][0]  = WALL;
		map[GRIDSIZE - 1][i] = WALL;
		map[i][GRIDSIZE - 1] = WALL; 
	}
	
	for(i = 0; i < GRIDSIZE; i +=2)
	{
		for(j = 0; j < GRIDSIZE; j += 2)
		{
			map[i][j] = WALL;
		}
	}
	
	//map[1][1] = PLAYER1;
}

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

void DrawMap()
{
	int i, j;
	
	for(i = 0; i < GRIDSIZE; i++)
	{
		for(j = 0; j < GRIDSIZE; j++)
		{
			if(map[i][j] == WALL)
				apply_surface( i * 35, j * 35, wall2, screen);			
		}
	}
}

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
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
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
    SDL_WM_SetCaption( "Move the Player", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the Player image
    square = load_image( "square.bmp" );
    bomb   = load_image( "circle.bmp" );
    wall2   = load_image( "wall.bmp" );

    //If there was a problem in loading the square
    if( square == NULL )
    {
        return false;
    }

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( square );

    //Quit SDL
    SDL_Quit();
}


Player::Player()
{
    //Initialize the offsets
    box.x = 35;
    box.y = 35;

    //Set the Player's dimentions
    box.w = SQUARE_WIDTH;
    box.h = SQUARE_HEIGHT;

    //Initialize the velocity
    xVel = 0;
    yVel = 0;
    
    bombCount = 0;
}

void Player::plantBomb()
{
	bombCount++;
	map[box.x/35][box.y/35] = PBOMB;
}

Bomb::Bomb()
{
    bombSquare.x = 0;
    bombSquare.y = 0;;
}

void Bomb::explode()
{
    //isPlanted = 0;
}

void Bomb::setRect(int x, int y)
{
    bombSquare.x = x;
    bombSquare.y = y;
}
void Player::setBombStatus(int bombNo, bool status)
{
    isPlanted[bombNo] = status;
}

void Player::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel -= 10; break;
            case SDLK_DOWN: yVel += 10; break;
            case SDLK_LEFT: xVel -= 10; break;
            case SDLK_RIGHT: xVel += 10; break;
            case SDLK_SPACE:	if(bombCount > 4)
            			{
            				break;
            			}
            			else
            			{
            				myBomb[bombCount].setRect(box.x, box.y);
            				setBombStatus(bombCount, 1);
                             		plantBomb();
                             		
                             		break;
                             	}
            default: ;
        }
    }
    //If a key was released
    else if( event.type == SDL_KEYUP )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: yVel += 10; break;
            case SDLK_DOWN: yVel -= 10; break;
            case SDLK_LEFT: xVel += 10; break;
            case SDLK_RIGHT: xVel -= 10; break;
            case SDLK_SPACE: break;
            default: ;
        }
    }
}

void Player::move()
{
	int yt,yb,xl,xr;
	
	box.x += xVel;
	box.y += yVel;
	 
	yt= box.y;
	yb= box.y + 30;
	
	xl= box.x;
	xr= box.x + 30;
	/*
	
	printf("xl = %d\nxr = %d\nyt = %d\nyb= %d \n", xl/35, xr/35, yt/35 ,yb/35);
	printf("map: map[xl/35][yt/35], %d\n", map[xl/35][yt/35]);
	printf("map: map[xr/35][yb/35], %d\n", map[xr/35][yb/35]);
	printf("map: map[xl/35][yb/35], %d\n", map[xl/35][yb/35]);
	printf("map: map[xr/35][yt/35], %d\n", map[xr/35][yt/35]);
	printf("*******\n");	
	*/
	prevX = box.x;
	prevY = box.y;
	
       
    //Move the Player up or down
    if(map[xl/35][yt/35] != 0 || map[xr/35][yb/35] != 0 
    	|| map[xl/35][yb/35] != 0 || map[xr/35][yt/35] != 0 )
    {
    	box.y -= yVel;
    	box.x -= xVel;
	}
}

void Player::show()
{
	apply_surface( box.x, box.y, square, screen );
    //Show the Player
    for(int i = 0; i < 17; i++)
    {
    	for(int j = 0; j < 17; j++)
    	{
    		if(map[i][j] == BOMB1)
    		{
    			apply_surface( i * 35, j * 35, bomb, screen );
    		}
    	}
    }
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
    //Quit flag
    bool quit = false;

    //The Player
    Player myPlayer;
    for(int i = 0; i < 6; i++)
        myPlayer.setBombStatus(i, 0);
    //The frame rate regulator
    Timer fps;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    //Set the wall
    //wall.x = 300;
    //wall.y = 40;
    //wall.w = 40;
    //wall.h = 400;
    
    InitMap();

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
        myPlayer.move();

        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        //Show the wall
        //SDL_FillRect( screen, &wall, SDL_MapRGB( screen->format, 0x77, 0x77, 0x77 ) );

        //Show the Player on the screen
        myPlayer.show();
        DrawMap();

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
    clean_up();

    return 0;
}
