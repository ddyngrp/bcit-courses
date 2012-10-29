/*
	MODULE: terminal.h

	PURPOSE: Contains global definitions and variables

	AUTHORS: Steffen L. Norgren
			 Doug Benner
*/

#ifndef _TERMINAL_H
#define _TERMINAL_H

#include <windows.h>
#include "resource.h"
#include "termInfo.h"

// Global Definitions
#define X_SIZE		640
#define Y_SIZE		360

#define PURGE_FLAGS	PURGE_TXABORT | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_RXCLEAR

// Global Variables
HINSTANCE		ghInst;			// Main application's global instance
HWND			ghWndMain;		// Main window's global handle
HWND			ghWndTerm;		// Child terminal window's global handle
HWND			ghWndStatusDlg; // Child status window's handle
HACCEL			ghAccel;		// Keyboard accelerator
OVERLAPPED		gOverlapped;	// HACK!
char			gszPort[10];	// Port Name

// Window placement variables
WORD gwBaseY;
LONG gcyMinimumWindowHeight;

// Status Updating
// TODO

// Global function Prototypes
int WINAPI TermWndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI TermChildProc(HWND, UINT, WPARAM, LPARAM);
void ClearScreen();
void InitFont();
void CmdPort(HWND);
void InitTermInfo();
void DestroyTermInfo();
void OutputBuffer(HWND, char *, DWORD);
void MenuDispatch(int, HWND, LPARAM);
BOOL NEAR ResizeTerm(HWND);
void ChooseFixedFont(HWND);
void InitNewFont(LOGFONT, COLORREF);
void FormatOutput(HDC, int);
void InitTTYInfo();

// Function Prototypes for Doug
void SetFormat(int, BOOL);
void PrintChar(char);
void SetCursorPosition(int, int);
void MoveCursor(int, int);
void EraseFromCursorToEOL();
void EraseFromSOLToCursor();
void EraseEntireScreen();
void EraseLine();
void NewLine();
void SaveCursorAttributes();
void RestoreCursorAttributes();
void SingleWidthLine();
void DoubleWidthLine();
void MoveBuffer();
void EraseFromCursorToEOS();
void EraseFromSOSToCursor();
void BackSpace();
void SetScrollingRegion(int, int);
void commConnect();
void commDisconnect();
int commSendString(const char *);
int commSendChar(char);

#endif