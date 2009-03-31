#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

/* message types */
#define KEEPALIVE	0
#define MAP			1
#define MOVE		2
#define BOMB		4
#define EXPLOSION	8
/* end message types */

/* program modes */
#define CLIENT	0
#define SERVER	1
/* end program modes */

/* important array indexes */
#define iTYPE	0
/* end important array indexes */

#define LISTEN_PORT	"3840"

/* protocol types */
#define TCP SOCK_STREAM
#define UDP SOCK_DGRAM
/* protocol types */

/* message-type errors for process_data */
#define ERR_UNKNOWN_INPUT		(-1)
#define ERR_SERV_RECV_MAP		(-2)
#define ERR_SERV_RECV_EXPLOSION	(-3)
#define ERR_CLNT_RECV_MOVE		(-4)
#define ERR_CLNT_RECV_BOMB		(-5)
/* end message-type errors */

/* global definitions */
#define MAP_LEN	255
#define MAP_ROWS 15
#define MAP_COLS 15
/* end global definitions */

static int conn_type = TCP;
static int sock = 0;
static int mode = CLIENT;
static struct sockaddr_in server;

int set_conn_type(int type);
int conn_setup(char *host, char *port);
void keepalive(); /* just an empty packet to let the other side know we're still here */

/* send the map */
int send_map(int sockets[], int num_sockets, unsigned char *map, size_t len);
int recv_map(unsigned char *map, size_t len); /* receive the map */

int request_move(int x, int y); /* request a move to the xy-coord */
int request_bomb(int type); /* request a bomb drop of the specified type */
int explode_bomb(int x, int y); /* explode the bomb at the xy-coords */

/* transfer the data, regardless of TCP/UDP */
int transfer(int socket, unsigned char *data, size_t len);
/* writes xy into the char-string and appends a null-char at the end */
int add_coords_xy(int x, int y, unsigned char *data, size_t len);
/* process the data that's received */
int process_data(unsigned char *data, size_t len);

int parse_info_byte(unsigned char *data);
int get_action_type(int info);
int get_player_id(int info);
int get_extra_info(int info);
unsigned char create_info_byte(int action, int player, int extra);

#endif
