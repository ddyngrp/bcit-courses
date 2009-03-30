#include "client.h"
#include "network.h"

extern int mode, conn_type, sock;

void start_client(char * server, char * port) {
	struct addrinfo hints, *serverinfo, *p;
	char serverIP[INET6_ADDRSTRLEN];
	char sendbuf[MAXLEN], recvbuf[MAXLEN];
	int sockfd;
	int ret;

	memset(&hints,0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if((ret = getaddrinfo(server, port, &hints, &serverinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
		exit(1);
	}

	for (p = serverinfo; p !=NULL; p = p->ai_next ) {

		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}

		if ((connect(sockfd, p->ai_addr, p->ai_addrlen)) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
	}

	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		exit(2);
	}
	
	inet_ntop(p->ai_family,get_in_addr((struct sockaddr*)p->ai_addr),serverIP,sizeof(serverIP));

	freeaddrinfo(serverinfo);

	/* Sending test data */
	/* test_data(sockfd); */

	/* TODO: Add the ability to detect server disconnects */
	while (fgets(sendbuf, MAXLEN, stdin)) {
		int r;
		if ((send(sockfd, sendbuf, strlen(sendbuf), 0)) == -1) {
			perror("send() call failed.");
			continue;
		}
		if ((r = recv(sockfd, recvbuf, MAXLEN, 0)) == -1) {
			perror("recv call() failed.");
			continue;
		}
		
        /*************************************************************
        ** creating udp socket to catch server tansaction.
        **
        ** by eddie
        ******************/
        if (strcmp(recvbuf,"start\n")==0){
            start_udp_client(server);            
        }
        
        
        
        
		recvbuf[r] = '\0';
		fprintf(stdout, "%s", recvbuf);
	}
}

void start_udp_client(char *hostname){

	int sd;

	struct sockaddr_in udpserver, udpclient;
	struct hostent *hp;
	int udp_port = 8000;
	char *inbuf,*outbuf;


	printf("initializing the socket");
    if ((sd = socket(AF_INET,SOCK_DGRAM,0))==-1){
        perror("Can't crete a socket\n");
        exit(1);
    }
    /*store server */
    bzero((char*)&udpserver,sizeof(udpserver));
    udpserver.sin_family=AF_INET;
    udpserver.sin_port = htons(udp_port);
    
    if ((hp = gethostbyname(hostname))==NULL){
        fprintf(stderr,"Can't get server's IP address\n");
        exit(1);
    }
    
    
    bcopy(hp->h_addr, (char *)&udpserver.sin_addr,hp->h_length);
    /*bind local address to the socket*/
    bzero((char*)&udpclient,sizeof(udpclient));
    udpclient.sin_family = AF_INET;
    udpclient.sin_port = htons(0);
    udpclient.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(sd,(struct sockaddr *)&udpclient, sizeof(udpclient)) ==-1){
        perror("Can't bind name to socket");
        exit(1);
    }
    
    /* sending keyboard inputs*/
   while (fgets(inbuf, MAXLEN, stdin)){
   	
   	    printf("start sending...\n");
        if (sendto(sd,inbuf,strlen(inbuf),0,(struct sockaddr *)&server, sizeof(udpserver))==-1){
            perror("sendto failure");
            exit(1);
        }
        printf("stuff sent!\n");
        /*receive data*/
        
        if (recvfrom(sd,outbuf,MAXLEN,0,(struct sockaddr *)&udpserver,(socklen_t *)sizeof(udpserver)) < 0){
            perror("recvfrom error");
            exit(1);
        }
        
        if (strcmp(outbuf,"quit\n") == 0){
            close(sd);
            break;
        }else{
            printf("length = %d; buf =%s",(int)strlen(outbuf),outbuf);
            break;
        }
   
   }

}
void test_data(int socket) {
	char buf[1000000];
	char recvbuf[MAXLEN];
	int i, r;

	for (i = 0; i < 1000000; i++) {
		sprintf(buf, "%d\n", i);
		if ((send(socket, buf, strlen(buf), 0)) == -1) {
			perror("send() call failed");
			continue;
		}

		if ((r = recv(socket, recvbuf, MAXLEN, 0)) == -1) {
			perror("recv call() failed");
			continue;
		}
		recvbuf[r] = '\0';
		fprintf(stdout, "%s", recvbuf);
	}
	exit(0);
}
