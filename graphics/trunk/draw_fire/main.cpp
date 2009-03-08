
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define TILE 35

SDL_Surface *screen;

typedef struct _Point{
  int x,y;
} Point, *pPoint;

typedef struct _fire
{
  Point center;
  int up, down, left, right;
} fire, *pFire;

SDL_Surface *load_image(char []);
void display_image(SDL_Surface *image, SDL_Rect* src, SDL_Rect* dest, 
				SDL_Surface *screen, int x, int y);
void apply_surface(int, int, SDL_Surface*);
bool draw_fire(fire f);

int main( void ) 
{ 
	int x, y;
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
	fire_position.down = 3;
	fire_position.left = 0;
	fire_position.right = 7;

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


  SDL_Surface *imgWalkable;
  SDL_Surface *imgBreakable;
  SDL_Surface *imgIndestructable;
  SDL_Surface *temp;
  char grass[] = "grass.bmp";
  char indes[] = "indestructable.bmp";
  char destruct[] = "breakable.bmp";
	
  imgWalkable = load_image(grass);	
  imgIndestructable = load_image(indes);
  imgBreakable = load_image(destruct);
  
  SDL_Rect src, dest;
 
  src.x = 0;
  src.y = 0;
  src.w = TILE;
  src.h = TILE;

  dest.w = TILE;
  dest.h = TILE;
  for(x = 0; (x/TILE) < 17; x += TILE){
    for(y = 0; (y/TILE) < 11; y += TILE){
      dest.x = x;
      dest.y = y;
      if(map[(y/TILE)][(x/TILE)] == 0){
        SDL_BlitSurface(imgIndestructable, &src, screen, &dest);
      }else if(map[(y/TILE)][(x/TILE)] == 1){
        SDL_BlitSurface(imgWalkable, &src, screen, &dest);
      }else{
        SDL_BlitSurface(imgBreakable, &src, screen, &dest);
      }
    }
  }
  draw_fire(fire_position);
  SDL_Flip(screen);
  SDL_Delay(5000);
  SDL_Quit(); 
  return 0; 
} 

bool draw_fire(fire f){
  SDL_Surface *imgCenter;
  SDL_Surface *imgVertical;
  SDL_Surface *imgHorizontal;
  SDL_Surface *imgLeftEnd;
  SDL_Surface *imgRightEnd;
  SDL_Surface *imgTopEnd;
  SDL_Surface *imgBottomEnd;
  SDL_Surface *temp;
 
  imgCenter 	= load_image("center.xcf");
  imgVertical	= load_image("vertical.xcf");
  imgHorizontal = load_image("horizontal.xcf");
  imgLeftEnd	= load_image("leftEnd.xcf");
  imgRightEnd	= load_image("rightEnd.xcf");
  imgTopEnd	= load_image("topEnd.xcf");
  imgBottomEnd	= load_image("bottomEnd.xcf");
  
  apply_surface((f.center.x*TILE), (f.center.y*TILE), imgCenter);
  
  if(f.left != 0){
    apply_surface((f.center.x - f.left) * TILE, (f.center.y) * TILE, imgLeftEnd);
    f.left--;
  }
  for(int position = (f.center.x - f.left); position != f.center.x; position++)
    apply_surface((position * TILE), f.center.y * TILE, imgHorizontal);
  	
  if(f.right != 0){
    apply_surface((f.center.x + f.right) * TILE, (f.center.y) * TILE, imgRightEnd);
    f.right--;
  }
  for(int position = (f.center.x + f.right); position != f.center.x; position--)
    apply_surface((position * TILE), f.center.y * TILE, imgHorizontal);
  
  if(f.up != 0){
    apply_surface(f.center.x * TILE, (f.center.y - f.up) * TILE, imgTopEnd);
    f.up--;
  }
  for(int position = (f.center.y - f.up); position != f.center.y; position++)
    apply_surface(f.center.x * TILE, (position * TILE), imgVertical);
  	
  if(f.down != 0){
    apply_surface(f.center.x * TILE, (f.center.y + f.down) * TILE, imgBottomEnd);
    f.down--;
  }
  for(int position = (f.center.y + f.down); position != f.center.y; position--)
  	apply_surface(f.center.x * TILE, (position * TILE), imgVertical);
  return true;
}

//loads the images
SDL_Surface *load_image(string filename)
{
  SDL_Surface* loadedImage = NULL; 
  SDL_Surface* optimizedImage = NULL; 
  
  loadedImage = IMG_Load(filename.c_str()); 
  
  if( loadedImage != NULL ) { 
    optimizedImage = SDL_DisplayFormat( loadedImage ); 
    SDL_FreeSurface( loadedImage ); 
  } 
  return optimizedImage;
}

//shows images on screen
void apply_surface( int x, int y, SDL_Surface* source)
{
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
