/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	winProc.c -   Handles the program's main window and associated events
--
--	PROGRAM:		datagram_analyzer.exe
--
--	FUNCTIONS:		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
--					InitWindow(HWND hWnd)
--					PaintWindow(HWND hWnd)
--
--
--	DATE:			January 26, 2009
--
--	REVISIONS:		February 20, 2009 - Modified for use in new program.
--
--	DESIGNERS:		Steffen L. Norgren
--
--	PROGRAMMER:		Steffen L. Norgren
--
--	NOTES:	This is a simple menu event handler. It responds to user menu selections
--			and takes appropriate action depending on the user's selection.
--			Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "winMain.h"

// Private function prototypes
int NEAR PaintWindow(HWND);
void InitWindow(HWND);


/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	WndProc
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	February 20, 2009 - Modified for use in new program.
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hWnd:		Window handle
--					UINT message:	Window message
--					WPARAM wParam:	Window message parameter (depends on message)
--					LPARAM lParam:	Window message parameter (depends on message)
-- 
--	RETURNS:	0: If message was processed
--				Otherwise it will return the value of DefWindowProc
-- 
--	NOTES:	Windows procedure for the main window.
--
---------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		case WM_CREATE: // window is created
			InitWindow(hWnd);
			break;

		case WM_DESTROY: // window is closed
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // menu commands
			MenuDispatch(LOWORD(wParam), hWnd, lParam);
			break;

		case WM_SIZE: // window is resized
			break;

		case WM_PAINT:
			PaintWindow(hWnd);
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		default:
			return (int)DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	InitWindow
-- 
--	DATE:		February 20, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	InitWindow(HWND hWnd)
--					HWND hWnd:		Window handle
-- 
--	RETURNS:	void
-- 
--	NOTES:	Initializes window settings, such as menu items, dialogues, enabled/disabled
--			items.
--
---------------------------------------------------------------------------------------*/
void InitWindow(HWND hWnd) {
	HMENU hMenu;

	hMenu = GetMenu(hWnd);

	// Initialize default settings
	mode = CLIENT;
	proto = TCP;

	// Disable the Connect/Disconnect Menu items
	EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_DISABLED | MF_GRAYED);
	EnableMenuItem(hMenu, ID_FILE_DISCONNECT, MF_DISABLED | MF_GRAYED);

	// Set Operation mode to client and protocol to TCP
	CheckMenuItem(hMenu, ID_OPERATIONMODE_CLIENT, MF_CHECKED);
	CheckMenuItem(hMenu, ID_PROTOCOL_TCP, MF_CHECKED);
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	PaintWindow
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	PaintWindow(HWND hWnd)
--					HWND hWnd:		Window handle
-- 
--	RETURNS:	void
-- 
--	NOTES:	Paints the rectangle determined by the paint struct of the DC.
--
---------------------------------------------------------------------------------------*/
int NEAR PaintWindow(HWND hWnd) {
	PAINTSTRUCT	ps;
	HDC			hDC;

	hDC = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);

	return TRUE;
}