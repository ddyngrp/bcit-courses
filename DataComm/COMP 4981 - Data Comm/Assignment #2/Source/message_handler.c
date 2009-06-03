/*------------------------------------------------------------------------------
-- SOURCE FILE:	message_handler.c - This module handles all message queues
-- 
-- PROGRAM:     client & server
-- 
-- FUNCTIONS:   mesg_send(char * mesg_data, int mesg_type, int priority)
--              mesg_recv(int mesg_type, char * mesg_data)
--              clear_buffer(char * buff[MAXMESSAGEDATA])
--              mesg_qrm()
-- 
-- DATE:        February 12, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- NOTES: This module handls all incoming and outgoing POSIX message queues.
--        Additionally it is also responsible for removing message queues when
--        the program terminates.
--
------------------------------------------------------------------------------*/
#include "message_handler.h"
#include "mesg.h"

int mesg_send(char * mesg_data, int mesg_type, int priority) {
	key_t key;
	int msqid, length, retval;
	Mesg message;
	
	message.mesg_type = mesg_type;
	message.mesg_len = sizeof(mesg_data);
	message.priority = priority;

	clear_buffer(message.mesg_data);

	length = sizeof(message) - sizeof(long);

	/* Copy the data into our struct */
	if (mesg_data != NULL) {
		strcpy(message.mesg_data, mesg_data);
	}

	if ((key = ftok("/dev/random", 'z')) == -1) {
		perror("ftok");
		return -1;
	}

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
		perror("msgget");
		return -1;
	}

	if ((retval = msgsnd(msqid, &message, length, 0)) == -1) {
		perror("msgsnd");
		return -1;
	}

	return 0;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    mesg_recv
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   server_status(int mesg_type, char * mesg_data)
--                            int mesg_type: the type message type, usually
--                                           the receiver's PID
--                            char * mesg_data: the data to be sent
-- 
-- RETURNS: -1 if there is an error, otherwise returns the message priority
-- 
-- NOTES: This function places a message onto the message queue with a type
--        of the receiving process.
--		  
------------------------------------------------------------------------------*/
int mesg_recv(int mesg_type, char * mesg_data) {
	key_t key;
	int msqid, length, retval;
	Mesg message;

	clear_buffer(mesg_data);

	length = sizeof(message) - sizeof(long);

	if ((key = ftok("/dev/random", 'z')) == -1) {
		perror("ftok");
		return -1;
	}

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
		perror("msgget");
		return -1;
	}

	if ((retval = msgrcv(msqid, &message, length, mesg_type, 0)) == -1) {
		perror("msgrcv");
		return -1;
	}

	memcpy(mesg_data, message.mesg_data, MAXMESSAGEDATA);

	return message.priority;
}

/*------------------------------------------------------------------------------
-- FUNCTION:    clear_buffer
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   clear_buffer(char buff[MAXMESSAGEDATA])
--                           buff: the buffer to be initialized with NULL chars
-- 
-- RETURNS: void
-- 
-- NOTES: This function simply fills a buffer with NULL characters
--		  
------------------------------------------------------------------------------*/
void clear_buffer(char buff[MAXMESSAGEDATA]) {
	int i;

	for (i = 0; i < MAXMESSAGEDATA; i++) {
		buff[i] = '\0';
	}
}

/*------------------------------------------------------------------------------
-- FUNCTION:    mesg_qrm
-- 
-- DATE:        January 21, 2008
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   mesg_qrm(void)
-- 
-- RETURNS: void
-- 
-- NOTES: This function removes the message queue after the program terminates
--		  
------------------------------------------------------------------------------*/
void mesg_qrm() {
	key_t key;
	int msqid, retval;

	if ((key = ftok("/dev/random", 'z')) == -1) {
		perror("ftok");
	}

	if ((msqid = msgget(key, 0644)) == -1) {
		perror("msgget");
	}

	if ((retval = msgctl(msqid, IPC_RMID, NULL)) == -1) {
		perror("msgctl");
	}
}
