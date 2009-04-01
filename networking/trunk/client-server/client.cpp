#include "client.h"
#include "network.h"
#include "DPlaya.h"
#include "serialize.h"

#define MAX_LEN 1024
#define BUF_LEN 64

extern int mode, conn_type, sock;

/******************************************************************************
 *  Function:    start_client
 * 
 *  Date:        March 2, 2009
 *
 *  Revisions:   March 29, 2009 - Steffen L. Norgren
 *                   Cleaned up code slightly.
 * 
 *  Designer:    Kyle Macdonald, Eddie Zhang
 *  Programmer:  Kyle Macdonald, Eddie Zhang
 * 
 *  Interface:   start_client(char * server, char * port)
 *		            char * server: the server IP or hostname
 *                  char * port: the server port
 * 
 *  Returns:     void
 * 
 *  Description: Sets up a client connection to a specified server.
 *
 *****************************************************************************/
void start_client(char * server, char * port) {
	struct addrinfo hints, *serverinfo, *p;
	char serverIP[INET6_ADDRSTRLEN];
	char sendbuf[MAXLEN], recvbuf[MAXLEN];
	int sockfd;
	int ret;
	fd_set readfds;


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

	/* TODO: Add the ability to detect server disconnects */
	while (fgets(sendbuf, MAXLEN, stdin)) {
		int r;
		if ((send(sockfd, sendbuf, strlen(sendbuf), 0)) == -1) {
			perror("send() call failed.");
			continue;
		}
		if (strcmp(sendbuf,"start\n") == 0){
			start_udp_client(server);            
		} else {
			if ((r = recv(sockfd, recvbuf, MAXLEN, 0)) == -1) {
				perror("recv call() failed.");
				continue;
			}
			recvbuf[r] = '\0';
			fprintf(stdout, "%s", recvbuf);
		}
	}
}

void start_udp_client(char *hostname){
	int sd;
	struct sockaddr_in udpserver, udpclient;
	struct hostent *hp;
	int udp_port = 8000;
	char inbuf[MAXLEN], outbuf[MAXLEN];
	DPlaya p1, p2;
	
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
    
    fflush(stdout);
    /* sending keyboard inputs*/
   for(;;){
   		int j;
   		inbuf[0] = 0;
   		outbuf[0] = 0;
   		fgets(inbuf, MAXLEN, stdin);

		inbuf[0] = '\0';
		

		p1.setX(1);
		p1.setY(2);
		p1.setNumBombs(3);
		p1.setDroppedBombs(4);
		p1.setID(5);

		serialize_player(&p1, inbuf, BUF_LEN);

		inbuf[(strlen(inbuf)+1)] = '\0';
        
        if (sendto(sd,inbuf,sizeof(DPlaya),0,(struct sockaddr *)&udpserver, sizeof(udpserver))==-1){
            perror("sendto failure");
            exit(1);
        }

		printf("len: %d\n", strlen(inbuf));
		printf("buf: %s\n", inbuf);

		if (recvfrom(sd,outbuf,sizeof(DPlaya),0,NULL,(socklen_t *)sizeof(udpserver)) < 0){
			perror("recvfrom error");
			exit(1);
		}

		unserialize_player(outbuf, &p2);
		printf("%d,%d\n", p1.getX(), p2.getX());
		printf("%d,%d\n", p1.getY(),p2.getY());
		printf("%d,%d\n", p1.getNumBombs(),p2.getNumBombs());
		printf("%d,%d\n", p1.getDroppedBombs(),p2.getDroppedBombs());
		printf("%d,%d\n", p1.getDPlayaID(),p2.getDPlayaID());
	}
}

void send_tcp_player(DPlaya p1, int sockfd) {
	char buf[BUF_LEN];
	serialize_player(&p1, buf, BUF_LEN);

	if ((send(sockfd, buf, sizeof(DPlaya), 0)) == -1) {
		perror("send() call failed.");
	}
}

DPlaya recv_tcp_player(int sockfd) {
	DPlaya p1;
	char buf[BUF_LEN];
	int r;

	if ((r = recv(sockfd, buf, sizeof(DPlaya), 0)) == -1) {
		perror("recv call() failed.");
		return p1;
	}

	unserialize_player(buf, &p1);

	return p1;
}

void send_udp_player(DPlaya p1, int socketfd) {
	char buf[BUF_LEN];
	struct sockaddr_in udpserver;

	serialize_player(&p1, buf, BUF_LEN);

	if (sendto(socketfd, buf,sizeof(DPlaya),0,(struct sockaddr *)&udpserver, sizeof(udpserver))==-1){
        perror("sendto failure");
        exit(1);
    }
}

DPlaya recv_udp_player(int socketfd) {
	DPlaya p1;
	char buf[BUF_LEN];
	struct sockaddr_in udpserver;
	int ret;

	if ((ret = recvfrom(socketfd, buf,sizeof(DPlaya),0,NULL,(socklen_t *)sizeof(udpserver))) <= 0){
		if(ret == 0) {
			fprintf(stderr, "Server closed\n", socketfd);
		} else {
			perror("recvfrom error");
		}

		exit(EXIT_FAILURE);
	} else {
		unserialize_player(buf, &p1);
	}

	return p1;
}

