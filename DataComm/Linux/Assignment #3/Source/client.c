#include "client.h"
#include "tools.h"
#include "signal_handler.h"

int start_client(const gchar * server) {
	struct addrinfo hints, *serverinfo, *p;
	char serverIP[INET6_ADDRSTRLEN];
	int ret;
	
	memset(&hints,0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if((ret = getaddrinfo(server, PORT, &hints, &serverinfo)) != 0) {
		return -1;
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
		return -1;
	}
	
	inet_ntop(p->ai_family,get_in_addr((struct sockaddr*)p->ai_addr),serverIP,sizeof(serverIP));

	freeaddrinfo(serverinfo);

	return 0;
}

void client_send(char * sendbuf) {
	int r;
	char  text_out[MAXLEN];
	char host[128];

	gethostname(host, 128);

	sprintf(text_out, "%s > %s", host, sendbuf);


	if ((r = send(sockfd, text_out, strlen(text_out), 0)) == -1) {
		perror("send() call failed");
	}
}

void *client_recv(void *ptr) {
	char	recvbuf[MAXLEN];
	int		r;

	for (;;) {
		if ((r = recv(sockfd, recvbuf, MAXLEN, 0)) == -1) {
			perror("recv call() failed");
			continue;
		}
		recvbuf[r] = '\n';
		recvbuf[r+1] = '\0';
		append_text(recvbuf);
	}
}

void append_text(char * text) {
	GtkTextBuffer   *chat_out; 
	GtkTextIter		iter;

	chat_out = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_chat_out));

	gtk_text_buffer_insert_at_cursor(chat_out, text, -1);

	/* Scroll to end */
	gtk_text_buffer_get_end_iter(chat_out, &iter);
	gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_chat_out), &iter, 0.0, FALSE, 0, 0);
}
