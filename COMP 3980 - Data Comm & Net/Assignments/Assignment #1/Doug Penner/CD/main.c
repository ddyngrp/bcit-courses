/* 
* File:   main.c
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#include <windows.h>
#include "main.h"
#include "resource.h"
#include "serial.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)	// creates the windows, taking the application handler, parent application handler, application name and visual specifications
{
	static TCHAR szAppName[] = TEXT ("DataComm Assignment 1");	// Application Name
	HWND         hwnd;		// window handlers for the 4 different windows.
	MSG          msg;		// message information for thread's message queue
	WNDCLASS     wndclass;	// Window class
	HMENU hmenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

	wndclass.style         = CS_HREDRAW | CS_VREDRAW;	// window class style (paint on vertical and horizontal redraw)
	wndclass.lpfnWndProc   = WndProc;					// pointer to window procedure (wndproc)
	wndclass.cbClsExtra    = 0;							// extra class memory (Not Used)
	wndclass.cbWndExtra    = sizeof(wndInfo *);			// extra class instance memory (holds pointer to struct)
	wndclass.hInstance     = hInstance;					// Window instance handler
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION);			// Icon handler (using application default)
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);				// Cursor handler (using arrow default)
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);		// Background Brush Handler (for erasing)
	wndclass.lpszMenuName  = TEXT("MYMENU");	// Menu Class name
	wndclass.lpszClassName = szAppName;			// Application Name (defined above)

	if (!RegisterClass (&wndclass))	// Register window class with operating system
	{
		MessageBox (NULL, TEXT ("This program requires Windows NT!"), szAppName, MB_ICONERROR);	// alert the user that the application requires Windows NT
		return 0;	// Quit!
	}

	hwnd = CreateWindow (szAppName, TEXT ("Dumb Terminal"),	// Create window (with class name)
		WS_OVERLAPPEDWINDOW,	// window name (using default)
		0, 0,					// Position (x,y)
		500, 500,	// Size(W,H)
		NULL,		// parent window
		hmenu,		// menu
		hInstance,	// instance handler
		NULL);		// lParam

	ShowWindow (hwnd, iCmdShow);	// Show window
	UpdateWindow (hwnd);	// Update window

	while (GetMessage (&msg, NULL, 0, 0))	// Start message catching loop
	{
		TranslateMessage (&msg);	// Translate message to make it usable
		DispatchMessage (&msg);	// Pass message back to OS for redistribution
	}
	return msg.wParam;	// Quit!
}
