#ifndef _SERIAL_H
#define _SERIAL_H

#include <windows.h>
#include "packet.h"
#include "events.h"

#define PURGE_FLAGS PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR

class Serial {
public:
	bool connected_;
	Serial();
	static DWORD WINAPI thread(PVOID pvoid);
	void getNewPacket();
	char getNextChar();
	Packet getPacket(int timeout);
	bool sendPacket(Packet& packet);
	bool Serial::sendString(const char *str, size_t len);
	friend DWORD WINAPI serialThread(PVOID pvoid);
	bool connect(LPCTSTR port);
	bool disconnect();
	bool connected();
	void getString(std::string& data8);
	bool foundChar(char c);
private:
	CRITICAL_SECTION portGuard_;
	Packet	packet_;
	bool	packetAvailable_;
	// Physical Port
	HANDLE hComm_;
	COMMPROP commProp_;
	COMMCONFIG commConfig_;
	DCB dcb_;
	// Thread
	HANDLE	thread_;
};

#endif
