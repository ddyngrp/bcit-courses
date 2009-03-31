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

extern int mode, conn_type, sock;

typedef struct _tmp_server {
	fd_set	master,
			read_fds;
	int		listener,
			fd_max,
			new_fd,
			recvBytes,
			mode;

	unsigned char	recvBuff[8192];
} tmp_server, *ptmp_server;

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
	struct addrinfo			hints, *ai, *p;
	socklen_t				addrlen;

	/* Allocate memory to the server struct */
	tmp_server *ptmp_server = (tmp_server *)malloc(sizeof(tmp_server));

	/* Since we have the possibility for IPv6, we need to make sure
	   we can hold an address of that length. */
	char remoteIP[INET6_ADDRSTRLEN];

	int yes = 1;	/* for setsockopt() SO_REUSEADDR, below */
	int i, j, rv;

	FD_ZERO(&ptmp_server->master);	/* clear the ptmp_server->master and temp socket sets */
	FD_ZERO(&ptmp_server->read_fds);
	
	ptmp_server->mode = SERVER; /* needed for network functions */

	/* Get a new socket and bind it! */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		/* address family unspecified */
	hints.ai_socktype = SOCK_STREAM;	/* streaming socket of course! */
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
		fprintf(stderr, "server: %s\n", gai_strerror(rv));
		perror("getaddrinfo()");
	}

	/* Setup the listening sockets */
	for (p = ai; p != NULL; p = p->ai_next) {
		ptmp_server->listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (ptmp_server->listener < 0) { /* yes it is free */
			continue;
		}

		/* Avoid address in use errors */
		setsockopt(ptmp_server->listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		/* Bind the socket, but close if in use */
		if (bind(ptmp_server->listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(ptmp_server->listener);
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
	if (listen(ptmp_server->listener, 10) == -1) {
		perror("listen"); /* massive listening failure */
	}

	/* add the new ptmp_server->listener to our ptmp_server->master set */
	FD_SET(ptmp_server->listener, &ptmp_server->master);

	/* keep track of the biggest file descriptor */
	ptmp_server->fd_max = ptmp_server->listener;

	/* main read loop */
	for (;;) {
		ptmp_server->read_fds = ptmp_server->master; /* copy master set */
		if (select(ptmp_server->fd_max+1, &ptmp_server->read_fds, NULL, NULL, NULL) == -1) {
			perror("select"); /* massive select failure */
		}

		/* cycle through the connections, looking for data */
		for (i = 0; i <= ptmp_server->fd_max; i++) {
			if (FD_ISSET(i, &ptmp_server->read_fds)) { /* new connection */
				if (i == ptmp_server->listener) {
					/* manage the new connection */
					addrlen = sizeof(remoteaddr);
					ptmp_server->new_fd = accept(ptmp_server->listener, (struct sockaddr *)&remoteaddr, &addrlen);

					if (ptmp_server->new_fd == -1) {
						perror("accept"); /* obviously the server hates us */
					} else { /* the server loves us */
						FD_SET(ptmp_server->new_fd, &ptmp_server->master); /* add to the master set */
						if (ptmp_server->new_fd > ptmp_server->fd_max) { /* make sure we don't go over the limit */
							ptmp_server->fd_max = ptmp_server->new_fd;
						}

						fprintf(stderr, "server: new connection from %s on socket %d\n",
								inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *)&remoteaddr),
									remoteIP, INET6_ADDRSTRLEN), ptmp_server->new_fd);
					}
				} else {
					/* handle data from the client */
					if ((ptmp_server->recvBytes = recv(i, ptmp_server->recvBuff, sizeof(ptmp_server->recvBuff), 0)) <= 0) {
						/* got an error for client close the connection */
						if (ptmp_server->recvBytes == 0) {
							/* connection close */
							printf("select: socket %d hung up\n", i);
						} else {
							perror("recv");
						}
						close(i);	/* goodbye */
						FD_CLR(i, &ptmp_server->master); /* remove from ptmp_server->master set */
					} else { /* we got data from a client */
						/*
						if (process_data(ptmp_server->recvBuff, ptmp_server->recvBytes) < 0) { 
							perror("process_data");
						} else {
							
						}*/
						for(j=0; ptmp_server->recvBuff[j]!='\n'; j++);
						ptmp_server->recvBuff[++j] = '\0';

						if(strcmp((const char*)ptmp_server->recvBuff, "start\n")==0) {
							start_udp_server();
						} else {
						
							for (j = 0; j <= ptmp_server->fd_max; j++) {
								if (FD_ISSET(j, &ptmp_server->master)) {
									/* only echo back to the client that connected
									 * TODO: This is where we would flesh out how to deal
									 * with the incoming data and to whom we would send it.
									 */
									if (j != ptmp_server->listener && j == i) {
										if (send(j, ptmp_server->recvBuff, ptmp_server->recvBytes, 0) == -1) {
											perror("send"); /* massive failure!!! */
										}
									}
								}
							}
						}
						
						/* Check for UDP start signal */
						
					}
				} /* end of handling data from the client */
			} /* end of new connection */
		} /* end of descriptor loop */
	} /* end of infinite while loop */
}
