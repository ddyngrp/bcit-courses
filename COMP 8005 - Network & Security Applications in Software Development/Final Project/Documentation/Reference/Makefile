# Makefile for Final Project – Prototype GUI
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0`
LDFLAGS=-lpthread

# cc -I/usr/local/include -o event-test event-test.c -L/usr/local/lib -levent

all:	prototype

prototype: prototype.o
		${CC} ${LDFLAGS} prototype.o -o prototype $(GTKFLAGS)
		rm *.o

prototype.o: prototype.c
		${CC} ${CFLAGS} prototype.c $(GTKFLAGS)

clean:
		rm -rf *.o prototype
