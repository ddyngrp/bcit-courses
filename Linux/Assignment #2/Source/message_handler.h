#ifndef _MESSAGE_HANDLER_H_
#define _MESSAGE_HANDLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define	MQ_FROM_CLIENT	2
#define MQ_FROM_SERVER	1

int mesg_send(char *, int);
char * mesg_recv(int);

#endif
