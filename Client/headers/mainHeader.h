
#ifndef MAINHEADER_H_
#define MAINHEADER_H_
//linux c/c++ headers
#include <string>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/sem.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <ctype.h>
#include <signal.h>
#include <iostream>
//SDL headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_rotozoom.h"

//local headers
#include "defs.h"
#include "OkCancel.h"
#include "POptMenu.h"
#include "MainMenu.h"
#include "InputOkCancel.h"
#include "s_player.h"
#include "user_map.h"
#include "n_network.h"
#include "textbox.h"

/* Global Defines */



//classes
class OkCancel;
class DPlaya;
class user_map;

//prototypes
bool draw_status_bar(std::string players[], SDL_Surface *tux[],SDL_Surface *screen,SDL_Color textColor );
bool init_everything(SDL_Surface** screen);
SDL_Surface *load_image( std::string filename );
bool optimizeImg( SDL_Surface ** img );
int start(int argc, char *argv[],  SDL_Surface *screen, OkCancel* exitMenu);
void getMenuItems(std::string menu[], FILE* fp, const char * type, int size);
//map
unsigned char** genRandomMap(int rowNum, int colNum);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination);
bool sdl_init(SDL_Surface ** screen);
SDL_Surface *load_image( std::string filename );
//logic
void fork_off(int tcpSockFd, int udpSockFd, struct sockaddr_in *server, DPlaya * allPlayers[8], user_map *map, SDL_Surface *screen);
void sig_handler (int sig);
void handle_input(int tcpSockFd, int udpSockFd, struct sockaddr_in *server, int Key);
void convertMap(unsigned char inMap[15][15], unsigned char outMap[17][17]);
//serialize
int serialize_player(DPlaya *player, char *buf, size_t buflen);
int unserialize_player(char *buf, DPlaya *player);
//network
int connection_setup(char * servIp);
void *get_in_addr(struct sockaddr *sa);
void sig_handler (int sig);
int start_udp_client(char *hostname);

#endif /* MAINHEADER_H_ */
