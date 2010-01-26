# Makefile for Assignment #1 - Processes vs. Threads
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpthread

all:	process thread

process: process.o
		${CC} process.o -o process
		rm process.o

thread: thread.o
		${CC} ${LDFLAGS} thread.o -o thread
		rm thread.o

process.o: process.c
		  ${CC} ${CFLAGS} process.c

thread.o: thread.c
		  ${CC} ${CFLAGS} thread.c

clean:
		rm -rf *.o process thread
