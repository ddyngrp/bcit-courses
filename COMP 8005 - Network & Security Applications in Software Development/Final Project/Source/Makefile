# Makefile for Final Project – Portable port Forwarder using libev
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc -D LINUX
CFLAGS=-c -Wall -pedantic
LDFLAGS=-lev

all:	forward-server

forward-server: forward-server.o
		${CC} ${LDFLAGS} forward-server.o -o forward-server
		rm *.o

forward-server.o: forward-server.c
		${CC} ${CFLAGS} forward-server.c

clean:
		rm -rf *.o forward-server
