/*---------------------------------------------------------------------------------------------
--      SOURCE FILE:	network.cpp - Set up and handle the messages to and from the server.
--									  Taken from assignment 3 work & modified to only do
--									  what we need.  
--            
--      PROGRAM:        TuxBomber 
--
--      FUNCTIONS:      void server_main()
--                      int new_client(int nfds, int listener, fd_set * all_fds)       
--
--      REVISIONS:      
--
--      DESIGNER:       Jaymz Boilard
--      PROGRAMMER:		Jaymz Boilard
---------------------------------------------------------------------------------------------*/
#include "general.h"
using namespace std;
void *get_in_addr(struct sockaddr *sa);

/*---------------------------------------------------------------------------------------------
--      FUNCTION: 		connection_setup
--
--      DATE:           March 18, 2009
--
--      REVISIONS:       
--
--      DESIGNER:       Jaymz Boilard
--      PROGRAMMER:     Jaymz Boilard
--
--      INTERFACE:      int client_main(char * servIp)
--
--      RETURNS:        void
--
--      NOTES:          Starts up the client just the same as assignment 3, but after
--						connecting to the server, it calls the fork_off function.
---------------------------------------------------------------------------------------------*/
int connection_setup(char * servIp)
{
	struct addrinfo hints, *serverinfo, *servIter;
	char serverIP[INET6_ADDRSTRLEN];
	int sockfd;
	int ret;
	
	bzero((char *) &hints, sizeof(hints)); //clear hints
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if((ret = getaddrinfo(servIp, PORT, &hints, &serverinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		exit(1);
	}

	for (servIter = serverinfo; servIter !=NULL; servIter = servIter->ai_next )
	{
		if ((sockfd = socket(servIter->ai_family, servIter->ai_socktype, servIter->ai_protocol)) == -1)
		{
			perror("client: socket");
			continue;
		}

		if ((connect(sockfd, servIter->ai_addr, servIter->ai_addrlen)) == -1)
		{
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
	}

	if (servIter == NULL)
	{
		fprintf(stderr, "client: failed to connect\n");
		exit(2);
	}
	else
		printf("Connected.  Type a message to chat or press EOF to end your session.\n");
	
	inet_ntop(servIter->ai_family,get_in_addr((struct sockaddr*)servIter->ai_addr),serverIP,sizeof(serverIP));
	freeaddrinfo(serverinfo);
	
	return sockfd;
}

/*---------------------------------------------------------------------------------------------
--      FUNCTION: 		get_in_addr
--
--      DATE:           March 18, 2009
--
--      REVISIONS:      March 15 - Added this function on the advice of a classmate
--								   Source: http://beej.us     
--
--      DESIGNER:       Brian Hall
--      PROGRAMMER:     Brian Hall
--
--      INTERFACE:      void *get_in_addr(struct sockaddr *sa)
--
--      RETURNS:        void
--
--      NOTES:          Returns the appropriate socket address depending on what version we are
--                      using.
---------------------------------------------------------------------------------------------*/
void *get_in_addr(struct sockaddr *sa)
{
	/* Check if the address is IPv4 & return it's socket address if it is*/
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);

	/* Return the IPv6 socket address */
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

