# Makefile for Final Project
#
# utilsor: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb
LDFLAGS=-lpcap -lcrypto -lz -levent

all:	client server

client: client.o cryptography.o compression.o ssh_utils.o packet_utils.o
	  ${CC} ${LDFLAGS} client.o cryptography.o compression.o ssh_utils.o packet_utils.o -o client

server: server.o cryptography.o compression.o file_watcher.o ssh_utils.o packet_utils.o
	  ${CC} ${LDFLAGS} server.o cryptography.o compression.o file_watcher.o ssh_utils.o packet_utils.o -o server

cryptography.o: cryptography.c
	${CC} ${CFLAGS} cryptography.c

compression.o: compression.c
	${CC} ${CFLAGS} compression.c

file_watcher.o: file_watcher.c
	${CC} ${CFLAGS} file_watcher.c

ssh_utils.o: ssh_utils.c
	${CC} ${CFLAGS} ssh_utils.c

packet_utils.o: packet_utils.c
	${CC} ${CFLAGS} packet_utils.c

client.o: client.c
	${CC} ${CFLAGS} client.c

server.o: server.c
	${CC} ${CFLAGS} server.c

clean:
		rm -rf *.o client server
