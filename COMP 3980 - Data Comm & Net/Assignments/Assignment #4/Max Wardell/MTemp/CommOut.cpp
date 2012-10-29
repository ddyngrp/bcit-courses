/*
****************************************************************************
* CommOut.cpp                                                              *
* Purpose: Sending completed packets from the buffer to the serial port.   *
* Additionally, CommOut handles the RVI process of receiving data and      *
* sending that to the GUI.                                                 *
* Author: Max Wardell                                                      *
* Version: 1.0                                                             *
****************************************************************************
*/

#include "CommOut.h"

//using namespace std;

//Outbuff gets populated, this function is called.
/*Purpose: */
//CommOut::CommOut(Buffer *buffer, GUI *gui, Serial *serial)
//:buffer_(buffer), gui_(gui), serial_(serial) {
CommOut::CommOut(Buffer *buffer, Serial *serial)
:buffer_(buffer), serial_(serial) {
	InitializeCriticalSection(&protGuard_);
	CreateThread(NULL, 0, &CommOut::thread, this, 0, NULL);
}

DWORD WINAPI CommOut::thread(PVOID pvoid) {
	CommOut *inst = (CommOut*)pvoid;
	static HANDLE hEvent[2];
	//Create 2 events, one for starting the thread, one for stopping it. The "on/off" switch of CommOut.
	hEvent[0] = CreateEvent(NULL, TRUE, FALSE, TEXT("Send Start Event"));
	hEvent[1] = CreateEvent(NULL, TRUE, FALSE, TEXT("Send Die Event"));
	while(true) {
		if(WaitForMultipleObjects(2, hEvent, FALSE, INFINITE) == 1) //Wait for an event to 'wake up' the method.
			return 0;
		EnterCriticalSection(&inst->protGuard_);
		inst->ConnectClient();
		LeaveCriticalSection(&inst->protGuard_);
	}
}

//Outbuff gets populated, this function is called.
/*Purpose: Connects to the receiver*/
void CommOut::ConnectClient() {
	static HANDLE hEvent[2];
	DWORD called = 0; //Calculates which event was called.
	//Create 2 events, one for starting the thread, one for stopping it. The "on/off" switch of CommOut.
	hEvent[0] = CreateEvent(NULL, TRUE, FALSE, TEXT("commOutStartEvent")); //Previously "Send Start Event"
	hEvent[1] = CreateEvent(NULL, TRUE, FALSE, TEXT("globalDieEvent"));    //Previously "Send Die Event"
	while(true) {
		called = WaitForMultipleObjects(2, hEvent, FALSE, INFINITE); //Wait for an event to 'wake up' the method.
		ENSURE_EXCEPTION(called, GOTO_IDLE_EXCEPTION);
		try {
			packet_ = serial_->getPacket(TIMEOUT_TIME);//Grab the packet from the serial port.
		}
		catch (const int i) {         //Never received a packet, timeout.
			//SetEvent(gotoIdle);
			continue;
			ENSURE_EXCEPTION(i, TIMEOUT_EXCEPTION);
		}
		if(packet_.valid() &&
			packet_.flags() == ACK1) //Packet is an ACK1,
			throw GOTO_IDLE_EXCEPTION;     //Break out of loop and send packet.
		else if(packet_.valid() &&
			packet_.flags() == RVI)  //Packet is an RVI
			RVIProcess();
		
	}
	SendPacket(); //Send the packet
}

/*Purpose: Sends the packet*/
void CommOut::SendPacket() {
	while(1) { //TODO: Change this condition
		if(buffer_->empty()) {  //If the buffer is empty,
			buffer_->send(NTS); //Send a NTS packet and
			throw GOTO_IDLE_EXCEPTION;//break; //break out of the Sending process
		}
		buffer_->send(packet_); //If the buffer isn't empty, send the packet.
	}
}

/*Purpose: Receives packets when in RVI mode; displays to GUI.*/
void CommOut::RVIProcess() { //Occurs when an RVI is sent
	int timeoutCount = 0, nackCount = 0;
	buffer_->send(ACK1); //Send an acknoledgement, letting the sender know you received the RVI
	//Connection Confirmed
	while(true) {
		try {
			packet_ = serial_->getPacket(TIMEOUT_TIME); //Grab the packet sent
		} catch (const int i) {
			if(++timeoutCount >= MAX_COUNT)
				throw GOTO_IDLE_EXCEPTION;
		}
		if(packet_.valid()) { //If the packet is valid,
			buffer_->send(ACK1); //Sent an ACK1..?
			if(packet_.flags() == RVI) //If the packet is an RVI (second one)
				throw GOTO_IDLE_EXCEPTION;
			nackCount = 0;
		}
		else { //If the packet is invalid,
			buffer_->send(NACK); //Send a NACK
			if(++nackCount >= MAX_COUNT) { //Keep count of how many NACKs you receive in a row.
				buffer_->send(NACK); //If the NACK count reaches its maximum, sent one final NACK and return back to IDLE.
				throw GOTO_IDLE_EXCEPTION; 
			}
		}
	}
}


