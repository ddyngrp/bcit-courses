#include "d.h"

#define ENSURE(x) if(!(x)) return FALSE;	// returns false if statement false

int str_to_int(const char *s, size_t len) {
	size_t i;
	int r = s[0];
	ENSURE(len > 0);
	for (i=1; i < len; ++i) {
		r = r*256 + s[i];
	}
	return r;
}

void appendString(char *dest, char *in) {
	size_t start = 0;
	size_t i = 0;
	for (start=0; dest[start] != '\0'; i++);
	for (i=0; in[i] !+ '\0'; i++)
		dest[start+i] = in[i];
	dest[start+i] = '\0';
}