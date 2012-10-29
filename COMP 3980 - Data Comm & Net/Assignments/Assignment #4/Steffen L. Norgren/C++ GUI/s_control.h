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
#include <string.h>

class Model {
    enum { TEXT_SIZE = 20 };
public:
    Model(char const * str) {
        SetText(str);
        _text[TEXT_SIZE] = '\0';
    }

    void SetText(char const * str) {
        strncpy_s(_text, str, TEXT_SIZE);
    }

    char const * GetText() const { return _text; }
    int GetLen() const { return (int)strlen(_text); }

private:
    char _text[TEXT_SIZE + 1];
};

class Controller {
public:
    Controller(HWND hWnd, CREATESTRUCT * pCreate);
    ~Controller();
	static DWORD WINAPI TimerThread(PVOID pVoid);
    void Size(int x, int y);
    void Paint();
    void Command(int cmd);
	void CreateChatWindow();
	void PopulateCOMPorts();
	void SendText(HWND);
	void SetText(HWND, char *);
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
	TCHAR		_szPort[10];
};

#endif

