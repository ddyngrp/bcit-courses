/* 
* File:   serial.c
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#include <windows.h>
#include "main.h"
#include "printing.h"
#include "serial.h"

// Changes the port being used to connect (COM1, COM2, etc)
void commSetNumber(HWND hwnd, serialConfig *conf, int port) {
	// Create port name from number
	wsprintf(conf->commName, TEXT("COM%d"),port);
	commReconnect(hwnd, conf);
}

// Disconnects, then connects if connected.
void commReconnect(HWND hwnd, serialConfig *conf) {	// reconnects to serial port using new paramaters if already connected
	if (conf->connected) {
		commDisconnect(hwnd, conf);
		commConnect(hwnd, conf);
	}
}

// Sets port to virgin state (only called once).
void commSetVirgin(HWND hwnd, serialConfig *conf) {
	conf->connected = FALSE;
	conf->init = FALSE;
	commSetNumber(hwnd, conf, 1);
}

// Connects to, sets up and configures (if virgin) port.
void commConnect(HWND hwnd, serialConfig *conf) {
	// EnableMenuItem(hmenu, ID_FILE_QUIT, MF_ENABLED);
	// EnableMenuItem(hmenu, ID_FILE_QUIT, MF_GRAYED);
	int success = TRUE;
	// disconnect any previous connection
	if (conf->connected)	// check if previous connection exists
		commDisconnect(hwnd, conf);	// disconnect previous connection

	// Connect to port
	conf->hComm = CreateFile(
		conf->commName,					// Port Name (ex: "COM1")
		GENERIC_READ | GENERIC_WRITE,	// read/write access
		0,						// share mode (0: do not share)
		NULL,					// security settings (none used)
		OPEN_EXISTING,			// action to take if exists/doesntexist (open only)
		FILE_FLAG_OVERLAPPED,	// enable overlapping
		NULL);					// create connection
	success = (conf->hComm != INVALID_HANDLE_VALUE || conf->hComm == 0);	// Check if com file was created properly
	if (success)
		success = SetupComm(conf->hComm, SERIAL_BUFFSIZE, SERIAL_BUFFSIZE);	// set up the connection

	// Configure port
	/*if (!conf->init) {
		conf->init = GetCommState(conf->hComm, &conf->dcb);
	}
	success = SetCommState(conf->hComm, &conf->dcb);*/
	CommConfigDialog (conf->commName, hwnd, &conf->commconfig);

	// Start reading thread
	conf->hThread = CreateThread(
		NULL,	// security attributes
		0,		// inital thread stack size, in bytes
		commReadThread,		// address of thread function
		hwnd,	// argument for new thread
		0,		// creation flags
		&conf->dThread
	);	// address of returned thread ID
	conf->connected = success;
}

// Disconnects port
void commDisconnect(HWND hwnd, serialConfig *conf) {	// disconnects with serial port if connected
	if (conf->connected) {
		conf->connected = FALSE;
		Sleep(10);	// wait for read thread to finish loop
		//ExitThread(conf->dThread);
		CloseHandle(conf->hComm);
	}
}

// Thread that continuously checks for characters comming in on the serial port.
DWORD WINAPI commReadThread(HWND hwnd) {
	char c;		// holds character found on serial port.
	wndInfo *wInfo = (wndInfo *)GetWindowLongPtr(hwnd, 0);	// Grab pointer to data structure from window's memory
	serialConfig *conf = &wInfo->serCon;
	while (conf->connected) {	// only loops while serial port is connected.
		c = commGetChar(conf);	// get character from serial port
		if (c != '\0')			// '\0' means that no characters were received
			printChar(hwnd, wInfo, c);	// print character from serial port.
		Sleep(10);				// saves some CPU time. :)
	}
	return 0;
}

// Sends a string through the serial port (currently only used for simple debugging)
int commSendString(serialConfig *conf, const char * s)
{
	int i;	// string index
	for(i=0; s[i]!='\0'; i++) {	// loop through characters
		if (!commSendChar(conf, s[i]))	// detect write error
			return FALSE;		// writting failed :(
	}
	return TRUE;				// done
}

int commSendChar(serialConfig *conf, char c) {
	DWORD numBytesWritten;			// records number of character successfully written (not used, but necessary for WriteFile)
	OVERLAPPED overlapped = {0};	// overlap for preventing simulatious access to serial port

	overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	// create event

	if (overlapped.hEvent == NULL)	// check for overlap error
		return FALSE;		// event error :(
	if (!conf->connected)	// make sure port is actually active
		return FALSE;		// not connected :(
	if (!WriteFile(conf->hComm, &c, 1, &numBytesWritten, &overlapped))	// write byte to port
		return FALSE;		// write failed :(
	return TRUE;			// done
}

// retrieves a single character from the serial port (returns '\0' if an error occured)
char commGetChar(serialConfig *conf) {
	COMSTAT comstat;				// stores serial status information
	char c = '\0';					// stores character from serial port
	DWORD numBytesRead;				// number of bytes successfully read (not used, but necessary for ReadFile)
	OVERLAPPED overlapped = {0};	// overlap to prevent simultanious access to serial port

	overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);	// create overlap event to prevent simultanious access to serial port
	ClearCommError(conf->hComm, NULL, &comstat);				// get status information from serial port

	if (overlapped.hEvent == NULL)	// check for overlap error
		return '\0';				// Event error :(

	if (!comstat.cbInQue)	// check if queue is empty
		return '\0';	// queue empty (nothing to do)

	ReadFile(conf->hComm, &c, 1, &numBytesRead, &overlapped);	// read a single character from the serial port
	return c;			// done
}
