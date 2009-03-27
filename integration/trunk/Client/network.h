#ifndef NETWORK_H
#define NETWORK_H

#include "general.h"

int connection_setup(char * servIp);
void *get_in_addr(struct sockaddr *sa);
void sig_handler (int sig);
int start_udp_client(char *hostname);

#endif

