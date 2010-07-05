# Makefile for Final Project
#
# utilsor: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpcap

all:	client server test

server: server.o
		${CC} ${LDFLAGS} server.o -o server

client: client.o
		${CC} ${LDFLAGS} client.o -o client

test: crypt.o
	  ${CC} ${LDFLAGS} crypt.o -o test

server.o: server.c
		${CC} ${CFLAGS} server.c 

client.o: client.c
		${CC} ${CFLAGS} client.c

crypt.o: crypt.c
	${CC} ${CFLAGS} crypt.c

clean:
		rm -rf *.o server client test
