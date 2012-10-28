# Makefile for simple server
#
# Author: Steffen L. Norgren
#

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb -g
LDFLAGS=-lpthread
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0`
SOURCES=main.c signal_handler.c server.c tools.c client.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=chat

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(GTKFLAGS)

.c.o:
		$(CC) $(CFLAGS) $< -o $@ $(GTKFLAGS)

clean:
		rm $(OBJECTS) $(EXECUTABLE)
