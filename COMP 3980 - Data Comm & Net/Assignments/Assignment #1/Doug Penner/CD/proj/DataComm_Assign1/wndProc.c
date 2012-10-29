/* 
* File:   wndProc.c
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#include <windows.h>
#include "main.h"
#include "resource.h"
#include "printing.h"
#include "serial.h"
#include "menu.h"

// WndProc for processing messages from OS.
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)	// Window procedure function, takes window handler, message, and 2 other paramaters (each with different types of informations)
{
	HDC            hdc;			// Device Context Handler
	int            x, y, i;		// temporary variables used for "foor loops"
	PAINTSTRUCT    ps;				// Painst Struct used for painting
	TEXTMETRIC     tm;				// Text Metric (for printing characters)

	wndInfo *wInfo = (wndInfo *)GetWindowLongPtr(hwnd, 0);	// Grab pointer to data structure from window's memory
	switch (message)	// Determine message type
	{
		case WM_CREATE:	// Create Window
			// set basic variables
			hdc = GetDC (hwnd);				// Get Device Context Handler from Window Handler
			wInfo = malloc(sizeof(wndInfo));	// Allocate memory for the data struct
			wInfo->pBuffer = NULL;			// Make sure pBuffer is set to null (instead of a random value)
			wInfo->dwCharSet = DEFAULT_CHARSET;
			SetWindowLongPtr(hwnd, 0, (LONG_PTR)wInfo);	// add wInfo pointer to window memory spot

			// Setup text data
			SelectObject (hdc, CreateFont (0, 0, 0, 0, 0, 0, 0, 0, wInfo->dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));	// Set font (default pixed pith font)
			GetTextMetrics (hdc, &tm);		// Load text metrics for printing text
			wInfo->cxChar = tm.tmAveCharWidth;	// Get width of single character
			wInfo->cyChar = tm.tmHeight;			// Get height of single character
			DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT)));	// UnLoad font

			// set up serial preliminary settings
			commSetVirgin(hwnd, &wInfo->serCon);

			ReleaseDC (hwnd, hdc);	// Release Device Context Handler
			return 0;           
		case WM_SIZE:	// Window was Resized
			// perform size calculations
			wInfo->cxClient = LOWORD (lParam);	// Get window width
			wInfo->cyClient = HIWORD (lParam);	// Get window height
			wInfo->cxBuffer = max (1, wInfo->cxClient / wInfo->cxChar);	// Get window width in characters
			wInfo->cyBuffer = max (1, wInfo->cyClient / wInfo->cyChar);	// Get window height in characters

			// replace pBuffer with new one of proper size
			if (wInfo->pBuffer != NULL)	// Check if pBuffer points to actual data
				free (wInfo->pBuffer);	// free up memory used by pBuffer
			wInfo->pBuffer = (TCHAR *) malloc (wInfo->cxBuffer * wInfo->cyBuffer * sizeof (TCHAR));	// Allocate new memory for pBuffer

			// clear screen
			for (y = 0; y < wInfo->cyBuffer; y++)		// loop through window's rows
				for (x = 0; x < wInfo->cxBuffer; x++)	// loop through characters in row
					BUFFER(x,y) = ' ';						// erase character with a space: ' '

			// reposition caret
			wInfo->xCaret = 0;	// move caret to left of window
			wInfo->yCaret = 0;	// move caret to top of window

			if (hwnd == GetFocus ())	// Check if window has focus
				SetCaretPos (wInfo->xCaret * wInfo->cxChar, wInfo->yCaret * wInfo->cyChar);	// set caret position to last character

			InvalidateRect (hwnd, NULL, TRUE);	// mark window as dirty (so it will be cleaned)
			return 0;	// leave

		case WM_SETFOCUS:	// Window has taken focus
			CreateCaret (hwnd, NULL, wInfo->cxChar, wInfo->cyChar);	// create caret
			SetCaretPos (wInfo->xCaret * wInfo->cxChar, wInfo->yCaret * wInfo->cyChar);	// set caret position to after last character
			return 0;	// done.

		case WM_KILLFOCUS:	// Window has lost focus
			DestroyCaret();	// destroy caret (no longer needed)
			return 0;		// done.

		case WM_CHAR:	// A charater was hit
			for (i = 0; i < (int) LOWORD (lParam); i++)	{	// Loop through characters
				commSendChar(&wInfo->serCon, (char)wParam);	// send character to serial port
			}
			return 0;	// done

		case WM_COMMAND:	// a menu item was hit
			menuProcessor(hwnd, wInfo, wParam);	// send data to menu handler
			break;			// done

		case WM_PAINT:	// window needs re-painting
			hdc = BeginPaint (hwnd, &ps);	// begin painting (VERY IMPORTANT)

			SelectObject (hdc, CreateFont (0, 0, 0, 0, 0, 0, 0, 0,	// get default fixed-pitch font
			wInfo->dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

			// print characters to screen
			for (y = 0; y < wInfo->cyBuffer; y++)	// loop through lines of the window
				TextOut (hdc, 0, y * wInfo->cyChar, & BUFFER(0,y), wInfo->cxBuffer);	// print line to window

			// finish up painting
			DeleteObject (SelectObject (hdc, GetStockObject (SYSTEM_FONT)));	// delete font handler
			EndPaint (hwnd, &ps);	// finish painting (VERY IMPORTANT)
		return 0;	// done

		case WM_DESTROY:	// window closed (time to quit)
			PostQuitMessage (0);	// tell OS to close program
			return 0;	// done
		}
	return DefWindowProc (hwnd, message, wParam, lParam);	// load default event handlers (for those not explicitly covered above)
}
