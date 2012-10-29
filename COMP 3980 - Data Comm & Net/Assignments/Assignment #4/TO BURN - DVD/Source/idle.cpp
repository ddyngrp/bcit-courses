#include <windows.h>
#include "idle.h"
#include "events.h"
#include "utils.h"

Idle::Idle(Buffer *buffer, Serial *serial, Controller *gui): 
				commOut_(new CommOut(buffer, serial, gui)), 
				commIn_(new Receiver(buffer, serial, gui)) {}

DWORD WINAPI Idle::thread(PVOID pvoid) {
	Idle *inst = (Idle*)pvoid;
	HANDLE get = CreateEvent(NULL, FALSE, FALSE, GET_NEW_PACKET_EVENT);
	HANDLE listen[] = {
		CreateEvent(NULL, FALSE, FALSE, COMMOUT_START_EVENT),
		CreateEvent(NULL, FALSE, FALSE, PACKET_FOUND_EVENT),	// start receiving
		CreateEvent(NULL, FALSE, FALSE, GLOBAL_DIE_EVENT)
	};
	int who;

	
	while (true) {
		who = WaitForMultipleObjects(3, listen, FALSE, INFINITE);
		try {
			switch (who) {
				case WAIT_OBJECT_0+0:	// send
					Sleep(1);
					inst->commOut_->ConnectClient();
					break;
				case WAIT_OBJECT_0+1:	// receiver
					Sleep(1);
					inst->commIn_->run();
					SetEvent(get);
					break;
				case WAIT_ABANDONED:	// die
					return 0;
			}
		} catch (...) {
			//ENSURE_EXCEPTION(i, GOTO_IDLE_EXCEPTION);
		}
		for (int i=0; i < 3; ++i) {
			ResetEvent(listen[i]);
		}
	}
	return 0;
}