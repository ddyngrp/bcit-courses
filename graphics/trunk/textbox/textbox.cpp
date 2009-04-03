#include "funcs.h"
using std::string;

SDL_Surface *screen;

/**/
int main(int argc, char **argv){
  SDL_Surface *background;

  sdl_init();
  if (screen == NULL) {
    printf("Unable to set video mode: %s\n", SDL_GetError());
    exit(2);
  }
  background = load_image( "background.png" );
  apply_background( 0, 0, 200, background, screen );

  request_input(screen, background);
  SDL_FreeSurface(screen);
}

char *request_input(SDL_Surface *screen, SDL_Surface *background){
  SDL_Surface *message = NULL;
  string str;
  bool quit = false;
  int cursor = 0;

  SDL_Event event;
  TTF_Font *font = NULL;
  SDL_Color textColor = {BLACK};

  if((font = TTF_OpenFont( FONT_PATH, FONT_SIZE )) == NULL){
    printf("Couldn't open desired font type: %s\n", SDL_GetError());
    exit(4);
  }

  char *user_input;

  while(quit == false){
    if( SDL_PollEvent( &event ) ){
      handle_input(event, str);
      message = TTF_RenderText_Solid(font, str.c_str(), textColor);
    }
    if(message != NULL){
      apply_background( 0, 0, 200, background, screen );
      apply_surface( cursor, 0, message, screen );
      cursor += FONT_WIDTH;
    }
    if( SDL_Flip(screen) == ERROR){
      printf("Couldn't paint screen: %s\n", SDL_GetError());
      fflush(stdout);
      exit(5);
    }
  }
  SDL_FreeSurface(message);
  TTF_CloseFont( font );
  TTF_Quit();

  return user_input;
}

void handle_input(SDL_Event event, string str){ 
  if( event.type == SDL_KEYDOWN ) { 
  string temp = str; 
    if( str.length() <= 16 ) { 
      if( event.key.keysym.unicode == (Uint16)' ' ) {
        str += (char)event.key.keysym.unicode; 
      } 
      if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) ) { 
        str += (char)event.key.keysym.unicode; 
      }else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) ) { 
        str += (char)event.key.keysym.unicode; 
      }else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) ) { 
        str += (char)event.key.keysym.unicode; 
      } 
    } 
    if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) ) { 
      str.erase( str.length() - 1 ); 
    }
  } 
} 

/*
  Author = Colby
  
*/
void sdl_init(){
  SDL_Init( SDL_INIT_EVERYTHING );
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {//turn video on
    printf("Unable to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  SDL_WM_SetCaption( "Tux Bomber", NULL ); 
  //Initialize SDL_ttf
  if( TTF_Init() == ERROR ){
    printf("Unable to turn texts on: %s\n", SDL_GetError());
    exit(6);
  }
  screen = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 16, SDL_DOUBLEBUF);
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
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface *screen){
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
//shows images on screen
void apply_background( int x, int y, int width, SDL_Surface* source, SDL_Surface *screen){
  //Holds offsets
  SDL_Rect offset;
  SDL_Rect src;

  src.x = 0;
  src.y = 0;
  src.w = width;
  src.h = FONT_SIZE;

  //Get offsets
  offset.x = x;
  offset.y = y;
  offset.w = 600;
  offset.h = 600;

  //Blit
  SDL_BlitSurface( source, &src, screen, &offset );
}
