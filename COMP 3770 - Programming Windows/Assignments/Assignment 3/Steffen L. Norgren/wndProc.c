/*
	MODULE: wndProc.c

	PURPOSE: Handles program's window.

	AUTHOR: Steffen L. Norgren
*/

#include <windows.h>
#include <windowsx.h>
#include "winMain.h"
#include "resource.h"
#include "chooseColour.h"
#include "linkedList.h"

// Private function prototypes
void PaintWindow(HWND);
void OpenChildWindows(HWND);
BOOL NEAR ScrollVert(HWND, WORD, WORD);
BOOL NEAR ScrollHorz(HWND, WORD, WORD);

// Private variables
int		selCount = 0;	// we'll use this to remove the newly drawn objects from the linked list
UINT	clpFormat;


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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	SCROLLINFO	si;

	switch (message) {
		case WM_CREATE: // case for when the window is created
			InitLinkedList();
			clpFormat = RegisterClipboardFormat(TEXT("DRAWING_OBJECT"));
			OpenChildWindows(hWnd);
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

		case WM_SIZE: // case for when the window is resized
			
			// Set vertical scrollbar range and page size
			si.cbSize	= sizeof(si);
			si.fMask	= SIF_RANGE | SIF_PAGE;
			si.nMin		= 0;
			si.nMax		= 1200;
			si.nPage	= Y_SIZE;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

			// Set horizontal scrollbar range and page size
			si.cbSize	= sizeof(si);
			si.fMask	= SIF_RANGE | SIF_PAGE;
			si.nMin		= 0;
			si.nMax		= 1600;
			si.nPage	= X_SIZE;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			break;

		case WM_VSCROLL: // when the vertical scrollbar is moved
			ScrollVert(ghWndCanvas, LOWORD(wParam), HIWORD(wParam));
			break;

		case WM_HSCROLL: // when the horizontal scrollbar is moved
			ScrollHorz(ghWndCanvas, LOWORD(wParam), HIWORD(wParam));
			break;

		case WM_PAINT:
			PaintWindow(hWnd);
			break;

		case WM_CLOSE:
			ClearLinkedList();
			DestroyWindow(hWnd);
			break;

		default:
			return (int)DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	FUNCTION: CanvasProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Windows procedure for the canvas window

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
LRESULT CALLBACK CanvasProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	// a rectangle to hold current selection coords and a boolean to know whether we are in a drawing mode or not
	static RECT		rect;
	static POINT	pt[2];
	static POINT	select;
	static BOOL		fDrawing;
	HMENU			hMenu;

	// We'll be iterating through the list to find a selected object
	pPROGRAM_ITEM	pListItem;
	pPROGRAM_ITEM	pPrevItem;

	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_CREATE: // case for when the window is created
			SetRect(&rect, 0, 0, 0, 0); 
			fDrawing = FALSE;
			break;

		case WM_MOUSEACTIVATE: // when the mouse moves into this window
			SetFocus(hWnd);
			return MA_ACTIVATE;
			break;

		case WM_LBUTTONDOWN:
			if(fDrawing) { // this should not happen, but no harm checking
				ReleaseCapture();
			}

			// start selecting
			fDrawing = TRUE;

			// mouse x and y in lParam
			rect.left = (short)LOWORD(lParam);
			rect.top = (short)HIWORD(lParam);
			rect.right = (short)LOWORD(lParam);
			rect.bottom = (short)HIWORD(lParam);
			pt[0].x = (short)LOWORD(lParam);
			pt[0].y = (short)HIWORD(lParam);
			pt[1].x = (short)LOWORD(lParam);
			pt[1].y = (short)HIWORD(lParam);

			// draw first to keep drawing/erasing in synch.
			// Check to see if we're drawing a line or a rectangle
			if (GetMenuState(hMenu, ID_TOOLS_LINE, MF_BYCOMMAND) == MF_CHECKED) {
				DrawLine(hWnd, (POINT *)&pt, gRGBCurrent, FALSE);
			}
			if (GetMenuState(hMenu, ID_TOOLS_RECTANGLE, MF_BYCOMMAND) == MF_CHECKED) {
				DrawRect(hWnd, &rect, gRGBCurrent, FALSE);
			}
			SetCapture(hWnd);
			return 0;

		case WM_MOUSEMOVE:
			if (fDrawing) {
				RECT	rcClient;

				GetClientRect(hWnd, &rcClient);
				
				// Check to see if we're drawing a line or a rectangle
				if (GetMenuState(hMenu, ID_TOOLS_LINE, MF_BYCOMMAND) == MF_CHECKED) {
					// erase old selection
					DrawLine(hWnd, (POINT *)&pt, gRGBCurrent, FALSE);
				}
				if (GetMenuState(hMenu, ID_TOOLS_RECTANGLE, MF_BYCOMMAND) == MF_CHECKED) {
					// erase old selection
					DrawRect(hWnd, &rect, gRGBCurrent, FALSE);
				}

				// mouse x and y in lParam
				rect.right = (short)LOWORD(lParam);
				rect.bottom = (short)HIWORD(lParam);
				pt[1].x = (short)LOWORD(lParam);
				pt[1].y = (short)HIWORD(lParam);

				// make sure our selection does not go outside client area
				if(rect.right < 0) {
					rect.right = 0;
					pt[1].x = 0;
				}
				if(rect.right > rcClient.right) {
					rect.right = rcClient.right;
					pt[1].x = rcClient.right;
				}
				if(rect.bottom < 0) {
					rect.bottom = 0;
					pt[1].x = 0;
				}
				if(rect.bottom > rcClient.bottom) {
					rect.bottom = rcClient.bottom;
					pt[1].y = rcClient.bottom;
				}

				// Check to see if we're drawing a line or a rectangle
				if (GetMenuState(hMenu, ID_TOOLS_LINE, MF_BYCOMMAND) == MF_CHECKED) {
					DrawLine(hWnd, (POINT *)&pt, gRGBCurrent, FALSE);
				}
				if (GetMenuState(hMenu, ID_TOOLS_RECTANGLE, MF_BYCOMMAND) == MF_CHECKED) {
					DrawRect(hWnd, &rect, gRGBCurrent, FALSE);
				}
			}
			break;

		case WM_LBUTTONUP:
			if(fDrawing)
			{
				// reset selection
				// Check to see if we're drawing a line or a rectangle
				if (GetMenuState(hMenu, ID_TOOLS_LINE, MF_BYCOMMAND) == MF_CHECKED) {
					DrawLine(hWnd, (POINT *)&pt, gRGBCurrent, FALSE);
				}
				if (GetMenuState(hMenu, ID_TOOLS_RECTANGLE, MF_BYCOMMAND) == MF_CHECKED) {
					DrawRect(hWnd, &rect, gRGBCurrent, FALSE);
				}
				fDrawing = FALSE;
				ReleaseCapture();

				// Check to see if we're drawing a line or a rectangle
				if (GetMenuState(hMenu, ID_TOOLS_LINE, MF_BYCOMMAND) == MF_CHECKED) {
					// Add line to queue
					InsertObject(pt, rect, TRUE, gRGBCurrent);
				}
				if (GetMenuState(hMenu, ID_TOOLS_RECTANGLE, MF_BYCOMMAND) == MF_CHECKED) {
					// Add rectangle to queue
					InsertObject(pt, rect, FALSE, gRGBCurrent);
				}

				// draw the newly created object
				InvalidateRect(hWnd, NULL, TRUE);
			}

			// Check to see if we're selecting an object
			if (GetMenuState(hMenu, ID_TOOLS_SELECT, MF_BYCOMMAND) == MF_CHECKED) {
				select.x = (short)LOWORD(lParam);
				select.y = (short)HIWORD(lParam);
				(PSLIST_HEADER)pListItem = gpListHead;

				// Reverse the linked list
				while (pListItem) {

					if (pListItem->fLine) {
						if (pListItem->rect.left < select.x && pListItem->rect.right > select.x &&
							pListItem->rect.bottom > select.y && pListItem->rect.top < select.y) {
								InsertObject(pListItem->line, pListItem->rect, TRUE, SELECTED_OBJECT);
								selCount++;
								break;
						}
					}
					else {
						if (pListItem->rect.left < select.x && pListItem->rect.right > select.x &&
							pListItem->rect.bottom > select.y && pListItem->rect.top < select.y) {
								InsertObject(pListItem->line, pListItem->rect, FALSE, SELECTED_OBJECT);
								selCount++;
								break;
						}
					}

					//switch to next list item
					pPrevItem = pListItem;
					pListItem = (pPROGRAM_ITEM)pListItem->ItemEntry.Next;
				}
			}
			return 0;

		case WM_PAINT:
			PaintWindow(hWnd);
			break;

		case WM_CLOSE:
			break;

		default:
			return (int)DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	FUNCTION: DrawLine(HWND, const RECT*)

	PURPOSE: Draws a line on the canvas

	PARAMETERS:
		hWnd	- Handle to the window
		pRect	- Pointer to our rectangle
		colour	- Colour of the object
		repaint	- Whether we're repainting the window (ignore SetROP2)

*/
static void DrawLine(HWND hWnd, POINT pPoint[], COLORREF colour, BOOL repaint)
{
	HDC hDC;
	HPEN hOldPen;
	HBRUSH hOldBrush;

	hDC = GetDC(hWnd);

	hOldPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 10, colour));
	hOldBrush = (HBRUSH)SelectObject(hDC, CreateSolidBrush(colour));

	if (!repaint) {
		SetROP2(hDC, R2_NOTXORPEN);
	}

	MoveToEx(hDC, pPoint[0].x, pPoint[0].y, NULL);
	LineTo(hDC, pPoint[1].x, pPoint[1].y);

	SelectObject(hDC, hOldBrush);
	DeleteObject(SelectObject(hDC, hOldPen));

	ReleaseDC(hWnd, hDC);
}

/*
	FUNCTION: DrawLine(HWND, const RECT*)

	PURPOSE: Draws a rectangle on the canvas

	PARAMETERS:
		hWnd	- Handle to the window
		pRect	- Pointer to object
		colour	- Colour of the object
		repaint	- Whether we're repainting the window (ignore SetROP2)

*/
static void DrawRect(HWND hWnd, RECT* pRect, COLORREF colour, BOOL repaint)
{
	HDC hDC;
	HPEN hOldPen;
	HBRUSH hOldBrush;

	hDC = GetDC(hWnd);

	hOldPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 1, colour));
	hOldBrush = (HBRUSH)SelectObject(hDC, CreateSolidBrush(colour));

	if (!repaint) {
		SetROP2(hDC, R2_NOTXORPEN);
	}

	Rectangle(hDC, pRect->left, pRect->top, pRect->right, pRect->bottom);

	SelectObject(hDC, hOldBrush);
	DeleteObject(SelectObject(hDC, hOldPen));

	ReleaseDC(hWnd, hDC);
}

/*
	FUNCTION: OpenChildWindows(HWND)

	PURPOSE: Creates the child window

	PARAMETERS:
		hWnd	- Handle to the window

*/
void OpenChildWindows(HWND hWnd) {
	ghWndCanvas = CreateWindow(TEXT("CanvasClass"), TEXT("Canvas"),
				  WS_CHILD | WS_VISIBLE,
				  0, 0,
				  X_CANVAS, Y_CANVAS,
				  hWnd, NULL, ghInst, NULL);
}

/*
	FUNCTION: PaintWindow(HWND)

	PURPOSE: Paints the area determined by the paint struct of the DC.

	PARAMETERS:
		hWnd	- Handle to the window

*/
void PaintWindow(HWND hWnd) {
	PAINTSTRUCT		ps;
	HDC				hDC;
	HMENU			hMenu;
	pPROGRAM_ITEM	pListItem;
	pPROGRAM_ITEM	pPrevItem;
	pPROGRAM_ITEM	pArray[MAX_OBJECTS]; // ugly hack since I can't reverse the stupid list
	int				i, iter = 0;

	hMenu = GetMenu(hWnd);
	hDC = BeginPaint(hWnd, &ps);

	(PSLIST_HEADER)pListItem = gpListHead;

	// Reverse the linked list
	while (pListItem) {

		// Add the pointers to our array
		if (QueryDepthSList(gpListHead) != 0 && iter != MAX_OBJECTS) {
			pArray[iter++] = pListItem;
		}

		//switch to next list item
		pPrevItem = pListItem;
		pListItem = (pPROGRAM_ITEM)pListItem->ItemEntry.Next;
	}

	if (selCount != 0) {
		// Remove the inserted objects
		for (; selCount != 0; --selCount) {
			InterlockedPopEntrySList(gpListHead);
		}
	}

	// Iterate backwards through our array of pointers
	if (QueryDepthSList(gpListHead) != 0) {
		// Make sure we don't iterate beyond the bounds of our array (ugly hack, yes)
		if (QueryDepthSList(gpListHead) > MAX_OBJECTS) {
			iter = MAX_OBJECTS;
		}
		for (i = iter - 1; i != 0; i--) {
			if (pArray[i]->fLine) {
				DrawLine(hWnd, pArray[i]->line, pArray[i]->colour, TRUE);
			}
			else { // Draw a rectangle
				DrawRect(hWnd, &(pArray[i]->rect), pArray[i]->colour, TRUE);
			}
		}
	}

	EndPaint(hWnd, &ps);
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
	SCROLLINFO	si;
	int			iScrollPos;

	si.cbSize	= sizeof(si);
	si.fMask	= SIF_ALL;
	GetScrollInfo(ghWndMain, SB_VERT, &si);

	// Save the current position for comparison
	iScrollPos = si.nPos;

	switch (wScrollCmd) {
		case SB_TOP: // moved to the top
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM: // moved to the bottom
			si.nPos = si.nMax;
			break;

		case SB_PAGEUP: // moved up by a page
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN: // moved down by a page
			si.nPos += si.nPage;
			break;

		case SB_LINEUP:	// move up a line
			si.nPos -= 10;
			break;

		case SB_LINEDOWN: // move down a line
			si.nPos += 10;
			break;

		case SB_THUMBTRACK: // manually positioned
			si.nPos = si.nTrackPos;
			break;

		default:
			return FALSE;
	}

	// Set the position and then retrieve it. Due to adjustments
	// by Windows, it may not be the same as the value set.
	si.fMask = SIF_POS;
	SetScrollInfo(ghWndMain, SB_VERT, &si, TRUE);
	GetScrollInfo(ghWndMain, SB_VERT, &si);

	// If the position has changed, scroll the window and update it
	if (si.nPos != iScrollPos) {
		ScrollWindow(ghWndMain, 0, iScrollPos - si.nPos, NULL, NULL);
		UpdateWindow(hWnd);
	}

	return TRUE;
}

/*
	BOOL NEAR ScrollHorz(HWND, WORD, WORD)

	PURPOSE: Scrolls the window horizontally

	PARAMETERS:
		hWnd		- Handle to the terminal window
		wScrollCmd	- The type of scrolling we're doing
		wScrollPos	- The scroll bar's position
*/
BOOL NEAR ScrollHorz(HWND hWnd, WORD wScrollCmd, WORD wScrollPos) {
	SCROLLINFO	si;
	int			iScrollPos;

	si.cbSize	= sizeof(si);
	si.fMask	= SIF_ALL;
	GetScrollInfo(ghWndMain, SB_HORZ, &si);

	// Save the current position for comparison
	iScrollPos = si.nPos;

	switch (wScrollCmd) {
		case SB_TOP: // moved to the top
			si.nPos = si.nMin;
			break;

		case SB_BOTTOM: // moved to the bottom
			si.nPos = si.nMax;
			break;

		case SB_PAGEUP: // moved up by a page
			si.nPos -= si.nPage;
			break;

		case SB_PAGEDOWN: // moved down by a page
			si.nPos += si.nPage;
			break;

		case SB_LINEUP:	// move up a line
			si.nPos -= 10;
			break;

		case SB_LINEDOWN: // move down a line
			si.nPos += 10;
			break;

		case SB_THUMBTRACK: // manually positioned
			si.nPos = si.nTrackPos;
			break;

		default:
			return FALSE;
	}

	// Set the position and then retrieve it. Due to adjustments
	// by Windows, it may not be the same as the value set.
	si.fMask = SIF_POS;
	SetScrollInfo(ghWndMain, SB_HORZ, &si, TRUE);
	GetScrollInfo(ghWndMain, SB_HORZ, &si);

	// If the position has changed, scroll the window and update it
	if (si.nPos != iScrollPos) {
		ScrollWindow(ghWndMain, iScrollPos - si.nPos, 0, NULL, NULL);
		UpdateWindow(hWnd);
	}

	return TRUE;
}

/*
	Function: EditCopy()

	PURPOSE: Copy's the selected item to the clipboard

	RETURN:
		TRUE	- Copy succeeded
		FALSE	- Error copying
*/
BOOL WINAPI EditCopy() {
	HGLOBAL hglbCopy;
	pPROGRAM_ITEM pCopy;
	CPDATA data;
	CPDATA *buffer = NULL;

	//pCopy = (pPROGRAM_ITEM)InterlockedPopEntrySList(gpListHead);
	(PSLIST_HEADER)pCopy = gpListHead;
	pCopy = (pPROGRAM_ITEM)pCopy->ItemEntry.Next;

	data.rect = pCopy->rect;
	data.line[0].x = pCopy->line[0].x;
	data.line[0].y = pCopy->line[0].y;
	data.line[1].x = pCopy->line[1].x;
	data.line[1].y = pCopy->line[1].y;
	data.fLine = pCopy->fLine;
	data.colour = pCopy->colour;

	// Open Clipboard and empty it
	if (!OpenClipboard(ghWndMain)) {
		return FALSE;
	}
	EmptyClipboard();

	hglbCopy = GlobalAlloc(GMEM_DDESHARE, sizeof(CPDATA)); 
	buffer = (CPDATA*)GlobalLock(hglbCopy);

	if (hglbCopy == NULL) {
		CloseClipboard(); 
		return FALSE;
	}

	// Copy onto clipboard
	*buffer = data;

	if (clpFormat == 0) {
		return FALSE;
	}

	GlobalUnlock(hglbCopy);
	SetClipboardData(clpFormat,hglbCopy);
	CloseClipboard();

	return TRUE;
}

/*
	Function: EditPaste()

	PURPOSE: Pastes data from the clipboard

	RETURN:
		TRUE	- Paste succeeded
		FALSE	- Error pasting
*/
BOOL WINAPI EditPaste() {
	HANDLE	hData;
	CPDATA pCopy;
	CPDATA *buffer = NULL;

	// Open Clipboard
	if (!OpenClipboard(ghWndMain)) {
		return FALSE;
	}

	// Get the buffer
	hData = GetClipboardData(clpFormat);
	buffer = (CPDATA*)GlobalLock(hData);
	
	// Make Local copy
	pCopy = *buffer;

	InsertObject(pCopy.line, pCopy.rect, pCopy.fLine, pCopy.colour);

	GlobalUnlock( hData );
	CloseClipboard();
	InvalidateRect(ghWndMain, NULL, TRUE);

	return TRUE;
}