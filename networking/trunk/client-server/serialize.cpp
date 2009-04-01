#include <stdio.h>
#include <stdlib.h>

#include "DPlaya.h"
#include "serialize.h"

#define BUF_LEN 64

/******************************************************************************
 *  Function:    serialize_player
 * 
 *  Date:        March 30, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   serialize_player(DPlaya *player, char *buf, int buflen)
 *		            DPlaya *player: Pointer to the DPlaya object to be serialized
 *                  char *buf: buffer to put the serialized form of the player into
 *					int buflen: the length of buf
 * 
 *  Returns:     0 on success or (-1) on failure.
 * 
 *  Description: Serialize player's data members into buf to be passed across the network.
 *
 *****************************************************************************/
int serialize_player(DPlaya *player, char *buf, size_t buflen) {
	if(buflen < sizeof(DPlaya)) {
		return -1;
	}
	
	memcpy(buf, player, sizeof(DPlaya));
	return 0;
}

/******************************************************************************
 *  Function:    unserialize_player
 * 
 *  Date:        March 30, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   unserialize_player(char *buf, DPlaya *player)
 *					char *buf: buffer to get the serialized form of the player from
 *		            DPlaya *player: Pointer to the DPlaya object to fill
 * 
 *  Returns:     0 on success or (-1) on failure.
 * 
 *  Description: Unserialize the info in buf and put it into player.
 *
 *****************************************************************************/
int unserialize_player(char *buf, DPlaya *player) {
	memcpy(player, buf, sizeof(DPlaya));
	return 0;
}
