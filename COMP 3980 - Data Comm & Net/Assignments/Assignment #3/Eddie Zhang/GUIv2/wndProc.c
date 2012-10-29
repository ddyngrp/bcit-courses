/*
	MODULE: wndProc.c

	PURPOSE: Handles program's window.

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#include "winMain.h"
#include <windowsx.h>

// Private function prototypes
BOOL NEAR PaintWindow(HWND);
void OpenChildWindows(HWND);

/*
	FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Windows procedure for the main window

	PARAMETERS:
		hWnd	- window handle
		message	- window message
		wParam	- window message parameter (depends on message)
		lParam	- window message parameter (depends on message)

	RETURN:
		If the message was processed, the return value is 0
		If the message was not processed and passed to DefWindowProc
		and the return value depends on the value of that function.

*/
BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE: // case for when the window is created
			OpenChildWindows(hWnd);
			ListBox_AddString(GetDlgItem(ghWndInfoTool, IDC_LST_RFID), TEXT("This is a string of something"));
			break;

		case WM_DESTROY: // case for when the window is closed
			PostQuitMessage(0);
			break;

		case WM_SETFOCUS: // case for when the window gains focus
			break;

		case WM_KILLFOCUS: // case for when the window focus is lost
			break;

		case WM_COMMAND: // case for menu commands
			MenuDispatch(LOWORD(wParam), hWnd, lParam);
			break;

		case WM_SIZE: { // case for when the window is resized
			// Main window size has changed, need to resize child windows
				WORD wTop;
				WORD wHeight;
				WORD wWidth = LOWORD(lParam);

				// Put Window in the middle
				wHeight = HIWORD(lParam);
				wTop = 0;
				MoveWindow(ghWndInfoTool, 0, wTop, wWidth, wHeight, TRUE);
			}
			break;

		case WM_PAINT:
			PaintWindow(hWnd);
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	FUNCTION: InfoToolProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Windows procedure for the information display window

	PARAMETERS:
		hWnd	- window handle
		message	- window message
		wParam	- window message parameter (depends on message)
		lParam	- window message parameter (depends on message)

	RETURN:
		If the message was processed, the return value is 0
		If the message was not processed and passed to DefWindowProc
		and the return value depends on the value of that function.

*/
BOOL CALLBACK InfoToolProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_DESTROY: // case for when the window is closed
			PostQuitMessage(0);
			break;

		case WM_SETFOCUS: // case for when the window gains focus
			break;

		case WM_KILLFOCUS: // case for when the window focus is lost
			break;

		case WM_COMMAND: { // case for menu commands
			switch(LOWORD(wParam)) {
				case IDC_BTN_START:
					ListBox_AddString(GetDlgItem(ghWndInfoTool, IDC_LST_RFID), TEXT("Pushed the Start Button!"));
					break;
				default:
					break;
			}
			}
			break;

		case WM_SIZE:
			break;

		case WM_PAINT:
			PaintWindow(hWnd);
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	FUNCTION: OpenChildWindows(HWND)

	PURPOSE: Creates the child window

	PARAMETERS:
		hWnd	- Handle to the window

*/
void OpenChildWindows(HWND hWnd) {
	ghWndInfoTool = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DLG_INFOTOOL), hWnd, InfoToolProc);

	if (ghWndInfoTool == NULL) {
		MessageBox(NULL, "The child window failed to open.", NULL, MB_OK | MB_ICONSTOP);
	}

	return;
}

/*
	FUNCTION: PaintWindow(HWND)

	PURPOSE: Paints the rectangle determined by the paint struct of the DC.

	PARAMETERS:
		hWnd	- Handle to the window

*/
BOOL NEAR PaintWindow(HWND hWnd) {
	PAINTSTRUCT	ps;
	HFONT		hOldFont;
	RECT		rect;
	HDC			hDC;

	hDC = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);

	return TRUE;
}