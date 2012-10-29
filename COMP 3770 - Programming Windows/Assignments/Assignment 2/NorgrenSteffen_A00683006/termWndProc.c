/*
	MODULE: termWndProc.c

	PURPOSE: Handles program's window and menu management.

	AUTHOR: Steffen L. Norgren
			A00683006
*/

#include "terminal.h"

// Function prototypes
void MenuDispatch(int, HWND, LPARAM);
BOOL NEAR ScrollVert(HWND, WORD, WORD);
BOOL NEAR ScrollHorz(HWND, WORD, WORD);
BOOL NEAR PaintWindow(HWND);
BOOL NEAR ResizeTerm(HWND, WORD, WORD);

/*------------------------------------------------------------------------------
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

/*-----------------------------------------------------------------------------*/
int WINAPI TermWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE: // case for when the window is created
			InitTermInfo();	// Initialize the terminal
			//CreateCaret(hWnd, NULL, XCHAR(TermInfo), YCHAR(TermInfo));
			//ShowCaret(hWnd);
			break;

		case WM_DESTROY: // case for when the window is closed
			DestroyTermInfo();
			PostQuitMessage(0);
			break;

		case WM_SETFOCUS: // case for when the window gains focus
			MoveCursor(hWnd);
			//ShowCaret(hWnd);
			break;

		case WM_KILLFOCUS: // case for when the window focus is lost
			//HideCaret(hWnd);
			break;

		case WM_COMMAND: // case for menu commands
			MenuDispatch(LOWORD(wParam), hWnd, lParam);
			break;

		case WM_KEYDOWN:
			switch (wParam) {
				case VK_HOME:	// case for when the HOME key is pressed
					COLUMN(TermInfo) = 0;
					ScrollHorz(hWnd, SB_TOP, HIWORD(wParam)); // follow the cursor by moving the scroll bar
					MoveCursor(hWnd);
					break;

				case VK_END:	// case for when the End key is pressed
					COLUMN(TermInfo) = MAXCOLS -3; // stupid scroll bar covering the text
					ScrollHorz(hWnd, SB_BOTTOM, HIWORD(wParam)); // follow the cursor by moving the scroll bar
					MoveCursor(hWnd);
					break;

				case VK_PRIOR:	// case for when the PageUp key is pressed
					if (ROW(TermInfo) - (YSIZE(TermInfo) / YCHAR(TermInfo)) < 0) {
						ROW(TermInfo) = 0;
						COLUMN(TermInfo) = 0;
					}
					else {
						ROW(TermInfo) = ROW(TermInfo) - (YSIZE(TermInfo) / YCHAR(TermInfo));
						COLUMN(TermInfo) = 0;
					}
					ScrollVert(hWnd, SB_PAGEUP, HIWORD(wParam)); // follow the cursor by moving the scroll bar
					MoveCursor(hWnd);
					break;

				case VK_NEXT:	// case for when the PageDown key is pressed
					if (ROW(TermInfo) + (YSIZE(TermInfo) / YCHAR(TermInfo)) > MAXROWS - 1) {
						ROW(TermInfo) = MAXROWS - 1;
						COLUMN(TermInfo) = 0;
					}
					else {
						ROW(TermInfo) = ROW(TermInfo) + (YSIZE(TermInfo) / YCHAR(TermInfo));
						COLUMN(TermInfo) = 0;
					}
					ScrollVert(hWnd, SB_PAGEDOWN, HIWORD(wParam)); // follow the cursor by moving the scroll bar
					MoveCursor(hWnd);
					break;

				case VK_LEFT:	// case for when the left arrow is pressed
					ScrollHorz(hWnd, SB_LINEUP, HIWORD(wParam));
					break;

				case VK_RIGHT:	// case for when the right arrow is pressed
					ScrollHorz(hWnd, SB_LINEDOWN, HIWORD(wParam));
					break;

				case VK_UP:		// case for when the up arrow is pressed
					ScrollVert(hWnd, SB_LINEUP, HIWORD(wParam));
					break;

				case VK_DOWN:	// case for when the down arrow is pressed
					ScrollVert(hWnd, SB_LINEDOWN, HIWORD(wParam));
					break;

				default:
					break;
			}

			break;

		case WM_CHAR: // when stuff is typed
			switch (wParam) {
				case '\r': // carriage return 
					OutputBuffer(ghWnd, (CHAR *)&wParam, 1);
					ScrollHorz(hWnd, SB_TOP, HIWORD(wParam)); // reset the horizontal scrollbar
					ResizeTerm(hWnd, LOWORD(lParam), HIWORD(lParam));
					break;

				case '\n': // line feed
					OutputBuffer(ghWnd, (CHAR *)&wParam, 1);
					ScrollHorz(hWnd, SB_TOP, HIWORD(wParam)); // reset the horizontal scrollbar
					ResizeTerm(hWnd, LOWORD(lParam), HIWORD(lParam));
					break;

				case '\t': // tab
					OutputBuffer(ghWnd, "    ", 4);
					ResizeTerm(hWnd, LOWORD(lParam), HIWORD(lParam));
					break;

				default:
					OutputBuffer(ghWnd, (CHAR *)&wParam, 1);
					ResizeTerm(hWnd, LOWORD(lParam), HIWORD(lParam));
					break;
			}
			break;

		case WM_SIZE: // case for when the window is resized
			ResizeTerm(hWnd, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_VSCROLL: // when the vertical scrollbar is moved
			ScrollVert(hWnd, LOWORD(wParam), HIWORD(wParam));
			break;

		case WM_HSCROLL: // when the horizontal scrollbar is moved
			ScrollHorz(hWnd, LOWORD(wParam), HIWORD(wParam));
			break;

		case WM_PAINT:
			PaintWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	FUNCTION: MenuDispatch(int, HWND, LPARAM)

	PURPOSE: Responds to menu selections

	PARAMETERS:
		iMenuChoice	- ID of the menu choice (from resource file)
		hWnd		- window handle of menu owner
		lParam		- window message parameter (depends on message)

*/
void MenuDispatch(int iMenuChoice, HWND hWnd, LPARAM lParam) {
	CHOOSEFONT	cf = {0};
	LOGFONT		lf;

	switch (iMenuChoice) {
		case ID_FILE_CONNECT:
			break;

		case ID_FILE_DISCONNECT:
			break;

		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		case ID_EDIT_FONT:
			lf = LFSCREENFONT(TermInfo);

			cf.lStructSize		= sizeof(CHOOSEFONT);
			cf.hwndOwner		= hWnd;
			cf.lpLogFont		= &lf;
			cf.Flags			= CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_EFFECTS;
			cf.rgbColors		= FGCOLOUR(TermInfo);

			if(!ChooseFont(&cf)) {
				// We need to recreate the caret
				//HideCaret(hWnd);
				//DestroyCaret();
				//CreateCaret(hWnd, NULL, XCHAR(TermInfo), YCHAR(TermInfo));
				//ShowCaret(hWnd);
				MoveCursor(hWnd);
				break;
			}

			InitNewFont(lf, cf.rgbColors);

			// Fix scroll bar sizes since we have a new font
			ResizeTerm(hWnd, (WORD)XSIZE(TermInfo), (WORD)YSIZE(TermInfo));
			InvalidateRect(hWnd, NULL, TRUE);

			// We need to recreate the caret
			//HideCaret(hWnd);
			//DestroyCaret();
			//CreateCaret(hWnd, NULL, XCHAR(TermInfo), YCHAR(TermInfo));
			//ShowCaret(hWnd);
			MoveCursor(hWnd);

			break;

		case ID_VIEW_CLEARSCREEN:
			ClearScreen();
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_HELP_ABOUT:
			MessageBox(hWnd, "COMP 3770 - Assignment #2\n\nAuthor:\tSteffen L. Norgren\nSet F\tA00683006",
				"About Terminal", MB_OK | MB_ICONINFORMATION);
			break;
	}
	return;
}

/*
	BOOL NEAR ScrollVert(HWND, WORD, WORD)

	PURPOSE: Scrolls the terminal window vertically

	PARAMETERS:
		hWnd		- Handle to the terminal window
		wScrollCmd	- The type of scrolling we're doing
		wScrollPos	- The scroll bar's position
*/
BOOL NEAR ScrollVert(HWND hWnd, WORD wScrollCmd, WORD wScrollPos) {
	int nScrollAmount;

	switch (wScrollCmd) {
		case SB_TOP: // moved to the top
			nScrollAmount = -YOFFSET(TermInfo);
			break;

		case SB_BOTTOM: // moved to the bottom
			nScrollAmount = YSCROLL(TermInfo) - YOFFSET(TermInfo);
			break;

		case SB_PAGEUP: // moved up by a page
			nScrollAmount = -YSIZE(TermInfo);
			break;

		case SB_PAGEDOWN: // moved down by a page
			nScrollAmount = YSIZE(TermInfo);
			break;

		case SB_LINEUP:	// move up a line
			nScrollAmount = -YCHAR(TermInfo);
			break;

		case SB_LINEDOWN: // move down a line
			nScrollAmount = YCHAR(TermInfo);
			break;

		case SB_THUMBPOSITION: // manually positioned
			nScrollAmount = wScrollPos - YOFFSET(TermInfo);
			break;

		default:
			return FALSE;
	}

	// if it reported a scroll amount that is larger the buffer
	if ((YOFFSET(TermInfo) + nScrollAmount) > YSCROLL(TermInfo)) {
		nScrollAmount = YSCROLL(TermInfo) - YOFFSET(TermInfo);
	}

	// if scrolling offset becomes less than zero
	if ((YOFFSET(TermInfo) + nScrollAmount) < 0) {
		nScrollAmount = -YOFFSET(TermInfo);
	}

	ScrollWindowEx(hWnd, 0, -nScrollAmount, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE);

	YOFFSET(TermInfo) = YOFFSET(TermInfo) + nScrollAmount;

	SetScrollPos(hWnd, SB_VERT, YOFFSET(TermInfo), TRUE);

	// We're displaying a character at a time, so we need to call this again... =(
	ResizeTerm(hWnd, (WORD)XSIZE(TermInfo), (WORD)YSIZE(TermInfo));

	return TRUE;
}

/*
	BOOL NEAR ScrollHorz(HWND, WORD, WORD)

	PURPOSE: Scrolls the terminal window horizontally

	PARAMETERS:
		hWnd		- Handle to the terminal window
		wScrollCmd	- The type of scrolling we're doing
		wScrollPos	- The scroll bar's position
*/
BOOL NEAR ScrollHorz(HWND hWnd, WORD wScrollCmd, WORD wScrollPos) {
	int nScrollAmount;

	switch (wScrollCmd) {
		case SB_TOP: // moved to the top
			nScrollAmount = -XOFFSET(TermInfo);
			break;

		case SB_BOTTOM: // moved to the bottom
			nScrollAmount = XSCROLL(TermInfo) - XOFFSET(TermInfo);
			break;

		case SB_PAGEUP: // moved up by a page
			nScrollAmount = -XSIZE(TermInfo);
			break;

		case SB_PAGEDOWN: // moved down by a page
			nScrollAmount = XSIZE(TermInfo);
			break;

		case SB_LINEUP:	// move up a line
			nScrollAmount = -XCHAR(TermInfo);
			break;

		case SB_LINEDOWN: // move down a line
			nScrollAmount = XCHAR(TermInfo);
			break;

		case SB_THUMBPOSITION: // manually positioned
			nScrollAmount = wScrollPos - XOFFSET(TermInfo);
			break;

		default:
			return FALSE;
	}

	// if it reported a scroll amount that is larger the buffer
	if ((XOFFSET(TermInfo) + nScrollAmount) > XSCROLL(TermInfo)) {
		nScrollAmount = XSCROLL(TermInfo) - XOFFSET(TermInfo);
	}

	// if scrolling offset becomes less than zero
	if ((XOFFSET(TermInfo) + nScrollAmount) < 0) {
		nScrollAmount = -XOFFSET(TermInfo);
	}

	ScrollWindowEx(hWnd, -nScrollAmount, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE);

	XOFFSET(TermInfo) = XOFFSET(TermInfo) + nScrollAmount;

	SetScrollPos(hWnd, SB_HORZ, XOFFSET(TermInfo), TRUE);

	// We're displaying a character at a time, so we need to call this again... =(
	ResizeTerm(hWnd, (WORD)XSIZE(TermInfo), (WORD)YSIZE(TermInfo));

	return TRUE;
}

/*
	BOOL NEAR PaintWindow(HWND)

	PURPOSE: Paints the rectangle determined by the paint struct of the DC.

	PARAMETERS:
		hWnd	- Handle to the terminal window

*/
BOOL NEAR PaintWindow(HWND hWnd) {
	PAINTSTRUCT	ps;
	HFONT		hOldFont;
	RECT		rect;
	HDC			hDC;
	int			nRow, nCol, nEndRow, nEndCol,
				nCount, nHorzPos, nVertPos, i;

	hDC = BeginPaint(hWnd, &ps);
	hOldFont = SelectObject(hDC, HSCREENFONT(TermInfo));
	SetTextColor(hDC, FGCOLOUR(TermInfo));
	SetBkColor(hDC, BGCOLOUR(TermInfo));
	
	rect = ps.rcPaint;

	// Define our painting regions
	nRow	= min(MAXROWS - 1, max(0, (rect.top + YOFFSET(TermInfo)) / YCHAR(TermInfo)));
	nEndRow	= min(MAXROWS -1, ((rect.bottom + YOFFSET(TermInfo) - 1) / YCHAR(TermInfo)));
	nCol	= min(MAXCOLS - 1, max(0, (rect.left + XOFFSET(TermInfo)) / XCHAR(TermInfo)));
	nEndCol	= min(MAXCOLS - 1, ((rect.right + XOFFSET(TermInfo) -1) / XCHAR(TermInfo)));
	nCount = nEndCol - nCol + 1;

	// Cycle through our buffer to paint the window
	for ( ; nRow <= nEndRow; nRow++) {
		nVertPos = (nRow * YCHAR(TermInfo)) - YOFFSET(TermInfo);
		nHorzPos = (nCol * XCHAR(TermInfo)) - XOFFSET(TermInfo);
		rect.top = nVertPos;
		rect.bottom = nVertPos + YCHAR(TermInfo);
		rect.left = nHorzPos;
		rect.right = nHorzPos + XCHAR(TermInfo) * nCount;
		SetBkMode(hDC, OPAQUE);
		ExtTextOut(hDC, nHorzPos, nVertPos, ETO_OPAQUE | ETO_CLIPPED, &rect,
			(LPSTR)(SCREEN(TermInfo) + nRow * MAXCOLS + nCol), nCount, NULL);
	}

	SelectObject(hDC, hOldFont);
	EndPaint(hWnd, &ps);
	MoveCursor(hWnd);

	return TRUE;
}

/*
	BOOL NEAR ResizeTerm(HWND, WORD, WORD)

	PURPOSE: Resizes the terminal window and sets up the scrolling regions

	PARAMETERS:
		hWnd	- Handle to the terminal window
		wWidth	- New horizontal size
		wHeight	- New vertical size

*/
BOOL NEAR ResizeTerm(HWND hWnd, WORD wWidth, WORD wHeight) {
	int nScrollAmount;

	// Adjust the vertical settings
	YSIZE(TermInfo) = (int)wHeight;
	YSCROLL(TermInfo) = max(0, (MAXROWS * YCHAR(TermInfo)) - YSIZE(TermInfo));
	nScrollAmount = min(YSCROLL(TermInfo), YOFFSET(TermInfo)) - YOFFSET(TermInfo);
	ScrollWindow(hWnd, 0, -nScrollAmount, NULL, NULL);

	YOFFSET(TermInfo) = YOFFSET(TermInfo) + nScrollAmount;
	SetScrollPos(hWnd, SB_VERT, YOFFSET(TermInfo), FALSE);
	SetScrollRange(hWnd, SB_VERT, 0, YSCROLL(TermInfo), TRUE);

	// Adjust horizontal settings
	XSIZE(TermInfo) = (int)wWidth;
	XSCROLL(TermInfo) = max(0, (MAXCOLS * XCHAR(TermInfo)) - XSIZE(TermInfo));
	nScrollAmount = min(XSCROLL(TermInfo), XOFFSET(TermInfo)) - XOFFSET(TermInfo);
	ScrollWindow(hWnd, 0, nScrollAmount, NULL, NULL);

	XOFFSET(TermInfo) = XOFFSET(TermInfo) + nScrollAmount;
	SetScrollRange(hWnd, SB_HORZ, 0, XSCROLL(TermInfo), FALSE);
	SetScrollPos(hWnd, SB_HORZ, XOFFSET(TermInfo), TRUE);

	InvalidateRect(hWnd, NULL, FALSE); // redraw the entire window

	return TRUE;
}