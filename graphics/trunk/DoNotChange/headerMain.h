/*
 * headerMain.h
 *
 *  Created on: 24-Mar-2009
 *      Author: d3vil
 */

#ifndef HEADERMAIN_H_
#define HEADERMAIN_H_

#include <unistd.h>
#include <iostream>
#include <string.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#define BLOCK_SIZE 35

int** genRandomMap(int rowNum, int colNum);
#endif /* HEADERMAIN_H_ */
