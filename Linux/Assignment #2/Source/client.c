#include "client.h"
#include "message_handler.h"
#include "mesg.h"

int main(int argc, char *argv[]) {
	char mesg_data[MAXMESSAGEDATA];
	int retval, data_retrieved = 0;

	if (argc < 2 || argc > 2) {
		print_help(argv[0]);
		exit(0);
	}
	else {
		server_status();
		fprintf(stderr, " * Server running, sending request for %s\n", argv[1]);

		// Send file name to the server
		if ((retval = mesg_send(argv[1], MQ_FROM_CLIENT)) == -1) {
			fatal("mesg_send");
		}


		while (1) { // receive from server
			clear_buffer(mesg_data);

			memcpy(mesg_data, mesg_recv(MQ_FROM_SERVER), MAXMESSAGEDATA);

			if (strlen(mesg_data) == 0) {
				if (!data_retrieved) {
					fprintf(stderr, " ! Server cannot find file %s\n", argv[1]);
				}
				else {
					fprintf(stderr, "========= End Data Output =========\n");
					fprintf(stderr, " * Transaction complete, file %s retrieved\n",
							argv[1]);
				}
				exit(0);
			}
			else {
				if (!data_retrieved) {
					fprintf(stderr, " * Retrieving data from server\n");
					fprintf(stderr, "=========== Data Output ===========\n");
					fprintf(stdout, "%s", mesg_data);
				}
				else {
					fprintf(stdout, "%s", mesg_data);
				}
				data_retrieved = 1;
			}
		}
	}

	return 0;
}

void server_status() {
	int retval;
	char * mesg_data;

	fprintf(stderr, " * Checking for server\n");

	// Verify that the server is running
	if ((retval == mesg_send(NULL, MQ_FROM_CLIENT)) == -1) {
		fatal("mesg_send");
	}

	fprintf(stderr, " * Waiting for server response\n");

	// Retrieve server status reply
	if ((mesg_data = mesg_recv(MQ_FROM_SERVER)) == NULL) {
		fatal("mesg_recv");
	}
}

void print_help(char * command) {
	fprintf(stderr, "%s: missing file operand\n", command);
	fprintf(stderr, "%s: [filename]\n", command);
}

void fatal(char * text) {
	perror(text);
	exit(1);
}
