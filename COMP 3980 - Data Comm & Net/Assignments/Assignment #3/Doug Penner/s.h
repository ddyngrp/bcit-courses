#ifndef _H_H
#define _H_H

#include <windows.h>

void invalid_packet(char *s, size_t len);
void transmitter_successfully_set_to(int id, int status);
void driver_successfully_set();
void baud_rate_successfully_set();
void token_priority_successfully_set();

#endif
