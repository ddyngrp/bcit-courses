#include "server.h"
#include "message_handler.h"
#include "mesg.h"

int main(int argc, char *argv[]) {
	FILE * fp;
	char * mesg_data, * file_name;
	char buff[MAXMESSAGEDATA];
	int retval;
	long byte_pos = 0;

	fprintf(stderr, " * Server starting, press CTRL+C to exit\n");

	while (1) {
		server_status(); // Wait for client to request server status
		while (1) {
			if ((mesg_data = mesg_recv(MQ_FROM_CLIENT)) == NULL) {
				fatal("mesg_recv");
			}

			file_name = mesg_data; // save the file name

			// Open file for reading
			if ((fp = fopen(file_name, "r")) == NULL) {
				fprintf(stderr, " ! File %s not found\n", file_name);

				// Send a null message to the client, indicating no file found
				if ((retval == mesg_send(NULL, MQ_FROM_SERVER)) == -1) {
					fatal("mesg_send");
				}
			}
			else {
				// Read file in blocks until EOF
				fprintf(stderr, " * Sending %s to client\n", file_name);
				while (!feof(fp)) {
					clear_buffer(buff);

					lseek((int)fp, byte_pos, SEEK_SET);
					fread(buff, MAXMESSAGEDATA, 1, fp);

					byte_pos += MAXMESSAGEDATA;

					if ((retval == mesg_send(buff, MQ_FROM_SERVER)) == -1) {
						fatal("mesg_send");
					}

					// Signal end of file
				}
				if (byte_pos != 0) {
					if ((retval == mesg_send(NULL, MQ_FROM_SERVER)) == -1) {
						fatal("mesg_send");
					}
				}
				fprintf(stderr, " * Transmission complete\n");
				byte_pos = 0;
			}

			break; // go back to initial state
		}
	}

	return 0;
}

void server_status() {
	int retval;
	char * mesg_data;

	// Wait for initial server status query
	fprintf(stderr, " * Waiting for client connection\n");
	if ((mesg_data = mesg_recv(MQ_FROM_CLIENT)) == NULL) {
		fatal("mesg_recv");
	}

	// Respond to server running request
	if ((retval = mesg_send(NULL, MQ_FROM_SERVER)) == -1) {
		fatal("mesg_send");
	}
	else {
		fprintf(stderr, " * Sent server status\n");
	}
}

void fatal(char * text) {
	perror(text);
	exit(1);
}
