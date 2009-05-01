# Makefile for simple server
#
# Author: Steffen L. Norgren
#

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb -g
LDFLAGS=-lpthread
GTKFLAGS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0`
WEBKITFLAGS=-L /usr/lib -I /usr/include/webkit-1.0/ -g `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0 webkit-1.0`
SOURCES=main.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=spry

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(GTKFLAGS) $(WEBKITFLAGS)

.c.o:
		$(CC) $(CFLAGS) $< -o $@ $(GTKFLAGS) $(WEBKITFLAGS)

clean:
		rm $(OBJECTS) $(EXECUTABLE)
