#include "funcs.h"

using std::string;

SDL_Surface *screen;

int main( void ) 
{ 
	fire fire_position;
	int map[MAP_HEIGHT][MAP_WIDTH] = {
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
	fire_position.down = 3;
	fire_position.left = 2;
	fire_position.right = 4;

  //Start SDL
  sdl_init();
  /*--------------------------------------------------------*/


  SDL_Surface *imgWalkable;
  SDL_Surface *imgBreakable;
  SDL_Surface *imgIndestructable;
	
  imgWalkable = load_image("../images/map/grass.bmp");	
  imgIndestructable = load_image("../images/map/indestructable.bmp");
  imgBreakable = load_image("../images/map/breakable.bmp");

  game_loop(imgWalkable, imgIndestructable, imgBreakable, map);

  draw_fire(fire_position);
  SDL_Flip(screen);
  SDL_Delay(5000);
  return 0; 
} 

void game_loop(SDL_Surface *imgWalkable, SDL_Surface *imgIndestructable, SDL_Surface *imgBreakable, int map[MAP_HEIGHT][MAP_WIDTH]){
	int x, y;
  for(x = 0; (x/TILE) < MAP_WIDTH; x += TILE){
    for(y = 0; (y/TILE) < MAP_HEIGHT; y += TILE){
      switch(map[(y/TILE)][(x/TILE)]){
      case 0:
        apply_surface(x, y, imgIndestructable);
        break;
      case 1:
        apply_surface(x, y, imgWalkable);
        break;
      case 2:
        apply_surface(x, y, imgBreakable);
        break;
      default:
        apply_surface(x, y, imgWalkable);
        break;
      }
    }
  }
}

void sdl_init(){
  SDL_Init( SDL_INIT_EVERYTHING );
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {//turn video on
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  screen = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 16, SDL_DOUBLEBUF);//video settings
  if (screen == NULL) {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    exit(2);
  }
  SDL_WM_SetCaption( "Tux Bomber", NULL ); 
}


//loads the images
SDL_Surface *load_image(string filename){
  SDL_Surface* optimizedImage = NULL; 
  SDL_Surface* loadedImage = NULL; 
  
  loadedImage = IMG_Load(filename.c_str()); 
  if( loadedImage != NULL ) { 
    optimizedImage = SDL_DisplayFormat( loadedImage ); 
    SDL_FreeSurface( loadedImage ); 
  }
  if( optimizedImage != NULL ) { 
    Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ); 
    SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); 
  }
  return optimizedImage;
}

//shows images on screen
void apply_surface( int x, int y, SDL_Surface* source){
  //Holds offsets
  SDL_Rect offset;
  SDL_Rect src;

  src.x = 0;
  src.y = 0;
  src.w = TILE;
  src.h = TILE;

  //Get offsets
  offset.x = x;
  offset.y = y;
  offset.w = TILE;
  offset.h = TILE;

  //Blit
  SDL_BlitSurface( source, &src, screen, &offset );
}
