#include <windows.h>

#define ENSURE(x) if(!(x)) return FALSE;	// returns FALSE if the statement is FALSE
int str_to_int(const char *s, size_t len);
