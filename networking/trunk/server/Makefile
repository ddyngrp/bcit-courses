# Makefile for simple server
#
# Author: Steffen L. Norgren
#

CC=gcc					# The compiler being used
CFLAGS=-c -Wall -pedantic -ggdb	# Compiler command line options
LDFLAGS=				# Linker command line options
SOURCES=master.c server.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=server

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm $(OBJECTS) $(EXECUTABLE)
