/*
	MODULE: modelControl.h

	PURPOSE: Main controller

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
 */

#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <windows.h>
#include "serial.h"
#include "Buffer.h"

class Model {
    enum { TEXT_SIZE = 20 };
public:
    Model(char const * str) {
        DisplayText(str);
        _text[TEXT_SIZE] = '\0';
    }

    void DisplayText(char const * str) {
        strncpy_s(_text, str, TEXT_SIZE);
    }

    char const * GetText() const { return _text; }
    int GetLen() const { return (int)strlen(_text); }

private:
    char _text[TEXT_SIZE + 1];
};

class Controller {
public:
    Controller(HWND hWnd, CREATESTRUCT * pCreate, Serial *serial, Buffer *buffer);
    ~Controller();
	static DWORD WINAPI TimerThread(PVOID pVoid);
    void Size(int x, int y);
    void Paint();
    void Command(int cmd);
	void CreateChatWindow();
	void PopulateCOMPorts();
	void SendText();
	void DisplayReceivedText(std::string);
	void DisplaySentText(std::string);
	void ClearText(HWND);
	void ToggleConnect();
	void ToggleSending();
	void ToggleReceiving();
	
	BOOL		_fConnected;
	WORD		_wSeconds;
	HWND		_hWndChat;
private:
	PAINTSTRUCT _paint;
    HWND		_hWnd;
    Model		_model;
	Serial *	_serial;
	Buffer *	_buffer;
	TCHAR		_szPort[10];
};

#endif

