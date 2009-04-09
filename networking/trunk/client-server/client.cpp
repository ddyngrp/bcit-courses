#include "client.h"
#include "network.h"
#include "DPlaya.h"
#include "serialize.h"
#include <sys/select.h>

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
	fd_set rfds;
	int stdin_fd = fileno(stdin);

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


	for(;;) {
		int r;

		FD_ZERO(&rfds);
		FD_SET(sockfd, &rfds);
		FD_SET(stdin_fd, &rfds);

		if(select(sockfd+1, &rfds, NULL, NULL, NULL) == -1) {
			perror("select() failed");	
		}

		if(FD_ISSET(sockfd, &rfds)) {
			if ((r = recv(sockfd, recvbuf, sizeof(recvbuf), 0)) == -1) {
				if(r == 0) {
					perror("server closed");
					//exit(EXIT_FAILURE);
				}
				perror("recv call() failed.");
				continue;
			}
			recvbuf[r] = '\0';
			fprintf(stdout, "%s", recvbuf);
			if (strcmp(recvbuf,"start\n") == 0)
				start_udp_client(server); 
		} else if(FD_ISSET(stdin_fd, &rfds)) {
			fgets(sendbuf, MAXLEN, stdin);
			if ((send(sockfd, sendbuf, strlen(sendbuf), 0)) == -1) {
				perror("send() call failed.");
				continue;
			}
		   
			if ((r = recv(sockfd, recvbuf, sizeof(recvbuf), 0)) == -1) {
				if(r == 0) {
					perror("server closed");
					exit(EXIT_FAILURE);
				}
				perror("recv call() failed.");
				continue;
			}
			recvbuf[r] = '\0';
			fprintf(stdout, "%s", recvbuf);
			if (strcmp(recvbuf,"start\n") == 0)
				start_udp_client(server); 
		}
	}

}

void start_udp_client(char *hostname){
	int sd;
	struct sockaddr_in udpserver, udpclient;
	struct hostent *hp;
	int udp_port = 8000;
	char inbuf[MAXLEN], outbuf[MAXLEN];
	DPlaya p1;
	fd_set rfds;
	int stdin_fd = fileno(stdin);

	printf("starting udp server..\n");
	
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
		int n;
   		inbuf[0] = 0;
   		outbuf[0] = 0;
		inbuf[1] = '\0';

		FD_ZERO(&rfds);
		FD_SET(sd, &rfds);
		FD_SET(stdin_fd, &rfds);

		select(sd+1, &rfds, NULL, NULL, NULL);
		if(FD_ISSET(sd, &rfds)) {
			if ((n = recvfrom(sd,outbuf,sizeof(DPlaya),0,NULL,(socklen_t *)sizeof(udpserver))) <= 0){
				if(n==0) {
					printf("server hung up\n");
					exit(EXIT_FAILURE);
				}
		
				perror("recvfrom error");
				exit(1);
			} else {
				unserialize_player(outbuf, &p1);
				printf("p1: %d %d %d\n", p1.getX(), p1.getY(), p1.getNumBombs());
			}
		} else if(FD_ISSET(stdin_fd, &rfds)) {
			if(fgets(inbuf, 2, stdin) == NULL) {
				perror("fgets() call failed");
				continue;
			}

			if (sendto(sd, inbuf,strlen(inbuf),0,(struct sockaddr *)&udpserver, sizeof(udpserver))==-1){
				perror("sendto failure");
				continue;
			}
		}
	}
}


