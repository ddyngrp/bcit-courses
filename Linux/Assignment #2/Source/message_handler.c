#include "message_handler.h"
#include "mesg.h"

int mesg_send(char * mesg_data, int mesg_type) {
	key_t key;
	int msqid, length, retval;
	Mesg message;
	
	message.mesg_type = mesg_type;
	message.mesg_len = sizeof(mesg_data);
	message.priority = 0;

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

	return 0;
}

void clear_buffer(char buff[MAXMESSAGEDATA]) {
	int i;

	for (i = 0; i < MAXMESSAGEDATA; i++) {
		buff[i] = '\0';
	}
}

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
