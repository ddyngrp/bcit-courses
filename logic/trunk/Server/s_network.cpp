#include "server.h"

/*
	Params:
		Char - The direction requested, as gotten from recv()
		Index - The ID of the player

	Basically the server is storing an array of indexes which correspond
	to the IP address of each client.  When they call recv() in the main
	processing function, it will then call receive_packet, passing in the data
	for char, and the index number corresponding to that IP.

	The Problem: Who is making and maintaining this array?  How do we extract
	the IP from the information gotten in recv() in order to map it to the ID?

	Problem 2: PLAYER_QUIT is only being sent via TCP.  In the main processing
	section, we need a way of receiving from either the TCP or UDP socket via
	select since we could receive from either of the two.

    answer: networking has an array with each ip, and the index that
            corresponds to it.  for each packet that network recieves, 
            they get the index that is mapped to the ip and call this
            function.  we no longer deal with PLAYER_QUIT, that was old code.

*/

void
recieve_packet(char b, int index)
{
	if (b == MOVE_UP) 
		move_player(index, MOVE_UP);
	else if (b == MOVE_DOWN) 
		move_player(index, MOVE_DOWN);
	else if (b == MOVE_LEFT) 
		move_player(index, MOVE_LEFT);
	else if (b == MOVE_RIGHT)
		move_player(index, MOVE_RIGHT);
	else if (b == PLANT_BOMB)
		plant_bomb(index);
}
