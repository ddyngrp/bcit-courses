#include "clientserver.h"

int main(int argc, char *argv[]) {
	struct addrinfo hints, *results;
	struct sockaddr_in *sa_i;
	struct sockaddr client_addr;
	char ip[INET_ADDRSTRLEN];
	int sock, client_sock, status;
	socklen_t client_addrlen = sizeof(struct sockaddr_storage);
	Packet p;
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	
	if((status = getaddrinfo(NULL, LISTEN_PORT, &hints, &results)) != 0) {
		fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
		return FAIL;
	}
	
	/* socket(AF_INET, SOCK_STREAM, IPPROTO_TCP) would work, but would be ip4 specific */
	sock = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
	bind(sock, results->ai_addr, results->ai_addrlen);
	listen(sock, MAX_CONNS);
	
	freeaddrinfo(results);
	
	while((client_sock = accept(sock, &client_addr, &client_addrlen)) != -1) {
		sa_i = (struct sockaddr_in *)&client_addr;
		inet_ntop(results->ai_family, &sa_i->sin_addr, ip, INET_ADDRSTRLEN);
		
		while((status = recv(client_sock, &p, sizeof(Packet), 0))) {
			printf("%s sent %d bytes %d %d\n", ip, status, p.x, p.y);
			send(client_sock, "got your message", strlen("got your message"), 0);
		}
		
		shutdown(client_sock, 2);
		close(client_sock);
	}
	
	return SUCCESS;
}