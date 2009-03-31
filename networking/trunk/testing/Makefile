CC = g++
CFLAGS = -Wall -ggdb
SOURCES = test.cpp network.cpp
OBJECTS = $(SOURCES:.cpp=.o)
PROG = tuxtest

project: $(SOURCES) $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm $(OBJECTS) $(PROG)