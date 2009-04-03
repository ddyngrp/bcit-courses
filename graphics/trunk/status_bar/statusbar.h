#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

bool draw_status_bar(std::string players[],SDL_Surface *tux[],SDL_Surface *screen,SDL_Color textColor );

#define BACKGROUND_IMG "background1.jpg"
#define FONT "ActionIs.ttf"
#define FONT_SIZE 25

#define PLAYERCOUNT 8
#define INC_X 150
#define INC_Y 50
#define RESET_Y 1
#define X_POS 30


#endif
