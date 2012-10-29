/*
	MODULE: bufferOut.c

	PURPOSE: Manages all buffer related output.

	AUTHOR: Steffen L. Norgren
			A00683006
*/

#include "terminal.h"

/*
	FUNCTION: OutputBuffer(HWND, char *, DWORD)

	PURPOSE: Send received buffer contents to the window

*/
void OutputBuffer(HWND hWnd, char * lpBuf, DWORD dwBufLen) {
	RECT	rect;
	int		i;

	// Update screen buffer with new buffer
	for (i = 0; i < (int)dwBufLen; i++) {
		switch (lpBuf[i]) {
			case ASCII_BS:	// backspace
				if (COLUMN(TermInfo) > 0) {
					SCREENCHAR(TermInfo, COLUMN(TermInfo) - 1, ROW(TermInfo)) = ' ';
					COLUMN(TermInfo)--;

					// redraw the area
					rect.left = (COLUMN(TermInfo) * XCHAR(TermInfo)) - XOFFSET(TermInfo);
					rect.right = rect.left + XCHAR(TermInfo);
					rect.top = (ROW(TermInfo) * YCHAR(TermInfo)) - YOFFSET(TermInfo);
					rect.bottom = rect.top + YCHAR(TermInfo);
					InvalidateRect(hWnd, &rect, FALSE);
				}
				break;

			case ASCII_CR:	// carriage return
				COLUMN(TermInfo) = 0;
				if (ROW(TermInfo)++ == MAXROWS - 1) {
					MoveMemory((LPSTR)(SCREEN(TermInfo)),
						(LPSTR)(SCREEN(TermInfo) + MAXCOLS), (MAXROWS - 1) * MAXCOLS);
					FillMemory((LPSTR)(SCREEN(TermInfo) + (MAXROWS - 1) * MAXCOLS), MAXCOLS, ' ');
					InvalidateRect(hWnd, NULL, FALSE);
					ROW(TermInfo)--;
				}
				break;

			case ASCII_LF:	// line feed
				COLUMN(TermInfo) = 0;
				if (ROW(TermInfo)++ == MAXROWS - 1) {
					MoveMemory((LPSTR)(SCREEN(TermInfo)),
						(LPSTR)(SCREEN(TermInfo) + MAXCOLS), (MAXROWS - 1) * MAXCOLS);
					FillMemory((LPSTR)(SCREEN(TermInfo) + (MAXROWS - 1) * MAXCOLS), MAXCOLS, ' ');
					InvalidateRect(hWnd, NULL, FALSE);
					ROW(TermInfo)--;
				}
				break;

			default:	// standard characters
				SCREENCHAR(TermInfo, COLUMN(TermInfo), ROW(TermInfo)) = lpBuf[i];

				rect.left = (COLUMN(TermInfo) * XCHAR(TermInfo)) - XOFFSET(TermInfo);
				rect.right = rect.left + XCHAR(TermInfo);
				rect.top = (ROW(TermInfo) * YCHAR(TermInfo)) - YOFFSET(TermInfo);
				rect.bottom = rect.top + YCHAR(TermInfo);
				InvalidateRect(hWnd, &rect, FALSE);

				// Line wrapping
				if (COLUMN(TermInfo) < MAXCOLS - 1) {
					COLUMN(TermInfo)++;
				}
				else {
					SendMessage(hWnd, WM_KEYDOWN, VK_HOME, 1);
					OutputBuffer(hWnd, "\r", 1);
				}
				break;
		}
	}

	MoveCursor(hWnd);
}

/*
	BOOL NEAR MoveCursor(HWND)

	PURPOSE: Moves the caret to the current position

	PARAMETERS:
		hWnd	- Handle to the terminal window

	NOTE: This function does nothing. Couldn't get the caret to
		  work properly with variable width fonts. =(

*/
BOOL NEAR MoveCursor(HWND hWnd) {
//	SetCaretPos((COLUMN(TermInfo) * XCHAR(TermInfo)) - XOFFSET(TermInfo),
//			(ROW(TermInfo) * YCHAR(TermInfo)) - YOFFSET(TermInfo));
	return TRUE;
}