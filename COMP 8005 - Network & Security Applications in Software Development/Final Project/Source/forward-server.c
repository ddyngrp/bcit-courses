/*-----------------------------------------------------------------------------
 * forward-server.c
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * forward-server.c is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * forward-server.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "forward-server.h"

int setnonblock(int fd)
{
	int flags;
	
	flags = fcntl(fd, F_GETFL);
	if (flags <= ERROR)
		return flags;
	
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) <= ERROR) 
		return -1;
	
	return ERROR_NONE;
}

static void read_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{ 
	int rlen = 0, wlen = 0;
	char read_buff[IO_BUFFER];
	
	if (revents & EV_READ) {
		/* if request is from client, sent to remote */
		if (w->fd == client->fd_in) {
			rlen = read(client->fd_in, &read_buff, IO_BUFFER);
			
			/* only send if we have data */
			if (rlen > 0)
				wlen = write(client->fd_out, read_buff, rlen);
			else {
				close(client->fd_in);
				close(client->fd_out);
				free(client);
				return;
			}

		} /* otherwise send remote results back to client */
		else if (w->fd == client->fd_out) {
			rlen = read(client->fd_out, &read_buff, IO_BUFFER);
			
			/* only send if we have data */
			if (rlen > 0)
				wlen = write(client->fd_in, read_buff, rlen);
		}
	}
}

static void accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	int fd_in, fd_out;
	struct sockaddr_in in_addr, out_addr;
	struct hostent *hent;
	socklen_t in_len = sizeof(in_addr);
	socklen_t out_len = sizeof(out_addr);
	
	/* create two linked objects: inbound & outboind client requests */
	fd_in = accept(w->fd, (struct sockaddr *)&in_addr, &in_len);
	
	if (fd_in == ERROR)
		return;
	
	/* create the outbound socket */
	if ((fd_out = socket(AF_INET, SOCK_STREAM, 0)) <= ERROR)
		return;
	
	/* create the sockaddr_in structure for the outbound connection */
	if (!(hent = gethostbyname(OUT_IP)))
		return;
	
	memcpy(&out_addr.sin_addr, hent->h_addr, hent->h_length);
	out_addr.sin_port = htons(OUT_PORT);
	out_addr.sin_family = AF_INET;
	
	/* attempt to make the outbound connection */
	if (connect(fd_out, (struct sockaddr *)&out_addr, out_len) <= ERROR)
		if (errno != EINPROGRESS)
			return;
	
	client = calloc(1, sizeof(*client));
	client->fd_in = fd_in;
	client->fd_out = fd_out;
	
	/* set inbound & outbound to non-blocking */
	if (setnonblock(client->fd_in) <= ERROR ||
		setnonblock(client->fd_out) <= ERROR)
		err(1, "failed to set socket to non-blocking");
	
	ev_io_init(&client->ev_read, read_cb, client->fd_in, EV_READ);
	ev_io_start(loop, &client->ev_read);

	ev_io_init(&client->ev_read_out, read_cb, client->fd_out, EV_READ);
	ev_io_start(loop, &client->ev_read_out);
}

int main()
{
	struct ev_loop *loop = ev_default_loop (0);	/* Use the default event loop */
	struct sockaddr_in listen_addr; 
	int listen_fd, reuseaddr_on = 1;

	/* create listening socket */
	listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
	if (listen_fd <= ERROR)
		err(1, "listen failed");
	
	/* reuse the socket address */
	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on,
				   sizeof(reuseaddr_on)) == -1)
		err(1, "setsockopt failed");
	
	/* set to listen on all addresses */
	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = INADDR_ANY;
	listen_addr.sin_port = htons(SERVER_PORT);
	
	/* bind the socket */
	if (bind(listen_fd, (struct sockaddr *)&listen_addr,
			 sizeof(listen_addr)) < 0)
		err(1, "bind failed");
	
	/* listen for new connections */
	if (listen(listen_fd, 5) <= ERROR)
		err(1, "listen failed");
	
	/* set to non-blocking */
	if (setnonblock(listen_fd) <= ERROR)
		err(1, "failed to set server socket to non-blocking");
	
	/* initialise socket watcher, then start it */
	ev_io_init(&ev_accept, accept_cb, listen_fd, EV_READ);
	ev_io_start(loop, &ev_accept);
	
	/* wait for events to arrive */
	ev_loop (loop, 0);
	
	/* loop exited, so end the program */
	return ERROR_NONE;
}
