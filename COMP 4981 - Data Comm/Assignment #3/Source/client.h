#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <gtk/gtk.h>

#define MAXLEN	1024
#define PORT	"3840"

int start_client(const gchar *);
void test_data(int);
void stop_client(void); /* implement later */
void *client_recv(void *);
void client_send(char *);
void append_text(char *);

int sockfd;

#endif
