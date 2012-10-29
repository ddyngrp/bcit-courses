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

	pSerial_->sendPacket(Packet(ACK0));

	while(true){
		// TODO: check received packet vs RVI mode order
		if(pBuffer_->danger()){
			enterRVIMode();
		}

		// Get Packet
		try{
			packet = pSerial_->getPacket(TIMEOUT_TIME);
		}catch(const int i){
			ENSURE_EXCEPTION(i, TIMEOUT_EXCEPTION);

				throw GOTO_RESET_EXCEPTION;

		}

		// Check Packet
		if (!packet.valid()) {
			pSerial_->sendPacket(Packet(NACK));
		} else {
			if (!packet.cmd()) {
				//gui->display(packet.data());
				pSerial_->sendPacket(Packet(ACK1));
				continue;
			} else {
				if(packet.flags() == NTS) {
					throw GOTO_IDLE_EXCEPTION;
				}
			}
		}
	}
}

void Receiver::enterRVIMode(){
	int flag;
	int tCount = 0 ;
	pSerial_->sendPacket(Packet(RVI));
	while(true){
		try{
			flag = pSerial_->getPacket().flags();
			if (flag == ACK1){
				break;
			}
		}catch(int i){
			ENSURE_EXCEPTION(i, TIMEOUT_EXCEPTION);
				throw GOTO_RESET_EXCEPTION;

		}
	}

	while(!(pBuffer_->safe())){
		pSerial_->sendPacket((pBuffer_->peek()));
		pBuffer_->pop();	
	}
	if(pBuffer_->safe()){
		throw GOTO_IDLE_EXCEPTION;
	}
}




