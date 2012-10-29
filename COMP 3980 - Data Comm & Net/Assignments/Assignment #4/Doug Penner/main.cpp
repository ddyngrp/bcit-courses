#include <windows.h>
#include <string>
#include "packet.h"
#include "serial.h"

using namespace std;

int main(char *args[], int argc) {
	/*
	static Buffer	*buffer;
	static Serial	*serial;
	static GUI		*gui(		buffer, serial);
	static CommIn	*commIn(	buffer, serial, gui);
	static CommOut	*commOut(	buffer, serial, gui);
	hBufferThread	= CreateThread(NULL, 0, Serial::thread	, serial	, 0, NULL);
	hCommInThread	= CreateThread(NULL, 0, CommIn::thread	, commIn	, 0, NULL);
	hCommOutThread	= CreateThread(NULL, 0, CommOut::thread	, commOut	, 0, NULL);
	hGUIThread		= CreateThread(NULL, 0, GUI::thread		, gui		, 0, NULL);
	*/
	Serial ser;
	//ser.properties(hwnd, TEXT("com1");
	ser.connect();
	for (int i=0; i < 10; ++i) {
		ser.sendPacket(Packet(string("hello")));
		Sleep(1000);
	}
	return 0;
}

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)	{
	return 0;
}