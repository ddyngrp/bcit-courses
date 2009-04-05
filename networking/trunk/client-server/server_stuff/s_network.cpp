#include "s_server.h"
#include "n_serialize.h"

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

extern DPlaya 	       *player_array[8];
extern unsigned char 	grid[17][18];

void
recieve_packet(char b, int index)
{
	if (b == MOVE_UP) 
		player_array[index]->move(grid, MOVE_UP);
	else if (b == MOVE_DOWN) 
		player_array[index]->move(grid, MOVE_DOWN);
	else if (b == MOVE_LEFT) 
		player_array[index]->move(grid, MOVE_LEFT);
	else if (b == MOVE_RIGHT)
		player_array[index]->move(grid, MOVE_RIGHT);
	else if (b == PLANT_BOMB)
		plant_bomb(index);
}

void *start_udp_server(void *ptr)
{
	int sd, port = 8000, n, j;
	socklen_t client_len;
	char udpbuf[MAX_LEN];
	struct sockaddr_in udpserver, udpclient;
	DPlaya p1, p2;
	
	printf("starting udp server..\n");
	fflush(stdout);

	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket Creation");
		exit(EXIT_FAILURE);
	}

	bzero((char *)&udpserver, sizeof(udpserver));
	udpserver.sin_family = AF_INET;
	udpserver.sin_port = htons(port);
	udpserver.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sd, (struct sockaddr *)&udpserver, sizeof(udpserver)) == -1) {
			perror("Binding Socket");
			exit(EXIT_FAILURE);
	}

	while(1)
	{
		client_len = sizeof(udpclient);
		
		if((n = recvfrom(sd, udpbuf, MAX_LEN, 0, (struct sockaddr *)&udpclient, &client_len)) <= 0)
		{
			if(n == 0)
			{
				fprintf(stderr,"Connection closed on socket: %d\n", sd);
				continue;
			} 
			else
			{
				perror("Recv From");
				exit(EXIT_FAILURE);
			}
		}

		for(j=0; udpbuf[j] != -1; j++);  //finds the length of the buffer
		udpbuf[j] = '\0';                //adds a null character to the end


	}

}

/*
printf("len: %d - buf: %s\n", strlen(udpbuf), udpbuf);

unserialize_player(udpbuf, &p1);

printf("%d\n", p1.getX());
printf("%d\n", p1.getY());
printf("%d\n", p1.getNumBombs());
printf("%d\n", p1.getDroppedBombs());
printf("%d\n", p1.getDPlayaID());

serialize_player(&p1, udpbuf, BUF_LEN);

if(strcmp(udpbuf, "quit\n")==0) {
	close(sd);
	printf("closing udp server..\n");
	return 0;
} else {
	if(sendto(sd, udpbuf, n, 0, (struct sockaddr *)&udpclient, client_len) < 0) {
		perror("Send To");
		exit(EXIT_FAILURE);
	}
}

pthread_testcancel();*/
		
		
