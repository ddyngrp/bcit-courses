#include "crc.h"

using namespace std;

unsigned char CRC::calc(string in)
{
	unsigned char crc = 0;
	for (size_t i=0; i < in.length(); ++i) {
		crc = crcTable[crc ^ in[i]];
	}
	return crc;
}