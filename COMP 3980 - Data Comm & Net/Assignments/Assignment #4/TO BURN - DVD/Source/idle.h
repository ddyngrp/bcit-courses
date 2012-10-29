#ifndef _IDLE_H
#define _IDLE_H

#include "serial.h"
#include "Buffer.h"
#include "CommOut.h"
#include "Receiver.h"
#include "s_control.h"

class Idle {
public:
	Idle(Buffer *buffer, Serial *serial, Controller *gui);
	static DWORD WINAPI thread(PVOID pvoid);
private:
	CommOut *commOut_;
	Receiver *commIn_;
};

#endif
