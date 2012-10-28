# Makefile for Assignment #1 - keycatcher
#
# Author: Steffen L. Norgren
#

CC=gcc			# The compiler being used
CFLAGS=-c -Wall -Os	# Compiler command line options
LDFLAGS=		# Linker command line options
SOURCES=keycatcher.c input.c output.c translate.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=keycatcher

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): 	$(OBJECTS)
		$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm $(OBJECTS) $(EXECUTABLE)
