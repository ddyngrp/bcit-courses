#ifndef _WINMAIN_H_
#define _WINMAIN_H_

// Global Definitions
#define X_SIZE		640
#define Y_SIZE		360
#define CLIENT		0
#define	SERVER		1
#define	TCP			0
#define	UDP			1

// Global Variables
HINSTANCE		ghInst;				// Main application's global instance
HWND			ghWndMain;			// Main window's global handle
HACCEL			ghAccel;			// Keyboard accelerator
HWND			ghWndOutput;		// The output dialog
int				mode, proto;		// The program's mode and protocol

// Global Functions
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void MenuDispatch(UINT, HWND, LPARAM);
BOOL CALLBACK Input_IP(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Input_Host(HWND, UINT, WPARAM, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();

#endif