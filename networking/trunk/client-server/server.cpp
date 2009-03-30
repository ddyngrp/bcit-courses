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
	fd_set			master;		
	fd_set			read_fds;
	int				fd_max;
	int				listener;
	int				new_fd;	
	struct 			sockaddr_storage remoteaddr;
	socklen_t		addrlen;
	unsigned char	buf[256];
	int				nBytes;

	/* Since we have the possibility for IPv6, we need to make sure
	   we can hold an address of that length. */
	char remoteIP[INET6_ADDRSTRLEN];

	int yes = 1;	/* for setsockopt() SO_REUSEADDR, below */
	int i, j, rv;

	struct addrinfo hints, *ai, *p;

	FD_ZERO(&master);	/* clear the master and temp socket sets */
	FD_ZERO(&read_fds);
	
	mode = SERVER; /* needed for network functions */

	/* Get a new socket and bind it! */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;		/* address family unspecified */
	hints.ai_socktype = SOCK_STREAM;	/* streaming socket of course! */
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
		fprintf(stderr, "server: %s\n", gai_strerror(rv));
		exit(1);
	}

	/* Setup the listening sockets */
	for (p = ai; p != NULL; p = p->ai_next) {
		listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
		if (listener < 0) { /* yes it is free */
			continue;
		}

		/* Avoid address in use errors */
		setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		/* Bind the socket, but close if in use */
		if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) {
			close(listener);
			continue;
		}

		break; /* We're finished */
	}

	/* Exit if nothing was bound */
	if (p == NULL) {
		fprintf(stderr, "server: failed to bind\n");
		exit(2);
	}

	freeaddrinfo(ai);	/* we no longer need this */

	/* listen!! */
	if (listen(listener, 10) == -1) {
		perror("listen"); /* massive listening failure */
		exit(3);
	}

	/* add the new listener to our master set */
	FD_SET(listener, &master);

	/* keep track of the biggest file descriptor */
	fd_max = listener;

	/* main read loop */
	for (;;) {
		read_fds = master; /* copy the master set */
		if (select(fd_max+1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select"); /* massive select failure */
			exit(4);
		}

		/* cycle through the connections, looking for data */
		for (i = 0; i <= fd_max; i++) {
			if (FD_ISSET(i, &read_fds)) { /* new connection */
				if (i == listener) {
					/* manage the new connection */
					addrlen = sizeof(remoteaddr);
					new_fd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

					if (new_fd == -1) {
						perror("accept"); /* obviously the server hates us */
					} else { /* the server loves us */
						FD_SET(new_fd, &master); /* add to the master set */
						if (new_fd > fd_max) { /* make sure we don't go over the limit */
							fd_max = new_fd;
						}

						fprintf(stderr, "server: new connection from %s on socket %d\n",
								inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *)&remoteaddr),
									remoteIP, INET6_ADDRSTRLEN), new_fd);
					}
				} else {
					/* handle data from the client */
					if ((nBytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
						/* got an error for client close the connection */
						if (nBytes == 0) {
							/* connection close */
							printf("select: socket %d hung up\n", i);
						} else {
							perror("recv");
						}
						close(i);	/* goodbye */
						FD_CLR(i, &master); /* remove from master set */
					} else { /* we got data from a client */
						if (process_data(buf, nBytes) < 0) { /* if there was an error processing the data */
							perror("process_data");
						} else {
							
						}
						
						for (j = 0; j <= fd_max; j++) {
							if (FD_ISSET(j, &master)) {
								/* only echo back to the client that connected
								 * TODO: This is where we would flesh out how to deal
								 * with the incoming data and to whom we would send it.
								 */
								if (j != listener && j == i) {
									if (send(j, buf, nBytes, 0) == -1) {
										perror("send"); /* massive failure!!! */
									}
								}
							}
						}

						if(strcmp((const char*)buf, "start\n")==0) {
							start_udp_server();
						}
					}
				} /* end of handling data from the client */
			} /* end of new connection */
		} /* end of descriptor loop */
	} /* end of infinite while loop */
}

void start_udp_server() {
	int sd, port = 8000, n, j;
	socklen_t client_len;
	char udpbuf[1024];
	struct sockaddr_in udpserver, udpclient;
	
	printf("starting udp server.\n");
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

	for(;;) {
		printf("waiting udp..\n");
		fflush(stdout);

		client_len = sizeof(udpclient);
		if((n = recvfrom(sd, udpbuf, 1024, 0, (struct sockaddr *)&udpclient, &client_len)) < 0) {
			perror("Recv From");
			exit(EXIT_FAILURE);
		}
		for(j=0; udpbuf[j] != '\n'; ++j);
		udpbuf[++j] = '\0';

		printf("sending udp..: %s\n", udpbuf);
		fflush(stdout);

		if(sendto(sd, udpbuf, n, 0, (struct sockaddr *)&udpclient, client_len) < 0) {
			perror("Send To");
			exit(EXIT_FAILURE);
		}

		if(strcmp(udpbuf, "quit\n")==0) {
			close(sd);
			printf("closing udp server\n");
			break;
		}
	}
}


