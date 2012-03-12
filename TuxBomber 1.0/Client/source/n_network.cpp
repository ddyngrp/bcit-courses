/******************************************************************************
 *  Source File: network.c
 *
 *  Program:     Tux Bomber
 *
 *  Functions:   *get_in_addr(struct sockaddr *sa)
 *               set_conn_type(int type)
 *               conn_setup(char *host, char *port)
 *               keepalive()
 *               send_map(unsigned char *map, size_t len)
 *               recv_map(unsigned char *map, size_t len)
 *               request_move(int x, int y)
 *               request_bomb(int type)
 *               explode_bomb(int x, int y)
 *               transfer(unsigned char *data, size_t len)
 *               add_coords_xy(int x, int y, unsigned char *data, size_t len)
 *               process_data(unsigned char *data, size_t len)
 *               parse_info_byte(unsigned char *data)
 *               get_action_type(int info)
 *               get_player_id(int info)
 *               get_extra_info(int info)
 *               create_info_byte(int action, int player, int extra)
 *				 int clientMessage(int nfds, int listener, int i, fd_set * all_fds)
 *
 *  Date:        March 2, 2009
 *
 *  Revisions:   March 20, 2009 - Steffen L. Norgren
 *                   Updated headers to cornform to Aman's standards             <--- LOL Steffen learn 2 spell, CORNform! LAWOAWLAWLALWLAWLAWLOLOLOALAOWLALWLAWLAWL
 *               March 29, 2009 - Steffen L. Norgren
 *                   Moved the sole function from "tools.c" to here as it
 *                   can be considered part of networking.
 *
 *  Designer:    David Young, Steffen L. Norgren
 *  Programmer:  David Young, Steffen L. Norgren
 *
 *  Description: Set the connection type to TCP or UDP.
 *
 *****************************************************************************/

#include "../headers/n_network.h"

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

	printf("Got into clientMessage()\n");
	if ((nBytes = recv(i, buf, sizeof(buf), 0)) <= 0)
	{
		/* Client gave an error or left, close it's connection & remove it from the set of FDs */
		if (nBytes == 0)
			printf("Client on socket %d left\n", i);
		else
			perror("recv");
		close(i);
		FD_CLR(i, all_fds);
		printf("nbytes <= 0\n");
	}
	else
	{
		/* we got data from a client */
		for (j = 0; j <= nfds; j++)
		{
			if (FD_ISSET(j, all_fds))
			{

				printf("Buffer contains: %s\n", buf);
				/* The client sent us a start message */
				if (strncmp(buf, "ready", 5) == 0)
				{

					return 1;
				}
			}
		}
	}
	printf("Got past clientMessage()\n");
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

