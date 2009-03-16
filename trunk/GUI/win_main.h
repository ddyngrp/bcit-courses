#ifndef _WIN_MAIN_H_
#define _WIN_MAIN_H_

#include <windows.h>
#include <windowsx.h>

// Global Definitions
#define X_SIZE		380
#define Y_SIZE		240
#define X_MIN_SIZE	450
#define Y_MIN_SIZE	200

// Global Variables
HINSTANCE		ghInst;				// Main application's global instance
HWND			ghWndMain,			// Main window's global handle
				ghDlgMain;			// Main dialogue window's global handle
HACCEL			ghAccel;			// Keyboard accelerator

// Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MenuDispatch(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlg_Main(HWND, UINT, WPARAM, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();

#endif