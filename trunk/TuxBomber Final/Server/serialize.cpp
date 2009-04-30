#include "serialize.h"
#include <sstream>

#include <arpa/inet.h> /* TODO: Remove this when finished debugging */

#define BUF_LEN 64

/******************************************************************************
 *  Function:    serialize_player
 * 
 *  Date:        March 30, 2009
 *
 *  Revisions:   April 6, 2009 - David Young
 *					Changed to fix some bugs we were having with memcpy.
 * 					Apparently memcpy can't be trusted for objects.
 *					Changed parameters and return type.
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   serialize_player(DPlaya *player)
 *		            DPlaya *player: Pointer to the DPlaya object to be serialized
 * 
 *  Returns:     const char * containing the serialized form of the player.
 * 
 *  Description: Serialize player's data members to be passed across the network.
 *
 *****************************************************************************/
const char *serialize_player(DPlaya *player) {
	std::ostringstream oss(std::ios::binary);
	oss.write((char *)player, sizeof(DPlaya));
	return oss.str().c_str();
}

/******************************************************************************
 *  Function:    unserialize_player
 * 
 *  Date:        March 30, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   unserialize_player(char *buf, DPlaya *player)
 *					char *buf: buffer to get the serialized form of the player from
 *		            DPlaya *player: Pointer to the DPlaya object to fill
 * 
 *  Returns:     0 on success or (-1) on failure.
 * 
 *  Description: Unserialize the info in buf and put it into player.
 *
 *****************************************************************************/
int unserialize_player(char *buf, DPlaya *player) {
	memcpy(player, buf, sizeof(DPlaya));
	return 0;
}

/******************************************************************************
 *  Function:    serialize_map
 * 
 *  Date:        April 1, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   serialize_map(char map[MAP_ROWS][MAP_COLS], char *serialized_form)
 *					char map[MAP_ROWS][MAP_COLS]: the MAP_ROWS by MAP_COLS array
 *						representing the map
 *		            char *serialized_form: buffer for storing the serialized form
 *						of the map
 * 
 *  Returns:     0 on success or (-1) on failure.
 * 
 *  Description: Serialize the info in map and put it into serialized_form.
 *
 *****************************************************************************/
int serialize_map(char map[MAP_ROWS][MAP_COLS], char *serialized_form) {
	for(int a = 0; a < MAP_ROWS; a++) {
		for(int b = 0; b < MAP_COLS; b++) {
			serialized_form[(a * MAP_ROWS) + b] = map[a][b];
		}
	}
	
	return 0;
}

/******************************************************************************
 *  Function:    unserialize_map
 * 
 *  Date:        April 1, 2009
 *
 *  Revisions:   
 * 
 *  Designer:    David Young
 *  Programmer:  David Young
 * 
 *  Interface:   unserialize_map(char *serialized_form, char map[MAP_ROWS][MAP_COLS])
 *		            char *serialized_form: buffer for storing the serialized form
 *						of the map
 *					char map[MAP_ROWS][MAP_COLS]: the MAP_ROWS by MAP_COLS array
 *						representing the map
 * 
 *  Returns:     0 on success or (-1) on failure.
 * 
 *  Description: Unserialize the info in serialized_form and put it into map.
 *
 *****************************************************************************/
int unserialize_map(char *serialized_form, char map[MAP_ROWS][MAP_COLS]) {
	for(int a = 0; a < MAP_ROWS; a++) {
		for(int b = 0; b < MAP_COLS; b++) {
			map[a][b] = serialized_form[(a * MAP_ROWS) + b];
		}
	}
	
	return 0;
}

/* implement this.. */
void send_tcp_player(DPlaya p1, int sockfd) {
	char buf[BUF_LEN];
	serialize_player(&p1);

	if ((send(sockfd, buf, sizeof(DPlaya), 0)) == -1) {
		perror("send() call failed.");
	}
}

/* implement this.. */
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

/* works .. */
int send_udp_player(DPlaya *p1, int socketfd, struct sockaddr_in *udpserver)
{
	int ret;

	if ((ret = sendto(socketfd, serialize_player(p1), 1024, 0, (struct sockaddr *)udpserver, sizeof(*udpserver))) == -1){
	       	perror("sendto failure");
	       	exit(1);
	}
	
	return ret;
}

/* doesn't work.. */
void recv_udp_player(DPlaya *p1, int socketfd, struct sockaddr_in udpserver) {
	char buf[BUF_LEN];
	int ret;

	if ((ret = recvfrom(socketfd, buf,sizeof(DPlaya),0,NULL,(socklen_t *)sizeof(udpserver))) <= 0){
		if(ret == 0) {
			fprintf(stderr, "Server closed: %d\n", socketfd);
		} else {
			perror("recvfrom error");
		}

		exit(EXIT_FAILURE);
	} else {
		unserialize_player(buf, p1);
		printf("%d %d %d recv_udp_player\n", p1->getX(), p1->getY(), p1->getNumBombs());
	}
}

