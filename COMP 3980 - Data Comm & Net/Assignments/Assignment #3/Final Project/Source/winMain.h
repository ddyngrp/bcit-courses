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
#define Y_SIZE		360
#define NUMBEROFPORTS 9

// Global Variables
HINSTANCE		ghInst;			// Main application's global instance
HWND			ghWndMain;		// Main window's global handle
HWND			ghWndInfoTool;	// Our main information display area
HACCEL			ghAccel;		// Keyboard accelerator

// Global Functions
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
int CALLBACK InfoToolProc(HWND, UINT, WPARAM, LPARAM);
void MenuDispatch(int, HWND, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();
int insertString(char* str);
void CheckAvailPorts(HWND hwnd);
void CommProperties(HWND hwnd, LPTSTR CommPort);
int CreateReadThread(HWND hwnd);

#endif