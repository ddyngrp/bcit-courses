# Makefile for Final Project
#
# utilsor: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpcap -lcrypto -lz

all:	test_crypto test_compression

test_crypto: cryptography.o
	  ${CC} ${LDFLAGS} cryptography.o -o test_crypto

test_compression: compression.o
	  ${CC} ${LDFLAGS} compression.o -o test_compression

cryptography.o: cryptography.c
	${CC} ${CFLAGS} cryptography.c

compression.o: compression.c
	${CC} ${CFLAGS} compression.c

clean:
		rm -rf *.o *.ciphertext *.plaintext *.deflated *.inflated test_crypto test_compression
