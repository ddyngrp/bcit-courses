#include "s_server.h"
#include "s_defs.h"
#include "n_network.h"
#include "n_serialize.h"

DPlaya 		*player_array[8];
unsigned char 	grid[17][18];
user_map *map;


int
main(void)
{
	fd_set	all_fds;		
	fd_set	read_fds;
	int nfds; /* The highest-numbered file descriptor in the set */
	int listener;
	int yes = 1;
	int i, j, rv, nBytes;
	int startReceived = 0;
	struct addrinfo hints, *ai, *servIter;
	struct server_info *sInfo;
	unsigned char outBuf[1024];
	unsigned char inBuf[2];
	char playerBuf[1024];

	for(int i = 0; i < 8; i++)
		player_array[i] = new DPlaya();
	player_array[0]->setX(35);
	player_array[0]->setY(35);
	player_array[0]->setImageName("tux.gif");
//	serialize_player(player_array[0], playerBuf, 1024);
	memcpy(playerBuf, serialize_player(player_array[0]), sizeof(DPlaya));
	for(j = 0; j <= nfds; j++)
	{
		if(FD_ISSET(j, &all_fds))
		{
			if(j == listener || j == i)
				continue;
			if(send(j, playerBuf, MAX_LEN, 0) == -1)
				perror("send");
		}
	}
	FD_ZERO(&all_fds);
	FD_ZERO(&read_fds);
	
	// initialize server settings
	if(!initialize_server(sInfo))
	{
		perror("ERROR: Unable to initialize server settings!\n");
		exit(1);
	}
	
	/* Clear and set family attributes! */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
		fprintf(stderr, "server: %s\n", gai_strerror(rv));
		exit(1);
	}

	/* Set up the listening socket */
	for (servIter = ai; servIter != NULL; servIter = servIter->ai_next)
	{
		listener = socket(servIter->ai_family, servIter->ai_socktype, servIter->ai_protocol);
		if (listener < 0)
			continue;
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		/* Close the socket & continue if it's already being used, else bind it */
		if (bind(listener, servIter->ai_addr, servIter->ai_addrlen) < 0)
		{
			close(listener);
			continue;
		}
		break;
	}

	/* Exit if bind was unsuccessful.  If it was, start listening. */
	if (servIter == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		exit(2);
	}if(inBuf[0] == MOVE_UP)
						player_array[0]->move(grid, MOVE_UP);
	printf("Server successfully started\n");

	if (listen(listener, 8) == -1)
	{
		perror("listen");
		exit(3);
	}

	/* Add new client to the set of all clients & make it the new nfds  */
	FD_SET(listener, &all_fds);
	nfds = listener;
	
	unsigned char **map;
	map = genRandomMap(17,18);
	
	for(int y = 0; y < 17; y++)
	{
		for(int x = 0; x < 18; x++)
		{
			printf("%5d", map[y][x]);
		}
		printf("\n");
	}
	printf("\n\n\n\n\n");
	for (int i = 0; i < 17; ++i)
		for (int j = 0; j < 18; ++j)
			outBuf[i * 17 + j] = map[i][j];
	
	/* Loop, waiting for client connections */
	while (!startReceived) /* While a client has not started the game */
	{
		read_fds = all_fds;
		if (select(nfds+1, &read_fds, NULL, NULL, NULL) == -1)
		{
			perror("select");
			exit(4);
		}
		/* Check each connection for input */
		for (i = 0; i <= nfds; i++)
		{
			if (FD_ISSET(i, &read_fds))
			{
				if (i == listener) /* New client connection */
				{
					nfds = new_client(nfds, listener, &all_fds); //add the client to the set of all clients
					break;
				}
				else /* Message from an already connected client */
				{
					startReceived = clientMessage(nfds, listener, i, &all_fds);	
					printf("Got a client message %d\n", startReceived);
				}
			}
		}
	}
	/* Clients connected */
	printf("Got out of receive loop\n");
	
	for (j = 0; j <= nfds; j++)
	{
		if (FD_ISSET(j, &all_fds))
		{
			if(j == listener || j == i)
				continue;

			if (send(j, outBuf, MAX_LEN, 0) == -1)
				perror("send");
		}
	}
	printf("Sent map: %s\n", outBuf);
	//serialize_player(player_array[0], playerBuf, 1024);
	memcpy(playerBuf, serialize_player(player_array[0]), sizeof(DPlaya));
	for(j = 0; j <= nfds; j++)
	{
		if(FD_ISSET(j, &all_fds))
		{
			if(j == listener || j == i)
				continue;
			if(send(j, playerBuf, MAX_LEN, 0) == -1)
				perror("send");
		}
	}

	printf("got into main input loop\n");
	//main input loop
	int count = 0;
	for(;;) 
	{
		read_fds = all_fds;
		int ret;
		if((ret = select(nfds+1, &read_fds, NULL, NULL, NULL)) == -1)
		{
			perror("select");
			exit(4);
		}
		/* Check each connection for input */
		for (i = 0; i <= nfds; i++)
		{
			if (FD_ISSET(i, &read_fds))
			{
				if (i == listener) 			//ignore request to join the session
					break;
				else 						//Message from an already connected client
				{
					if ((nBytes = recv(i, inBuf, 2, 0)) <= 0)
					{
						/* Client gave an error or left, close it's connection & remove it from the set of FDs */
						if (nBytes == 0)
							printf("Client on socket %d left\n", i);
						else
							perror("recv");
						close(i);
						FD_CLR(i, &read_fds);
						printf("nbytes <= 0\n");
					}
					printf("received a movement: %d count: %d\n", inBuf[0] - '0', ++count);
					
					if(inBuf[0] - '0' == MOVE_UP) {
						player_array[0]->move(grid, MOVE_UP);
					} else if(inBuf[0] - '0' == MOVE_DOWN) {
						player_array[0]->move(grid, MOVE_DOWN);
					} else if(inBuf[0] - '0' == MOVE_RIGHT) {
						player_array[0]->move(grid, MOVE_RIGHT);
					} else if(inBuf[0] - '0' == MOVE_LEFT) {
						player_array[0]->move(grid, MOVE_LEFT);
					}
						
						printf("player x: %d", player_array[0]->getX());
					
					//serialize_player(player_array[0], playerBuf, 1024);
					memcpy(playerBuf, serialize_player(player_array[0]), sizeof(DPlaya));
					for(j = 0; j <= nfds; j++)
					{
						if(FD_ISSET(j, &all_fds))
						{
							if(j == listener)
								continue;
							if(send(j, playerBuf, sizeof(playerBuf), 0) == -1)
								perror("send");
						}
					}
				}
				if(--ret <= 0)
					break;
			}
		}
	}
	//send(outBuf, ptcp_server->recvBuff, ptcp_server->recvBytes, 0)
	//send any important initial data via TCP (ie. map & players)
	//send_map(int *sockets, int num_sockets, unsigned char map[MAP_ROWS][MAP_COLS])
	//void *start_udp_server(void *ptr)
	
	//create our UDP socket & bind it
	//listen for client commands & process them
}
