#include "network.h"

/***********************************************
 * Function: set_conn_type
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: set_conn_type(int type)
 *		int type: The type of connection to use
 * 
 * Returns: 0 on success or (-1) on error.
 * 
 * Description: Set the connection type.
 ***********************************************/
int set_conn_type(int type) {
	if(type == TCP || type == UDP) {
		conn_type = type;
		return 0;
	} else {
		fprintf(stderr, "invalid connection type in %s:set_conn_type\n", __FILE__);
		return -1;
	}
}

/***********************************************
 * Function: conn_setup
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: conn_setup(char *host, char *port)
 *		char *host: The IP-address or hostname to connect to
 *		char *port: The port number to connect to
 * 
 * Returns: 0 on success, (-1) on failure.
 * 
 * Description: Connect to the specified host and port.
 ***********************************************/
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


/***********************************************
 * Function: keepalive
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: keepalive()
 * 
 * Returns: Void.
 * 
 * Description: Send a KEEPALIVE packet to let the other side
 *		know we're still here.
 ***********************************************/
void keepalive() {
	unsigned char data = KEEPALIVE;
	transfer(&data, 1);
}

/***********************************************
 * Function: send_map
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: send_map(unsigned char *map, size_t len)
 *		unsigned char *map: The map's character representation
 *		size_t len: The length of the map string
 * 
 * Returns: 0 on success or (-1) if malloc fails.
 * 
 * Description: Sends the map to the client.
 ***********************************************/
int send_map(unsigned char *map, size_t len) {
	unsigned char *data = (unsigned char *)malloc(len + 1);
	
	if(data == NULL) {
		fprintf(stderr, "malloc failed in send_map\n");
		return -1;
	}
	
	data[iTYPE] = MAP;
	memcpy(data + 1, map, len);
	
	if(transfer(data, len + 1) < len + 1) { /* not the whole len was transfered */
		return -1;
	}
	
	return 0;
}

/* receive a map from the server */
int recv_map(unsigned char *map, size_t len) {
	/* this is where logic converts the uchar* into the format they want */
	return 0;
}

/***********************************************
 * Function: request_move
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: request_move(int x, int y)
 *		int x: The x-coordinate the client wants to move to
 *		int y: The y-coordinate the client wants to move to
 * 
 * Returns: 0 on success or (-1) if malloc fails.
 * 
 * Description: Send a request to the server, asking to move to xy
 ***********************************************/
int request_move(int x, int y) {
	int len = sizeof(unsigned char) * ((sizeof(int) * 2) + 2);
	unsigned char *data = (unsigned char *)malloc(len);
	
	if(data == NULL) {
		fprintf(stderr, "malloc failed in request_move\n");
		return -1;
	}
	
	data[iTYPE] = MOVE;
	add_coords_xy(x, y, data + 1, len - 1);
	transfer(data, len);
	
	return 0;
}

/***********************************************
 * Function: request_bomb
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: request_bomb(int type)
 *		int type: The type of bomb to drop
 * 
 * Returns: 0 on success.
 * 
 * Description: Send a request to the server, asking to drop
 *		a bomb at xy
 ***********************************************/
int request_bomb(int type) {
	int len = sizeof(int) + 2;
	unsigned char data[len];
	
	data[iTYPE] = BOMB;
	memcpy(data + 1, &type, sizeof(int));
	data[len - 1] = '\0';
	transfer(data, len);
	
	return 0;
}

/***********************************************
 * Function: explode_bomb
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: explode_bomb(int x, int y)
 *		int x: The x-coordinate of the bomb to blow up
 *		int y: The y-coordinate of the bomb to blow up
 * 
 * Returns: 0 on success.
 * 
 * Description: Send a message to all the clients, saying that the
 *		bomb at xy blew up.
 ***********************************************/
int explode_bomb(int x, int y) {
	int len = sizeof(unsigned char) * ((sizeof(int) * 2) + 2);
	unsigned char *data = (unsigned char *)malloc(len);
	
	data[iTYPE] = EXPLOSION;
	add_coords_xy(x, y, data + 1, len - 1);
	transfer(data, len);
	
	return 0;
}

/***********************************************
 * Function: transfer
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: transfer(unsigned char *data, size_t len)
 *		unsigned char *data: The string of data to transfer
 *		size_t len: The length of the data string
 * 
 * Returns: 0 on success or (-1) on error.
 * 
 * Description: Transfer the data, regardless of TCP/UDP
 ***********************************************/
int transfer(unsigned char *data, size_t len) {
	if(conn_type == TCP) {
		return send(sock, data, len, 0);
	} else if(conn_type == UDP) {
		return sendto(sock, data, len, 0, (struct sockaddr *)&server, sizeof(server));
	} else { /* this should never happen */
		return -1;
	}
}

/***********************************************
 * Function: add_coords_xy
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: add_coords_xy(int x, int y, unsigned char *data, size_t len)
 *		int x: The first coordinate to add
 *		int y: The second coordinate to add
 *		unsigned char *data: The data string to add the coords into
 *		size_t len: The length of the data string
 * 
 * Returns: 0 on success or (-1) on error.
 * 
 * Description: Writes x and y into the string and appends a null-char
 ***********************************************/
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

/***********************************************
 * Function: process_data
 * 
 * Designed by: David Young
 * Coded by: David Young
 * 
 * Date: March 2, 2009
 * 
 * Interface: process_data(unsigned char *data, size_t len)
 *		unsigned char *data: The string to get data from
 *		size_t len: The length of the data string
 * 
 * Returns: 0 on success or a negative value on failure.
 *		The failure values are listed in network.h
 * 
 * Description: Process the data that's received.
 ***********************************************/
/* process the data that's received */
int process_data(unsigned char *data, size_t len) {
	switch(data[iTYPE]) {
		case KEEPALIVE: /* do nothing */
			break;
			
		case MAP: /* deal with the map */
			if(mode == CLIENT) {
				/* update the map */
			} else if(mode == SERVER){ /* why is the client sending the server a map? */
				return ERR_SERV_RECV_MAP;
			} else {
				return ERR_UNKNOWN_INPUT;
			}
			
			break; /* end case MAP */
			
		case MOVE: /* client requesting a move */
			if(mode == CLIENT) { /* client shouldn't get a MOVE message */
				return ERR_CLNT_RECV_MOVE;
			} else if(mode == SERVER) {
				/* the client wants to move to this position */
			} else {
				return ERR_UNKNOWN_INPUT;
			}
			
			break; /* end case MOVE */
			
		case BOMB: /* client requesting a bomb drop */
			if(mode == CLIENT) {
				return ERR_CLNT_RECV_BOMB;
			} else if(mode == SERVER) {
				/* the client wants to drop a bomb of the specified type */
			} else {
				return ERR_UNKNOWN_INPUT;
			}
			
			break; /* end case BOMB */
			
		case EXPLOSION: /* draw the explosion */
			if(mode == CLIENT) {
				/* draw the explosion */
			} else if(mode == SERVER) { /* only servers send EXPLOSION messages */
				return ERR_SERV_RECV_EXPLOSION;
			} else {
				return ERR_UNKNOWN_INPUT;
			}
			
			break; /* end case EXPLOSION */
			
		default: /* this should never happen */
			return ERR_UNKNOWN_INPUT;
	}
	
	return 0;
}
