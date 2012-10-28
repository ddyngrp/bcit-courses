# Makefile for Assignment #1 - Backdoor Communication
#                              using BSD-style tcp/ip headers
#
# utilsor: Steffen L. Norgren <ironix@trollop.org>
#         A00683006
#

CC=gcc
CFLAGS=-Os -c -Wall -pedantic
LDFLAGS=-lpcap

all:	backdoor-betty backdoor-carl

backdoor-betty: backdoor-betty.o utils.o pkt_cap.o
		${CC} ${LDFLAGS} backdoor-betty.o utils.o pkt_cap.o -o backdoor-betty

backdoor-carl: backdoor-carl.o utils.o pkt_cap.o
		${CC} ${LDFLAGS} backdoor-carl.o utils.o pkt_cap.o -o backdoor-carl

backdoor-betty.o: backdoor-betty.c
		${CC} ${CFLAGS} backdoor-betty.c 

backdoor-carl.o: backdoor-carl.c
		${CC} ${CFLAGS} backdoor-carl.c

utils.o: utils.c
	${CC} ${CFLAGS} utils.c

pkt_cap.o: pkt_cap.c
	${CC} ${CFLAGS} pkt_cap.c

clean:
		rm -rf *.o backdoor-betty backdoor-carl
