/*------------------------------------------------------------------------------
	MODULE: dumbterm.h

	PURPOSE: Contains global definitions and variables

	AUTHOR: Steffen L. Norgren
		A00683006

/*-----------------------------------------------------------------------------*/

#include <commctrl.h>
#include "resource.h"	// menu resource
#include "ttyinfo.h"	// TTY definitions & structs

// Global Variables
OSVERSIONINFO	gOSV;
HINSTANCE		ghInst;		// main application's global instance
HWND			ghwndMain;	// main window's global handle
HACCEL			ghAccel;	// keyboard accelerator (detect key combinations)

// Global Defines
#define X_START_POS	100
#define Y_START_POS	100
#define X_SIZE		730
#define Y_SIZE		447

#define PURGE_FLAGS	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR

#define AMOUNT_TO_READ		128

// Function prototypes
BOOL CmdPort(HWND);
void InitTTYInfo();
void ClearTTYContents();
void InitFont();
void StartReadThread();
void OutputBuffer(HWND, char *, DWORD);
DWORD WINAPI ReaderProc();

// Port Name
char gszPort[10];