# Makefile for simple server
#
# Author: Steffen L. Norgren
#

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb -g
LDFLAGS=
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0`
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=chat

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(GTKFLAGS)

.c.o:
		$(CC) $(CFLAGS) $< -o $@ $(GTKFLAGS)

clean:
		rm $(OBJECTS) $(EXECUTABLE)
