#include "network.h"

/* set the connection type. either TCP or UDP */
int set_conn_type(int type) {
	if(type == TCP || type == UDP) {
		conn_type = type;
		return 0;
	} else {
		fprintf(stderr, "invalid connection type in %s:set_conn_type\n", __FILE__);
		return -1;
	}
}

/* connect to the server, with IP or hostname "host", on port "port" */
int conn_setup(char *host, char *port) {
	struct addrinfo hints, *results;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = conn_type;
	
	if(getaddrinfo(host, port, &hints, &results) == -1) {
		fprintf(stderr, "getaddrinfo failed in %s:connect_to_server\n", __FILE__);
		return -1;
	}
	
	sock = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
	
	memcpy(&server, (struct sockaddr_in *)results->ai_addr, sizeof(server));
	
	if(conn_type == TCP) {
		connect(sock, (struct sockaddr *)&server, sizeof(server));
	}
	
	return 0;
}

/* send an empty packet to let the other side know we're still here */
int keepalive() {
	unsigned char data = KEEPALIVE;
	transfer(&data, 1);
	return 0;
}

/* send the map to the clients */
int send_map(unsigned char *map) {
	/* not sure of actual map format yet */
	return 0;
}

/* receive a map from the server */
int recv_map(unsigned char *map) {
	/* not sure of actual map format yet */
	return 0;
}

/* send a request to the server, asking if you can move to xy */
int request_move(int x, int y) {
	int len = sizeof(unsigned char) * ((sizeof(int) * 2) + 2);
	unsigned char *data = (unsigned char *)malloc(len);
	
	data[iTYPE] = MOVE;
	add_coords_xy(x, y, data + 1, len - 1);
	transfer(data, len);
	
	return 0;
}

/* send a request to the server, asking if you can drop a bomb at current xy */
int request_bomb(int type) {
	int len = (sizeof(int) * 2) + 2;
	unsigned char data[len];
	
	data[iTYPE] = BOMB;
	memcpy(data + 1, &type, sizeof(int));
	data[len - 1] = '\0';
	transfer(data, len);
	
	return 0;
}

/* send a message to all the clients, saying that the bomb at xy blew up */
int explode_bomb(int x, int y) {
	int len = sizeof(unsigned char) * ((sizeof(int) * 2) + 2);
	unsigned char *data = (unsigned char *)malloc(len);
	
	data[iTYPE] = EXPLOSION;
	add_coords_xy(x, y, data + 1, len - 1);
	transfer(data, len);
	
	return 0;
}

/* transfer the data, regardless of TCP/UDP */
int transfer(unsigned char *data, size_t len) {
	if(conn_type == TCP) {
		send(sock, data, len, 0);
	} else {
		sendto(sock, data, len, 0, (struct sockaddr *)&server, sizeof(server));
	}
	
	return 0;
}

/* writes xy into the char-string and appends a null-char at the end */
int add_coords_xy(int x, int y, unsigned char *data, size_t len) {
	if(len < (2 * sizeof(int)) + 1) {
		fprintf(stderr, "len is < required length in add_coords_xy\n");
		return -1;
	}
	
	memcpy(data, &x, sizeof(int));
	memcpy(data + sizeof(int), &y, sizeof(int));
	
	data[len - 1] = '\0';
	
	return 0;
}

/* process the data that's received */
int process_data(unsigned char *data, size_t len) {
	switch(data[iTYPE]) {
		case KEEPALIVE: /* do nothing */
			break;
			
		case MAP: /* deal with the map */
			if(mode == CLIENT) {
				/* update the map */
			} else if(mode == SERVER){
				/* why is the client sending the server a map? */
			} else {
				return -1;
			}
			
			break; /* end case MAP */
			
		case MOVE: /* move the player */
			if(mode == CLIENT) {
				/* move the player */
			} else if(mode == SERVER) {
				/* the client wants to move to this position */
			} else {
				return -1;
			}
			
			break; /* end case MOVE */
			
		case BOMB: /* drop a bomb */
			if(mode == CLIENT) {
				/* drop a bomb here */
			} else if(mode == SERVER) {
				/* the client wants to drop a bomb of the specified type */
			} else {
				return -1;
			}
			
			break; /* end case BOMB */
			
		case EXPLOSION: /* draw the explosion */
			if(mode == CLIENT) {
				/* draw the explosion */
			} else if(mode == SERVER) {
				/* why is the client sending us an explosion message? */
			} else {
				return -1;
			}
			
			break; /* end case EXPLOSION */
			
		default: /* this should never happen */
			return -1;
	}
	
	return 0;
}
