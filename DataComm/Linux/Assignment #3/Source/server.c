#include "server.h"
#include "signal_handler.h"
#include "tools.h"

/* Initialize sockets, etc. */
void *start_server(void *ptr) {
	fd_set	master;
	fd_set	read_fds;
	int		fd_max;
	int		listener;
	int		new_fd;	
	struct sockaddr_storage remoteaddr;
	socklen_t	addrlen;
	char	buf[256];
	char	conn_text[256];
	int		nBytes;
	int		yes = 1;	/* for setsockopt() SO_REUSEADDR, below */
	int		i, j, rv;

	struct addrinfo hints, *ai, *p;

	/* Remote Host Info */
	struct hostent *remoteHost;

	GtkTextBuffer   *client_list; /* Output for the client list */
	GtkTextIter		iter;
	client_list = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_client_list));

	FD_ZERO(&master);	/* clear the master and temp socket sets */
	FD_ZERO(&read_fds);

	/* Get a new socket and bind it! */
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		/* address family unspecified */
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
					}
					else { /* the server loves us */
						FD_SET(new_fd, &master); /* add to the master set */
						if (new_fd > fd_max) { /* make sure we don't go over the limit */
							fd_max = new_fd;
						}

						/* Get the client's hostname */
						remoteHost = gethostbyaddr(get_in_addr((struct sockaddr *)&remoteaddr), sizeof(struct sockaddr), AF_INET);
						sprintf(conn_text, "%s connected on socket %d\n", remoteHost->h_name, new_fd);

						gtk_text_buffer_insert_at_cursor(client_list, conn_text, -1);
						gtk_text_buffer_get_end_iter(client_list, &iter);
						gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(client_list), &iter, 0.0, FALSE, 0, 0);
					}
				}
				else {
					/* handle data from the client */
					if ((nBytes = recv(i, buf, sizeof(buf), 0)) <= 0) {
						/* got an error for client close the connection */
						if (nBytes == 0) {
							/* connection close */
							remoteHost = gethostbyaddr(get_in_addr((struct sockaddr *)&remoteaddr), sizeof(struct sockaddr), AF_INET);
							sprintf(conn_text, "client on socket %d hung up\n", i);
							gtk_text_buffer_insert_at_cursor(client_list, conn_text, -1);
							gtk_text_buffer_get_end_iter(client_list, &iter);
							gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(client_list), &iter, 0.0, FALSE, 0, 0);
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
							if (FD_ISSET(j, &master)) {
								/* echo incoming data to all clients ecept the sender */
								if (j != listener && j != i) {
									if (send(j, buf, nBytes, 0) == -1) {
										perror("send"); /* massive failure!!! */
									}
								}
							}
						}
					}
				} /* end of handling data from the client */
			} /* end of new connection */
		} /* end of descriptor loop */
	} /* end of infinite while loop */
}
