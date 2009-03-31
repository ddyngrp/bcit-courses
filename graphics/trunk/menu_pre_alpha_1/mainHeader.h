/*
 * mainHeader.h
 *
 *  Created on: 24-Mar-2009
 *      Author: d3vil
 */

#ifndef MAINHEADER_H_
#define MAINHEADER_H_
#include <string>
#include <string.h>
#include <strings.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_rotozoom.h"

#define NUM_OPTS 			5
#define DEF_FONT_SIZE 		70
#define DEF_SEL_FONT_SIZE 	100
#define SCREEN_WIDTH 		600
#define SCREEN_HEIGHT 		800

bool init_everything(SDL_Surface* screen);
SDL_Surface *load_image( std::string filename );
bool optimizeImg( SDL_Surface * img );

#endif /* MAINHEADER_H_ */
