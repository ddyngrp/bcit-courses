/*
	MODULE: winMain.h

	PURPOSE: Contains global definitions and variables

	AUTHORS: Steffen L. Norgren
*/

#ifndef _WINMAIN_H_
#define _WINMAIN_H_

#include <windows.h>

// Global Definitions
#define X_SIZE		300
#define Y_SIZE		200


// Global Variables
HINSTANCE		ghInst;			// Main application's global instance
HWND			ghWndMain;		// Main window's global handle

// Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();

#endif