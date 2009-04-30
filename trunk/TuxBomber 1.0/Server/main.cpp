#include "s_server.h"
#include "s_defs.h"
#include "s_network.h"
#include "utils.h"
#include "serialize.h"

#define MULTI_ADDR "225.0.0.37"
#define MULTI_PORT 31337

DPlaya 		*player_array[8];
unsigned char 	grid[17][18];
user_map *map;
struct sockaddr_in addr;
int fd;
int expectedClients;
int playerCount;


int
main(int argc, char * argv[])
{
	fd_set	all_fds;		
	fd_set	read_fds;
	int nfds; /* The highest-numbered file descriptor in the set */
	int listener;
	int yes = 1;
	int i, j, rv;
	struct addrinfo hints, *ai, *servIter;
	struct server_info *sInfo;
	unsigned char outBuf[1024];
	unsigned char inBuf[3];
	char playerBuf[1024];
	unsigned char **map;
	int idCount = 0;
    char str[256];
	int sd, n, player_loc;
	socklen_t client_len;
	unsigned char udpbuf[MAX_LEN];
	struct sockaddr_in udpserver, udpclient;
	struct sockaddr_in clientIP[8];
	u_long lttl;

	if(argc != 2)
	{
		printf("Usage: %s [player limit]\n", argv[0]);
		exit(0);
	}
	
	printf("------------------------------\n");
	printf("Tux Bomber v1.0\n");
	printf("Data Comm 0x131B\n");
	printf("April 2009\n");
	printf("------------------------------\n");
	
	expectedClients = atoi(argv[1]);
	playerCount = expectedClients;

	for(i = 0; i < expectedClients; i++)
		player_array[i] = new DPlaya();

    /* Initialize client table */
	for (i = 0; i < expectedClients; i++)
	{
	    memset(&clientIP[i], 0, sizeof(clientIP[i]));
        //clientIP[i].sin_addr.s_addr = 0;
		clientIP[i].sin_family = AF_INET;
		clientIP[i].sin_port = htons(8000);
	}
	 
	FD_ZERO(&all_fds);
	FD_ZERO(&read_fds);
	
	printf("Initializing server settings...");
	
	// initialize server settings
	if(!initialize_server(sInfo))
	{
		perror("ERROR: Unable to initialize server settings!\n");
		exit(1);
	}
	
	printf(" Success!\n");
	
	/* Clear and set family attributes! */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
	{
		fprintf(stderr, "server: %s\n", gai_strerror(rv));
		exit(1);
	}

    printf("Creating TCP socket...");
    
	// Set up the listening socket
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
	}

	if (listen(listener, 8) == -1)
	{
		perror("listen");
		exit(3);
	}
	
    printf(" Success!\n");

	/* Add new client to the set of all clients & make it the new nfds  */
	FD_SET(listener, &all_fds);
	nfds = listener;
	
	printf("Generating map...");
	
	map = genRandomMap(17,18);
	
	for(int y = 0; y < 17; y++)
		for(int x = 0; x < 18; x++)
			grid[y][x] = map[y][x];
	
	for (i = 0; i < 17; ++i)
		for (j = 0; j < 18; ++j)
			outBuf[i * 17 + j] = map[i][j];
			
	printf(" Success!\n");
	printf("Waiting for clients...\n");
	
	/* Loop, waiting for client connections until we have all of them. */
	while (idCount < expectedClients)
	{
		read_fds = all_fds;
		if (select(nfds + 1, &read_fds, NULL, NULL, NULL) == -1)
		{
			perror("select");
			exit(4);
		}
		
		/* Check each connection for input */
		for (i = 3; i <= nfds; i++)
		{
			if (FD_ISSET(i, &read_fds))
			{
				if (i == listener) /* New client connection */
				{   
					nfds = new_client(nfds, listener, &all_fds, player_array[idCount], &clientIP[idCount]);
					
					printf("Client %d connected\n", idCount);
					
					if (idCount == 0) 
					{
						player_array[idCount]->setX(35);
						player_array[idCount]->setY(35);
					}
					else if (idCount == 1)
					{
						player_array[idCount]->setX(15 * 35 - 1);
						player_array[idCount]->setY(15 * 35 - 1);
					}
					else if (idCount == 2)
					{
						player_array[idCount]->setX(35);
						player_array[idCount]->setY(15 * 35 - 1);
					}
					else if (idCount == 3)
					{
						player_array[idCount]->setX(15 * 35 - 1);
						player_array[idCount]->setY(35);
					}
					sprintf(str, "resources/img/models/in_game/%d.png\0", idCount);
					player_array[idCount]->setImageName(str);
					player_array[idCount]->setID(idCount);
					player_array[idCount]->setNumBombs(5);
					idCount++;
					
					break;
				}
			}
		}
	}
	
	printf("Sending out map and client information...");
	
	for (j = 3; j <= nfds; j++)
	{
		if (FD_ISSET(j, &all_fds))
		{
			if(j == listener)
				continue;

			if (send(j, outBuf, MAX_LEN, 0) == -1)
				perror("send");
		}
	}
	
	for (j = 3; j <= nfds; j++)
	{
		if (FD_ISSET(j, &all_fds))
		{
			if(j == listener)
				continue;

			if (send(j, argv[1], 1024, 0) == -1)
				perror("send");
		}
	}
	
	/* Copy all players and send them out */
	for(i = 0; i < expectedClients; i++)
	{
		memcpy(playerBuf, player_array[i], 1024);
		
		for(j = 3; j <= nfds; j++)
		{
			if(FD_ISSET(j, &all_fds))
			{
				if(j == listener)
					continue;
				if(send(j, playerBuf, MAX_LEN, 0) == -1)
					perror("send");
			}
		}
	}
	
	printf(" Success!\n");
	printf("Creating UDP socket...");
	
	/* Create udp listen socket */
	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("Socket Creation");
		exit(EXIT_FAILURE);
	}

    /* initialize sockaddr struct */
	bzero((char *)&udpserver, sizeof(udpserver));
	udpserver.sin_family = AF_INET;
	udpserver.sin_port = htons(8000);
	udpserver.sin_addr.s_addr = htonl(INADDR_ANY);

    /* bind socket to address */
	if(bind(sd, (struct sockaddr *)&udpserver, sizeof(udpserver)) == -1)
	{
		perror("Binding Socket");
		exit(EXIT_FAILURE);
	}
	
	/* create what looks like an ordinary UDP socket */
    if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
        perror("socket");
        exit(1);
    }
    
    /* set up destination address */
    memset(&addr,0,sizeof(addr));
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(MULTI_ADDR);
    addr.sin_port=htons(MULTI_PORT);
    
    lttl = 10;
    
    setsockopt(fd, IPPROTO_IP, IP_MULTICAST_TTL, (char *)lttl, sizeof(lttl));
    
    printf(" Success!\n");
	
	printf("Starting game. HAVE FUN! :D\n");
	/*********************** GAME STARTED HERE! ************************/
	while(playerCount > 1) 
	{
	    memset(udpbuf, 0, sizeof(udpbuf));
	    memset(outBuf, 0, sizeof(outBuf));
	    client_len = sizeof(udpclient);

		/* listen for connection */
	    if((n = recvfrom(sd, inBuf, 3, 0, (struct sockaddr *)&udpclient, &client_len)) <= 0)
	    {
	        /* socket closed */
			if(n == 0)
			{
				fprintf(stderr,"Connection closed on socket: %d\n", sd);
				continue;
			}
			else /* error */
			{
				perror("Recv From");
				exit(EXIT_FAILURE);
			}
	    }

        if((player_loc = get_player_loc(udpclient.sin_addr.s_addr)) >= 0 && player_loc < MAX_PLAYERS)
        {
            clientIP[player_loc].sin_port = udpclient.sin_port;
        
		    if(inBuf[0] - '0'== MOVE_UP)
			player_array[player_loc]->move(grid, MOVE_UP);
		    else if(inBuf[0] - '0' == MOVE_DOWN) 
			player_array[player_loc]->move(grid, MOVE_DOWN);
		    else if(inBuf[0] - '0' == MOVE_RIGHT)
			player_array[player_loc]->move(grid, MOVE_RIGHT);
		    else if(inBuf[0] - '0' == MOVE_LEFT)
			player_array[player_loc]->move(grid, MOVE_LEFT);
		    else if(inBuf[0] - '0' == PLANT_BOMB)
			plant_bomb(player_loc);
		   
		    outBuf[0] = 'P';
		    outBuf[1] = 'P';
		    
		    memcpy(outBuf + 2, player_array[player_loc], 1024);
		    
	        if (sendto(fd,outBuf,sizeof(outBuf),0,(struct sockaddr *) &addr, sizeof(addr)) < 0) {
	            perror("sendto");
	            exit(1);
	        }
    	}
	}
	
    outBuf[0] = 'G';

    if (sendto(fd,outBuf,sizeof(outBuf),0,(struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("sendto");
        exit(1);
    }
    sleep(2);
    shutdown(fd, 2);
    close(fd);
    
	printf("Game over!\n");
	
	free(map);

	return 0;
}

