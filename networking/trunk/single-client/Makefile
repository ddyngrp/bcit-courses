CC = gcc
CFLAGS = -Wall -ggdb

project: client server

clean:
	@rm -f *.o *.bak client server
	@echo Project cleaned

client: client.o
	@$(CC) $(CFLAGS) client.o -o client
	@echo Client successfully built

client.o: client.c
	@$(CC) $(CFLAGS) -c client.c

server: server.o
	@$(CC) $(CFLAGS) server.o -o server
	@echo Server successfully built

server.o: server.c
	@$(CC) $(CFLAGS) -c server.c