# Makefile for Assignment #1 - Backdoor Communication
#                              using BSD-style tcp/ip headers
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-c -Wall -pedantic
LDFLAGS=

all:	backdoor-betty backdoor-carl

backdoor-betty: backdoor-betty.o auth.o crypt.o
		${CC} ${LDFLAGS} backdoor-betty.o auth.o crypt.o -o backdoor-betty

backdoor-carl: backdoor-carl.o auth.o crypt.o
		${CC} ${LDFLAGS} backdoor-carl.o auth.o crypt.o -o backdoor-carl

backdoor-betty.o: backdoor-betty.c
		${CC} ${CFLAGS} backdoor-betty.c 

backdoor-carl.o: backdoor-carl.c
		${CC} ${CFLAGS} backdoor-carl.c

auth.o: auth.c
	${CC} ${CFLAGS} auth.c

crypt.o: crypt.c
	${CC} ${CFLAGS} crypt.c

clean:
		rm -rf *.o backdoor-betty backdoor-carl
