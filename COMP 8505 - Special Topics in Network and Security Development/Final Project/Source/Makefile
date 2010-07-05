# Makefile for Final Project
#
# utilsor: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpcap -lcrypto

all:	client server test

server: server.o
		${CC} ${LDFLAGS} server.o -o server

client: client.o
		${CC} ${LDFLAGS} client.o -o client

test: cryptography.o
	  ${CC} ${LDFLAGS} cryptography.o -o test

server.o: server.c
		${CC} ${CFLAGS} server.c 

client.o: client.c
		${CC} ${CFLAGS} client.c

cryptography.o: cryptography.c
	${CC} ${CFLAGS} cryptography.c

clean:
		rm -rf *.o *.ciphertext *.plaintext server client test
