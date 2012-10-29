/* 
* File:   printing.c
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#include <windows.h>
#include "main.h"
#include "printing.h"

// prints a character to the screen
void printChar(HWND hwnd, wndInfo *wInfo, TCHAR c) {
	HDC hdc;
	int j, k;
	TCHAR * tmpBuffer;	// where the actual information is stored
	switch (c)	{ // Attempt to identify specific character
		case '\b':	// backspace
			// Do Nothing
			break;	// done

		case '\t':                    // tab
			do {	// add 8 spaces
				SendMessage (hwnd, WM_CHAR, ' ', 1);	// add one of the spaces
			}
			while (wInfo->xCaret % 8 != 0);
			break;	// done

		case '\n':	// line feed
				// Nothing needs to be done, because windows always follows a '\n' with a '\r'
			break;	// done

		case '\r':	// carriage return
			wInfo->xCaret = 0;//reset the caret

			if (++wInfo->yCaret == wInfo->cyBuffer) {	// check if caret is on the last line
				wInfo->yCaret = wInfo->cyBuffer - 1;	// put the caret back on the current line by moving it back 1
				tmpBuffer = wInfo->pBuffer + wInfo->cxBuffer;	// copy pBuffer to tmpBuffer, omiting the first line

				// copy tmpBuffer back to pBuffer (one character at a time)
				for(k = 0; tmpBuffer[k] != '\0'; k++)	// loop through characters in tmpBuffer
					wInfo->pBuffer[k] = tmpBuffer[k];	// send tmpBuffer character to pBuffer

				// Erase last line
				for(j = 0; j < wInfo->cxBuffer; j++)	// loop through last line
					BUFFER(j, wInfo->yCaret) = ' ';		// erase character

				wInfo->cyClient = max(0, wInfo->cyClient - 1);	// set the caret position
				InvalidateRect (hwnd, NULL, FALSE);				// mark the window as dirty
				UpdateWindow(hwnd);								// force the window to be updated (redraw)
			}
			break;	// done

		case '\x1B':	// escape (returns to command mode)
			// No Command Mode Need :)
			break;	// done

		default:	// regular character was hit (alpha-numeric, symbolic, etc)
			BUFFER (wInfo->xCaret, wInfo->yCaret) = c;	// get characters hit

			// HideCaret (hwnd);	// hide the caret (not needed for now)
			hdc = GetDC (hwnd);	// get the Device Context Handler

			SelectObject (hdc, CreateFont (0, 0, 0, 0, 0, 0, 0, 0,	// Get default fixed-pitch font
			wInfo->dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

			TextOut (hdc, wInfo->xCaret * wInfo->cxChar, wInfo->yCaret * wInfo->cyChar,	// print characters
			& BUFFER (wInfo->xCaret, wInfo->yCaret), 1);

			DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT)));	// delete font handler
			ReleaseDC (hwnd, hdc);	// release the Device Context Handler (no longer needed)
			// ShowCaret (hwnd);		// make the caret visible again

			if (++wInfo->xCaret == wInfo->cxBuffer)	// check if we are at the end of the line
			{
				wInfo->xCaret = 0;		// send caret to home position (far left)
				if (++wInfo->yCaret == wInfo->cyBuffer)	// check if we are on the last line
					wInfo->yCaret = 0;	// send caret to top
			}
			break;	// done
	}

	SetCaretPos (wInfo->xCaret * wInfo->cxChar, wInfo->yCaret * wInfo->cyChar);	// move the caret to the next character position
}
void printString(HWND hwnd, wndInfo *wInfo, TCHAR *c) {
	int i;
	for (i=0; c[i] != '\0'; i++) {
		printChar(hwnd, wInfo, c[i]);
	}
}
void printLine(HWND hwnd, wndInfo *wInfo, TCHAR *c) {
	printString(hwnd, wInfo, c);
	printChar(hwnd, wInfo, '\r');
}
