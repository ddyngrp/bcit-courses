/*
	MODULE: wndProc.c

	PURPOSE: Handles program's window.

	AUTHORS: Steffen L. Norgren
*/

#include "winMain.h"

// Private Definitions
#define BUTTONCLASS		TEXT("Button")
#define ID_BUTTON		0x8801
#define BUTTONWIDTH		100
#define BUTTONHEIGHT	25
#define BUTTONOFFSET	10


// Private function prototypes
int NEAR PaintWindow(HWND);
DWORD WINAPI ThreadProc(LPVOID);

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
	HANDLE	hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("P1"));
	HWND	hWndBttn;

	switch (message) {
		case WM_CREATE: // case for when the window is created
			// Create our button
			hWndBttn = CreateWindow( BUTTONCLASS, TEXT("Drink Me"), 
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
						BUTTONOFFSET, 
						BUTTONOFFSET, BUTTONWIDTH, 
						BUTTONHEIGHT, hWnd,
						(HMENU)ID_BUTTON,
						ghInst, NULL );
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)0, 0, 0);
			break;

		case WM_DESTROY: // case for when the window is closed
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // case for menu commands
			switch (LOWORD(wParam)) {
				case ID_BUTTON:
					//MessageBox(NULL, TEXT("You die."), NULL, MB_OK | MB_ICONSTOP);
					SetEvent(hEvent);
					break;
			}
			break;

		case WM_SIZE: // case for when the window is resized
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

/*
	FUNCTION: PaintWindow(HWND)

	PURPOSE: Paints the rectangle determined by the paint struct of the DC.

	PARAMETERS:
		hWnd	- Handle to the window

*/
int NEAR PaintWindow(HWND hWnd) {
	PAINTSTRUCT	ps;
	HDC			hDC;

	hDC = BeginPaint(hWnd, &ps);
	EndPaint(hWnd, &ps);

	return TRUE;
}

/*
	FUNCTION: ThreadProc(HWND)

	PURPOSE: Waits for a quit message

	PARAMETERS:
		iValue	- data to be passted to the thread

*/
DWORD WINAPI ThreadProc(LPVOID iValue) {
	HANDLE	hQuitEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("quit"));
	DWORD	dwEvent;
	BOOL	loop = TRUE;

	dwEvent = WaitForSingleObject(hQuitEvent, INFINITE);

	while (loop) {
		switch (dwEvent) {
			case WAIT_OBJECT_0:
				loop = FALSE;
				SendMessage(ghWndMain, WM_DESTROY, 0, 0);
				break;
			case WAIT_ABANDONED:
				loop = FALSE;
				SendMessage(ghWndMain, WM_DESTROY, 0, 0);
				break;
		}
	}

	return 0;
}