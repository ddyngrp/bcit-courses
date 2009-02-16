#include "server.h"

int main(int argc, char *argv[]) {
	struct addrinfo hints;
	struct addrinfo *servinfo;
	struct sockaddr_in *sa_i;
	char ip[INET_ADDRSTRLEN];
	
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	
	if(getaddrinfo("digg.com", NULL, &hints, &servinfo) == -1) {
		fprintf(stderr, "Error\n");
	} else {
		sa_i = (struct sockaddr_in *)servinfo->ai_addr;
		inet_ntop(AF_INET, &(sa_i->sin_addr), ip, INET_ADDRSTRLEN);
		printf("ip of digg.com is %s\n", ip);
	}
	
	freeaddrinfo(servinfo);
	
	return 0;
}