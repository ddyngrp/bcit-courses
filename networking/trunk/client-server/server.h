#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "DPlaya.h"
#include "serialize.h"

#define PORT	"3840"

struct tcp_server {
	fd_set	master,
			read_fds;
	int		listener,
			fd_max,
			new_fd,
			recvBytes,
			mode;

	unsigned char	recvBuff[8192];
};

void tcp_listen(void);
void start_server(void);
void *start_udp_server(void *);

#endif
