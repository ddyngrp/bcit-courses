#ifndef SERVER_H
#define SERVER_H

#include "mainHeader.h"
/* s_player.cpp */
bool   	addPlayer(const int);

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

/* s_init.cpp */
bool	initialize_server(struct server_info *);

struct fire {
	int left, right, up, down;
	int x,y;
};

struct coords {
	int x,y;
	int len;
    	int id;
};

struct server_info
{
	unsigned char 		grid[GRID_HEIGHT][GRID_WIDTH];
	DPlaya 			    *player_array;
	unsigned char 		player_count;
	bool 			    game_running;
};

#endif
