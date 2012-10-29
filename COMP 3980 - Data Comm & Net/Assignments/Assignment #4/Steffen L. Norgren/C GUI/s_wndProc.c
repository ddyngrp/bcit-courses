/*
	MODULE: wndProc.c

	PURPOSE: Handles program's window.

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#include "s_resource.h"
#include "s_winMain.h"

// Private function prototypes
int NEAR PaintWindow(HWND);
void OpenChildWindows(HWND);
void ResizeWindow(LPARAM);

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
	switch (message) {
		case WM_CREATE: // case for when the window is created
			OpenChildWindows(hWnd);
			break;

		case WM_DESTROY: // case for when the window is closed
			CloseHandle(ghTimer);
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // case for menu commands
			MenuDispatch(LOWORD(wParam), hWnd, lParam);
			break;

		case WM_SIZE: // case for when the window is resized
			ResizeWindow(lParam);
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
	FUNCTION: ChatProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Windows procedure for the chat window

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
LRESULT CALLBACK ChatProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_INITDIALOG:
			PopulateCOMPorts(hWnd);
			ghTimer = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TimerThread, hWnd, 0, NULL);
			break;

		case WM_DESTROY: // case for when the window is closed
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // case for dialog events
			DialogDispatch(hWnd, wParam);
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
	FUNCTION: OpenChildWindows(HWND)

	PURPOSE: Creates the child window

	PARAMETERS:
		hWnd	- Handle to the window

*/
void OpenChildWindows(HWND hWnd) {
	ghWndChat = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DLG_CHAT), hWnd, ChatProc);

	if (ghWndChat == NULL) {
		MessageBox(NULL, TEXT("The child window failed to open."), NULL, MB_OK | MB_ICONSTOP);
	}

	return;
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
	FUNCTION: ResizeWindow(LPARAM)

	PURPOSE: Manages resizing the window and all its associated elements.

	PARAMETERS:
		lParam	- Window size parameter.

*/
void ResizeWindow(LPARAM lParam) {
	// Main window size has changed, need to resize child windows
	WORD wTop;
	WORD wHeight;
	WORD wWidth = LOWORD(lParam);
	RECT wRect;
	int	minWidth = 436;

	// Set the dialog size
	GetWindowRect(ghWndMain, &wRect);
	wHeight = HIWORD(lParam);
	wTop = 0;
	MoveWindow(ghWndChat, 0, wTop, wWidth, wHeight, TRUE);

	// Set the group box size & move its elements
	MoveWindow(GetDlgItem(ghWndChat,IDC_GRP_CONNECTION), 5, 5, wWidth - 10, 50, TRUE);
	MoveWindow(GetDlgItem(ghWndChat,IDC_RAD_SND), wWidth - 80, 18, 65, 15, TRUE);
	MoveWindow(GetDlgItem(ghWndChat,IDC_RAD_RCV), wWidth - 80, 35, 65, 15, TRUE);

	// Make sure our lables are positioned properly (top lable doesn't matter)
	MoveWindow(GetDlgItem(ghWndChat,IDC_LBL_SNT), 5, (wHeight/4) + 90, 60, 20, TRUE);
	MoveWindow(GetDlgItem(ghWndChat,IDC_LBL_SND), 5, (wHeight/2) + 112, 80, 20, TRUE);

	// Make sure our window elements resize properly
	if (wWidth <= minWidth && wWidth > X_MIN_SIZE) {
		MoveWindow(GetDlgItem(ghWndChat,IDC_LBL_ACTIVITY), (minWidth/2) + 13, 28, 65, 15, TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_LBL_TIMER), (minWidth/2) + 81, 28, 45, 15, TRUE);

		MoveWindow(GetDlgItem(ghWndChat,IDC_RCVD_TEXT), 5, 83, minWidth - 15, (wHeight/4) + 0, TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_SNT_TEXT), 5, (wHeight/4) + 106, minWidth - 15, (wHeight/4) + 0, TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_SND_TEXT), 5, (wHeight/2) + 128, minWidth - 85,
			(wRect.bottom - wRect.top) - (wHeight/2 + 180), TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_BTN_SEND), minWidth - 75, (wHeight/2) + 128, 65,
			(wRect.bottom - wRect.top) - (wHeight/2 + 180), TRUE);
	}
	else {
		MoveWindow(GetDlgItem(ghWndChat,IDC_LBL_ACTIVITY), (wWidth/2) + 13, 28, 65, 15, TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_LBL_TIMER), (wWidth/2) + 81, 28, 45, 15, TRUE);

		MoveWindow(GetDlgItem(ghWndChat,IDC_RCVD_TEXT), 5, 83, wWidth - 10, (wHeight/4) + 0, TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_SNT_TEXT), 5, (wHeight/4) + 106, wWidth - 10, (wHeight/4) + 0, TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_SND_TEXT), 5, (wHeight/2) + 128, wWidth - 80,
			(wRect.bottom - wRect.top) - (wHeight/2 + 180), TRUE);
		MoveWindow(GetDlgItem(ghWndChat,IDC_BTN_SEND), wWidth - 70, (wHeight/2) + 128, 65,
			(wRect.bottom - wRect.top) - (wHeight/2 + 180), TRUE);
	}

	// Make sure we don't size the window beyond some minimum constraints
	if (wWidth <= X_MIN_SIZE && wHeight > Y_MIN_SIZE) {
		MoveWindow(ghWndMain, wRect.left, wRect.top, X_MIN_SIZE + 10, wRect.bottom - wRect.top, TRUE);
	}
	else if (wWidth <= X_MIN_SIZE && wHeight <= Y_MIN_SIZE) {
		MoveWindow(ghWndMain, wRect.left, wRect.top, X_MIN_SIZE + 10, Y_MIN_SIZE + 10, TRUE);
	}
	else if (wWidth > X_MIN_SIZE && wHeight <= Y_MIN_SIZE) {
		MoveWindow(ghWndMain, wRect.left, wRect.top, wRect.right - wRect.left, Y_MIN_SIZE + 10, TRUE);
	}
}