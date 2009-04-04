#include "server.h"
#include "defs.h"

int
main(void)
{
	fd_set	all_fds;		
	fd_set	read_fds;
	int nfds; /* The highest-numbered file descriptor in the set */
	int listener;
	int yes = 1;
	int i, rv;
	int startReceived = 0;
	struct addrinfo hints, *ai, *servIter;
	struct server_info *sInfo;

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
	}
	printf("Server successfully started\n");

	if (listen(listener, 8) == -1)
	{
		perror("listen");
		exit(3);
	}

	/* Add new client to the set of all clients & make it the new nfds  */
	FD_SET(listener, &all_fds);
	nfds = listener;

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
					nfds = new_client(nfds, listener, &all_fds); //add the client to the set of all clients
				else /* Message from an already connected client */
					startReceived = clientMessage(nfds, listener, i, &all_fds);	
			}
		}
	}
	/* Clients connected */
	
	//initialize the map
	//initialize players
	//send any important initial data via TCP (ie. map & players)
	//send_map(int *sockets, int num_sockets, unsigned char map[MAP_ROWS][MAP_COLS])
	//void *start_udp_server(void *ptr)
	
	//create our UDP socket & bind it
	//listen for client commands & process them
	

}

/*------------------------------------------------------------------------------------------------------
--      FUNCTION: 		clientMessage
--
--      DATE:           March 18, 2009
--
--      REVISIONS:              
--
--      DESIGNER:       Jaymz Boilard
--      PROGRAMMER:     Jaymz Boilard
--
--      INTERFACE:      int new_client(int nfds, int listener, fd_set * all_fds)
--
--      RETURNS:        TRUE when a client sent us a message to start the game, else FALSE.
--
--      NOTES:          Called when the select command in server_main() finds a message from a 
--						client.
------------------------------------------------------------------------------------------------------*/
int clientMessage(int nfds, int listener, int i, fd_set * all_fds)
{
	char buf[256];
	int nBytes, j;

	if ((nBytes = recv(i, buf, sizeof(buf), 0)) <= 0)
	{
		/* Client gave an error or left, close it's connection & remove it from the set of FDs */
		if (nBytes == 0)
			printf("Client on socket %d left\n", i);
		else
			perror("recv");
		close(i);
		FD_CLR(i, all_fds);
	}
	else
	{
		/* we got data from a client */
		for (j = 0; j <= nfds; j++)
		{
			if (FD_ISSET(j, all_fds))
			{
				if(j == listener || j == i)
					continue;

				/* The client sent us a start message */
				if (!strcmp(buf, "start"))
					return 1;		
			}
		}
	}
	/* No start message */
	return 0;
}

/*------------------------------------------------------------------------------------------------------
--      FUNCTION: new_client
--
--      DATE:           March 18, 2009
--
--      REVISIONS:              
--
--      DESIGNER:       Jaymz Boilard
--      PROGRAMMER:     Jaymz Boilard
--
--      INTERFACE:      int new_client(int nfds, int listener, fd_set * all_fds)
--
--      RETURNS:        The highest-numbered file descriptor (nfds)
--
--      NOTES:          This function is called when the select() call from server_main finds 
--                      that the incoming message is a request to join the chat.  We will add its
--                      network information to the set of all file descriptors, and update the nfds.
------------------------------------------------------------------------------------------------------*/
int new_client(int nfds, int listener, fd_set * all_fds)
{
	socklen_t clientLen;
	int new_fd;
	struct sockaddr_in client;

	clientLen = sizeof(client);
	new_fd = accept(listener, (struct sockaddr *)&client, &clientLen);
	if (new_fd == -1)
		perror("accept");
	else
	{
		FD_SET(new_fd, all_fds);	
		printf("New connection from %s on socket %d\n", inet_ntoa(client.sin_addr), new_fd);
	}
	if (new_fd > nfds)
		return new_fd;
	else
		return nfds;
}

