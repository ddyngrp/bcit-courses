/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	events.c -   A general purpose event handler for menus and dialogs.
--
--	PROGRAM:		winsock_tool.exe
--
--	FUNCTIONS:		MenuDispatch(UINT iMenuChoice, HWND hWnd, LPARAM lParam)
--					Input_Host(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					Input_IP(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					Input_Port(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					Input_Service(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--
--	DATE:			January 26, 2009
--
--	REVISIONS:		
--
--	DESIGNERS:		Steffen L. Norgren
--
--	PROGRAMMER:		Steffen L. Norgren
--
--	NOTES:	This is a simple menu event handler. It responds to user menu and dialog
--			selections and takes appropriate action depending on the user's input.
--			Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include <windows.h>
#include <commctrl.h>
#include "winMain.h"
#include "resource.h"
#include "wsTools.h"

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	MenuDispatch
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	MenuDispatch(UINT iMenuChoice, HWND hWnd, LPARAM lParam)
--					UINT iMenuChoice:	ID of the menu choice (from resource file)
--					HWND hWnd:			Window handle of menu owner
--					LPARAM lParam:		Window message parameter (depends on message)
-- 
--	RETURNS:	void
-- 
--	NOTES:	This function simply deals with menu events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
void MenuDispatch(UINT iMenuChoice, HWND hWnd, LPARAM lParam) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	switch (iMenuChoice) {
		// File Menu
		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		case ID_EDIT_CLEAROUTPUT:
			ClearOutput();
			break;

		case ID_WINSOCK_RESOLVEIPADDRESS:
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_IP_INPUT), hWnd, Input_IP);
			break;

		case ID_WINSOCK_RESOLVEHOSTNAME:
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_HOST_INPUT), hWnd, Input_Host);
			break;

		case ID_WINSOCK_RESOLVESVCNAME:
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_PORT_INPUT), hWnd, Input_Port);
			break;

		case ID_WINSOCK_RESOLVESVCPORT:
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_SVC_INPUT), hWnd, Input_Service);
			break;
		
		default:
			// No action necessary
			break;
	}
	return;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	Input_Host
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	Input_Host(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hDlg:		Dialog handle
--					UINT message:	Dialog message
--					WPARAM wParam:	Dialog message parameter (depends on message)
--					LPARAM lParam:	Dialog message parameter (depends on message)
-- 
--	RETURNS:	0:	the message was processed
--				!0:	the message was not processed and passed to DefWindowProc
--
--	NOTES:	This function simply deals with dialog events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
BOOL CALLBACK Input_Host(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	int cTxtLen;
	PSTR pszHostName;

	switch (message) {
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, IDC_HOST_NAME));
			return FALSE;

		case WM_SETFOCUS:
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					if (GetWindowTextLength(GetDlgItem(hDlg, IDC_HOST_NAME)) < 4) {
						MessageBox(NULL, (LPCSTR)"Host name must be greater than 4 characters.",
									NULL, MB_OK | MB_ICONSTOP);
						break;
					}
					else {
						cTxtLen = GetWindowTextLength(GetDlgItem(hDlg, IDC_HOST_NAME));

						pszHostName = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtLen + 1),
										MEM_COMMIT, PAGE_READWRITE);

						GetWindowText(GetDlgItem(hDlg, IDC_HOST_NAME), (LPSTR)pszHostName, cTxtLen + 1);

						EndDialog(hDlg, wParam);
						ws_name_addr(pszHostName); // Lookup the host name
						return TRUE;
					}

				case IDCANCEL:
					EndDialog(hDlg, wParam); 
					return TRUE;
			}
			return TRUE;
	}
	return FALSE;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	Input_IP
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	Input_IP(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hDlg:		Dialog handle
--					UINT message:	Dialog message
--					WPARAM wParam:	Dialog message parameter (depends on message)
--					LPARAM lParam:	Dialog message parameter (depends on message)
-- 
--	RETURNS:	0:	the message was processed
--				!0:	the message was not processed and passed to DefWindowProc
--
--	NOTES:	This function simply deals with dialog events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
BOOL CALLBACK Input_IP(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	LPDWORD	pdwAddr;

	switch (message) {
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, IDC_IP_ADDRESS));
			return FALSE;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					pdwAddr = (LPDWORD)VirtualAlloc((LPVOID)NULL, (DWORD)(4),
								MEM_COMMIT, PAGE_READWRITE);

					if (SendMessage(GetDlgItem(hDlg, IDC_IP_ADDRESS), IPM_GETADDRESS, 0,
							(LPARAM)(LPDWORD)pdwAddr) != 4) {
						MessageBox(NULL, (LPCSTR)"Please all four parts of the IP address.",
									NULL, MB_OK | MB_ICONSTOP);
						break;
					}
					else {
						EndDialog(hDlg, wParam); 
						ws_addr_name(pdwAddr); // Look up the IP address
						return TRUE;
					}

				case IDCANCEL:
					EndDialog(hDlg, wParam); 
					return TRUE;
			}
			return TRUE;
	}
	return FALSE;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	Input_Port
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	Input_Port(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hDlg:		Dialog handle
--					UINT message:	Dialog message
--					WPARAM wParam:	Dialog message parameter (depends on message)
--					LPARAM lParam:	Dialog message parameter (depends on message)
-- 
--	RETURNS:	0:	the message was processed
--				!0:	the message was not processed and passed to DefWindowProc
--
--	NOTES:	This function simply deals with dialog events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
BOOL CALLBACK Input_Port(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	int cTxtPortLen, cTxtProtoLen;
	PSTR pszPortNum, pszProto;

	switch (message) {
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, IDC_PORT_NUMBER));
			return FALSE;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					if (GetWindowTextLength(GetDlgItem(hDlg, IDC_PORT_NUMBER)) == 0) {
						MessageBox(NULL, (LPCSTR)"Port number field cannot be empty.",
									NULL, MB_OK | MB_ICONSTOP);
						break;
					}
					else if (GetWindowTextLength(GetDlgItem(hDlg, IDC_PROTO)) != 3) {
						MessageBox(NULL, (LPCSTR)"Protocol must be either TCP or UDP.",
									NULL, MB_OK | MB_ICONSTOP);
						break;
					}
					else {
						cTxtPortLen = GetWindowTextLength(GetDlgItem(hDlg, IDC_PORT_NUMBER));
						cTxtProtoLen = GetWindowTextLength(GetDlgItem(hDlg, IDC_PROTO));

						pszPortNum = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtPortLen + 1),
										MEM_COMMIT, PAGE_READWRITE);
						pszProto = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtProtoLen + 1),
										MEM_COMMIT, PAGE_READWRITE);

						GetWindowText(GetDlgItem(hDlg, IDC_PORT_NUMBER), (LPSTR)pszPortNum, cTxtPortLen + 1);
						GetWindowText(GetDlgItem(hDlg, IDC_PROTO), (LPSTR)pszProto, cTxtProtoLen + 1);

						if (isdigit(*pszPortNum)) {
							if (atoi(pszPortNum) < 0 || atoi(pszPortNum) > 65535) {
								MessageBox(NULL, (LPCSTR)"Port must be a non-negative number from 1-65535.",
										NULL, MB_OK | MB_ICONSTOP);
								break;
							}
						}
						else {
							MessageBox(NULL, (LPCSTR)"Port must be a number.",
										NULL, MB_OK | MB_ICONSTOP);
							break;
						}

						// Check for proper protocol entry
						if (toupper(pszProto[0]) == 'T') {
							if (toupper(pszProto[1]) != 'C' || toupper(pszProto[2]) != 'P') {
								MessageBox(NULL, (LPCSTR)"Protocol must be either TCP or UDP.",
									NULL, MB_OK | MB_ICONSTOP);
								break;
							}
						}
						if (toupper(pszProto[0]) == 'U') {
							if (toupper(pszProto[1]) != 'D' || toupper(pszProto[2]) != 'P') {
								MessageBox(NULL, (LPCSTR)"Protocol must be either TCP or UDP.",
									NULL, MB_OK | MB_ICONSTOP);
								break;
							}
						}

						EndDialog(hDlg, wParam);
						ws_port_svc(pszPortNum, pszProto); // Lookup the service name
						return TRUE;
					}

				case IDCANCEL:
					EndDialog(hDlg, wParam); 
					return TRUE;
			}
			return TRUE;
	}
	return FALSE;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	Input_Service
-- 
--	DATE:		January 26, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	Input_Service(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hDlg:		Dialog handle
--					UINT message:	Dialog message
--					WPARAM wParam:	Dialog message parameter (depends on message)
--					LPARAM lParam:	Dialog message parameter (depends on message)
-- 
--	RETURNS:	0:	the message was processed
--				!0:	the message was not processed and passed to DefWindowProc
--
--	NOTES:	This function simply deals with dialog events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
BOOL CALLBACK Input_Service(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	int cTxtSvcLen, cTxtProtoLen;
	PSTR pszSvcName, pszProto;

	switch (message) {
		case WM_INITDIALOG:
			SetFocus(GetDlgItem(hDlg, IDC_SVC_NAME));
			return FALSE;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					if (GetWindowTextLength(GetDlgItem(hDlg, IDC_SVC_NAME)) == 0) {
						MessageBox(NULL, (LPCSTR)"Service field cannot be empty.",
									NULL, MB_OK | MB_ICONSTOP);
						break;
					}
					else if (GetWindowTextLength(GetDlgItem(hDlg, IDC_PROTO)) != 3) {
						MessageBox(NULL, (LPCSTR)"Protocol must be either TCP or UDP.",
									NULL, MB_OK | MB_ICONSTOP);
						break;
					}
					else {
						cTxtSvcLen = GetWindowTextLength(GetDlgItem(hDlg, IDC_SVC_NAME));
						cTxtProtoLen = GetWindowTextLength(GetDlgItem(hDlg, IDC_PROTO));

						pszSvcName = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtSvcLen + 1),
										MEM_COMMIT, PAGE_READWRITE);
						pszProto = (PSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(cTxtProtoLen + 1),
										MEM_COMMIT, PAGE_READWRITE);

						GetWindowText(GetDlgItem(hDlg, IDC_SVC_NAME), (LPSTR)pszSvcName, cTxtSvcLen + 1);
						GetWindowText(GetDlgItem(hDlg, IDC_PROTO), (LPSTR)pszProto, cTxtProtoLen + 1);

						// Check for proper protocol entry
						if (toupper(pszProto[0]) == 'T') {
							if (toupper(pszProto[1]) != 'C' || toupper(pszProto[2]) != 'P') {
								MessageBox(NULL, (LPCSTR)"Protocol must be either TCP or UDP.",
									NULL, MB_OK | MB_ICONSTOP);
								break;
							}
						}
						if (toupper(pszProto[0]) == 'U') {
							if (toupper(pszProto[1]) != 'D' || toupper(pszProto[2]) != 'P') {
								MessageBox(NULL, (LPCSTR)"Protocol must be either TCP or UDP.",
									NULL, MB_OK | MB_ICONSTOP);
								break;
							}
						}

						EndDialog(hDlg, wParam);
						ws_svc_port(pszSvcName, pszProto); // Lookup port number
						return TRUE;
					}

				case IDCANCEL:
					EndDialog(hDlg, wParam); 
					return TRUE;
			}
			return TRUE;
	}
	return FALSE;
}