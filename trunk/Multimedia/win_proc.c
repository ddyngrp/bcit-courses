/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	winProc.c -   Handles the program's main window and associated events
--
--	PROGRAM:		music_streamer.exe
--
--	FUNCTIONS:		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
--					InitWindow(HWND hWnd)
--					PaintWindow(HWND hWnd)
--
--
--	DATE:			March 16, 2009
--
--	REVISIONS:		
--
--	DESIGNERS:		Steffen L. Norgren
--
--	PROGRAMMER:		Steffen L. Norgren
--
--	NOTES:	This is a simple menu event handler. It responds to user menu selections
--			and takes appropriate action depending on the user's selection.
--			Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include "win_main.h"
#include "resource.h"


// Private function prototypes
int NEAR PaintWindow(HWND);
void InitWindow(HWND);


/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	WndProc
-- 
--	DATE:		March 16, 2009
-- 
--	REVISIONS:	
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
            fileInit(hWnd);
			break;

		case WM_DESTROY: // window is closed
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // menu commands
			MenuDispatch(hWnd, message, wParam, lParam);
			break;

		case WM_SIZE: // window is resized
			{
				// Main window size has changed, need to resize child windows
				WORD wTop = 0;
				WORD wHeight = HIWORD(lParam);
				WORD wWidth = LOWORD(lParam);
				RECT wRect;

				GetWindowRect(ghWndMain, &wRect);

				// Put Window in the middle
				MoveWindow(ghDlgMain, 0, wTop, wWidth, wHeight, TRUE);
			}
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
--	DATE:		March 16, 2009
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
	// Create our main output dialog, which is part of the main window
	ghDlgMain =  CreateDialog(ghInst, MAKEINTRESOURCE(IDD_MAIN), hWnd, Dlg_Main);

	if (ghDlgMain == NULL) {
		MessageBox(hWnd, TEXT("Failed to create ghDlgMain!"), NULL, MB_OK | MB_ICONSTOP);
	}
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	PaintWindow
-- 
--	DATE:		March 16, 2009
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