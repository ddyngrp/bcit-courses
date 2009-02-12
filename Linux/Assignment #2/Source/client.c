/*------------------------------------------------------------------------------
-- SOURCE FILE:	client.c - A program that connects to a server and retrieves a
--                         file if it exists.
-- 
-- PROGRAM:     client
-- 
-- FUNCTIONS:   server_status()
--              print_help()
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
-- NOTES: This program will request and retrieve a text file from a server via
--        POSIX message queues. You can set a priority for the client from 0 to
--        32768. The lower the priority, the faster the transfer.
--
------------------------------------------------------------------------------*/
#include "client.h"
#include "message_handler.h"
#include "mesg.h"

pid_t pid_client, pid_server;

int main(int argc, char *argv[]) {
	char mesg_data[MAXMESSAGEDATA];
	int retval, data_retrieved = 0;

	pid_client = getpid();

	if (argc < 3 || argc > 3) {
		print_help(argv[0]);
		exit(0);
	}
	else {
		server_status();
		fprintf(stderr, " * Server running, sending request for %s\n", argv[1]);

		/* Send file name to the server */
		if ((retval = mesg_send(argv[1], pid_client, atoi(argv[2]))) == -1) {
			fatal("mesg_send");
		}


		while (1) { /* receive from server */
			clear_buffer(mesg_data);

			mesg_recv(pid_server, mesg_data);

			if (strlen(mesg_data) == 0) {
				if (!data_retrieved) {
					fprintf(stderr, " ! Server cannot find file %s\n", argv[1]);
				}
				else {
					fprintf(stderr, "========= End Data Output =========\n");
					fprintf(stderr, " * Transaction complete, file %s retrieved\n",
							argv[1]);
				}
				clear_buffer(mesg_data);

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
void server_status() {
	int retval;
	char mesg_data[MAXMESSAGEDATA];
	char tmpPid[5];

	sprintf(tmpPid, "%d", pid_client); /* Convert pid to string */

	fprintf(stderr, " * Checking for server\n");

	/* Verify that the server is running */
	if ((retval == mesg_send(tmpPid, MQ_FROM_CLIENT, 0)) == -1) {
		fatal("mesg_send");
	}

	fprintf(stderr, " * Waiting for server response\n");

	/* Retrieve server status reply */
	if ((retval = mesg_recv(MQ_FROM_SERVER, mesg_data)) == -1) {
		fatal("mesg_recv");
	}

	pid_server = atoi(mesg_data); /* Set the server's PID */

	fprintf(stderr, " * Server's PID is %d\n", pid_server);

}

/*------------------------------------------------------------------------------
-- FUNCTION:    print_help
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   print_help(void)
-- 
-- RETURNS: void
-- 
-- NOTES: This function simply prints out help on how to use the program.
--		  
------------------------------------------------------------------------------*/
void print_help(char * command) {
	fprintf(stderr, "%s: missing operand\n", command);
	fprintf(stderr, "%s: [filename] [priority {0...5}]\n", command);
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
-- NOTES: This function prints out an error message and terminates the program
--		  
------------------------------------------------------------------------------*/
void fatal(char * text) {
	perror(text);
	exit(1);
}
