#include "client.h"
#include "message_handler.h"

int main(int argc, char *argv[]) {
	char * mesg_data;
	int retval;

	if (argc < 3 || argc > 3) {
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

		printf(" * Retrieving data from server\n");

		while (1) { // receive from server
			if ((mesg_data = mesg_recv(MQ_FROM_SERVER)) == NULL) {
					fatal("mesg_recv");
			}

			if (strlen(mesg_data) == 0) {
				exit(0);
			}
			else {
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
	printf("%s: missing operand\n", command);
	printf("%s: [filename] [destination]\n", command);
}

void fatal(char * text) {
	perror(text);
	exit(1);
}
