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
#include "resource.h"

// Global Definitions
#define X_SIZE		640
#define Y_SIZE		360
//#define X_SIZE		1280
//#define Y_SIZE		900

// Global Variables
HINSTANCE		ghInst;			// Main application's global instance
HWND			ghWndMain;		// Main window's global handle
HWND			ghWndInfoTool;	// Our main information display area
HACCEL			ghAccel;		// Keyboard accelerator

// Global Functions
BOOL CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK InfoToolProc(HWND, UINT, WPARAM, LPARAM);
void MenuDispatch(int, HWND, LPARAM);

#endif