# Makefile for simple server
#
# Author: Steffen L. Norgren
#

CC=g++
CFLAGS=-c -Wall -pedantic -ggdb
LDFLAGS=-lpthread
SOURCES=master.cpp server.cpp client.cpp tools.cpp network.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=clisrv

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		@$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		@$(CC) $(CFLAGS) $< -o $@

clean:
		@rm $(OBJECTS) $(EXECUTABLE)
