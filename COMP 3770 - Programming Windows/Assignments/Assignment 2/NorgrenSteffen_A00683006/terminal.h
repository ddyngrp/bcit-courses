/*
	MODULE: terminal.h

	PURPOSE: Contains global definitions and variables

	AUTHOR: Steffen L. Norgren
			A00683006
*/

#include <windows.h>
#include "resource.h"
#include "termInfo.h"

// Global Variables
OSVERSIONINFO	gOSV;		// Operating System Version INfo
HINSTANCE		ghInst;		// Main application's global instance
HWND			ghWnd;		// Main window's global handle
HACCEL			ghAccel;	// Keyboard accelerator

// Global Definitions
#define X_START_POS	100
#define Y_START_POS	100
#define X_SIZE		580
#define Y_SIZE		400

// Global function Prototypes
int WINAPI TermWndProc(HWND, UINT, WPARAM, LPARAM);
void ClearTerminal();
void InitFont();
void DestroyTermInfo();
void OutputBuffer(HWND, char *, DWORD);
BOOL NEAR MoveCursor(HWND);
