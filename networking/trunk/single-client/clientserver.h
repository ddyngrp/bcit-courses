#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_PORT "3840" /* the port we're listening on. decimal rep of 0xF00 */
#define MAX_CONNS 8 /* number of connections allowed at once */

#define SUCCESS 0
#define FAIL -1

#define KEEPALIVE 0
#define REQ_MOVE  1
#define ACT_MOVE  2
#define REQ_BOMB  4
#define ACT_BOMB  8

typedef struct {
	int type;
	unsigned short x, y;
} Packet;

#endif