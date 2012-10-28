# Makefile for Assignment #1 - Portable covert communications
#                              using BSD-style tcp/ip headers
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-c -Wall -pedantic
LDFLAGS=

all:	covert

covert: covert.o
		${CC} ${LDFLAGS} covert.o -o covert
		rm *.o

covert.o: covert.c
		${CC} ${CFLAGS} covert.c

clean:
		rm -rf *.o covert
