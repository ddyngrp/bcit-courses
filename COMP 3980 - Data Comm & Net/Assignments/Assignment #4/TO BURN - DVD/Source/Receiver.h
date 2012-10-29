#ifndef RECEIVER_H
#define RECEIVER_H
// TODO: remove these
//#define GOTO_IDLE_EXCEPTION 1000
//#define TIMEOUT_TIME 100


#include<windows.h>
#include "Buffer.h"
#include "s_control.h"
#include "utils.h"
#include "serial.h"
#include "exceptions.h"
#include "protocol.h"


class Receiver{
public:

	//static DWORD WINAPI thread(PVOID pvoid);
	Receiver();
	Receiver(Buffer *pBuffer, Serial *pSerial, Controller *pGUI):pBuffer_(pBuffer),
		pSerial_(pSerial),pGUI_(pGUI){}
	void run();
	void enterRVIMode();
	//void readPacket();

private:
	Buffer *pBuffer_;
	Serial *pSerial_;
	Controller	*pGUI_;
	CRITICAL_SECTION cs_;
	
	
};

#endif

