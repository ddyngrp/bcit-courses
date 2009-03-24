#ifndef FUNCS_H
#define FUNCS_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800
#define TILE 35

#define MAP_HEIGHT 11
#define MAP_WIDTH 17

#define ERROR -1

typedef struct _Point{
  int x,y;
} Point, *pPoint;

typedef struct _fire
{
  Point center;
  int up, down, left, right;
} fire, *pFire;

SDL_Surface *load_image(std::string);
void apply_surface(int, int, SDL_Surface*);

void sdl_init();
void game_loop(SDL_Surface *, SDL_Surface *, SDL_Surface *, int [MAP_HEIGHT][MAP_WIDTH]);

bool draw_fire(fire f);
void draw_fire_center(Point center);
void draw_fire_arm_down(Point, int);
void draw_fire_arm_up(Point, int);
void draw_fire_arm_right(Point, int);
void draw_fire_arm_left(Point, int);

#endif

