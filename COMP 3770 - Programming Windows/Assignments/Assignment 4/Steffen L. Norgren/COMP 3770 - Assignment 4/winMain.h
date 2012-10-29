/*
	MODULE: winMain.h

	PURPOSE: Contains global definitions and variables

	AUTHORS: Steffen L. Norgren
*/

#ifndef _WINMAIN_H_
#define _WINMAIN_H_

#include <windows.h>

// Global Definitions
#define X_SIZE		800
#define Y_SIZE		600


// Global Variables
HINSTANCE		ghInst;			// Main application's global instance
HWND			ghWndMain;		// Main window's global handle
HACCEL			ghAccel;		// Keyboard accelerator
BOOL			gfCritSects;	// Whether we have synchronization enabled
HANDLE			ghEvent;		// Event to hold the quit message

// Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK RaceProc(HWND, UINT, WPARAM, LPARAM);
void MenuDispatch(UINT, HWND, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();

#endif