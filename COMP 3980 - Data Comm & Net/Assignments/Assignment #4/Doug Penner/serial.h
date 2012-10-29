#ifndef _SERIAL_H
#define _SERIAL_H

#include <windows.h>
#include "packet.h"
#include "events.h"

class Serial {
public:
	bool connected_;
	Serial();
	static DWORD WINAPI thread(PVOID pvoid);
	void getNewPacket();
	char getNextChar();
	Packet getPacket(int timeout);
	bool sendPacket(Packet& packet);
	friend DWORD WINAPI serialThread(PVOID pvoid);
	bool connect();
	std::string getString();
	void properties(HWND hwnd, LPTSTR port);
private:
	CRITICAL_SECTION portGuard_;
	Packet	packet_;
	bool	packetAvailable_;
	// Physical Port
	LPCTSTR port_;
	HANDLE hComm_;
	COMMPROP commProp_;
	COMMCONFIG commConfig_;
	// Thread
	HANDLE	thread_;
	// Events
	HANDLE	packetFoundEvent_;
	HANDLE	getNewPacketEvent_;
	HANDLE	globalDieEvent_;
	HANDLE	recStartEvent_;
};

#endif
