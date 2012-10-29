#ifndef COMMOUT_H
#define COMMOUT_H

/*
****************************************************************************
* CommOut.cpp                                                              *
* Purpose: Sending completed packets from the buffer to the serial port.   *
* Additionally, CommOut handles the RVI process of receiving data and      *
* sending that to the GUI.                                                 *
* Author: Max Wardell                                                      *
* Version: 1.0                                                             *
****************************************************************************
*/

#include <windows.h>
#include "functions.h" //General functions such as windows.h
#include "Buffer.h"
#include "crc.h"
#include "events.h"
#include "exceptions.h"
#include "packet.h"
#include "serial.h"
#include "utils.h"

#define MAX_COUNT    4 //Maximum amount any kind of counter, such as a nackcounter or timeout counter.
#define TIMEOUT_TIME 100 //Length of a timeout

class CommOut {
public:
	//Contructor, initializes pointers the the GUI, buffer and serial port.
	//CommOut(Buffer *buffer, GUI *gui, Serial *serial):buffer_(buffer), gui_(gui), serial_(serial) {}
	CommOut(Buffer *buffer, Serial *serial);
	static DWORD WINAPI CommOut::thread(PVOID pvoid);
	void ConnectClient();
	void SendPacket();
	void RVIProcess();

private:
	Buffer *buffer_;
	//GUI    *gui_;
	Serial *serial_;
	CRITICAL_SECTION protGuard_;
	Packet packet_;
};

#endif
