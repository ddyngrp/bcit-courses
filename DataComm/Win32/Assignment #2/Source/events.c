/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	events.c -   A general purpose event handler for menus and dialogs.
--
--	PROGRAM:		datagram_analyzer.exe
--
--	FUNCTIONS:		MenuDispatch(UINT iMenuChoice, HWND hWnd, LPARAM lParam)
--					Input_Host(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					Input_IP(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--
--	DATE:			January 26, 2009
--
--	REVISIONS:		February 20, 2009 - Modified for use in new program.
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
--	REVISIONS:	February 20, 2009 - Modified for use in new program.
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
		case ID_FILE_CONNECT:
			break;
		case ID_FILE_DISCONNECT:
			break;
		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		// Operation Mode Menu
		case ID_OPERATIONMODE_CLIENT:
			if (mode != CLIENT) {
				CheckMenuItem(hMenu, ID_OPERATIONMODE_CLIENT, MF_CHECKED);
				CheckMenuItem(hMenu, ID_OPERATIONMODE_SERVER, MF_UNCHECKED);
				mode = CLIENT;
			}
			break;
		case ID_OPERATIONMODE_SERVER:
			if (mode != SERVER) {
				CheckMenuItem(hMenu, ID_OPERATIONMODE_CLIENT, MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_OPERATIONMODE_SERVER, MF_CHECKED);
				mode = SERVER;
			}
			break;
		case ID_PEERADDRESS_IPADDRESS: // Open IP Address Dialogue
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_IP_INPUT), hWnd, Input_IP);
			break;
		case ID_PEERADDRESS_HOSTNAME: // Open Hostname Dialogue
			DialogBox(ghInst, MAKEINTRESOURCE(IDD_HOST_INPUT), hWnd, Input_Host);
			break;

		// Protocol Menu
		case ID_PROTOCOL_TCP:
			if (proto != TCP) {
				CheckMenuItem(hMenu, ID_PROTOCOL_TCP, MF_CHECKED);
				CheckMenuItem(hMenu, ID_PROTOCOL_UDP, MF_UNCHECKED);
				proto = TCP;
			}
			break;
		case ID_PROTOCOL_UDP:
			if (proto != UDP) {
				CheckMenuItem(hMenu, ID_PROTOCOL_TCP, MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_PROTOCOL_UDP, MF_CHECKED);
				proto = UDP;
			}
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
--	REVISIONS:	February 20, 2009 - Modified for use in new program.
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

						// Validate host name
						if (!ws_name_addr(pszHostName)) { // Lookup the host name
							break;
						}
						else {
							EndDialog(hDlg, wParam);
							return TRUE;
						}
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
--	REVISIONS:	February 20, 2009 - Modified for use in new program.
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
						// Validate IP Address
						if (!ws_addr_name(pdwAddr)) { // Look up the IP address
							break;
						}
						else {
							EndDialog(hDlg, wParam);
							return TRUE;
						}
					}

				case IDCANCEL:
					EndDialog(hDlg, wParam); 
					return TRUE;
			}
			return TRUE;
	}
	return FALSE;
}