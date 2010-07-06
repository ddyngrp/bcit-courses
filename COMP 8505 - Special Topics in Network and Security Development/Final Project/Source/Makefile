# Makefile for Final Project
#
# utilsor: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb
LDFLAGS=-lpcap -lcrypto -lz -levent

all:	test_ssh

test_ssh: ssh_utils.o cryptography.o compression.o
	  ${CC} ${LDFLAGS} ssh_utils.o cryptography.o compression.o -o test_ssh

cryptography.o: cryptography.c
	${CC} ${CFLAGS} cryptography.c

compression.o: compression.c
	${CC} ${CFLAGS} compression.c

file_watcher.o: file_watcher.c
	${CC} ${CFLAGS} file_watcher.c

ssh_utils.o: ssh_utils.c
	${CC} ${CFLAGS} ssh_utils.c

clean:
		rm -rf *.o test_ssh
