/* 
* File:   serial.c
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#include <windows.h>
#include "serial.h"
#include "vt100.h"
#include "terminal.h"

// Changes the port being used to connect (COM1, COM2, etc)
void commSetNumber(int port) {
	// Create port name from number
	commReconnect();
}

// Disconnects, then connects if connected.
void commReconnect() {	// reconnects to serial port using new paramaters if already connected
	if (TTYInfo.fConnected) {
		commDisconnect();
		commConnect();
	}
}

// Sets port to virgin state (only called once).
void commSetVirgin() {
	//CONNECTED(TTYInfo) = FALSE;
	TTYInfo.fConnected = FALSE;
	commSetNumber(1);
}

// Connects to, sets up and configures (if virgin) port.
void commConnect() {
	DCB dcb;
	HMENU hMenu;

	// Make sure we're not connected
	if (!CONNECTED(TTYInfo)) {
		// Menu
		hMenu = GetMenu(ghWndMain);	// get the menu handle
		EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_GRAYED | MF_DISABLED); // disable the connect menu
		EnableMenuItem(hMenu, ID_FILE_DISCONNECT, MF_ENABLED); // enable the disconnect menu
		EnableMenuItem(hMenu, ID_EDIT_SETTINGS, MF_GRAYED | MF_DISABLED); // disable the TTY menu

		COMDEV(TTYInfo) = CreateFile(gszPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);

		FillMemory(&dcb, sizeof(dcb), 0);

		dcb.BaudRate = BAUDRATE(TTYInfo);	// set the baud rate
		dcb.ByteSize = BYTESIZE(TTYInfo);	// set the data bits
		dcb.fParity = PARITY(TTYInfo);		// set the parity
		dcb.StopBits = STOPBITS(TTYInfo);	// set the stop bits

		SetCommState(COMDEV(TTYInfo), &dcb);	// update the COM port configuration

		CONNECTED(TTYInfo) = TRUE;	// we are now connected (hopefully)
	}
	// Start reading thread
	TTYInfo.hThread = CreateThread(
		NULL,	// security attributes
		0,		// inital thread stack size, in bytes
		commReadThread,		// address of thread function
		ghWndTerm,	// argument for new thread
		0,		// creation flags
		&TTYInfo.hThread
	);	// address of returned thread ID
	TTYInfo.fConnected = TRUE;
}


// Disconnects port
void commDisconnect() {	// disconnects with serial port if connected
	HMENU hMenu;
	// Check if we're connected
	if (CONNECTED(TTYInfo)) {
		// Menu
		hMenu = GetMenu(ghWndMain);	// get the menu handle
		EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_ENABLED); // enable the connect menu
		EnableMenuItem(hMenu, ID_FILE_DISCONNECT, MF_GRAYED | MF_DISABLED); // disable the connect menu
		EnableMenuItem(hMenu, ID_EDIT_SETTINGS, MF_ENABLED); // enable the TTY menu

		// lower DTR
		EscapeCommFunction(COMDEV(TTYInfo), CLRDTR);
		
		// Purge reads/writes, and I/O buffer
		PurgeComm(COMDEV(TTYInfo), PURGE_FLAGS);

		CloseHandle(COMDEV(TTYInfo)); // release the handle

		TTYInfo.fThreadDone = TRUE; // we want the thread to end
		CONNECTED(TTYInfo) = FALSE; // we are  now disconnected
	}
}

// Thread that continuously checks for characters comming in on the serial port.
DWORD WINAPI commReadThread() {
	char *charBuff;		// holds character found on serial port.
	DWORD evtMask;
	COMSTAT comstat;				// stores serial status information
	DWORD numBytesRead;
	COMMTIMEOUTS timeOuts;
	int i, read;

	gOverlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	// create overlap event to prevent simultanious access to serial port

	// Timeouts in milliseconds
	memset(&timeOuts, 0, sizeof(timeOuts));
	timeOuts.ReadIntervalTimeout = 0;
	timeOuts.ReadTotalTimeoutMultiplier = 5;
	timeOuts.ReadTotalTimeoutConstant = 50;
	SetCommTimeouts(TTYInfo.hCommPort, &timeOuts);

	SetCommMask(TTYInfo.hCommPort, EV_RXCHAR);
	
	while (TTYInfo.fConnected) {	// only loops while serial port is connected.
		if (WaitCommEvent(TTYInfo.hCommPort, &evtMask, NULL)) {
			charBuff = '\0';					// stores character from serial port

			ClearCommError(TTYInfo.hCommPort, NULL, &comstat);	// get status information from serial port
			charBuff = malloc(comstat.cbInQue);

			if ((evtMask & EV_RXCHAR) && comstat.cbInQue) {	// check if queue is empty
				ReadFile(TTYInfo.hCommPort, charBuff, comstat.cbInQue, &numBytesRead, &gOverlapped);	// read a single character from the serial port
			}

			for (i = 0; i < (int)numBytesRead; i++) {
				if (charBuff[i] > 0) { // don't know why, I just had to
					interpretChar(charBuff[i]);
				}
			}
		}
	}
	return 0;
}



// Sends a string through the serial port (currently only used for simple debugging)
int commSendString(const char * s) {
	int i;	// string index	
	for(i=0; s[i]!='\0'; i++) {		// loop through characters
		if (!commSendChar(s[i]))	// detect write error
			return FALSE;			// writting failed :(
	}
	return TRUE;	// done
}

int commSendChar(char c) {
	DWORD numBytesWritten;			// records number of character successfully written (not used, but necessary for WriteFile)
	OVERLAPPED overlapped = {0};	// overlap for preventing simulatious access to serial port

	if (!TTYInfo.fConnected)	// make sure port is actually active
		return FALSE;			// not connected :(

	//WriteFile(wMem->hComm, (LPBYTE)&wParam, 1, &wMem->numofBWriten, &overlaped
	if (!WriteFile(COMDEV(TTYInfo), &c, 1, &numBytesWritten, &overlapped))	// write byte to port
		return FALSE;		// write failed :(

	CloseHandle(overlapped.hEvent);
	return TRUE;			// done
}