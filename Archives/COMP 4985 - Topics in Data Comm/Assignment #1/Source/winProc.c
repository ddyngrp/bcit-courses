/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	winProc.c -   Handles the program's main window and associated events
--
--	PROGRAM:		winsock_tool.exe
--
--	FUNCTIONS:		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
--					CreateChildWindows(HWND hWnd)
--					PaintWindow(HWND hWnd)
--					OutputText(LPCTSTR pszText)
--					ClearOutput()
--
--
--	DATE:			January 26, 2009
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

#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "winMain.h"
#include "wsTools.h"

// Private function prototypes
int NEAR PaintWindow(HWND);
void CreateChildWindows(HWND);


/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	WndProc
-- 
--	DATE:		January 26, 2009
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
			CreateChildWindows(hWnd);
			break;

		case WM_DESTROY: // window is closed
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // menu commands
			MenuDispatch(LOWORD(wParam), hWnd, lParam);
			break;

		case WM_SIZE: // window is resized
			{
				// Main window size has changed, need to resize child windows
				WORD wTop;
				WORD wHeight;
				WORD wWidth = LOWORD(lParam);

				// Put Window in the middle
				wHeight = HIWORD(lParam);
				wTop = 0;
				MoveWindow(ghWndOutput, 0, wTop, wWidth, wHeight, TRUE);
				MoveWindow(GetDlgItem(ghWndOutput,IDC_OUTPUT), 0, 0, wWidth - 2, wHeight, TRUE);
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
--	FUNCTION:	CreateChildWindows
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	CreateChildWindows(HWND hWnd)
--					HWND hWnd:		Window handle
-- 
--	RETURNS:	void
-- 
--	NOTES:	Creates the child window(s) for this application.
--
---------------------------------------------------------------------------------------*/
void CreateChildWindows(HWND hWnd) {
	// Create our main output dialog, which is part of the main window
	ghWndOutput = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_OUTPUT), hWnd, NULL);

	if (ghWndOutput == NULL) {
		MessageBox(NULL, TEXT("A child window failed to open."), NULL, MB_OK | MB_ICONSTOP);
	}
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

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	OutputText
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	OutputText(LPCTSTR pszText)
--					LPCTSTR pszText:	Long pointer to a string
-- 
--	RETURNS:	void
-- 
--	NOTES:	Outputs text into the main window's dialog box edit control.
--
---------------------------------------------------------------------------------------*/
void OutputText(LPCTSTR pszText) {
	HWND hWndEdit = GetDlgItem(ghWndOutput, IDC_OUTPUT);
	int nLength = Edit_GetTextLength(hWndEdit); 

	Edit_SetSel(hWndEdit, nLength, nLength);
	Edit_ReplaceSel(hWndEdit, pszText);
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	ClearOutput
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	ClearOutput(void)
-- 
--	RETURNS:	void
-- 
--	NOTES:	Clears the text in the main window's dialog box edit control.
--
---------------------------------------------------------------------------------------*/
void ClearOutput() {
	SetWindowText(GetDlgItem(ghWndOutput, IDC_OUTPUT), NULL);
}