/******************************************************************************
 *  Source File: network.c
 *
 *  Program:     Tux Bomber
 *
 *  Functions:   start_server(void)
 *               
 *  Date:        March 2, 2009
 *
 *  Revisions:   March 30, 2009 - Steffen L. Norgren
 *                   Added headers.
 * 
 *  Designer:    Steffen L. Norgren
 *  Programmer:  Steffen L. Norgren
 * 
 *  Description: Manages all server-side network communications
 *
 *****************************************************************************/

#include "server.h"
#include "network.h"
#include "utils.h"
#include "globals.h"

extern DPlaya *player_array[MAX_PLAYERS];

int mode = CLIENT, conn_type = TCP, sock = 0;
struct tcp_server *ptcp_server;
struct sockaddr_in server;

void tcp_listen(void) {
	struct addrinfo	hints, *ai, *p;
	int yes = 1;	/* for setsockopt() SO_REUSEADDR, below */
	int rv;

	/* Get a new socket and bind it! */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;			/* forcing IPv4, use AF_UNSPEC to allow IPv6 */
	hints.ai_socktype = SOCK_STREAM;	/* streaming socket of course! */
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
		fprintf(stderr, "server: %s\n", gai_strerror(rv));
		perror("getaddrinfo()");
	}

	/* Setup the listening sockets */
	for (p = ai; p != NULL; p = p->ai_next) {
		ptcp_server->listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (ptcp_server->listener < 0) { /* yes it is free */
			continue;
		}

		/* Avoid address in use errors */
		setsockopt(ptcp_server->listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		/* Bind the socket, but close if in use */
		if (bind(ptcp_server->listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(ptcp_server->listener);
			continue;
		}

		break; /* We're finished */
	}

	/* Exit if nothing was bound */
	if (p == NULL) {
		perror("server: failed to bind\n");
	}

	freeaddrinfo(ai);	/* we no longer need this */

	/* listen!! */
	if (listen(ptcp_server->listener, 10) == -1) {
		perror("listen"); /* massive listening failure */
	}

	/* add the new ptcp_server->listener to our ptcp_server->master set */
	FD_SET(ptcp_server->listener, &ptcp_server->master);

	/* keep track of the biggest file descriptor */
	ptcp_server->fd_max = ptcp_server->listener;
}

/******************************************************************************
 *  Function:    start_server
 * 
 *  Date:        March 2, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    Steffen L. Norgren
 *  Programmer:  Steffen L. Norgren
 * 
 *  Interface:   start_server(void)
 * 
 *  Returns:     void
 * 
 *  Description: Sets up server sockets and listens for new connections.
 *
 *****************************************************************************/
void start_server(void) {
	struct sockaddr_storage	remoteaddr;
	struct sockaddr_in sa_in;
	socklen_t				addrlen;
	pthread_t				udp_thread;

	/* Allocate memory to the server struct */
	ptcp_server = (struct tcp_server *)malloc(sizeof(struct tcp_server));

	/* Since we have the possibility for IPv6, we need to make sure
	   we can hold an address of that length. */
	char remoteIP[INET_ADDRSTRLEN];
	client_obj c_info[8];

	int i, j, ret, ci, ii;

	for(ci=0; ci < 8; ci++) {
		c_info[ci].ip = -1;
		c_info[ci].client_desc = -1;
	}
	ci = 0;

	FD_ZERO(&ptcp_server->master);	/* clear the ptcp_server->master and temp socket sets */
	FD_ZERO(&ptcp_server->read_fds);

	/* Setup our listening socket */
	tcp_listen();

	/* main read loop */
	for (;;) {
		ptcp_server->read_fds = ptcp_server->master; /* copy master set */
		if (select(ptcp_server->fd_max+1, &ptcp_server->read_fds, NULL, NULL, NULL) == -1) {
			perror("select"); /* massive select failure */
		}

		/* cycle through the connections, looking for data */
		for (i = 0; i <= ptcp_server->fd_max; i++) {
			if (FD_ISSET(i, &ptcp_server->read_fds)) { /* new connection */
				if (i == ptcp_server->listener) {
					/* manage the new connection */
					addrlen = sizeof(remoteaddr);
					ptcp_server->new_fd = accept(ptcp_server->listener, (struct sockaddr *)&remoteaddr, &addrlen);
					
					memcpy(&sa_in, &remoteaddr, sizeof(sa_in));
					
					c_info[ii].ip = sa_in.sin_addr.s_addr;
					c_info[ii++].client_desc = i;

					if((ret = add_player(sa_in.sin_addr.s_addr)) < 0) { /* spectator or error (depends what we want in the future) */
						
					} else  { /* player was successfully added */
						DPlaya *player = player_array[ret];
						printf("Player %d. x: %d, y: %d\n", player->getDPlayaID(), player->getX(), player->getY());
					}

					if (ptcp_server->new_fd == -1) {
						perror("accept"); /* obviously the server hates us */
					} else { /* the server loves us */
						FD_SET(ptcp_server->new_fd, &ptcp_server->master); /* add to the master set */
						if (ptcp_server->new_fd > ptcp_server->fd_max) { /* make sure we don't go over the limit */
							ptcp_server->fd_max = ptcp_server->new_fd;
						}

						fprintf(stderr, "server: new connection from %s on socket %d\n",
								inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *)&remoteaddr),
									remoteIP, INET6_ADDRSTRLEN), ptcp_server->new_fd);
					}
				} else {
					/* handle data from the client */
					if ((ptcp_server->recvBytes = recv(i, ptcp_server->recvBuff, sizeof(ptcp_server->recvBuff), 0)) <= 0) {
						/* got an error for client close the connection */
						if (ptcp_server->recvBytes == 0) {
							/* connection close */
							printf("select: socket %d hung up\n", i);

							for (j = 0; j <= ptcp_server->fd_max; j++) {
								for(ii=0; ii < 8; ii++) {								
									if(c_info[ii].client_desc==j) {
										c_info[j].ip = -1;
										c_info[j].client_desc = -1;
									}
								}
							}	
						} else {
							perror("recv");
						}
						close(i);	/* goodbye */
						FD_CLR(i, &ptcp_server->master); /* remove from ptcp_server->master set */
					} else { /* we got data from a client */
						/*if ((rv = process_data(ptcp_server->recvBuff, ptcp_server->recvBytes) < 0)) { 
							//perror("process_data");
						}*/



						/* Sending to clients is handled by network.cpp
						 * enable this for echo testing */
						for (j = 0; j <= ptcp_server->fd_max; j++) {
							if (FD_ISSET(j, &ptcp_server->master)) {
								if (j != ptcp_server->listener /*&& j == i*/) {
									if (send(j, ptcp_server->recvBuff, ptcp_server->recvBytes, 0) == -1) {
										perror("send");
									}
								}
							}
						}

						if (strcmp((const char*)ptcp_server->recvBuff, "start\n") == 0) {
							/* Create UDP Server thread */
							pthread_create(&udp_thread, NULL, start_udp_server, (void *) &c_info);
							/* start_udp_server(); */
						} /*else {
							printf("%s", (const char*)ptcp_server->recvBuff);
						}*/
					}
				} /* end of handling data from the client */
			} /* end of new connection */
		} /* end of descriptor loop */
	} /* end of infinite while loop */
}



