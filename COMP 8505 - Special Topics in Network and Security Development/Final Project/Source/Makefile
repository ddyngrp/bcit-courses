# Makefile for Final Project
#
# utilsor: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpcap -lcrypto -lz

all:	test_crypto test_compression test_file_watcher test_ssh

test_crypto: cryptography.o
	  ${CC} ${LDFLAGS} cryptography.o -o test_crypto

test_compression: compression.o
	  ${CC} ${LDFLAGS} compression.o -o test_compression

test_file_watcher: file_watcher.o
	  ${CC} ${LDFLAGS} file_watcher.o -o test_file_watcher

test_ssh: ssh_utils.o
	  ${CC} ${LDFLAGS} ssh_utils.o -o test_ssh

cryptography.o: cryptography.c
	${CC} ${CFLAGS} cryptography.c

compression.o: compression.c
	${CC} ${CFLAGS} compression.c

file_watcher.o: file_watcher.c
	${CC} ${CFLAGS} file_watcher.c

ssh_utils.o: ssh_utils.c
	${CC} ${CFLAGS} ssh_utils.c

clean:
		rm -rf *.o *.ciphertext *.plaintext *.deflated *.inflated test_crypto test_compression test_file_watcher test_ssh
