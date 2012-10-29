#include "Buffer.h"

Buffer::Buffer():count_(0)
{ 
	InitializeCriticalSection(&cs_);
	hEvent_[0] = CreateEvent(NULL, TRUE, FALSE, TEXT("Send Start Event"));
	hEvent_[1] = CreateEvent(NULL, TRUE, FALSE, TEXT("Send Die Event"));
}

void Buffer::send(Packet p) {
	EnterCriticalSection(&cs_);
	packetList_.push_front(p);
	
	if(count_ == 0) { // buffer is empty
		SetEvent(hEvent_[0]);
	}
	count_++;
	LeaveCriticalSection(&cs_);
}

Packet Buffer::peek() {
	EnterCriticalSection(&cs_);
	Packet p = *packetList_.end();
	LeaveCriticalSection(&cs_);
	return p;
}

void Buffer::pop() {
	EnterCriticalSection(&cs_);
	packetList_.pop_back();

	if(count_ == 1) { // buffer is almost empty
		SetEvent(hEvent_[1]);
	}
	count_--;
	LeaveCriticalSection(&cs_);
}

bool Buffer::danger() {
	return count_ >= BUFFMAX;
}

bool Buffer::safe() {
	return count_ <= BUFFMIN;
}

bool Buffer::empty() {
	if(count_==0)
		return true;

	return false;
}
