#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void server_status();
void fatal(char *);
void catch_sig(int);

#endif
