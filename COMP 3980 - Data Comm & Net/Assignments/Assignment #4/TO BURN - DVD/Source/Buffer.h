#ifndef BUFFER_H
#define BUFFER_H

#include <windows.h>
#include <stdio.h>
#include <list>
#include "packet.h"

//when buffer reaches
#define BUFFMAX 30
// send RVI

#include "packet.h"
//when buffer reaches
#define BUFFMIN 5
// end RVI

class Buffer {
public:
	Buffer();
	~Buffer(){ DeleteCriticalSection(&cs_); }
	void send(Packet p);	// add packet on the list
	Packet peek();			// returns next packet on list
	void pop();				// takes packet off list
	bool danger();			// send rvi
	bool safe();			// end rvi
	bool empty();
	std::list<Packet> packetList_;
private:
	CRITICAL_SECTION cs_;
	int count_;
	HANDLE hEvent_;
};

#endif BUFFER_H
