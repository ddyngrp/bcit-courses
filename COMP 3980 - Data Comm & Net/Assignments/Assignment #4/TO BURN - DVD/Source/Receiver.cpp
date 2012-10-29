#include "Receiver.h"

void Receiver::run() {
	// TODO: HACKING!
	Packet p = pSerial_->getPacket(INFINITE);
	if (p.valid())
		if (!p.cmd())
			pGUI_->DisplayReceivedText(p.data());
	return;

	Packet packet;
	int tCount = 0;

	pSerial_->sendPacket(Packet(ACK0));

	while(true){
		// TODO: check received packet vs RVI mode order
		if(pBuffer_->danger()) {
			enterRVIMode();
		}

		// Get Packet
		try{
			packet = pSerial_->getPacket(TIMEOUT_TIME);
		}catch(const int i) {
			ENSURE_EXCEPTION(i, TIMEOUT_EXCEPTION);
				throw GOTO_RESET_EXCEPTION;
		}

		// Check Packet
		if (!packet.valid()) {
			pSerial_->sendPacket(Packet(NACK));
		} else {
			if (!packet.cmd()) {
				pGUI_->DisplayReceivedText(packet.data().c_str());
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
			flag = pSerial_->getPacket(TIMEOUT_TIME).flags();
			if (flag == ACK1) {
				break;
			}
		}
		catch(int i){
			ENSURE_EXCEPTION(i, TIMEOUT_EXCEPTION);
				throw GOTO_RESET_EXCEPTION;

		}
	}

	while(!(pBuffer_->safe())) {
		pSerial_->sendPacket((pBuffer_->peek()));
		pBuffer_->pop();	
	}
	if(pBuffer_->safe()) {
		throw GOTO_IDLE_EXCEPTION;
	}
}




