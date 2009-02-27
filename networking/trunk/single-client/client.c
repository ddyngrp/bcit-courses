#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "clientserver.h"

int main(int argc, char *argv[]) {
	struct addrinfo hints;
	struct addrinfo *results;
	int sock;
	int a;
	Packet p;
	char buf[32];
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo("127.0.0.1", "3840", &hints, &results);
	fork();fork();fork();
	sock = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
	connect(sock, results->ai_addr, results->ai_addrlen);
	for(a = 0; a < 10; a++) {
		usleep(100000); /* sleep for 100,000 us, or 100 ms between sends */
		memset(&p, 0, sizeof(Packet));
		p.type = REQ_MOVE;
		p.x = a;
		p.y = a;
		send(sock, &p, sizeof(Packet), 0);
		recv(sock, buf, 32, 0);
		printf("%s\n", buf);
	}
	
	shutdown(sock, 2);
	close(sock);
	
	return 0;
}