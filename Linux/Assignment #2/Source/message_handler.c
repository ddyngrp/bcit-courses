#include "message_handler.h"
#include "mesg.h"

int mesg_send(char * mesg_data, int mesg_type) {
	key_t key;
	int msqid, length, retval;
	Mesg message = {mesg_type, sizeof(mesg_data), {}};

	length = sizeof(message) - sizeof(long);

	// Copy the data into our struct
	if (mesg_data != NULL) {
		strcpy(message.mesg_data, mesg_data);
	}
	else {
		message.mesg_data[0] = '\0';
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

char * mesg_recv(int mesg_type) {
	key_t key;
	int msqid, length, retval;
	char * mesg_data;
	Mesg message;

	length = sizeof(message) - sizeof(long);

	if ((key = ftok("/dev/random", 'z')) == -1) {
		perror("ftok");
		return NULL;
	}

	if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
		perror("msgget");
		return NULL;
	}

	if ((retval = msgrcv(msqid, &message, length, mesg_type, 0)) == -1) {
		perror("msgrcv");
		return NULL;
	}

	mesg_data = message.mesg_data;

	return mesg_data;
}
