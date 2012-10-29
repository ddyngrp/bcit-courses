#include "E_Receiver.h"


void 
Receiver::sendACK(Packet& p){
	comm.send(Packet(ACK0));
	comm.send(Packet(ACK1));
	comm.send(Packet(NACK));
	comm.send(Packet(SEQ));
	comm.send(Packet(NTS));
}

void
Receiver::ReceivePackets(){
	Packet packet(serial.receive());
	if packet.valid()
	if packet.flags() == ACK0
	gui.display(packet.data());
}

void 
Receiver::sendRVIWhenReceiveACK(){
	if (buffer.danger()){
		comm.sendPacket(Packet(RVI));
	}
}


void 
Receiver::sendPacket(){
}