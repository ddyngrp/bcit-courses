#include <windows.h>

#include "packets.h"
#include "functions.h"

/**
	parses a packet
	@param s packets to parse as a string
	@return TRUE or FALSE (FALSE if invalid, else return value of related function, else TRUE)
**/
int parse_packet() {
	int i;
	char *data;

	// validate packet
	if (!validate_packet(packet.p, packet.total)) {	// validate packet
		//invalid_packet(packet, len);	// run any logs, etc to do with errors	// TODO: implement
		return FALSE;
	}

	// get data section
	data = malloc(sizeof(char) * (PACKET_DATA_LENGTH(packet.total) + 1));	// create data string
	for (i=0; i<packet.total-8; i++) {
		data[i] = packet.p[i+6];
	}
	data[PACKET_DATA_LENGTH(packet.total)] = '\0';	// add null terminating character *IMPORTANT*

	// handle packet
	interpret_cmd(packet.p[PACKET_CMD1], packet.p[PACKET_CMD2], data, packet.total-8);
	return TRUE;
}

/**
	interprets a packet by cmd1 value and calls the appropriate function
	@param cmd1	secondary flow control paramater
	@param cmd2 primary flow control paramater (determines function to call)
	@param data data section of the packet
	@param len number of bytes in the data array
**/
int interpret_cmd(char cmd1, char cmd2, char *data, size_t len) {
	switch (cmd2) {	// determine cmd2
		case CMD2_ENTER_DOWNLOAD_MODE:
			return FALSE;	// this should NEVER happend!!!

		case CMD2_FIND_TOKEN:
			return received_find_token(data, len);

		case CMD2_PASS_THROUGH:
			return FALSE;	// this should NEVER happend!!!
	}
	return TRUE;	// default return value for un-used cmd2 values
}

/**
	validates a packet
	@param s packet to validate as a string
	@return TRUE or FALSE
**/
int validate_packet() {
	// structure and basic values (size, SOF, DEV_ID)
	ENSURE(packet.total >= PACKET_LENGTH_MIN)	// min packet length
	ENSURE(packet.total <= PACKET_LENGTH_MAX)	// max packet length
	ENSURE(packet.p[PACKET_SOF] == SOF)			// SOF byte
	ENSURE(packet.p[PACKET_LSB] + (256*packet.p[PACKET_MSB]) == packet.total)	// length check (LSB + MSB)
	ENSURE(packet.p[PACKET_DEV_ID] == DEV_ID)		// packet ID (static)

	return TRUE;
}

/**
	Performes Longitudal Redundency Check
	@param s string to check
	@param len length of string
	@return lrc value
**/
int lrc(const char* s, size_t len) {
	size_t i = 0;
	int lrc = 0;
	for (i=0; i < len; ++i) {
		lrc ^= s[i];	// XOR lrc with current character
	}
	return lrc;
}

/**
	Done searching for a token.
**/
int received_find_token(char *data, size_t len) {
	char * tempTag[15];
	char * output[255];
	int i;

	ENSURE(len > 0);
	switch(data[0]) {
		case ERROR_NONE:
			ENSURE(len > 2);
			switch(data[1]) {	// Entity ID
				case ID_14443A:
					ENSURE(len == 7);
					break;

				case ID_14443B:
					ENSURE(len == 7);
					break;

				case ID_15693:
					ENSURE(len == 12);
					strcpy_s(output, 255, "15693 - Tag ID: ");

					for (i = (int)len - 5; i >= 0; i--) {
						sprintf(&tempTag[i], "%02x", (unsigned char)data[i + 4]);
						strcat_s(output, 255, &tempTag[i]);
					}
					
					send_beepToggle();
					Sleep(500);
					send_beepToggle();

					insertString((char *)output);
					Search();
					break;

				case ID_TAGIT:
					ENSURE(len == 6);
					strcpy_s(output, 255, "Tag-It - Tag ID: ");

					for (i = (int)len - 3; i >= 0; i--) {
						sprintf(&tempTag[i], "%02x", (unsigned char)data[i + 2]);
						strcat_s(output, 255, &tempTag[i]);
					}
				
					send_beepToggle();
					Sleep(500);
					send_beepToggle();
	
					insertString((char *)output);
					Search();
					break;

				case ID_LFDST:
					strcpy_s(output, 255, "LF DST - Tag ID: ");

					for (i = (int)len - 5; i >= 0; i--) {
						sprintf(&tempTag[i], "%02x", (unsigned char)data[i + 4]);
						strcat_s(output, 255, &tempTag[i]);
					}

					send_beepToggle();
					Sleep(500);
					send_beepToggle();

					insertString((char *)output);
					Search();
					break;

				case ID_14434:
					break;

				case ID_APOLLO:
					break;
			}
			break;

		case ERROR_TOKEN_NOT_PRESENT:
			ENSURE(len == 1);
			Search();
			break;

		default:
			return FALSE;
	}
	return TRUE;
}
