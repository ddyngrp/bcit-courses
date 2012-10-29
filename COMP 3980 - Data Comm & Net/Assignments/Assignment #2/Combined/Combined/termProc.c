/*
	MODULE: termWndProc.c

	PURPOSE: Handles program's window and menu management.

	AUTHORS: Steffen L. Norgren
			 Doug Penner
*/

#include "terminal.h"

// Private function prototypes
BOOL NEAR PaintWindow(HWND);
void OpenTermWindow(HWND);

/*
	FUNCTION: TermWndProc(HWND, UINT, WPARAM, LPARAM)

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
int WINAPI TermWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE: // case for when the window is created
			InitTermInfo();	// Initialize the terminal
			InitTTYInfo();	// Initialize TTY default settings
			OpenTermWindow(hWnd);
			SetFocus(ghWndTerm);
			break;

		case WM_DESTROY: // case for when the window is closed
			DestroyTermInfo();
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // case for menu commands
			MenuDispatch(LOWORD(wParam), hWnd, lParam);
			break;

		case WM_KEYDOWN: // when a key is pressed
			SendMessage(ghWndTerm, WM_KEYDOWN, wParam, lParam);
			break;

		case WM_CHAR: // when stuff is typed
			SendMessage(ghWndTerm, WM_CHAR, wParam, lParam);
			break;

		case WM_SIZE:
			{ // case for when the window is resized
			// Main window size has changed, need to resize child windows
				WORD wTop;
				WORD wHeight;
				WORD wWidth = LOWORD(lParam);

				wHeight = gwBaseY;
				wTop = 0;
				
				// Put Terminal Window in the middle
				wHeight = HIWORD(lParam);
				wTop = gwBaseY;
				MoveWindow(ghWndTerm, 0, wTop, wWidth, wHeight, TRUE);
			}
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		default:
			return (int)DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	FUNCTION: TermChildProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Windows procedure for the terminal child window

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
int WINAPI TermChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	char esc = 27;
	char action;

	switch (message) {
		case WM_SETFOCUS: // case for when the window gains focus
			CreateCaret(hWnd, (HBITMAP)1, XCHAR(TermInfo), YCHAR(TermInfo));
			SetCaretPos(COLUMN(TermInfo) * XCHAR(TermInfo), ROW(TermInfo) * YCHAR(TermInfo));
			ShowCaret(hWnd);
			break;

		case WM_KILLFOCUS: // case for when the window focus is lost
			break;

		case WM_MOUSEACTIVATE: // when the mouse moves into this window
			SetFocus(hWnd);
			return MA_ACTIVATE;
			break;

		case WM_KEYDOWN: // when a key is pressed
			switch (wParam) {
				case VK_UP:
					action = 'A';
					commSendString(&esc);
					commSendString(&action);
					break;

				case VK_DOWN:
					action = 'B';
					commSendString(&esc);
					commSendString(&action);
					break;

				case VK_LEFT:
					action = 'D';
					commSendString(&esc);
					commSendString(&action);
					break;

				case VK_RIGHT:
					action = 'C';
					commSendString(&esc);
					commSendString(&action);
					break;
			}
			break;

		case WM_CHAR: // when stuff is typed
			commSendChar((char)LOWORD(wParam));
			break;

		case WM_SIZE: // case for when the window is resized
			ResizeTerm(hWnd);
			break;

		case WM_PAINT:
			SetCaretPos(COLUMN(TermInfo) * XCHAR(TermInfo), ROW(TermInfo) * YCHAR(TermInfo));
			PaintWindow(hWnd);
			break;

		default:
			return (int)DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
/*
	FUNCTION: OpenTermWindow(HWND)

	PURPOSE: Creates the terminal child window

	PARAMETERS:
		hWnd	- Handle to the terminal window

*/
void OpenTermWindow(HWND hWnd) {
	ghWndTerm = CreateWindow("TermChildClass", "Terminal Window",
		WS_CHILD | WS_VISIBLE,
		0, 0,
		0, 0,
		hWnd, (HMENU)IDR_MENU, ghInst, NULL);

	return;
}

/*
	FUNCTION: PaintWindow(HWND)

	PURPOSE: Paints the rectangle determined by the paint struct of the DC.

	PARAMETERS:
		hWnd	- Handle to the terminal window

*/
BOOL NEAR PaintWindow(HWND hWnd) {
	PAINTSTRUCT	ps;
	HFONT		hOldFont, font;
	HDC			hDC;
	int			nRow, nCol;

	//hDC = BeginPaint(hWnd, &ps);
	//hOldFont = SelectObject(hDC, HSCREENFONT(TermInfo));
	//SetTextColor(hDC, FGCOLOUR(TermInfo));
	//SetBkColor(hDC, BGCOLOUR(TermInfo));

	hDC = BeginPaint(hWnd, &ps);
	hOldFont = SelectObject(hDC, HSCREENFONT(TermInfo));
	SetBkMode(hDC, OPAQUE);

	for (nRow = 0; nRow <= MAXROWS; nRow++) {
		for (nCol = 0; nCol <= MAXCOLS; nCol++) {
			if (FORMATCODE(TermInfo, nRow, nCol) & FORMAT_UL) {
				LFSCREENFONT(TermInfo).lfUnderline = 1;
				font = CreateFontIndirect(&LFSCREENFONT(TermInfo));
				SelectObject(hDC, font);

				FormatOutput(hDC, FORMATCODE(TermInfo, nRow, nCol));
				ExtTextOut(hDC, nCol * XCHAR(TermInfo), nRow * YCHAR(TermInfo), ETO_OPAQUE | ETO_CLIPPED, NULL,
					&SCREENCHAR(TermInfo, nRow, nCol), 1, NULL);

				DeleteObject(font);
				LFSCREENFONT(TermInfo).lfUnderline = 0;
				font = CreateFontIndirect(&LFSCREENFONT(TermInfo));
				SelectObject(hDC, font);
				DeleteObject(font);
			}
			else {
				FormatOutput(hDC, FORMATCODE(TermInfo, nRow, nCol));
				ExtTextOut(hDC, nCol * XCHAR(TermInfo), nRow * YCHAR(TermInfo), ETO_OPAQUE | ETO_CLIPPED, NULL,
					&SCREENCHAR(TermInfo, nRow, nCol), 1, NULL);
			}
		}
	}

	SelectObject(hDC, hOldFont);
	EndPaint(hWnd, &ps);
	ReleaseDC(hWnd, hDC);

	return TRUE;
}

/*
	FUNCTION: ResizeTerm(HWND, WORD, WORD)

	PURPOSE: Resizes the terminal window upon any change in font size.

	PARAMETERS:
		hWnd	- Handle to the terminal window

*/
BOOL NEAR ResizeTerm(HWND hWnd) {
	RECT rcWindow, rcClient;
	POINT pt, ptDiff;

	GetWindowRect(ghWndMain, &rcWindow);
	GetClientRect(ghWndMain, &rcClient);

	ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;

	pt.x = XSIZE(TermInfo);
	pt.y = YSIZE(TermInfo);

	// Resize the child terminal window
	MoveWindow(hWnd, rcClient.left, rcClient.top, pt.x, pt.y, TRUE);

	// Resize the main terminal window
	MoveWindow(ghWndMain, rcWindow.left, rcWindow.top, pt.x + ptDiff.x, pt.y + ptDiff.y, TRUE);

	InvalidateRect(ghWndMain, NULL, FALSE);
	
	return TRUE;
}