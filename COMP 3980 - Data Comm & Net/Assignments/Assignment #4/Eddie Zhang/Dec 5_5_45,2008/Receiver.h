#ifndef RECEIVER_H
#define RECEIVER_H
// TODO: remove these
#define GOTO_IDLE_EXCEPTION 1000
#define TIMEOUT_TIME 100


#include<windows.h>
#include "Buffer.h"
#include "gui.h"
#include "utils.h"
#include "serial.h"
#include "exceptions.h"


class Receiver{
public:

	//static DWORD WINAPI thread(PVOID pvoid);
	Receiver();
	Receiver(Buffer *pBuffer, Serial *pSerial, GUI *pGUI):pBuffer_(pBuffer),
		pSerial_(pSerial),pGUI_(pGUI){}
	void run();
	void enterRVIMode();
	//void readPacket();

private:
	Buffer *pBuffer_;
	Serial *pSerial_;
	GUI		*pGUI_;
	CRITICAL_SECTION cs_;
	
	
};

#endif

