/* 
 * File:   serial.h
 * Author: doug
 *
 * Created on February 15, 2008, 8:37 AM
 */

#ifndef _SERIAL_H
#define	_SERIAL_H

#include <windows.h>	// add basic window control availability
#include "termInfo.h"

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
void commSetVirgin();
void commSetNumber(int);

// Connection Management
void commConnect();
void commDisconnect();
void commReconnect();

// Transmission Management
int commSendChar(char);
char commGetChar();

// Threading Management
DWORD WINAPI commReadThread();

#endif	/* _SERIAL_H */
