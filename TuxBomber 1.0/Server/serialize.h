#ifndef SERIALIZE_H
#define SERIALIZE_H

#include "serialize.h"
#include "s_defs.h"
#include "s_player.h"

#include <arpa/inet.h> /* TODO: Remove this when finished debugging */

#define BUF_LEN 64

const char *serialize_player(DPlaya *player);
int unserialize_player(char *buf, DPlaya *player);
int serialize_map(char map[MAP_ROWS][MAP_COLS], char *serialized_form);
int unserialize_map(char *serialized_form, char map[MAP_ROWS][MAP_COLS]);
void send_tcp_player(DPlaya p1, int sockfd);
DPlaya recv_tcp_player(int sockfd);
int send_udp_player(DPlaya *p1, int socketfd, struct sockaddr_in *udpserver);
void recv_udp_player(DPlaya *p1, int socketfd, struct sockaddr_in udpserver);

#endif

