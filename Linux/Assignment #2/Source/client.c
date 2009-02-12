#include "client.h"
#include "message_handler.h"

int main(int argc, char *argv[]) {
	char * mesg_data;
	int retval, data_retrieved = 0;

	if (argc < 2 || argc > 2) {
		print_help(argv[0]);
		exit(0);
	}
	else {
		server_status();
		printf(" * Server running, sending request for %s\n", argv[1]);

		// Send file name to the server
		if ((retval = mesg_send(argv[1], MQ_FROM_CLIENT)) == -1) {
			fatal("mesg_send");
		}


		while (1) { // receive from server
			if ((mesg_data = mesg_recv(MQ_FROM_SERVER)) == NULL) {
					fatal("mesg_recv");
			}

			if (strlen(mesg_data) == 0) {
				if (data_retrieved == 0) {
					printf(" ! Server cannot find file %s\n", argv[1]);
				}
				else {
					printf(" * Transaction complete, file %s retrieved\n", argv[1]);
				}
				exit(0);
			}
			else {
				data_retrieved = 1;
				printf(" * Retrieving data from server\n");
				printf("=========== Data Output ===========\n");
				printf("%s\n", mesg_data);
				printf("========= End Data Output =========\n");
			}

		}
	}

	return 0;
}

void server_status() {
	int retval;
	char * mesg_data;

	printf(" * Checking for server\n");

	// Verify that the server is running
	if ((retval == mesg_send(NULL, MQ_FROM_CLIENT)) == -1) {
		fatal("mesg_send");
	}

	printf(" * Waiting for server response\n");

	// Retrieve server status reply
	if ((mesg_data = mesg_recv(MQ_FROM_SERVER)) == NULL) {
		fatal("mesg_recv");
	}
}

void print_help(char * command) {
	printf("%s: missing file operand\n", command);
	printf("%s: [filename]\n", command);
}

void fatal(char * text) {
	perror(text);
	exit(1);
}
