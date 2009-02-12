# Makefile for Assignment #2 - Message Queue File Transfer
#
# Author: Steffen L. Norgren
#

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb
LDFLAGS=-lpthread

all: client server

client: client.o message_handler.o
		${CC} ${LDFLAGS} client.o message_handler.o -o client

server: server.o message_handler.o
		${CC} ${LDFLAGS} server.o message_handler.o -o server

client.o: client.c
		  ${CC} ${CFLAGS} client.c

server.o: server.c
		  ${CC} ${CFLAGS} server.c

message_handler.o: message_handler.c
				   ${CC} ${CFLAGS} message_handler.c

clean:
		rm -rf *.o server client
