#include "client.h"

int main(int argc, char* argv[])
{
	struct addrinfo hints, *serverinfo, *p;
	char ass[INET6_ADDRSTRLEN];
	char sendbuf[MAXLEN], recvbuf[MAXLEN];
	int sockfd;
	
	if (argc != 2)
	{
		fprintf(stderr, "Usage: <ip address>\n");
		return 1;
	}

	memset(&hints,0,sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if(!(getaddrinfo(argv[1],PORT,&hints,&serverinfo))) {
		perror("get address info failed");
		return 1;
	}

	for (p = serverinfo; p !=NULL; p = p->ai_next ){
		if ((sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
		{
			perror("Socket create fail.");
			continue;
		}
		
		if((connect(sockfd,p->ai_addr,p->ai_addrlen))==-1)
		{
			perror("connection fail.");
			continue;
		}
		
		break;
	}

	if (p == NULL)
	{
		perror(" failed to connect.");
		return 2;
	}

	inet_ntop(p->ai_family,get_in_addr((struct sockaddr*)p->ai_addr),ass,sizeof(ass));

	freeaddrinfo(serverinfo);

	while(fgets(sendbuf, MAXLEN, stdin)) {
		if((send(sockfd, sendbuf, strlen(sendbuf), 0))==-1) {
			perror("send failed");
		}
		
		if((recv(sockfd, recvbuf, MAXLEN, 0))==-1) {
			perror("recv failed");
		}
	}

	return 0;
	
}
