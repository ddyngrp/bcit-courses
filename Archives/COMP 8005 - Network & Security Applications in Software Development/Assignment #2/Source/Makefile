# Makefile for Assignment #2 - Scalability Comparison of select-, multi-threaded-,
#                              and epoll-based client-server implementations.
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpthread -levent

# cc -I/usr/local/include -o event-test event-test.c -L/usr/local/lib -levent

all:	server-multi-threaded client

server-multi-threaded: server-multi-threaded.o
		${CC} ${LDFLAGS} server-multi-threaded.o -o server-multi-threaded
		rm *.o

client: client.o
		${CC} ${LDFLAGS} client.o -o client
		rm *.o

server-multi-threaded.o: server-multi-threaded.c
		${CC} ${CFLAGS} server-multi-threaded.c

client.o: client.c
		${CC} ${CFLAGS} client.c

clean:
		rm -rf *.o *.csv server-multi-threaded client
