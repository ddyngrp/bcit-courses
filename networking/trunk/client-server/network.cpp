/******************************************************************************
 *  Source File: network.c
 *
 *  Program:     Tux Bomber
 *
 *  Functions:   *get_in_addr(struct sockaddr *sa)
 *               send_map(unsigned char *map, size_t len)
 *               recv_map(unsigned char *map, size_t len)
 *               transfer(unsigned char *data, size_t len)
 *               add_coords_xy(int x, int y, unsigned char *data, size_t len)
 *               process_data(unsigned char *data, size_t len)
 *               
 *  Date:        March 2, 2009
 *
 *  Revisions:   March 20, 2009 - Steffen L. Norgren
 *                   Updated headers to cornform to Aman's standards
 *               March 29, 2009 - Steffen L. Norgren
 *                   Moved the sole function from "tools.c" to here as it
 *                   can be considered part of networking.
 *				April 6, 2009 - David Young
 *					Changed a WHOLE bunch of stuff yesterday and today.
 *					Today I took out a bunch of functions that aren't being used anymore.
 * 
 *  Designer:    David Young, Steffen L. Norgren
 *  Programmer:  David Young, Steffen L. Norgren
 * 
 *  Description: Set the connection type to TCP or UDP.
 *
 *****************************************************************************/

#include "network.h"
#include "serialize.h"
#include "server_stuff/s_defs.h"
#include "DPlaya.h"

extern DPlaya *player_array[MAX_PLAYERS];
extern unsigned char grid[15][15];
extern int mode, conn_type, sock;
extern struct tcp_server *ptcp_server;
extern struct sockaddr_in server;

int get_player_loc(unsigned long ip_netformat) {
	int pos;
	
	for(pos = 0; pos < MAX_PLAYERS; pos++) {
		if(player_array[pos] != NULL && player_array[pos]->get_ip_netformat() == ip_netformat) {
			return pos;
		}
	}
	
	return -1;
}

void receive_packet(char b, int index) {
	if (b == MOVE_UP) 
		player_array[index]->move(grid, MOVE_UP);
	else if (b == MOVE_DOWN) 
		player_array[index]->move(grid, MOVE_DOWN);
	else if (b == MOVE_LEFT) 
		player_array[index]->move(grid, MOVE_LEFT);
	else if (b == MOVE_RIGHT)
		player_array[index]->move(grid, MOVE_RIGHT);
//	else if (b == PLANT_BOMB)
		//plant_bomb(index);
}

/******************************************************************************
 *  Function:    set_conn_type
 * 
 *  Date:        March 2, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    Steffen L. Norgren
 *  Programmer:  Steffen L. Norgren
 * 
 *  Interface:   *get_in_addr(struct sockaddr *sa)
 *		            sockaddr *sa: pointer to the socket address struct
 * 
 *  Returns:     sockaddr_in if the address is IPv4
 *               sockaddr_in6 if the address is IPv6
 * 
 *  Description: Returns an appropriate socket struct based on whether the
 *               input address is IPv4 or IPv6
 *
 *****************************************************************************/
void *get_in_addr(struct sockaddr *sa) {
	/* Check if the address is IPv4 */
	if (sa->sa_family == AF_INET) {
		/* Return the IPv4 socket address */
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	/* Return the IPv6 socket address */
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/******************************************************************************
 *  Function:    send_map
 * 
 *  Date:        March 2, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   send_map(unsigned char *map, size_t len)
 *                   unsigned char map[MAP_ROWS][MAP_COLS]: The map's character representation
 *
 *  Returns:     0 on success or (-1) if malloc fails.
 * 
 *  Description: Sends the map to the client.
 *
 *****************************************************************************/
int send_map(int *sockets, int num_sockets, unsigned char map[MAP_ROWS][MAP_COLS]) {
	unsigned char *data = (unsigned char *)calloc((MAP_ROWS * MAP_COLS) + 1, sizeof(unsigned char));
	int a, len = MAP_ROWS * MAP_COLS;
	
	if(data == NULL) {
		fprintf(stderr, "malloc failed in send_map\n");
		return -1;
	}
	
	data[iTYPE] = MAP;
	memcpy(data + 1, map, len);
	
	for(a = 0; a < num_sockets; a++) {
		if(transfer(sockets[a], data, len + 1) < len + 1) { /* not the whole len was transfered */
			return -1;
		}
	}
	
	return 0;
}

/******************************************************************************
 *  Function:    recv_map
 * 
 *  Date:        March 2, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   recv_map(unsigned char *map, size_t len)
 *                   unsigned char *map: The map's character representation
 *                   size_t len: The length of the map string
 *
 *  Returns:     0 on success or (-1) if malloc fails.
 * 
 *  Description: Receives the map from a client.
 *
 *****************************************************************************/
int recv_map(unsigned char *map, size_t len) {
	/* this is where logic converts the uchar* into the format they want */
	return 0;
}

/******************************************************************************
 *  Function:    transfer
 * 
 *  Date:        March 2, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   transfer(unsigned char *data, size_t len)
 *                   unsigned char *data: The string of data to transfer
 *                   size_t len: The length of the data string
 *
 *  Returns:     0 on success or (-1) on error
 * 
 *  Description: Transfer the data, regardless of TCP/UDP
 *
 *****************************************************************************/
int transfer(int sockt, unsigned char *data, size_t len) {
	if(sockt == -1) { /* the socket is invalid */
		return -1;
	}
	
	if(conn_type == TCP) {
		return send(sockt, data, len, 0);
	} else if(conn_type == UDP) {
		return sendto(sockt, data, len, 0, (struct sockaddr *)&server, sizeof(server));
	} else { /* this should never happen */
		return -1;
	}
}

/******************************************************************************
 *  Function:    add_coords_xy
 * 
 *  Date:        March 2, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   add_coords_xy(int x, int y, unsigned char *data, size_t len)
 *                   int x: The first coordinate to add
 *                   int y: The second coordinate to add
 *                   unsigned char *data: The data string to add the coords into
 *                   size_t len: The length of the data string
 *
 *  Returns:     0 on success or (-1) on error
 * 
 *  Description: Writes x and y into the string and appends a null-char
 *
 *****************************************************************************/
int add_coords_xy(int x, int y, unsigned char *data, size_t len) {
	if(len < (2 * sizeof(int)) + 1) {
		fprintf(stderr, "len is < required length in add_coords_xy\n");
		return -1;
	}
	
	memcpy(data, &x, sizeof(int));
	memcpy(data + sizeof(int), &y, sizeof(int));
	
	data[len - 1] = '\0';
	
	return 0;
}

