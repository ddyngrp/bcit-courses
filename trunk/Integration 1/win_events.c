/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	win_events.c - A general purpose event handler for menus and dialogs.
--
--	PROGRAM:		music_streamer.exe
--
--	FUNCTIONS:		MenuDispatch(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					Dlg_Main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--
--	DATE:			March 16, 2009
--
--	REVISIONS:		
--
--	DESIGNERS:		Steffen L. Norgren
--
--	PROGRAMMER:		Steffen L. Norgren
--
--	NOTES:	This is a simple menu event handler. It responds to user menu and dialog
--			selections and takes appropriate action depending on the user's input.
--			Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include "win_main.h"
#include "resource.h"
static int busyFlag = 0;
WAVEFORMATEX pwfx;
HWAVEOUT hwo;

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	MenuDispatch
-- 
--	DATE:		March 16, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	MenuDispatch(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hWnd:		Window handle
--					UINT message:	Window message
--					WPARAM wParam:	Window message parameter (depends on message)
--					LPARAM lParam:	Window message parameter (depends on message)
-- 
--	RETURNS:	0:	the message was processed
--				!0:	the message was not processed and passed to DefWindowProc
-- 
--	NOTES:	This function simply deals with menu events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
BOOL CALLBACK MenuDispatch(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	switch (LOWORD(wParam)) {
		// File Menu
		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return FALSE;
		
		default:
			// No action necessary
			return TRUE;
	}
	return TRUE;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	Dlg_Main
-- 
--	DATE:		March 16, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	Dlg_Main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hDlg:		Dialogue handle
--					UINT message:	Dialogue message
--					WPARAM wParam:	Dialogue message parameter (depends on message)
--					LPARAM lParam:	Dialogue message parameter (depends on message)
-- 
--	RETURNS:	0:	the message was processed
--				!0:	the message was not processed and passed to DefWindowProc
-- 
--	NOTES:	This function simply deals with dialogue events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
BOOL CALLBACK Dlg_Main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_INITDIALOG:
			return FALSE;

		case WM_SETFOCUS:
			break;

		case WM_COMMAND: // Process user input
			switch (LOWORD(wParam)) {
				// Buttons
				default:
					return FALSE;
			}
			return TRUE;
	}
	return FALSE;
}
