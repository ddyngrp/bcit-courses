# Makefile for Assignment #2 - Scalability Comparison of select-, multi-threaded-,
#                              and epoll-based client-server implementations.
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpthread

all:	server-multi-threaded server-select server-epoll client

server-multi-threaded: server-multi-threaded.o
		${CC} server-multi-threaded.o -o server-multi-threaded
		rm server-multi-threaded.o

server-select: server-select.o
		${CC} ${LDFLAGS} server-select.o -o server-select
		rm server-select.o

server-epoll: server-epoll.o
		${CC} ${LDFLAGS} server-epoll.o -o server-epoll
		rm server-epoll.o

client: client.o
		${CC} ${LDFLAGS} client.o -o client
		rm client.o

server-multi-threaded.o: server-multi-threaded.c
		  ${CC} ${CFLAGS} server-multi-threaded.c

server-select.o: server-select.c
		  ${CC} ${CFLAGS} server-select.c

server-epoll.o: server-epoll.c
		  ${CC} ${CFLAGS} server-epoll.c

client.o: client.c
		  ${CC} ${CFLAGS} client.c

clean:
		rm -rf *.o server-multi-threaded server-select server-epoll client
