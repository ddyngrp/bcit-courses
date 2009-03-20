# Makefile for simple server
#
# Author: Steffen L. Norgren
#

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb
LDFLAGS=
SOURCES=master.c server.c client.c tools.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=clisrv

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm $(OBJECTS) $(EXECUTABLE)
