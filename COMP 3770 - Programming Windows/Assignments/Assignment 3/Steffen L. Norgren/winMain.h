/*
	MODULE: winMain.h

	PURPOSE: Contains global definitions and variables

	AUTHOR: Steffen L. Norgren
*/

#ifndef _WINMAIN_H_
#define _WINMAIN_H_

#include <windows.h>

// Global Definitions
#define X_SIZE		800
#define Y_SIZE		600
#define X_CANVAS	1600
#define Y_CANVAS	1200

// Global Variables
HINSTANCE		ghInst;			// Main application's global instance
HWND			ghWndMain;		// Main window's global handle
HWND			ghWndCanvas;	// Canvas' global handle
HWND			ghWndToolBox;	// Canvas' Tool Box handle
HACCEL			ghAccel;		// Keyboard accelerator

// Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK CanvasProc(HWND, UINT, WPARAM, LPARAM);
void MenuDispatch(UINT, HWND, LPARAM);
BOOL OpenToolBox(HWND);
static void DrawLine(HWND, POINT*, COLORREF, BOOL repaint);
static void DrawRect(HWND, RECT*, COLORREF, BOOL repaint);
BOOL WINAPI EditCopy();
BOOL WINAPI EditPaste();

#endif