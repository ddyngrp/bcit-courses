#include <windows.h>
#include <sstream>
#include "serial.h"
#include "packet.h"
#include "exceptions.h"
#include "utils.h"
#include "message.h"

using namespace std;

// ========================= Thread ========================= //

/*
keeps getting packets from serial port (pre-fetching)
@param pvoid - unused
*/
DWORD WINAPI Serial::thread(PVOID pvoid) {
	Serial *inst = (Serial*)pvoid;
	HANDLE listen[] = {inst->getNewPacketEvent_, inst->globalDieEvent_};
	while (true) {
		if (WaitForMultipleObjects(2, listen, FALSE, INFINITE) == 1)
			break;
		inst->getNewPacket();
	}
	return 0;
}

// ========================= Serial ========================= //

/*
Constructs the serial port class
*/
Serial::Serial(): port_(NULL),
					packetFoundEvent_(CreateEvent(NULL, FALSE, FALSE, PACKET_FOUND_EVENT)),
					getNewPacketEvent_(CreateEvent(NULL, FALSE, FALSE, GET_NEW_PACKET_EVENT)),
					globalDieEvent_(CreateEvent(NULL, FALSE, FALSE, GLOBAL_DIE_EVENT)),
					recStartEvent_(CreateEvent(NULL, FALSE, FALSE, COMMIN_START_EVENT)) {
	InitializeCriticalSection(&portGuard_);
}

/*
Gets a new packet from the serial port.
Note: this function is called by Serial::thread!
*/
void Serial::getNewPacket() {
	packet_ = NULL;	// resets packet to "new" state
	while(getNextChar() != SOH);	// wait for an SOH
	packet_ += SOH;
	while(!packet_.complete()) {	// wait for packet to be complete
		try {
			packet_ += getNextChar(); // get char
		} catch (int i) {
			ENSURE_EXCEPTION(i, PACKET_TOO_SMALL_EXCEPTION);
			packet_.clear();
		}
	}
	packetAvailable_ = true;
	SetEvent(packetFoundEvent_);
}

/*
Tries to get a packet within a certain timeframe
@throws TIMEOUT_EXCEPTION if no packet found
@param timeout - max time to wait for a packet
@returns the new packet
*/
Packet Serial::getPacket(int timeout) {
	if (!packetAvailable_)
		WaitForSingleObject(packetFoundEvent_, timeout);	// give the serial thread time to find a packet
	ENSURE_BOOL_THROW(packetAvailable_, TIMEOUT_EXCEPTION);	// check if a packet has been found yet
	Packet p(packet_);
	SetEvent(getNewPacketEvent_);
	return p;
}

bool Serial::sendPacket(Packet& packet){
	bool retVal = true;
	EnterCriticalSection(&portGuard_);
	// Create Overlap
	OVERLAPPED osWrite = {0};
	DWORD dwWritten;
	//Create this write operation's OVERLAPPED structure's hEvent.
	osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(osWrite.hEvent == NULL) {
		retVal =  false;
	} else if(WriteFile(hComm_, packet.data().c_str(), packet.length(), &dwWritten, &osWrite)){
		CloseHandle(osWrite.hEvent);
	} else if (GetLastError() != ERROR_IO_PENDING) {
		retVal = false;
	}
	// Done
	LeaveCriticalSection(&portGuard_);
	return retVal;
}

char Serial::getNextChar() {
	static string data;
	while (data.empty())
		data = getString();
	char c = data[0];
	data.erase(0);
	return c;
}

string Serial::getString() {
	bool success = false;
	EnterCriticalSection(&portGuard_);
	char inbuff[128];
	DWORD nBytesRead, dwEvent;
	COMSTAT comstat;
	COMMTIMEOUTS timeOuts;
	OVERLAPPED osRead = {0};
	osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//Set the total timeout interval
	memset(&timeOuts, 0, sizeof(timeOuts));
	timeOuts.ReadTotalTimeoutMultiplier = 5;
	timeOuts.ReadTotalTimeoutConstant = 50;
	SetCommTimeouts(hComm_, &timeOuts);

	SetCommMask(hComm_, EV_RXCHAR);
	
	if(WaitCommEvent(hComm_, &dwEvent, NULL)) {
		ClearCommError(hComm_, NULL, &comstat);
		success = ((dwEvent & EV_RXCHAR) &&
				comstat.cbInQue &&
				ReadFile(hComm_, &inbuff, min(127, comstat.cbInQue), &nBytesRead, &osRead) &&
				nBytesRead);
	}
	ResetEvent(osRead.hEvent);
	PurgeComm(hComm_, PURGE_RXCLEAR);
	LeaveCriticalSection(&portGuard_);
	if (!success)
		throw COMM_READ_EXCEPTION;
	return string(inbuff, nBytesRead);
}

bool Serial::connect() {
	bool retVal = true;
	EnterCriticalSection(&portGuard_);
	if (port_ == NULL)
		Message::ChoosePort();
	else if((hComm_ = CreateFile(port_, GENERIC_READ | GENERIC_WRITE, 0,
				NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL)) ==
				INVALID_HANDLE_VALUE)
		Message::ErrorFailedPort();
	else if(!SetCommState(hComm_, &commConfig_.dcb))
		Message::FailedSavePort();
	else if(!SetupComm(hComm_, 8, 8))
		Message::FailedConnection();
	else if(!GetCommProperties(hComm_, &commProp_))
		Message::FailedConnection();
	else
		retVal = true;
	LeaveCriticalSection(&portGuard_);
	return retVal;
}

void Serial::properties(HWND hwnd, LPTSTR port) {
	port_ = port;
	if(connected_) {
		Message::CntChngSettings();
	} else {
		commConfig_.dwSize = sizeof(COMMCONFIG);
		commConfig_.wVersion = 0x100;
		if(!CommConfigDialog(port_, hwnd, &commConfig_)) {
			Message::FailedPort();
		}
	}
}