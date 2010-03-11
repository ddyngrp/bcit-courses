# Makefile for Assignment #2 - Scalability Comparison of select-, multi-threaded-,
#                              and epoll-based client-server implementations.
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS_MT=-lpthread
LDFLAGS_EV=-levent

# cc -I/usr/local/include -o event-test event-test.c -L/usr/local/lib -levent

all:	server-multi-threaded server-select server-epoll client

server-multi-threaded: server-multi-threaded.o
		${CC} ${LDFLAGS_MT} server-multi-threaded.o -o server-multi-threaded
		rm *.o

server-select: server-select.o
		${CC} ${LDFLAGS_EV} server-select.o -o server-select
		rm *.o

server-epoll: server-epoll.o
		${CC} ${LDFLAGS_EV} server-epoll.o -o server-epoll
		rm *.o

client: client.o
		${CC} ${LDFLAGS_MT} client.o -o client
		rm *.o

server-multi-threaded.o: server-multi-threaded.c
		${CC} ${CFLAGS} server-multi-threaded.c

server-select.o: server-select.c
		${CC} ${CFLAGS} server-select.c

server-epoll.o: server-epoll.c
		${CC} ${CFLAGS} server-epoll.c

client.o: client.c
		${CC} ${CFLAGS} client.c

clean:
		rm -rf *.o *.csv server-multi-threaded server-select server-epoll client
