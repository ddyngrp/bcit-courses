#include <iostream>
#include "D_packet.h"

class Receiver {
public:

	void sendACK(const Packet&);
	void ReceivePackets();
	void sendRVIWhenReceiveACK();
	void sendPacket();

private:
	void enter_rvi();
};





