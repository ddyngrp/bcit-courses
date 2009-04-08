/******************************************************************************
 *  Source File: network.c
 *
 *  Program:     Tux Bomber
 *
 *  Functions:  *get_in_addr(struct sockaddr *sa)
 *				void receive_packet(char b, int index)
 *              
 *  Date:       March 2, 2009
 *
 *  Revisions:  March 20, 2009 - Steffen L. Norgren
 *                   Updated headers to cornform to Aman's standards
 *              March 29, 2009 - Steffen L. Norgren
 *                   Moved the sole function from "tools.c" to here as it
 *                   can be considered part of networking.
 *				April 6, 2009 - David Young
 *					Changed a WHOLE bunch of stuff yesterday and today.
 *					Today I took out a bunch of functions that aren't being used anymore.
 *				April 8, 2009 - David Young
 *					Took out almost every network-related function I
 *					had previously written. (No longer needed)
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
 *  Function:    get_in_addr
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

