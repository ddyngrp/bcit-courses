# Makefile for Final Project – Portable port Forwarder using libev
#
# Author: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-c -Wall
LDFLAGS=

all:	oob_cli oob_svr

oob_cli: oob_cli.o
		${CC} ${LDFLAGS} oob_cli.o -o oob_cli
		rm *.o

oob_cli.o: oob_cli.c
		${CC} ${CFLAGS} oob_cli.c

oob_svr: oob_svr.o
		${CC} ${LDFLAGS} oob_svr.o -o oob_svr
		rm *.o

oob_svr.o: oob_svr.c
		${CC} ${CFLAGS} oob_svr.c

clean:
		rm -rf *.o oob_cli oob_svr
