/*------------------------------------------------------------------------------
-- SOURCE FILE:	server.c - This program acts as a file server to multiple
--                         clients.
-- 
-- PROGRAM:     server
-- 
-- FUNCTIONS:   serve_client(pid_t pid_client)
--              wait_for_client(void)
--              *zombie_harvester(void)
--              catch_sig(int signo)
--              fatal(char * text)
-- 
-- DATE:        February 12, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- NOTES: This program will handle requests from multiple clients to send files
--        via POSIX message queues. It will also give each client a priority
--        depending on the priority passed from the client.
--
------------------------------------------------------------------------------*/
#include "server.h"
#include "message_handler.h"
#include "mesg.h"

pid_t pid_master;

int main(int argc, char *argv[]) {
	pthread_t zombie_thread;

	pid_master = getpid();

	signal(SIGINT, catch_sig); /* we want to remove the queue when terminated */

	fprintf(stderr, " * Server starting, press CTRL+C to exit\n");
	pthread_create(&zombie_thread, NULL, &zombie_harvester, NULL);

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

/*------------------------------------------------------------------------------
-- FUNCTION:    serve_client
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   serve_client(pid_t pid_client)
--                           pid_t pid_client: the PID of the client process
--                                             to which the message is sent
-- 
-- RETURNS: void
-- 
-- NOTES: This function handles reading files from the drive, client priorities
--        as well as finalizing all client connection requests by sending the
--        new forked process ID to the client via a POSIX message.
--		  
------------------------------------------------------------------------------*/
void serve_client(pid_t pid_client) {
	FILE * fp;
	char mesg_data[MAXMESSAGEDATA];
	char file_name[255];
	char buff[MAXMESSAGEDATA];
	char tmpPid[6];
	int retval, priority;
	long byte_pos = 0;
	pid_t pid_server;

	pid_server = getpid();

	while (1) {
		sprintf(tmpPid, "%d", pid_server);

		/* Respond with server's PID */
		if ((retval = mesg_send(tmpPid, MQ_FROM_SERVER, 0)) == -1) {
			fatal("mesg_send");
		}
		else {
			fprintf(stderr, " [%d] Sent server status\n", pid_server);
		}

		if ((priority = mesg_recv(pid_client, mesg_data)) == -1) {
			fatal("mesg_recv");
		}

		memcpy(file_name, mesg_data, 255);
		clear_buffer(mesg_data); /* clear the incomming message buffer */

		/* Open file for reading */
		if ((fp = fopen(file_name, "r")) == NULL) {
			fprintf(stderr, " [%d] File %s not found\n", pid_server, file_name);

			/* Send a null message to the client, indicating no file found */
			if ((retval == mesg_send(NULL, pid_server, 0)) == -1) {
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
				
				usleep(priority * 2000);
				if ((retval == mesg_send(buff, pid_server, 0)) == -1) {
					fatal("mesg_send");
				}

				clear_buffer(buff);
			}
			/* Signal end of file */
			if (byte_pos != 0) {
				if ((retval == mesg_send(NULL, pid_server, 0)) == -1) {
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

/*------------------------------------------------------------------------------
-- FUNCTION:    wait_for_client
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   wait_for_client(void)
-- 
-- RETURNS: void
-- 
-- NOTES: This function waits for a NULL message to arrive from a client,
--        containing the client's PID as the messsage type. This allows the
--        server to set up two-way communication with the cliant as it responds
--        by forking a new sever process.
--		  
------------------------------------------------------------------------------*/
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


	if (getpid() != pid_master) {
		signal(SIGINT, NULL);
		serve_client(pid_client);
	}
}

/*------------------------------------------------------------------------------
-- FUNCTION:    zombie_harvester
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   *zombie_harvester(void)
-- 
-- RETURNS: void
-- 
-- NOTES: This function simply cycles through an infinite loop looking for
--        forked server processes that have terminated in order ot clean
--        them up.
--		  
------------------------------------------------------------------------------*/
void *zombie_harvester() {
	while(1) {
		while (waitpid(-1, NULL, WNOHANG) > 0) {
			; /* don't hang if no kids are dead yet */
		}
	}
}

/*------------------------------------------------------------------------------
-- FUNCTION:    server_status
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   server_status(void)
-- 
-- RETURNS: void
-- 
-- NOTES: This function sends a null message to the server in order to
--        verify that the server is running. The server will respond with
--        a null message if it is running. 
--		  
------------------------------------------------------------------------------*/
void catch_sig(int signo) {
	if (signo == SIGINT) {
		signal(SIGINT, NULL);
		mesg_qrm();
		kill(getpid(), SIGTERM);
	}
}

/*------------------------------------------------------------------------------
-- FUNCTION:    fatal
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   fatal(char * text)
--                    text: the text to display for the error
-- 
-- RETURNS: void
-- 
-- NOTES: This function sends a null message to the server in order to
--		  
------------------------------------------------------------------------------*/
void fatal(char * text) {
	perror(text);
	exit(1);
}
