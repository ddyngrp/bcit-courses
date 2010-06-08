# Makefile for Assignment #1 - Backdoor Communication
#                              using BSD-style tcp/ip headers
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-c -Wall -pedantic
LDFLAGS=

all:	backdoor-betty

backdoor-betty: backdoor-betty.o
		${CC} ${LDFLAGS} backdoor-betty.o -o backdoor-betty
		rm *.o

backdoor-betty.o: backdoor-betty.c
		${CC} ${CFLAGS} backdoor-betty.c

clean:
		rm -rf *.o backdoor-betty
