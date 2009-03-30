#include "server.h"

void start_udp_server() {
	int sd, port = 8000, n, j;
	socklen_t client_len;
	char udpbuf[1024];
	struct sockaddr_in udpserver, udpclient;
	
	printf("starting udp server.\n");
	fflush(stdout);

	if((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Socket Creation");
		exit(EXIT_FAILURE);
	}

	bzero((char *)&udpserver, sizeof(udpserver));
	udpserver.sin_family = AF_INET;
	udpserver.sin_port = htons(port);
	udpserver.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(sd, (struct sockaddr *)&udpserver, sizeof(udpserver)) == -1) {
			perror("Binding Socket");
			exit(EXIT_FAILURE);
	}

	for(;;) {
		printf("waiting udp..\n");
		fflush(stdout);

		client_len = sizeof(udpclient);
		if((n = recvfrom(sd, udpbuf, 1024, 0, (struct sockaddr *)&udpclient, &client_len)) < 0) {
			perror("Recv From");
			exit(EXIT_FAILURE);
		}
		for(j=0; udpbuf[j] != '\n'; ++j);
		udpbuf[++j] = '\0';

		printf("sending udp..: %s\n", udpbuf);
		fflush(stdout);

		if(sendto(sd, udpbuf, n, 0, (struct sockaddr *)&udpclient, client_len) < 0) {
			perror("Send To");
			exit(EXIT_FAILURE);
		}

		if(strcmp(udpbuf, "quit\n")==0) {
			close(sd);
			printf("closing udp server\n");
			break;
		}
	}
}