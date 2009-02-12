#include "server.h"
#include "message_handler.h"
#include "mesg.h"

pid_t pid_master;

int main(int argc, char *argv[]) {

	pid_master = getpid();

	signal(SIGINT, catch_sig); /* we want to remove the queue when terminated */

	fprintf(stderr, " * Server starting, press CTRL+C to exit\n");

	while (1) {
		if (getpid() == pid_master) {
			wait_for_client(); /* Wait for client to request server status */
		}
		else {
			exit(0);
		}
	}

	return 0;
}

void serve_client(pid_t pid_client) {
	FILE * fp;
	char mesg_data[MAXMESSAGEDATA];
	char file_name[255];
	char buff[MAXMESSAGEDATA];
	char tmpPid[5];
	int retval;
	long byte_pos = 0;
	pid_t pid_server;

	while (1) {
		pid_server = getpid();

		sprintf(tmpPid, "%d", pid_server);

		/* Respond with server's PID */
		if ((retval = mesg_send(tmpPid, MQ_FROM_SERVER)) == -1) {
			fatal("mesg_send");
		}
		else {
			fprintf(stderr, " [%d] Sent server status\n", pid_server);
		}

		if ((retval = mesg_recv(pid_client, mesg_data)) == -1) {
			fatal("mesg_recv");
		}

		memcpy(file_name, mesg_data, 255);
		clear_buffer(mesg_data); /* clear the incomming message buffer */

		/* Open file for reading */
		if ((fp = fopen(file_name, "r")) == NULL) {
			fprintf(stderr, " [%d] File %s not found\n", pid_server, file_name);

			/* Send a null message to the client, indicating no file found */
			if ((retval == mesg_send(NULL, pid_server)) == -1) {
				fatal("mesg_send");
			}
		}
		else {
			/* Read file in blocks until EOF */
			fprintf(stderr, " [%d] Sending %s to client\n", pid_server, file_name);
			while (!feof(fp)) {
				lseek((int)fp, byte_pos, SEEK_SET);
				fread(buff, MAXMESSAGEDATA, 1, fp);

				byte_pos += MAXMESSAGEDATA;

				if ((retval == mesg_send(buff, pid_server)) == -1) {
					fatal("mesg_send");
				}

				clear_buffer(buff);
			}
			/* Signal end of file */
			if (byte_pos != 0) {
				if ((retval == mesg_send(NULL, pid_server)) == -1) {
					fatal("mesg_send");
				}
			}
			fclose(fp);
			fprintf(stderr, " [%d] Transmission of %s to client %d complete\n",
					pid_server, file_name, pid_client);
			byte_pos = 0;
		}
		break;
	}
}

void wait_for_client() {
	int retval;
	pid_t pid_child, pid_client;
	char mesg_data[MAXMESSAGEDATA];

	/* Wait for initial server status query */
	fprintf(stderr, " [%d] Waiting for client connection\n", getpid());
	if ((retval = mesg_recv(MQ_FROM_CLIENT, mesg_data)) == -1) {
		fatal("mesg_recv");
	}

	pid_client = atoi(mesg_data); /* Set the client's PID */
	fprintf(stderr, " [%d] Client's PID is %d\n", getpid(), pid_client);

	if ((pid_child = fork()) == -1) {
		fatal("fork");
	}

	while (waitpid(-1, NULL, WNOHANG) > 0) {
		; /* don't hang if no kids are dead yet */
	}

	if (getpid() != pid_master) {
		signal(SIGINT, NULL);
		serve_client(pid_client);
	}
}

void catch_sig(int signo) {
	if (signo == SIGINT) {
		signal(SIGINT, NULL);
		mesg_qrm();
		kill(getpid(), SIGTERM);
	}
}

void fatal(char * text) {
	perror(text);
	exit(1);
}
