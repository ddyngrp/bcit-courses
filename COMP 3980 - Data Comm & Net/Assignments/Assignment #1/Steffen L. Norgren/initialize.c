/*------------------------------------------------------------------------------
	MODULE: initialize.c

	PURPOSE: Initializes global data structures

	AUTHOR: Steffen L. Norgren
		A00683006

/*-----------------------------------------------------------------------------*/

#include <windows.h>
#include <commctrl.h>
#include "dumbterm.h"

/*------------------------------------------------------------------------------
	FUNCTION: ClearTTYContents()

	PURPOSE: Clears the tty buffer

/*-----------------------------------------------------------------------------*/
void ClearTTYContents() {
	FillMemory(SCREEN(TTYInfo), MAXCOLS * MAXROWS, ' ');
	ROW(TTYInfo) = 0;
	COLUMN(TTYInfo) = 0;
}

/*------------------------------------------------------------------------------
	FUNCTION: InitTTYInfo()

	PURPOSE: Initializes TTY default settings

/*-----------------------------------------------------------------------------*/
void InitTTYInfo() {
	// Initialize general TTY info
	COMDEV(TTYInfo)		= NULL;
	CONNECTED(TTYInfo)	= FALSE;
	PORT(TTYInfo)		= '0';			// setting to 0 since we know nothing about
										// the current COM port configuration
	BAUDRATE(TTYInfo)	= CBR_9600;
	BYTESIZE(TTYInfo)	= 8;
	PARITY(TTYInfo)		= NOPARITY;
	STOPBITS(TTYInfo)	= ONESTOPBIT;

	InitFont();
	ClearTTYContents();
}

/*------------------------------------------------------------------------------
	FUNCTION: InitFont()

	PURPOSE: Initialize the font for displaying TTY data

/*-----------------------------------------------------------------------------*/
void InitFont() {
	TEXTMETRIC	tm;
	HDC			hdc;

	hdc = GetDC(ghwndMain);
	
	// set the font to be the default fixed-pitch font
	SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, FIXED_PITCH, NULL));

	GetTextMetrics(hdc, &tm);
	ReleaseDC(ghwndMain, hdc);

	// get text width & height
	XCHAR(TTYInfo) = tm.tmAveCharWidth;
	YCHAR(TTYInfo) = tm.tmHeight + tm.tmExternalLeading;
}

/*------------------------------------------------------------------------------
	FUNCTION: StartReadThread()

	PURPOSE: Starts a thread for reading from the COM port

/*-----------------------------------------------------------------------------*/
void StartReadThread() {
	DWORD dwReadId;

	READTHREAD(TTYInfo) = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE)ReaderProc, (LPVOID)ghwndMain, 0, &dwReadId);
}