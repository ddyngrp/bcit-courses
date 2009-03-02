#ifndef TUXBOMBER_NETWORK_H
#define TUXBOMBER_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define KEEPALIVE	0
#define MAP			1
#define MOVE		2
#define BOMB		4
#define EXPLOSION	8

#define CLIENT	0
#define SERVER	1

#define iTYPE	0

#define LISTEN_PORT	"3840"

#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM

int conn_type = TCP;
int sock = 0;
int mode = CLIENT;
struct sockaddr_in server;

int set_conn_type(int type);
int conn_setup(char *host, char *port);
int keepalive(); /* just an empty packet to let the other side know we're still here */

/* look into using memcpy for map_class->char* and vise versa */
int send_map(unsigned char *map); /* send the map */
int recv_map(unsigned char *map); /* receive the map */

int request_move(int x, int y); /* request a move to the xy-coord */
int request_bomb(int type); /* request a bomb drop of the specified type */
int explode_bomb(int x, int y); /* explode the bomb at the xy-coords */

/* transfer the data, regardless of TCP/UDP */
int transfer(unsigned char *data, size_t len);
/* writes xy into the char-string and appends a null-char at the end */
int add_coords_xy(int x, int y, unsigned char *data, size_t len);
/* process the data that's received */
int process_data(unsigned char *data, size_t len);

#endif
