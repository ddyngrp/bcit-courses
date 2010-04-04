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

#define SERVER_PORT 9000

struct client {
	int fd;
	ev_io ev_write;
	ev_io ev_read;
};

ev_io ev_accept;

int setnonblock(int fd)
{
	int flags;
	
	flags = fcntl(fd, F_GETFL);
	if (flags < 0)
		return flags;
	flags |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flags) < 0) 
		return -1;
	
	return 0;
}

static void write_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{ 
	struct client *cli= ((struct client*) (((char*)w) - offsetof(struct client, ev_write)));
	char superjared[]="Testing";
	
	if (revents & EV_WRITE) {
		write(cli->fd, superjared, strlen(superjared));
		ev_io_stop(EV_A_ w);
	}
	close(cli->fd);
	free(cli);
}

static void read_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{ 
	struct client *cli= ((struct client*) (((char*)w) - offsetof(struct client, ev_read)));
	int r=0;
	char rbuff[1024];
	if (revents & EV_READ) {
		r=read(cli->fd, &rbuff, 1024);
	}
	ev_io_stop(EV_A_ w);
	ev_io_init(&cli->ev_write, write_cb, cli->fd, EV_WRITE);
	ev_io_start(loop, &cli->ev_write);
}

static void accept_cb(struct ev_loop *loop, struct ev_io *w, int revents)
{
	int client_fd;
	struct client *client;
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	client_fd = accept(w->fd, (struct sockaddr *)&client_addr, &client_len);
	if (client_fd == -1) {
		return;
	}
	
	client = calloc(1, sizeof(*client));
	client->fd=client_fd;
	if (setnonblock(client->fd) < 0)
		err(1, "failed to set client socket to non-blocking");
	ev_io_init(&client->ev_read, read_cb, client->fd, EV_READ);
	ev_io_start(loop, &client->ev_read);
}

int main()
{
	struct ev_loop *loop = ev_default_loop (0);
	int listen_fd;
	struct sockaddr_in listen_addr; 
	int reuseaddr_on = 1;
	listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
	if (listen_fd < 0)
		err(1, "listen failed");
	if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_on, sizeof(reuseaddr_on)) == -1)
		err(1, "setsockopt failed");
	memset(&listen_addr, 0, sizeof(listen_addr));
	listen_addr.sin_family = AF_INET;
	listen_addr.sin_addr.s_addr = INADDR_ANY;
	listen_addr.sin_port = htons(SERVER_PORT);
	if (bind(listen_fd, (struct sockaddr *)&listen_addr, sizeof(listen_addr)) < 0)
		err(1, "bind failed");
	if (listen(listen_fd, 5) < 0)
		err(1, "listen failed");
	if (setnonblock(listen_fd) < 0)
		err(1, "failed to set server socket to non-blocking");
	
	ev_io_init(&ev_accept, accept_cb, listen_fd, EV_READ);
	ev_io_start(loop, &ev_accept);
	ev_loop (loop, 0);
	return 0;
}
