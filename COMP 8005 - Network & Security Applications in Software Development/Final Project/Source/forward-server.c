/*-----------------------------------------------------------------------------
 * forward-server.c
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * forward-server.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
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

static void write_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{ 
	char buffer[] = "Data sent back!";
	struct client *client = ((struct client*) (((char*)w) -
							offsetof(struct client, ev_write)));
	
	if (revents & EV_WRITE) {
		write(client->fd, buffer, strlen(buffer));
		ev_io_stop(EV_A_ w);
	}
	
	close(client->fd);
	free(client);
}

static void read_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{ 
	struct client *client = ((struct client*) (((char*)w) -
							offsetof(struct client, ev_read)));
	int r = 0;
	char rbuff[IO_BUFFER];
	
	if (revents & EV_READ)
		r = read(client->fd, &rbuff, IO_BUFFER);
	
	ev_io_stop(EV_A_ w);
	ev_io_init(&client->ev_write, write_cb, client->fd, EV_WRITE);
	ev_io_start(loop, &client->ev_write);
}

static void accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	int client_fd;
	struct client *client;
	struct sockaddr_in client_addr;
	
	socklen_t client_len = sizeof(client_addr);
	
	client_fd = accept(w->fd, (struct sockaddr *)&client_addr, &client_len);
	
	if (client_fd == ERROR)
		return;
	
	client = calloc(1, sizeof(*client));
	client->fd = client_fd;
	
	if (setnonblock(client->fd) <= ERROR)
		err(1, "failed to set client socket to non-blocking");
	
	ev_io_init(&client->ev_read, read_cb, client->fd, EV_READ);
	ev_io_start(loop, &client->ev_read);
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
