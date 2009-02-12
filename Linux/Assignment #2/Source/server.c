#include "server.h"
#include "message_handler.h"
#include "mesg.h"

pid_t pid_client, pid_server, pid_master;

int main(int argc, char *argv[]) {
	FILE * fp;
	char mesg_data[MAXMESSAGEDATA];
	char file_name[255];
	char buff[MAXMESSAGEDATA];
	int retval;
	long byte_pos = 0;

	pid_master = getpid();

	signal(SIGINT, catch_sig); // we want to remove the queue when terminated

	fprintf(stderr, " * Server starting, press CTRL+C to exit\n");

	while (1) {

		server_status(); // Wait for client to request server status

		while (1) {
			if ((retval = mesg_recv(pid_client, mesg_data)) == -1) {
				fatal("mesg_recv");
			}

			memcpy(file_name, mesg_data, 255);
			clear_buffer(mesg_data); // clear the incomming message buffer

			// Open file for reading
			if ((fp = fopen(file_name, "r")) == NULL) {
				fprintf(stderr, " ! File %s not found\n", file_name);

				// Send a null message to the client, indicating no file found
				if ((retval == mesg_send(NULL, pid_server)) == -1) {
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

					if ((retval == mesg_send(buff, pid_server)) == -1) {
						fatal("mesg_send");
					}

				}
				// Signal end of file
				if (byte_pos != 0) {
					if ((retval == mesg_send(NULL, pid_server)) == -1) {
						fatal("mesg_send");
					}
				}
				fclose(fp);
				fprintf(stderr, " * Transmission of %s complete\n", file_name);
				byte_pos = 0;
			}
			// Terminate the process if it is a child
			if (getpid() != pid_master) {
				fprintf(stderr, "Killing myself\n");
				kill(getpid(), SIGKILL);
			}

			break; // go back to initial state
		}
	}

	return 0;
}

void server_status() {
	int retval;
	char mesg_data[MAXMESSAGEDATA];
	char tmpPid[5];

	// Wait for initial server status query
	fprintf(stderr, " * Waiting for client connection\n");
	if ((retval = mesg_recv(MQ_FROM_CLIENT, mesg_data)) == -1) {
		fatal("mesg_recv");
	}

	pid_client = atoi(mesg_data); // Set the client's PID
	fprintf(stderr, " * Client's PID is %d\n", pid_client);
	pid_server = getpid();

	sprintf(tmpPid, "%d", pid_server);

	// Respond with server's PID
	if ((retval = mesg_send(tmpPid, MQ_FROM_SERVER)) == -1) {
		fatal("mesg_send");
	}
	else {
		fprintf(stderr, " * Sent server status\n");
	}
}

void catch_sig(int signo) {
	// Terminate process
	if (signo == SIGINT) { // SIGTERM
		signal(SIGINT, NULL);
		mesg_qrm();
		kill(getpid(), SIGTERM);
	}
}

void fatal(char * text) {
	perror(text);
	exit(1);
}
