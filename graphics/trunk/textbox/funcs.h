#ifndef FUNCS_H
#define FUNCS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define TILE 35

#define MAP_HEIGHT 11
#define MAP_WIDTH 17

#define BLACK 0,0,0

#define FONT_PATH "lazy.ttf"
#define FONT_SIZE 14
#define FONT_WIDTH 7

#define ERROR -1

typedef struct _Point{
  int x,y;
} Point, *pPoint;


SDL_Surface *load_image(std::string);
void apply_surface(int, int, SDL_Surface*, SDL_Surface *);

void sdl_init();
char *request_input(SDL_Surface *, SDL_Surface *);

void apply_background( int x, int y, int width, SDL_Surface* source, SDL_Surface *screen);
void handle_input(SDL_Event, std::string);

#endif

