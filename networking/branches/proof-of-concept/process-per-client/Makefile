# Makefile for process-per-client proof of concept
#
# Author: Steffen L. Norgren
#

CC=gcc					# The compiler being used
CFLAGS=-c -Wall -Os		# Compiler command line options
LDFLAGS=				# Linker command line options
SOURCES=master.c client.c server.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=process-per-client

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm $(OBJECTS) $(EXECUTABLE)
