# Makefile for Assignment #2 - Message Queue File Transfer
#
# Author: Steffen L. Norgren
#

CC=gcc					# The compiler being used
CFLAGS=-c -Wall -ggdb	# Compiler command line options
LDFLAGS=				# Linker command line options

all: client server

client: client.o message_handler.o
		${CC} ${LDFLAGS} client.o message_handler.o -o client

server: server.o file_handler.o message_handler.o
		${CC} ${LDFLAGS} server.o file_handler.o message_handler.o -o server

client.o: client.c
		  ${CC} ${CFLAGS} client.c

server.o: server.c
		  ${CC} ${CFLAGS} server.c

file_handler.o: file_handler.c
				${CC} ${CFLAGS} file_handler.c

message_handler.o: message_handler.c
				   ${CC} ${CFLAGS} message_handler.c

clean:
		rm -rf *.o server client
