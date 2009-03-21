#ifndef LOGIC_H
#define LOGIC_H

#include "general.h"
#include "graphics.h"

void fork_off(int sockfd);
void sig_handler (int sig);
void handle_input(SDL_Event event);

#endif

