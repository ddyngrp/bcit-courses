#include "server.h"

/* Get sockaddr for IPv4 or IPv6 */
void *get_in_addr(struct sockaddr *sa) {
	/* Check if the address is IPv4 */
	if (sa->sa_family == AF_INET) {
		/* Return the IPv4 socket address */
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	/* Return the IPv6 socket address */
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/* Initialize sockets, etc. */
void start_server(void) {
	fd_set	master;		/* the master file descriptor list */
	fd_set	read_fds;	/* temp file descriptor for select() */
	int		fd_max;
	int		listener;	/* listening socket */
	int		new_fd;		/* newly accept()ed socket descriptor */
	struct sockaddr_storage remoteaddr;	/* client's address */
	socklen_t	addrlen;
	char	buf[8192];	/* buffer for received data */
	int		nBytes;

	/* Since we have the possibility for IPv6, we need to make sure
	   we can hold an address of that length. */
	char remoteIP[INET6_ADDRSTRLEN];

	int yes = 1;	/* for setsockopt() SO_REUSEADDR, below */
	int i, j, rv;

	struct addrinfo hints, *ai, *p;

	FD_ZERO(&master);	/* clear the master and temp socket sets */
	FD_ZERO(&read_fds);

	/* Get a new socket and bind it! */
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;		/* address family unspecified */
	hints.ai_socktype = SOCK_STREAM;	/* streaming socket of course! */
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0) {
		fprintf(stderr, "server: %s\n", gai_strerror(rv));
		exit(1);
	}

	/* Setup the listening sockets */
	for (p = ai; p != NULL; p->ai_next) {
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
	while (1) {
		read_fds = master; /* copy the master set */
		if (select(fd_max+1, &read_fds, NULL, NULL, NULL) == -1) {
			perror("select"); /* massive select failure */
			exit(4);
		}

		/* cycle through the connections, looking for data */
		for (i = 0; i <= fd_max; i++) {
			if (FD_ISSET(i, &read_fds)) { /* new connection */
				/* manage the new connection */
				addrlen = sizeof(remoteaddr);
				new_fd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);
				
				if (new_fd == -1) {
					perror("accept"); /* obviously the server hates us */
				}
				else { /* the server loves us */
					FD_SET(new_fd, &master); /* add to the master set */
					if (new_fd > fd_max) { /* make sure we don't go over the limit */
						fd_max = new_fd;
					}

					printf("server: new connection from %s on socket %d\n",
							inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr *)&remoteaddr),
								remoteIP, INET6_ADDRSTRLEN), new_fd);
					}
			}
			else {
				/* handle data from the client */
				if ((nBytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
					/* got an error for client close the connection */
					if (nBytes == 0) {
						/* connection close */
						printf("select: socket %d hung up\n", i);
					}
					else {
						perror("recv");
					}
					close(i);	/* goodbye */
					FD_CLR(i, &master); /* remove from master set */
				}
				else {
					/* we got data from a client */
					for (j = 0; j <= fd_max; j++) {
						/* sent to every client -- this will be where we process data
						   in the future. This section should be fleshed out */
						if (FD_ISSET(j, &master)) {
							/* only echo back to the client that connected */
							if (j != listener && j = i) {
								if (send(j, buf, nBytes, 0) == -1) {
									perror("send"); /* massive failure!!! */
								}
							}
						}
					}
				} /* end of handling data from the client */
			} /* end of new connection */
		} /* end of descriptor loop */
	} /* end of infinite while loop */
}
