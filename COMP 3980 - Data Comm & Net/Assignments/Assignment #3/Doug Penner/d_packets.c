#include <windows.h>

#include "s.h"
#include "d.h"

/**
	parses a packet
	@param s packets to parse as a string
	@return TRUE or FALSE (FALSE if invalid, else return value of related function, else TRUE)
**/
int parse_packet(char *packet, size_t len) {
	char *data;

	// validate packet
	if (!validate_packet(packet, len)) {	// validate packet
		invalid_packet(packet, len);	// run any logs, etc to do with errors
		return FALSE;
	}

	// get data section
	data = malloc(PACKET_DATA_LENGTH(len) + 1);	// create data string
	strncpy_s(data, len, &packet[PACKET_DATA1], PACKET_DATA_LENGTH(len));	// copy data section to string
	data[PACKET_DATA_LENGTH(len)] = '\0';	// add null terminating character *IMPORTANT*

	// handle packet
	interpret_cmd(packet[PACKET_CMD1], packet[PACKET_CMD2], data, len);
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
		case CMD2_GET_VERSION:
			return received_get_version(data, len);
		case CMD2_FIND_TOKEN:
			return received_find_token(data, len);
		case CMD2_TOKEN_PRIORITY:
			return received_token_priority(data, len);
		case CMD2_SET_DRIVER:
			return received_set_driver(data, len);
		case CMD2_PASS_THROUGH:
			return FALSE;	// this should NEVER happend!!!
		case CMD2_SET_BAUD_RATE:
			return received_set_baud_rate(data, len);
		case CMD2_TRANSMITTER_ON:
			return received_set_transmitter(TRUE, cmd1, data, len);
		case CMD2_TRANSMITTER_OFF:
			return received_set_transmitter(FALSE, cmd1, data, len);
		default:
			return TRUE;	// default return value for un-used cmd2 values
	}
}

/**
	validates a packet
	@param s packet to validate as a string
	@return TRUE or FALSE
**/
int validate_packet(char* packet, size_t len) {
	size_t packet_length = 0;

	// structure and basic values (size, SOF, DEV_ID)
	ENSURE(len >= PACKET_LENGTH_MIN)	// min packet length
	ENSURE(len <= PACKET_LENGTH_MAX)	// max packet length
	ENSURE(packet[PACKET_SOF] == PACKET_SOF)			// SOF byte
	ENSURE(packet[PACKET_LSB] + packet[PACKET_MSB] == len)			// length check (LSB + MSB)
	ENSURE(packet[PACKET_DEV_ID] == PACKET_DEV_ID)		// packet ID (static)

	// calucated values (BCC, CMD)
	ENSURE(packet[PACKET_LRC1(len)] + packet[PACKET_LRC2(len)] == 0xFF)	// BCC cross-check (LRC1 vs LRC2)
	ENSURE(lrc(packet, PACKET_LRC1(len)) == packet[PACKET_LRC1(len)])	// BCC validation (up to LRC1)
	ENSURE(packet[PACKET_CMD1] >= PACKET_CMD1_MIN && packet[PACKET_CMD1] <= PACKET_CMD1_MAX);	// CMD1
	ENSURE(packet[PACKET_CMD2] >= PACKET_CMD2_MIN && packet[PACKET_CMD2] <= PACKET_CMD2_MAX);	// CMD2

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
