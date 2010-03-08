# Makefile for Assignment #2 - Scalability Comparison of select-, multi-threaded-,
#                              and epoll-based client-server implementations.
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS_EV_MT=-lpthread
LDFLAGS_EV_EV=-levent

all:	server-multi-threaded server-select server-epoll client

server-multi-threaded: server-multi-threaded.o linked-list.o
		${CC} ${LDFLAGS_EV_MT} server-multi-threaded.o linked-list.o -o server-multi-threaded
		rm *.o

server-select: server-select.o
		${CC} ${LDFLAGS_EV} server-select.o linked-list.o -o server-select
		rm *.o

server-epoll: server-epoll.o
		${CC} ${LDFLAGS_EV} server-epoll.o linked-list.o -o server-epoll
		rm *.o

client: client.o
		${CC} ${LDFLAGS_EV} client.o linked-list.o -o client
		rm *.o

server-multi-threaded.o: server-multi-threaded.c
		${CC} ${CFLAGS} server-multi-threaded.c linked-list.c

server-select.o: server-select.c
		${CC} ${CFLAGS} server-select.c linked-list.c

server-epoll.o: server-epoll.c
		${CC} ${CFLAGS} server-epoll.c linked-list.c

client.o: client.c
		${CC} ${CFLAGS} client.c linked-list.c

clean:
		rm -rf *.o server-multi-threaded server-select server-epoll client
