/*This source code copyrighted by Lazy Foo' Productions (2004-2009) and may not
be redestributed without written permission.*/

//The headers
#include "player.h"
#include "timer.h"
using namespace std;


//The frame rate
const int FRAMES_PER_SECOND = 20;

//The attributes of the Player
const int SQUARE_WIDTH = 20;
const int SQUARE_HEIGHT = 20;


//The surfaces
SDL_Surface *screen;
SDL_Surface *square  = NULL;
SDL_Surface *bomb    = NULL;
SDL_Surface *wall2   = NULL;

//The event structure
SDL_Event event;
SDL_Thread *bombThread= NULL;
//The wall
SDL_Rect wall;
bool quit;

int main( void ) 
{ 
  int x, y;
  Timer fps;
  //Player myPlayer;
  SDL_Surface *imgWalkable;
  SDL_Surface *imgBreakable;
  SDL_Surface *imgIndestructable;
  SDL_Surface *temp;

  
  fire fire_position;
  int map[11][17] = {//5,5
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,2,2,1,2,2,2,1,2,2,2,2,1,1,0},
    {0,1,0,2,0,2,0,1,0,1,0,1,0,2,0,1,0},
    {0,1,2,2,1,1,1,2,2,2,2,2,2,2,1,2,0},
    {0,2,0,2,0,1,0,2,0,1,0,2,0,2,0,2,0},
    {0,2,2,1,1,0,1,1,2,2,1,2,2,2,2,1,0},
    {0,1,0,2,0,1,0,2,0,2,0,1,0,2,0,2,0},
    {0,2,2,1,2,1,2,2,2,2,2,2,1,2,2,1,0},
    {0,1,0,2,0,2,0,1,0,2,0,2,0,1,0,1,0},
    {0,1,1,1,2,2,1,2,2,2,2,2,2,1,1,1,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  };
  
  fire_position.center.x = 5;
  fire_position.center.y = 5;

  fire_position.up = 2;
  fire_position.down = 2;
  fire_position.left = 2;
  fire_position.right = 2;
  
  if( init(screen) == false )
    {
        return 1;
    }

  //Start SDL
  /*
   * SDL_Surface *screen;
   * 
   */
  /*--------------------------------------------------------*/
  SDL_Init( SDL_INIT_EVERYTHING );

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {//turn video on
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
 
  atexit(SDL_Quit);
 
  screen = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 16, SDL_DOUBLEBUF | SDL_FULLSCREEN);//video settings
  if (screen == NULL) {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    return 1;
  }
  /*--------------------------------------------------------*/

  Player myPlayer;

  wall2   = load_image("center.xcf");
  imgWalkable = load_image("grass.bmp");	
  imgIndestructable = load_image("indestructable.bmp");
  imgBreakable = load_image("breakable.bmp");
  
  SDL_Rect src, dest;
 
  src.x = 0;
  src.y = 0;
  src.w = TILE;
  src.h = TILE;

  dest.w = TILE;
  dest.h = TILE;
  /*for(x = 0; (x/TILE) < 17; x += TILE)
  {
    for(y = 0; (y/TILE) < 11; y += TILE)
    {
      dest.x = x;
      dest.y = y;
      if(map[(y/TILE)][(x/TILE)] == 0)
        SDL_BlitSurface(imgIndestructable, &src, screen, &dest);
      else if(map[(y/TILE)][(x/TILE)] == 1)
        SDL_BlitSurface(imgWalkable, &src, screen, &dest);
      else
        SDL_BlitSurface(imgBreakable, &src, screen, &dest);
      }
  }*/
  
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
        //myPlayer.move();

        //Fill the screen white
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

        //Show the wall
        //SDL_FillRect( screen, &wall, SDL_MapRGB( screen->format, 0x77, 0x77, 0x77 ) );

        //Show the Player on the screen
        //myPlayer.show();
        DrawMap(map, wall2, screen);

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
    
  SDL_Flip(screen);
  SDL_Delay(5000);
  SDL_Quit(); 
  return 0; 
} 


