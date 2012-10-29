/*
	MODULE: wndProc.c

	PURPOSE: Handles program's window.

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#include "functions.h"
#include "resource.h"
#include "winMain.h"
#include <windowsx.h>


// Private function prototypes
int NEAR PaintWindow(HWND);
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//	char escCode = 27, bracketCode = 91, oCode = 79;
	char initMsg[] = {0x01, 0x08, 0x00, 0x03, 0x01, 0x40, 0x4B, 0xB4};

	HMENU hmenu = GetMenu(hWnd);
	switch (message) {
		case WM_CREATE: // case for when the window is created
			CheckAvailPorts(hWnd);
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
			switch(LOWORD(wParam)) {
				case ID_PORT_COM1:
					CommProperties(hWnd, TEXT("com1"));
					break;
				case ID_PORT_COM2:
					CommProperties(hWnd, TEXT("com2"));
					break;
				case ID_PORT_COM3:
					CommProperties(hWnd, TEXT("com3"));
					break;
				case ID_PORT_COM4:
					CommProperties(hWnd, TEXT("com4"));
					break;
				case ID_PORT_COM5:
					CommProperties(hWnd, TEXT("com5"));
					break;
				case ID_PORT_COM6:
					CommProperties(hWnd, TEXT("com6"));
					break;
				case ID_PORT_COM7:
					CommProperties(hWnd, TEXT("com7"));
					break;
				case ID_PORT_COM8:
					CommProperties(hWnd, TEXT("com8"));
					break;
				case ID_PORT_COM9:
					CommProperties(hWnd, TEXT("com9"));
					break;
				case ID_CONNECTION_CONNECT:
					mode = CONNECT;
					if(OpenPort(lpszCommName)) {
						CreateReadThread(hWnd);
						EnableMenuItem(hmenu, ID_CONNECTION_DCONNECT, MF_ENABLED);
						EnableMenuItem(hmenu, ID_CONNECTION_CONNECT, MF_GRAYED);

						EnableWindow(GetDlgItem(ghWndInfoTool,IDC_BTN_START), TRUE);

						//Send the initial packet to the RFID
						InitPacket(initMsg);
					}
					else
						mode = COMMAND;
					break;

				case ID_CONNECTION_DCONNECT:
					if(CloseHandle(hThread) && CloseHandle(hComm)) {
						mode = COMMAND;
						hComm = NULL;
						hThread = NULL;
						EnableMenuItem(hmenu, ID_CONNECTION_CONNECT, MF_ENABLED);
						EnableMenuItem(hmenu, ID_CONNECTION_DCONNECT, MF_GRAYED);

						EnableWindow(GetDlgItem(ghWndInfoTool,IDC_BTN_START), FALSE);
						EnableWindow(GetDlgItem(ghWndInfoTool,IDC_BTN_STOP), FALSE);

					}
					break;

				case ID_HELP_ABOUT:
					HelpAbout();
					break;

				case ID_FILE_EXIT:
					PostQuitMessage(0);
					break;
			}
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
				MoveWindow(GetDlgItem(ghWndInfoTool,IDC_LST_RFID), 5, 38, wWidth - 15, wHeight - 48, TRUE);
			}
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
int CALLBACK InfoToolProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int i, count;

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
					// Start looking for tags
					scanTags = 1;
					Search();
					EnableWindow(GetDlgItem(ghWndInfoTool,IDC_BTN_START), FALSE);
					EnableWindow(GetDlgItem(ghWndInfoTool,IDC_BTN_STOP), TRUE);
					break;

				case IDC_BTN_STOP:
					// Stop Looking for tags
					scanTags = 0;
					EnableWindow(GetDlgItem(ghWndInfoTool,IDC_BTN_START), TRUE);
					EnableWindow(GetDlgItem(ghWndInfoTool,IDC_BTN_STOP), FALSE);
					break;

				case IDC_BTN_CLEAR:
					count = ListBox_GetCount(GetDlgItem(ghWndInfoTool, IDC_LST_RFID));
					for (i = 0; i < count; i++) {
						ListBox_DeleteString(GetDlgItem(ghWndInfoTool, IDC_LST_RFID), 0);
					}
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
	ghWndInfoTool = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DLG_INFOTOOL), hWnd, InfoToolProc);

	if (ghWndInfoTool == NULL) {
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

int insertString(char* str)
{
	HWND dlg = GetDlgItem(ghWndInfoTool, IDC_LST_RFID);

	ListBox_InsertString(dlg, -1,str);
	ListBox_SetCurSel(dlg, ListBox_GetCount(dlg) - 1);
	SetFocus(dlg);
	return TRUE;

}

/*int CreateReadThread(HWND hwnd)
*Purpose: Creates an additional thread for reading.
*Arg 1 - Decides whether the window will be normal, maximized or minimized.
*/
int CreateReadThread(HWND hwnd) {
	if((hThread = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE) ReadThread, hwnd,
		0, NULL)) == INVALID_HANDLE_VALUE) {
		ReadThreadErrorMsg();
		CloseHandle (hComm);
		return FALSE;
	}
	return TRUE;
}

/*void CommProperties(HWND hwnd, LPTSTR CommPort)
*Purpose: Prompts the user for the comm settings and saves them.
*Arg 1 - Handle to the window procedure.
*Arg 2 - The name of the port to be opened.
*/
void CommProperties(HWND hwnd, LPTSTR CommPort) {
	if(mode == CONNECT) {
		CntChngSettingsMsg();
		return;
	}
	commConfig.dwSize = sizeof(COMMCONFIG);
	commConfig.wVersion = 0x100;
	if(!CommConfigDialog(CommPort, hwnd, &commConfig)) {
        FailedPortMsg();
		return;
	}
	lpszCommName = CommPort;
}

void CheckAvailPorts(HWND hwnd) {
	int i;
	HMENU hmenu = GetMenu(hwnd);
	LPCWSTR CommPort = (LPCWSTR)TEXT("com4");
	UINT portNumber = ID_PORT_COM1;
	for(i = 0; i < NUMBEROFPORTS; i++) {
		switch(i) {
		case 1:
			CommPort = (LPCWSTR)TEXT("com1");
			portNumber = ID_PORT_COM1;
			break;
		case 2:
			CommPort = (LPCWSTR)TEXT("com2");
			portNumber = ID_PORT_COM2;
			break;
		case 3:
			CommPort = (LPCWSTR)TEXT("com3");
			portNumber = ID_PORT_COM3;
			break;
		case 4:
			CommPort = (LPCWSTR)TEXT("com4");
			portNumber = ID_PORT_COM4;
			break;
		case 5:
			CommPort = (LPCWSTR)TEXT("com5");
			portNumber = ID_PORT_COM5;
			break;
		case 6:
			CommPort = (LPCWSTR)TEXT("com6");
			portNumber = ID_PORT_COM6;
			break;
		case 7:
			CommPort = (LPCWSTR)TEXT("com7");
			portNumber = ID_PORT_COM7;
			break;
		case 8:
			CommPort = (LPCWSTR)TEXT("com8");
			portNumber = ID_PORT_COM8;
			break;
		case 9:
			CommPort = (LPCWSTR)TEXT("com9");
			portNumber = ID_PORT_COM9;
			break;
		}
		if((hComm = CreateFile((LPCSTR)CommPort, GENERIC_READ | GENERIC_WRITE, 0,
				NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL))
				== INVALID_HANDLE_VALUE) {
			EnableMenuItem(hmenu, portNumber, MF_GRAYED);
			
		}
		CloseHandle(hComm);
	}
}