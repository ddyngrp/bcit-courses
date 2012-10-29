//#include <windows.h>

#include <string>

#include <iostream>

#include "packet.h"

#include "crc.h"

#include "utils.h"



using namespace std;



// ========================= Constructors ========================= //

// for serial port

Packet::Packet(): packet_(""), length_(0) {}



// for copying (shouldn't need)

Packet::Packet(const Packet& packet): packet_(packet.packet_), length_(packet.length_) {}	// copy constructor



// for Protocol Controllers

Packet::Packet(char flag): length_(minLength_) {

	packet_ = SOH + (char)0x04 + flag;

}



// for GUI

Packet::Packet(const std::string data): length_(data.length() + 4) {

	packet_ += SOH;

	packet_ += NONE;

	packet_ += data;

}	// turn string into packet



// create a fully custom packet (flags and data section)

Packet::Packet(int flags, string data):packet_(""), length_(minLength_ + data.length()) {

	packet_ += SOH;

	packet_ += (data.length() + 5);

	packet_ += flags;

	packet_ += data;

}



// ========================= Methods ========================= //



// append char (for empty constructor)

void Packet::operator+=(const char chr) {

	packet_ += chr;

}



// checks if there are enough characters for the packet to be valid

//		Note: Only packet length is checked!!!

bool Packet::complete() {

	return packet_.length() >= minLength_ && packet_.length() == (size_t)packet_[1];

}



// get SEQ bit

bool Packet::seq() {

	return (packet_[2] & SEQ) == SEQ;

}



// validates the packet

bool Packet::valid() {

	ENSURE_BOOL(packet_.length() >= minLength_);

	ENSURE_BOOL(packet_[0] == SOH);

	ENSURE_BOOL((size_t)packet_[1] == packet_.length());

	ENSURE_BOOL(CRC::calc(packet_.substr(0, packet_.length()-2)));

	return true;

}



// gets the flags section of the packet (with SEQ set to 0)

int Packet::flags() {

	return (packet_[2] & (!SEQ));

}



// gets the data section of the packet

string Packet::data() {

	return packet_.substr(4, packet_.length()-2);

}



string Packet::toString(bool seq) {

	// set sequence bit

	char flags = packet_[2];

	if (seq)

		flags = flags | SEQ;

	else

		flags = flags & (!SEQ);

	

	//packet_.replace(2, 1, 1, 'X');

	return packet_;

}



void Packet::calcCRC() {

	// generate CRC

	if (packet_.length() == length_)	// remove old CRC

		packet_ = packet_.substr(0,length_-1);

	packet_ += CRC::calc(packet_);	// re-calculate CRC

}



// resets the packet to blank

void Packet::clear() {

	length_ = 0;

	packet_.clear();

}



// gets the length of the packet

int Packet::length() {

	return length_;

}



bool Packet::cmd() {

	return (length_ == minLength_);

}



// prints the packet to an ostream

//		Note: SEQ set to 0!

void Packet::print() {

	calcCRC();

	cout << toString(false) << endl;

}

