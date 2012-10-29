#include <windows.h>

#include "d.h"
#include "k.h"
#include "s.h"

/**
	A list of tag types that can be read.
**/
int received_get_version(char *data, size_t len) {
	size_t i = 0;
	ENSURE(len > 0 && len % 3 == 1);	// ensure proper data length
	if (data[0] == ERROR_NONE) {				// verify that there were no errors
		for(i=1; i < len; i += 3) {		// loop through versions found
			found_version(data[i], data[i+2], data[i+1]);	// report version
		}
	}
	return TRUE;
}

/**
	Done searching for a token.
**/
int received_find_token(char *data, size_t len) {
	ENSURE(len > 0);
	switch(data[0]) {
		case ERROR_NONE:
			ENSURE(len > 2);
			switch(data[1]) {	// Entity ID
				case ID_14443A:
					ENSURE(len == 7);
					found_tag_14443b(data[2], str_to_int(&data[3], 4));
				break;
				case ID_14443B:
					ENSURE(len == 7);
					found_tag_14443b(data[2], str_to_int(&data[3], 4));
				break;
				case ID_15693:
					ENSURE(len == 12);
					found_tag_15693(data[2], data[3], str_to_int(&data[4], 8));
				break;
				case ID_TAGIT:
					ENSURE(len == 10);
					found_tag_tagit(str_to_int(&data[2], 4), str_to_int(&data[6], 4));
				break;
				case ID_LFDST:
					ENSURE(len == 6);
					found_tag_lfdst(data[2], str_to_int(&data[3], 3));
				break;
				case ID_14434:
					found_tag_14434(&data[2], len-2);	// TODO: find actual paramaters
				break;
				case ID_APOLLO:
					found_tag_apollo(&data[2], len-2);	// TODO: find actual paramaters
				break;

			}
		break;
		case ERROR_TOKEN_NOT_PRESENT:
			ENSURE(len == 1);
			found_tag_none();
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

int received_token_priority(char *data, size_t len) {
	ENSURE(len > 0);
	switch (data[0]) {
		case ERROR_NONE:
			ENSURE(len == 1)
			token_priority_successfully_set();
		break;
		// TODO: find other possible values
		default:
			return FALSE;
		break;
	}
	return TRUE;
}

int received_set_driver(char *data, size_t len) {
	ENSURE(len > 0);
	switch (data[0]) {
		case ERROR_NONE:
			ENSURE(len == 1);
			driver_successfully_set();
		break;
		// TODO: find other possible values
		default:
			return FALSE;
		break;
	}
	return TRUE;
}
int received_set_baud_rate(char *data, size_t len) {
	ENSURE(len > 0);
	switch (data[0]) {
		case ERROR_NONE:
			ENSURE(len == 1)
			baud_rate_successfully_set();
		break;
		// TODO: find other possible values
		default:
			return FALSE;
		break;
	}
	return TRUE;
}
int received_set_transmitter(int status, int id, char *data, size_t len) {
	ENSURE(len > 1);
	switch (data[0]) {
		case ERROR_NONE:
			ENSURE(len == 1);
			transmitter_successfully_set_to(id, status);	// pass id and on/off/toggle
		break;
		// TODO: find other possible values
		default:
			return FALSE;
		break;
	}
	return TRUE;
}
