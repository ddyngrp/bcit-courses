#ifndef _WINMAIN_H_
#define _WINMAIN_H_

// Global Definitions
#define X_SIZE		640
#define Y_SIZE		360

// Global Variables
HINSTANCE		ghInst;				// Main application's global instance
HWND			ghWndMain;			// Main window's global handle
HACCEL			ghAccel;			// Keyboard accelerator
HWND			ghWndOutput;		// The output dialog
HWND			ghWndInput_Host,	// Host name input dialog
				ghWndInput_IP,		// IP input dialog
				ghWndInput_Port,	// Port input dialog
				ghWndInput_Service;	// Service input dialog

// Global Functions
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Input_Host(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Input_IP(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Input_Port(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Input_Service(HWND, UINT, WPARAM, LPARAM);
void MenuDispatch(UINT, HWND, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();
void OutputText(LPCTSTR);
void ClearOutput();

#endif