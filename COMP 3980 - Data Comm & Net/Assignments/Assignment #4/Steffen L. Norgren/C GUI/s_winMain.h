/*
	MODULE: winMain.h

	PURPOSE: Contains global definitions and variables

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#ifndef _WINMAIN_H_
#define _WINMAIN_H_

#include <windows.h>

// Global Definitions
#define X_SIZE		640
#define Y_SIZE		400
#define	X_MIN_SIZE	429
#define Y_MIN_SIZE	346

// Global Variables
HINSTANCE		ghInst;			// Main application's global instance
HWND			ghWndMain;		// Main window's global handle
HWND			ghWndChat;		// Our main information display area
HACCEL			ghAccel;		// Keyboard accelerator
char			gszPort[10];	// COMP Port Name
HANDLE			ghTimer;		// Timer thread
WORD			gwSeconds;		// Activity timer

// Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChatProc(HWND, UINT, WPARAM, LPARAM);
void MenuDispatch(UINT, HWND, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();
void PopulateCOMPorts(HWND);
void DialogDispatch(HWND, WPARAM);
void SendText(HWND);
void SetText(HWND, char *);
void ClearText(HWND);
void ToggleConnect();
void ToggleSending();
void ToggleReceiving();
void TimerThread();

#endif