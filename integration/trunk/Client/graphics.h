#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "general.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_thread.h" 

#define WALL 1
#define GRIDSIZE 17
#define PLAYER1 2
#define BOMB1 3
#define PBOMB 4
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define TILE 35
#define SCREEN_BPP 32
#define SQUARE_WIDTH 20;
#define SQUARE_HEIGHT 20;

typedef struct _Point{
  int x,y;
} Point, *pPoint;

typedef struct _fire
{
  Point center;
  int up, down, left, right;
} fire, *pFire;

SDL_Surface *load_image(std::string filename);
bool draw_fire(fire f, SDL_Surface * screen);bool init(SDL_Surface *screen);
void display_image(SDL_Surface *image, SDL_Rect* src, SDL_Rect* dest, SDL_Surface *screen, int x, int y);
void DrawMap(int map[11][17], SDL_Surface *wall2, SDL_Surface *screen);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);

#endif




