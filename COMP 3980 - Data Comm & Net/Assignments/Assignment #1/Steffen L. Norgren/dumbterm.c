/*------------------------------------------------------------------------------
	MODULE: dumbterm.c

	PURPOSE: Program's entry point and window management

	AUTHOR: Steffen L. Norgren
			A00683006

/*-----------------------------------------------------------------------------*/

#include <windows.h>
#include "dumbterm.h"

//	Prototypes for functions called only within this file
BOOL InitializeApplication(HINSTANCE, int);
BOOL VersionCheck();
int WINAPI DTWndProc(HWND, UINT, WPARAM, LPARAM);
void MenuCommandDispatch(int, HWND, LPARAM);
BOOL CALLBACK SelectPortDlgProc(HWND, UINT, WPARAM, LPARAM);
void OpenComPort();
void CloseComPort();
void SendToComPort(WPARAM);
BOOL NEAR PaintWindow(HWND);
BOOL NEAR SizeTTY(HWND, WORD, WORD);
BOOL NEAR MoveCursor(HWND);

/*------------------------------------------------------------------------------
	FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

	PURPOSE: Start application and process all window messages

	PARAMETERS:
		hInstance		- this application's instance
		hPrevInstance	- previous instance of this application (always NULL)
		lpCmdLine		- command line parameters
		nCmdShow		- code for showing the window

	RETURN:
		1 for success
		0 for failure to start application

/*-----------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow) {

	MSG	msg;

	// verify program can run on this version of windows
	if (!VersionCheck()) {
		MessageBox(NULL, "Dumb Terminal can't run on this version of Windows.",
			NULL, MB_OK | MB_ICONSTOP);
		return 0; // cause the program to exit
	}

	// attempt to initialize the application and create the main window and class
	if (!InitializeApplication(hInstance, nCmdShow)) {
		MessageBox(NULL, "Dumb Terminal couldn't start!", NULL, MB_OK | MB_ICONSTOP);
		return 0;
	}

	// message loop
	while (GetMessage(&msg, NULL, 0, 0)) {	// get message form queue
		// check to see if this is a keyboard accelerator message
		if (!TranslateAccelerator(ghwndMain, ghAccel, &msg)) {
			TranslateMessage(&msg);				// for keystroke translation
			DispatchMessage(&msg);				// pass message back to the windows for processing
		}
	}

	return msg.wParam;	// exit parameter to be returned to the OS
}

/*------------------------------------------------------------------------------
	FUNCTION: VersionCheck(void)

	PURPOSE: Verifies that the correct version of Windows is running

	RETURN:
		TRUE	- success, version verified for running this application
		FALSE	- correct version not verified

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for this assignment.

/*-----------------------------------------------------------------------------*/
BOOL VersionCheck() {
	gOSV.dwOSVersionInfoSize = sizeof(gOSV);
	if (!GetVersionEx(&gOSV)) {
		return FALSE;
	}

	if (gOSV.dwPlatformId == VER_PLATFORM_WIN32s) {
		return FALSE;
	}

	return TRUE;
}

/*------------------------------------------------------------------------------
	FUNCTION: InitializeApplication(HINSTANCE hInst, int nCmdShow)

	PURPOSE: Register window classes and create the main window

	PARAMETERS:
		hInst		- HINSTANCE for this application
		nCmdShow	- Code for showing this window

	RETURN:
		TRUE	- successful initialization of this application
		FALSE	- failure to initialize application

/*-----------------------------------------------------------------------------*/
BOOL InitializeApplication(HINSTANCE hInst, int nCmdShow) {
	TCHAR		szAppName[] = TEXT("Dumb Terminal, Assignment #1");
	WNDCLASS	wc;

	// Setup the program's main window class
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= DTWndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInst;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_DTMENU);
	wc.lpszClassName	= szAppName;

	// Register wndclass to OS so appropriate window messages are sent to the application.
	if (!RegisterClass(&wc)) {
		return FALSE;
	}
	
	// Create the main window
	ghwndMain = CreateWindow(szAppName, "Dumb Terminal",
		WS_OVERLAPPEDWINDOW,
		X_START_POS, Y_START_POS,
		X_SIZE, Y_SIZE,
		NULL, NULL, hInst, NULL);

	// Show the main window
	ShowWindow(ghwndMain, nCmdShow);
	UpdateWindow(ghwndMain);

	ghInst = hInst;	// set the global instance for this program
	ghAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_DTACCELERATOR));

	return TRUE;
}

/*------------------------------------------------------------------------------
	FUNCTION: DTWndProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Windows procedure for the main window

	PARAMETERS:
		hwnd	- window handle
		message	- window message
		wParam	- window message parameter (depends on message)
		lParam	- window message parameter (depends on message)

	RETURN:
		If the message was processed, the return value is 0
		If the message was not processed and passed to DefWindowProc
		and the return value depends on the value of that function.

/*-----------------------------------------------------------------------------*/
int WINAPI DTWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_CREATE: // case for when the window is created
			// Initialize TTY Info
			InitTTYInfo();
			break;

		case WM_SETFOCUS: // case for when the window gains focus
			MoveCursor(hwnd);
			ShowCaret(hwnd);
			break;

		case WM_KILLFOCUS: // case for when the window focus is lost
			HideCaret(hwnd);
			break;

		case WM_COMMAND: // case for menu commands
			MenuCommandDispatch(LOWORD(wParam), hwnd, lParam);
			break;

		case WM_CHAR: // when stuff is typed
			if (CONNECTED(TTYInfo)) {
				SendToComPort(wParam);
			}
			break;

		case WM_SIZE: // case for when the window is resized
			SizeTTY(hwnd, LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_PAINT:
			PaintWindow(hwnd);
			break;

		case WM_DESTROY: // case for when the window is closed
			CloseComPort();
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

/*------------------------------------------------------------------------------
	FUNCTION: MenuCommandDispatch(int, HWND, LPARAM)

	PURPOSE: Responds to menu selections

	PARAMETERS:
		iMenuChoice	- ID of the menu choice (from resource file)
		hwnd		- window handle of menu owner
		lParam		- window message parameter (depends on message)

/*-----------------------------------------------------------------------------*/
void MenuCommandDispatch(int iMenuChoice, HWND hwnd, LPARAM lParam) {
	switch (iMenuChoice) {
		case ID_FILE_EXIT: // case for exiting the program
			CloseComPort();
			PostMessage(hwnd, WM_CLOSE, 0, 0);
			break;

		case ID_TTY_CONFIGURE: // open the com port selector
			CmdPort(hwnd);
			break;

		case ID_TTY_CLEAR:
			ClearTTYContents();
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case ID_FILE_CONNECT: // connect using our COM settings
			OpenComPort();
			break;

		case ID_FILE_DISCONNECT:
			CloseComPort();
			break;
	}
	return;
}

/*------------------------------------------------------------------------------
	FUNCTION: OpenComPort()

	PURPOSE: Opens the COM port for reading and writing

/*-----------------------------------------------------------------------------*/
void OpenComPort() {
	DCB dcb;
	HMENU hMenu;

	// Make sure we're not connected
	if (!CONNECTED(TTYInfo)) {
		hMenu = GetMenu(ghwndMain);	// get the menu handle

		EnableMenuItem(hMenu,
			ID_FILE_CONNECT, MF_GRAYED | MF_DISABLED); // disable the connect menu
		EnableMenuItem(hMenu,
			ID_FILE_DISCONNECT, MF_ENABLED); // enable the disconnect menu
		EnableMenuItem(hMenu,
			ID_TTY_CONFIGURE, MF_GRAYED | MF_DISABLED); // disable the TTY menu

		COMDEV(TTYInfo) = CreateFile(gszPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);
		FillMemory(&dcb, sizeof(dcb), 0);

		dcb.BaudRate = BAUDRATE(TTYInfo);	// set the baud rate
		dcb.ByteSize = BYTESIZE(TTYInfo);	// set the data bits
		dcb.fParity = PARITY(TTYInfo);		// set the parity
		dcb.StopBits = STOPBITS(TTYInfo);	// set the stop bits

		SetCommState(COMDEV(TTYInfo), &dcb);	// update the COM port configuration

		CONNECTED(TTYInfo) = TRUE;	// we are now connected (hopefully)
		CreateCaret(ghwndMain, NULL, XCHAR(TTYInfo), YCHAR(TTYInfo));
		ShowCaret(ghwndMain);
	}

	StartReadThread();
}

/*------------------------------------------------------------------------------
	FUNCTION: CloseComPort()

	PURPOSE: Closes all active connections and releases the COM handle

/*-----------------------------------------------------------------------------*/
void CloseComPort() {
	HMENU hMenu;

	// Check if we're connected
	if (CONNECTED(TTYInfo)) {
		hMenu = GetMenu(ghwndMain);	// get the menu handle

		EnableMenuItem(hMenu,
			ID_FILE_CONNECT, MF_ENABLED); // enable the connect menu
		EnableMenuItem(hMenu,
			ID_FILE_DISCONNECT, MF_GRAYED | MF_DISABLED); // disable the connect menu
		EnableMenuItem(hMenu,
			ID_TTY_CONFIGURE, MF_ENABLED); // enable the TTY menu

		// lower DTR
		EscapeCommFunction(COMDEV(TTYInfo), CLRDTR);
		
		// Purge reads/writes, and I/O buffer
		PurgeComm(COMDEV(TTYInfo), PURGE_FLAGS);

		CloseHandle(COMDEV(TTYInfo)); // release the handle

		THREADDONE(TTYInfo) = TRUE; // we want the thread to end
		CONNECTED(TTYInfo) = FALSE; // we are  now disconnected
		HideCaret(ghwndMain);
	}
}

/*------------------------------------------------------------------------------
	FUNCTION: SendToComPort(WPARAM)

	PURPOSE: Send character to COM port

	PARAMETERS:
		wParam	- window message parameter (the character to send)

/*-----------------------------------------------------------------------------*/
void SendToComPort(WPARAM wParam) {
	ULONG lrc;
	COMSTAT cs;

	if(!WriteFile(COMDEV(TTYInfo), (LPBYTE)&wParam, 1, &lrc, NULL)) {
		// handle error
		ClearCommError(COMDEV(TTYInfo), &lrc, &cs);
	}
}

/*------------------------------------------------------------------------------
	FUNCTION: ReadFromComPortThread(LPVOID)

	PURPOSE: Thread function controls reading from the COM port

	RETURN:
		Always 1

	NOTES: This is a very simple thread implementation and it utterly
		   fails if you start typing too fast.

/*-----------------------------------------------------------------------------*/
DWORD WINAPI ReaderProc() {
	OVERLAPPED	osReader = {0};	// overlapped structure for read operations
	DWORD		dwRead;			// bytes actually read
	char		lpBuf[AMOUNT_TO_READ];

	THREADDONE(TTYInfo) = FALSE; // don't want this finishing before it starts!

	while (!THREADDONE(TTYInfo)) {
		ReadFile(COMDEV(TTYInfo), lpBuf, AMOUNT_TO_READ, &dwRead, &osReader);
		OutputBuffer(ghwndMain, lpBuf, dwRead);
		Sleep(100);
	}

	CloseHandle(osReader.hEvent);

	return 1L;
}

/*------------------------------------------------------------------------------
	FUNCTION: OutputBuffer(HWND, char *, DWORD)

	PURPOSE: Send received buffer contents to the window

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for this assignment.

/*-----------------------------------------------------------------------------*/
void OutputBuffer(HWND hTTY, char * lpBuf, DWORD dwBufLen) {
	RECT	rect;
	int		i;

	// Update screen buffer with new buffer
	for (i = 0; i < (int)dwBufLen; i++) {
		switch (lpBuf[i]) {
			case ASCII_BEL:	// BEEP BEEP!
				MessageBeep(0);
				break;

			case ASCII_BS:	// backspace
				if (COLUMN(TTYInfo) > 0) {
					COLUMN(TTYInfo)--;
				}
				break;

			case ASCII_CR:	// carriage return
				COLUMN(TTYInfo) = 0;
				if (ROW(TTYInfo)++ == MAXROWS - 1) {
					MoveMemory((LPSTR)(SCREEN(TTYInfo)),
						(LPSTR)(SCREEN(TTYInfo) + MAXCOLS), (MAXROWS - 1) * MAXCOLS);
					FillMemory((LPSTR)(SCREEN(TTYInfo) + (MAXROWS - 1) * MAXCOLS), MAXCOLS, ' ');
					InvalidateRect(hTTY, NULL, FALSE);
					ROW(TTYInfo)--;
				}
				break;

			case ASCII_LF:	// line feed
				COLUMN(TTYInfo) = 0;
				if (ROW(TTYInfo)++ == MAXROWS - 1) {
					MoveMemory((LPSTR)(SCREEN(TTYInfo)),
						(LPSTR)(SCREEN(TTYInfo) + MAXCOLS), (MAXROWS - 1) * MAXCOLS);
					FillMemory((LPSTR)(SCREEN(TTYInfo) + (MAXROWS - 1) * MAXCOLS), MAXCOLS, ' ');
					InvalidateRect(hTTY, NULL, FALSE);
					ROW(TTYInfo)--;
				}
				break;

			default:	// standard characters
				SCREENCHAR(TTYInfo, COLUMN(TTYInfo), ROW(TTYInfo)) = lpBuf[i];

				rect.left = (COLUMN(TTYInfo) * XCHAR(TTYInfo)) - XOFFSET(TTYInfo);
				rect.right = rect.left + XCHAR(TTYInfo);
				rect.top = (ROW(TTYInfo) * YCHAR(TTYInfo)) - YOFFSET(TTYInfo);
				rect.bottom = rect.top + YCHAR(TTYInfo);
				InvalidateRect(hTTY, &rect, FALSE);

				// Line wrapping
				if (COLUMN(TTYInfo) < MAXCOLS - 1) {
					COLUMN(TTYInfo)++;
				}
				else {
					OutputBuffer(hTTY, "\r", 1);
				}
				break;
		}
	}

	MoveCursor(hTTY);
}

/*------------------------------------------------------------------------------
	FUNCTION: PaintWindow(HWND)

	PURPOSE: Updates the window with the contents of the screen buffer

	PARAMETERS:
		hwnd		- handle for the window to be painted upon

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for this assignment.

/*-----------------------------------------------------------------------------*/
BOOL NEAR PaintWindow(HWND hwnd) {
	PAINTSTRUCT	ps;
	HFONT		hFont;
	RECT		rect;
	HDC			hdc;
	int			nRow, nCol, nEndRow, nEndCol;
	int			nCount, nHorizPos, nVertPos;	// yes, it is setup for scrolling, but won't

	hdc = BeginPaint(hwnd, &ps);
	hFont = SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0, FIXED_PITCH, NULL));
	rect = ps.rcPaint;

	nRow = min(MAXROWS - 1, max(0, (rect.top + YOFFSET(TTYInfo)) / YCHAR(TTYInfo)));
	nEndRow = min(MAXROWS - 1, ((rect.bottom + YOFFSET(TTYInfo) - 1) / YCHAR(TTYInfo)));
	nCol = min(MAXCOLS - 1, max(0, (rect.left + XOFFSET(TTYInfo)) / XCHAR(TTYInfo)));
	nEndCol = min(MAXCOLS - 1, ((rect.right + XOFFSET(TTYInfo) - 1) / XCHAR(TTYInfo)));
	nCount = nEndCol - nCol + 1;

	for (; nRow <= nEndRow; nRow++) {
		nVertPos = (nRow * YCHAR(TTYInfo)) - YOFFSET(TTYInfo);
		nHorizPos = (nCol * XCHAR(TTYInfo)) - XOFFSET(TTYInfo);

		rect.top = nVertPos;
		rect.bottom = nVertPos + YCHAR(TTYInfo);
		rect.left = nHorizPos;
		rect.right = nHorizPos + XCHAR(TTYInfo) * nCount;

		ExtTextOut(hdc, nHorizPos, nVertPos, ETO_OPAQUE | ETO_CLIPPED, & rect,
			(LPSTR)(SCREEN(TTYInfo) + nRow * MAXCOLS + nCol), nCount, NULL);
	}

	SelectObject(hdc, hFont);
	EndPaint(hwnd, &ps);
	MoveCursor(hwnd);
	
	return TRUE;
}

/*------------------------------------------------------------------------------
	FUNCTION: SizeTTY(HWND)

	PURPOSE: Updates the size of the current window.

	PARAMETERS:
		hwnd	- handle for the window being resized
		wWidth	- the new window width
		wHeight	- the new window height

	RETURN:
		Always true

/*-----------------------------------------------------------------------------*/
BOOL NEAR SizeTTY(HWND hwnd, WORD wWidth, WORD wHeight) {
	
	// adjust vertical settings
	YSIZE(TTYInfo) = (int)wHeight;
	YOFFSET(TTYInfo) = 0; // we aren't using scrollbars

	// adjust horizontal settings
	XSIZE(TTYInfo) = (int)wWidth;
	XOFFSET(TTYInfo) = 0;

	InvalidateRect(hwnd, NULL, FALSE);

	return TRUE;
}

/*------------------------------------------------------------------------------
	FUNCTION: MoveCursor(HWND)

	PURPOSE: Moves the cursor

	PARAMETERS:
		hwnd	- handle for the window being resized

	RETURN:
		Always true

/*-----------------------------------------------------------------------------*/
BOOL NEAR MoveCursor(HWND hwnd) {
	if (CONNECTED(TTYInfo)) {
		SetCaretPos((COLUMN(TTYInfo) * XCHAR(TTYInfo)) - XOFFSET(TTYInfo),
			(ROW(TTYInfo) * YCHAR(TTYInfo)) - YOFFSET(TTYInfo));
	}

	return TRUE;
}