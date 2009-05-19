# Makefile for Spry

CC=gcc
CFLAGS=-c -Wall -pedantic -ggdb -g
LDFLAGS=-lpthread
GTKOPTS=-export-dynamic `pkg-config --cflags --libs gtk+-2.0 libsoup-2.4`
WEBKITOPTS=-L /usr/lib -I /usr/include/webkit-1.0/ -g `pkg-config --libs webkit-1.0`
MISCOPTS=
SOURCES=main.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=spry

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(GTKOPTS) $(WEBKITOPTS) $(MISCOPTS)

.c.o:
		$(CC) $(CFLAGS) $< -o $@ $(GTKOPTS) $(WEBKITOPTS) $(MISCOPTS)

clean:
		rm $(OBJECTS) $(EXECUTABLE)
