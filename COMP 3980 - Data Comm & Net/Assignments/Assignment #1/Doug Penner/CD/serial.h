/* 
 * File:   serial.h
 * Author: doug
 *
 * Created on February 15, 2008, 8:37 AM
 */

#ifndef _SERIAL_H
#define	_SERIAL_H

#include <windows.h>	// add basic window control availability
#include "main.h"

#define READ_BUF_SIZE 8

#define SERIAL_PARITY_NONE 0
#define SERIAL_PARITY_ODD 1
#define SERIAL_PARITY_EVEN 2
#define SERIAL_PARITY_MARK 3
#define SERIAL_PARITY_SPACE 4

#define SERIAL_STOPBITS_1 0
#define SERIAL_STOPBITS_15 1
#define SERIAL_STOPBITS_2 2

#define SERIAL_BUFFSIZE 8

// Settings Management
void commSetVirgin(HWND, serialConfig *);
void commSetNumber(HWND, serialConfig *, int);

// Connection Management
void commConnect(HWND, serialConfig *);
void commDisconnect(HWND, serialConfig *);
void commReconnect(HWND, serialConfig *);

// Transmission Management
int commSendChar(serialConfig *, char);
char commGetChar(serialConfig *);

// Threading Management
DWORD WINAPI commReadThread(LPVOID);

#endif	/* _SERIAL_H */
