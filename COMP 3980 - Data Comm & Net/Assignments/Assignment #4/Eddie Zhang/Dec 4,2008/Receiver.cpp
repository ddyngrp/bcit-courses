#include "Receiver.h"


//
//DWORD WINAPI Receiver::thread(PVOID pvoid){
//	Receiver *instance = (Receiver*)pvoid;
//
//
//	static HANDLE hEvent[
//	
//
//	bool running = true;
//
//	hEvent[0] = CreateEvent(NULL, TRUE,FALSE,TEXT("START EVENT"));
//	hEvent[1] = CreateEvent(NULL, TRUE,FALSE,TEXT("DIE EVENT"));
//
//	while(running){
//		if (WaitForMultipleObjects(2, hEvent, FALSE, INFINITE) == 1);
//			break;
//		instance->run();
//	}
//	return 0;
//}

void Receiver::run() {
	
	Packet packet;
	int tCount = 0;
	while(true){
		
		pSerial_->sendPacket(Packet(ACK0));
		// TODO: check received packet vs RVI mode order
		if(pBuffer_->danger()){
				//enter RVI mode;
		}

		// Get Packet
		try{
			packet = pSerial_->getPacket(TIMEOUT_TIME);
		}catch(const int i){
			ENSURE_EXCEPTION(i, TIMEOUT_EXCEPTION);
			if (tCount == 4)
				throw GOTO_RESET_EXCEPTION;
			else
				tCount++;
			continue;
		}
		
		// Check Packet
		if (!packet.valid()) {
			pSerial_->sendPacket(Packet(NACK));
		} else if (!packet.cmd()) {
			//gui->display(packet.data());
			break;
		}

	}
}
void Receiver::enterRVIMode(){
	
	pSerial_->sendPacket(Packet(RVI));
	while(!(pBuffer_->safe())){
		pSerial_->sendPacket((pBuffer_->peek()));
		pBuffer_->pop();	
	}

}




