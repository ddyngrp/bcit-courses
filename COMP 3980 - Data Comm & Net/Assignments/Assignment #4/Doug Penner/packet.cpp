#include <windows.h>
#include <string>
#include "packet.h"
#include "crc.h"
#include "utils.h"

using namespace std;

Packet::Packet(): packet_(""), length_(0) {}

Packet::Packet(const Packet& packet): packet_(packet.packet_), length_(packet.length_) {}	// copy constructor

Packet::Packet(std::string packet): packet_(packet), length_(packet.length()) {}				// turn string into packet

Packet::Packet(char flag): length_(minLength_) {
	packet_ = SOH + (char)0x04 + flag;
}

void Packet::seq(bool toggle) {	// only call once on a packet!!!
	packet_[2] = (toggle) ? (packet_[2] | SEQ) : (packet_[2] & (!SEQ));		// set SEQ bit
}

bool Packet::seq() {
	return (packet_[2] & SEQ) == SEQ;
}

Packet::Packet(int flags, string data):packet_(""), length_(minLength_ + data.length()) {
	packet_ += SOH;
	packet_ += data.length() + 5;
	packet_ += flags;
	packet_ += data;
}

void Packet::operator+=(const char chr) {
	packet_ += chr;
}

bool Packet::complete() {
	return packet_.length() >= minLength_ && packet_.length() == packet_[1];
}

bool Packet::valid() {
	ENSURE_BOOL(packet_.length() >= minLength_);
	ENSURE_BOOL(packet_[0] == SOH);
	ENSURE_BOOL(packet_[1] == packet_.length());
	ENSURE_BOOL(CRC::calc(packet_.substr(0, packet_.length()-2)));
	return true;
}

int Packet::flags() {
	return (packet_[2] & (!SEQ));
}

string Packet::data() {
	return packet_.substr(4, packet_.length()-2);
}

string Packet::toString() {
	if (packet_.length() == length_)	// remove CRC
		packet_ = packet_.substr(0,length_-1);
	// re-calculate CRC
	packet_ += CRC::calc(packet_);	// re-calculate CRC
	// return packet
	return packet_;
}

void Packet::clear() {
	length_ = 0;
	packet_.clear();
}

int Packet::length() {
	return length_;
}

bool Packet::cmd() {
	return length_ == minLength_;
}