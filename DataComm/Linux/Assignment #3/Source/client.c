/*------------------------------------------------------------------------------
-- SOURCE FILE:	client.c - Receives data from a remote server via a socket
-- 
-- PROGRAM:     chat
-- 
-- FUNCTIONS:   start_client(const gchar * server)
--              client_send(char * sendbuf)
--              *client_recv(void *ptr)
--              append_text(char * text)
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- NOTES: This deals with connecting to a remote server via a socket as well
--        as maintaining a thread that reads incoming data from the socket.
--        Additionally, this deals with displaying received data in the GUI.
--
------------------------------------------------------------------------------*/

#include "client.h"
#include "tools.h"
#include "signal_handler.h"

/*------------------------------------------------------------------------------
-- FUNCTION:    start_client
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   start_client(const gchar * server)
--                   server: the hostname or IP address of the server
-- 
-- RETURNS: 0  if successful
--          -1 if there was an error
-- 
-- NOTES: This function creates a socket and connects to a specified server.
--		  
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
-- FUNCTION:    client_send
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   client_send(char * sendbuf)
--                   sendbuf: the data to be sent to the server
-- 
-- RETURNS: void
-- 
-- NOTES: This function simply sends data to a connected server. It also
--        appends the client's hostname for identification.
--		  
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
-- FUNCTION:    client_recv
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   *client_recv(void *ptr)
--                   *ptr: a pointer to data to be handled by this function
--                         NOTE: this is not used.
-- 
-- RETURNS: void
-- 
-- NOTES: This function is meant to be a thread that goes though an endless
--        loop, looking for data incoming on the connected socket.
--		  
------------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------------
-- FUNCTION:    append_text
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   append_text(char * text)
--                   text: the text to be appended to the GUI's display
-- 
-- RETURNS: void	
-- 
-- NOTES: This function outputs any text passed though it into the chat client's
--        main window.
--		  
------------------------------------------------------------------------------*/
void append_text(char * text) {
	GtkTextBuffer   *chat_out; 
	GtkTextIter		iter;

	chat_out = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_chat_out));

	gtk_text_buffer_insert_at_cursor(chat_out, text, -1);

	/* Scroll to end */
	gtk_text_buffer_get_end_iter(chat_out, &iter);
	gtk_text_view_scroll_to_iter(GTK_TEXT_VIEW(text_chat_out), &iter, 0.0, FALSE, 0, 0);
}
