#include "server.h"
#include "message_handler.h"
#include "file_handler.h"
#include "mesg.h"

int main(int argc, char *argv[]) {
	char * mesg_data;
	char * file_data;
	char * data_chunk;
	int i, data_size;

	while (1) {
		server_status(); // Wait for client to request server status
		while (1) {
			if ((mesg_data = mesg_recv(MQ_FROM_CLIENT)) == NULL) {
				fatal("mesg_recv");
			}

			file_data = read_file(mesg_data);
			data_size = sizeof(file_data);

			// MAXMESSAGEDATA
			i = 0;
			data_chunk = (char *)malloc(MAXMESSAGEDATA);
			while (i != -1) {
				data_chunk[i] = file_data[i];
				i++;
				if (i == MAXMESSAGEDATA - 1) {
					printf("sending...\n");
					mesg_send(data_chunk, MQ_FROM_SERVER);
			
					i = -1;
				}
			}

			printf("data sent...\n");
			mesg_send(NULL, MQ_FROM_SERVER);
			
			free(data_chunk);
			free(file_data);

			break; // go back to initial state
		}
	}

	return 0;
}

void server_status() {
	int retval;
	char * mesg_data;

	// Wait for initial server status query
	printf(" * Waiting for client connection\n");
	if ((mesg_data = mesg_recv(MQ_FROM_CLIENT)) == NULL) {
		fatal("mesg_recv");
	}

	// Respond to server running request
	if ((retval = mesg_send(NULL, MQ_FROM_SERVER)) == -1) {
		fatal("mesg_send");
	}
	else {
		printf(" * Sent server status\n");
	}
}

void fatal(char * text) {
	perror(text);
	exit(1);
}
