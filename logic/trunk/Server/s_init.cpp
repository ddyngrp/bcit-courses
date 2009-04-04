#include "server.h"

bool initialize_server(struct server_info *sInfo)
{	
	// set memory for struct
	sInfo = (struct server_info *)malloc(sizeof(struct server_info));
	
	if(sInfo == NULL)
		return false;
	
	// Setup server information
	sInfo->player_array	= new DPlaya[MAX_PLAYERS];
	sInfo->player_count	= 0;
	sInfo->game_running	= false;
	
	return true;
}
