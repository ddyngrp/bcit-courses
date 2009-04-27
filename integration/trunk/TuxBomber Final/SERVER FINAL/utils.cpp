#include "utils.h"

extern DPlaya *player_array[MAX_PLAYERS];
extern unsigned char player_count;

/******************************************************************************
 *  Function:  	add_player
 * 
 *  Date:      	April 8, 2009
 *
 *  Revisions: 	
 * 
 *	Designer:   David Young
 * 	Programmer:	David Young
 * 
 * 	Interface:	add_player(unsigned long ip_netformat)
 * 
 * 	Returns:	The players new position within the array (if successful) or
 *				MAX_PLAYERS if the array is full.
 *				(-1) if an error occurs.
 * 
 *  Description: Attempts to add a player to player_array and returns their position.
 *
 *****************************************************************************/
int add_player(unsigned long ip_netformat) {
	int pos;

	if((pos = get_player_loc(ip_netformat)) == MAX_PLAYERS) { /* player not found */
		if((pos = get_first_avail()) == -1) { /* no free space in the array */
			return MAX_PLAYERS;
		} else {
			player_array[pos] = new DPlaya();
			player_array[pos]->setID(pos); /* set the player's ID to their position in player_array */
		}
	}
	
	if(pos < 0 || pos >= MAX_PLAYERS) { /* if not 0-MAX_PLAYERS, it's invalid */
		return (-1);
	}
	
	return pos;
}

/******************************************************************************
 *  Function:   get_player_loc
 * 
 *  Date:       April 8, 2009
 *
 *  Revisions:  
 * 
 *  Designer:   David Young
 *  Programmer: David Young
 * 
 *  Interface:  get_player_loc(unsigned long ip_netformat)
 * 
 *  Returns:    Position of the player within the array, or MAX_PLAYERS if not found.
 * 
 *  Description: Searches player_array for the player associated with the IP address
 *					stored in ip_netformat and returns their position within the array
 *					(if successful) or MAX_PLAYERS if unsuccessful.
 *
 *****************************************************************************/

int get_player_loc(unsigned long ip_netformat) {
	int pos;
	
	for(pos = 0; pos < MAX_PLAYERS; pos++) {
		if(player_array[pos] != NULL && player_array[pos]->getIPAddress() == ip_netformat) { /* if this player's IP is the same as the IP we're searching for */
			return pos;
		}
	}

	return -1; /* should be MAX_PLAYERS if we've made it here */
}

/******************************************************************************
 *  Function:   get_first_avail
 * 
 *  Date:       April 8, 2009
 *
 *  Revisions:  
 * 
 *  Designer:   David Young
 *  Programmer: David Young
 * 
 *  Interface:  get_first_avail()
 * 
 *  Returns:    Index of the first avilable position in player_array or -1.
 * 
 *  Description: Finds the first availble position in player_array and returns
 *					either its index or (-1) if the array is full.
 *
 *****************************************************************************/
int get_first_avail() {
	for(int pos = 0; pos < MAX_PLAYERS; pos++) {
		if(player_array[pos] == NULL) {
			return pos;
		}
	}

	return -1;
}

