# Makefile for simple server
#
# Author: Steffen L. Norgren
#

CC=g++
CFLAGS=-c -Wall -pedantic -ggdb
LDFLAGS=-lpthread -lSDL -lSDL_image
SOURCES=globals.cpp master.cpp server.cpp udp_server.cpp client.cpp network.cpp serialize.cpp utils.cpp DPlaya.cpp funcs.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=clisrv

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		@rm $(OBJECTS) $(EXECUTABLE)
