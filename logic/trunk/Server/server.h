ifndef SERVER_H
#define SERVER_H

#include <cstdio>
#include "s_player.h"
#include "defs.h"
#include "headerMain.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "user_map.h"
#include "funcs.h"
#include <pthread.h>

/* s_movement.cpp */
void   	move_player(const int, const int);

/* s_player.cpp */
bool   	addPlayer(const int);
void 	player_quit(const int playerID);

/* s_network.cpp */
void recieve_packet(const char, const int);

/* s_bomb.cpp */
void   	plant_bomb(const int);
void   	explode_bomb(const int, const int, const int);
void   	start_fuse(const int, const int, const int);
void    fire_to_map(struct fire);
void    *countdown(void *);

/* s_explosion.cpp */
void   	kill_if_here(const int, const int);
bool   	block_here(const int, const int);
void 	destroy_block(const int, const int);
void 	send_player_class(DPlaya *player);
void	send_map(const unsigned char grid[17][18]);

struct fire {
	int left, right, up, down;
	int x,y;
};

struct coords {
	int x,y;
	int len;
        int id; 
};

unsigned char 		grid[17][18];
DPlaya 			**player_array;
unsigned char 		player_count = 0;
bool 			game_running = false;

#endif
