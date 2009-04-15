#ifndef LOGIC_H
#define LOGIC_H

#include "general.h"
#include "Map/init.h"
#include "Map/user_map.h"
#include "s_player.h"

void fork_off(int tcpSockFd, int udpSockFd, DPlaya * allPlayers[8], user_map *map, SDL_Surface *screen);
void sig_handler (int sig);
void handle_input(int tcpSockFd, int udpSockFd, int Key);
void convertMap(unsigned char inMap[15][15], unsigned char outMap[17][17]);
#endif
