/* 
* File:   main.h
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#ifndef _MAIN_H
#define	_MAIN_H

#include <windows.h>

#define BUFFER(x,y) *(wInfo->pBuffer + y * wInfo->cxBuffer + x)	// creates a text buffer

typedef struct _serialConfig {	// struct for holding serial-configuration data
	WCHAR commName[5];	// string equiv of serial port (ex: "COM1"), Note: use TEXT("COM1") when setting!
	COMMCONFIG commconfig;	// Comm configuration (for dialog)
	int init;			// set true when dcb has been initialized
	int connected;		// set true once connection has been made
	int threadQuit;		// when set true, reading thread will quit at end of current loop
	HANDLE hComm;		// handler to serial connection file
	HANDLE hThread;		// handler to serial read thread
	DWORD dThread;		// device id of read thread.
} serialConfig;			// shortcuts for references sizes of struct

typedef struct _wndInfo {	// struct for holding window-specific data
	int cxClient, cyClient;	// size of the window (px)
	int cxBuffer, cyBuffer;	// buffer x and y boundaries in characters
	int xCaret, yCaret;		// current caret location
	TCHAR * pBuffer;		// where the actual information is stored
	serialConfig serCon;	// struct holding serial configuration information
	int cxChar, cyChar;		// x and y character sizes
	DWORD dwCharSet;		// character set (usually just using default)
} wndInfo;	// shortcuts for references sizes of struct

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);	// declares the WndProc method written later in the file

#endif
