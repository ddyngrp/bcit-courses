#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

void *zombie_harvester();
void serve_client(pid_t);
void wait_for_client();
void fatal(char *);
void catch_sig(int);

#endif
