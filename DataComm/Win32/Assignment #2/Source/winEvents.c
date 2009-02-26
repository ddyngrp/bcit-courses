/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	winEvents.c - A general purpose event handler for menus and dialogs.
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

#include "wsCliSrv.h" // Must be first!
#include <winsock2.h>
#include <windows.h>
#include <commctrl.h>
#include "winMain.h"
#include "resource.h"
#include "wsTools.h"

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	MenuDispatch
-- 
--	DATE:		February 20, 2009
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
		case ID_FILE_CONNECT:
			if (mode == CLIENT) {
				if (Client() == TRUE) {
					EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_DISABLED);
					EnableMenuItem(hMenu, ID_FILE_DISCONNECT, MF_ENABLED);
				}
			}
			else if (mode == SERVER) {
				if (Server() == TRUE) {
					EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_DISABLED);
					EnableMenuItem(hMenu, ID_FILE_DISCONNECT, MF_ENABLED);
				}
			}
			break;
		case ID_FILE_DISCONNECT:
			EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_ENABLED);
			EnableMenuItem(hMenu, ID_FILE_DISCONNECT, MF_DISABLED);
			PostMessage(ghWndMain, WM_SOCKET, SocketInfo->Socket, FD_CLOSE);
			break;
		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		// Operation Mode Menu
		case ID_OPERATIONMODE_CLIENT:
			if (mode != CLIENT) {
				CheckMenuItem(hMenu, ID_OPERATIONMODE_CLIENT, MF_CHECKED);
				CheckMenuItem(hMenu, ID_OPERATIONMODE_SERVER, MF_UNCHECKED);

				// Enable Client functions
				EnableWindow(GetDlgItem(ghWndOutput, IDC_ED_SIZE), TRUE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_ED_REPEAT), TRUE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_BTN_OPEN), TRUE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_BTN_SEND), TRUE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_CHK_SENDFILE), FALSE);

				// Clear any currently open file info
				SetWindowText(GetDlgItem(ghWndOutput, IDC_ED_FILE), NULL);
				mode = CLIENT;
			}
			break;
		case ID_OPERATIONMODE_SERVER:
			if (mode != SERVER) {
				CheckMenuItem(hMenu, ID_OPERATIONMODE_CLIENT, MF_UNCHECKED);
				CheckMenuItem(hMenu, ID_OPERATIONMODE_SERVER, MF_CHECKED);

				// Disable Client functions
				EnableWindow(GetDlgItem(ghWndOutput, IDC_ED_SIZE), FALSE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_ED_REPEAT), FALSE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_BTN_OPEN), FALSE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_BTN_SEND), FALSE);
				EnableWindow(GetDlgItem(ghWndOutput, IDC_CHK_SENDFILE), FALSE);

				// Clear any currently open file info
				SetWindowText(GetDlgItem(ghWndOutput, IDC_ED_FILE), NULL);
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
--	FUNCTION:	Main_Output
-- 
--	DATE:		February 20, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	Main_Output(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
BOOL CALLBACK Main_Output(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_INITDIALOG:
			// Fill Out Default Values
			SetWindowText(GetDlgItem(hDlg, IDC_ED_SIZE), TEXT("1024"));
			SetWindowText(GetDlgItem(hDlg, IDC_ED_REPEAT), TEXT("10"));
			EnableWindow(GetDlgItem(hDlg, IDC_CHK_SENDFILE), FALSE);

			SetFocus(GetDlgItem(hDlg, IDC_HOST_NAME));
			return FALSE;

		case WM_SETFOCUS:
			break;

		case WM_COMMAND: // Process user input
			switch (LOWORD(wParam)) {
				// Buttons
				case IDC_BTN_OPEN: // Open a file
					{
						OPENFILENAME ofn;	// common dialog box structure
						char szFile[260];	// buffer for file name

						// Initialize OPENFILENAME
						ZeroMemory(&ofn, sizeof(ofn));
						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = hDlg;
						ofn.lpstrFile = szFile;

						// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
						// use the contents of szFile to initialize itself.
						ofn.lpstrFile[0] = '\0';
						ofn.nMaxFile = sizeof(szFile);
						ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
						ofn.nFilterIndex = 1;
						ofn.lpstrFileTitle = NULL;
						ofn.nMaxFileTitle = 0;
						ofn.lpstrInitialDir = NULL;
						ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

						// Display the Open dialog box. 
						if (GetOpenFileName(&ofn) == TRUE) { // Set the global file handle
							// Close existing file handle
							if (ghOF != NULL) {
								CloseHandle(ghOF);
							}
							ghOF = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL,
											OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);

							// Show the file that is currently open
							SetWindowText(GetDlgItem(hDlg, IDC_ED_FILE), szFile);

							// Enable sending files
							EnableWindow(GetDlgItem(hDlg, IDC_CHK_SENDFILE), TRUE);
						}
					}
					return TRUE;
				case IDC_BTN_SEND: // Send data
					FillBuffer(4096);
					PostMessage(ghWndMain, WM_SOCKET, SocketInfo->Socket, FD_WRITE);
					return TRUE;
				case IDC_BTN_CLEAR: // Clear log
					ClearLog();
					return TRUE;
				case IDC_BTN_SAVE: // Save log file
					{
						OPENFILENAME ofn;	// common dialog box structure
						char szFile[260];	// buffer for file name

						// Initialize OPENFILENAME
						ZeroMemory(&ofn, sizeof(ofn));
						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = hDlg;
						ofn.lpstrFile = szFile;

						// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
						// use the contents of szFile to initialize itself.
						ofn.lpstrFile[0] = '\0';
						ofn.nMaxFile = sizeof(szFile);
						ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
						ofn.nFilterIndex = 1;
						ofn.lpstrFileTitle = NULL;
						ofn.nMaxFileTitle = 0;
						ofn.lpstrInitialDir = NULL;
						ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

						// Display the Open dialog box.
						if (GetSaveFileName(&ofn) == TRUE) { // Set the global file handle
							// Close existing file handle
							if (ghSF != NULL) {
								CloseHandle(ghSF);
							}
							ghSF = CreateFile(ofn.lpstrFile, GENERIC_WRITE, 0, (LPSECURITY_ATTRIBUTES)NULL,
											OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
						}
					}
					return TRUE;

				// Check Boxes
				case IDC_CHK_SENDFILE: // Enable/Disable 
					return TRUE;
			}
			return TRUE;
	}
	return FALSE;
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
	HMENU hMenu;
	int cTxtLen;
	PSTR pszHostName;

	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_INITDIALOG:
			if (gHostName != NULL) { // If previously input, place value in window
				SetWindowText(GetDlgItem(hDlg, IDC_HOST_NAME), gHostName);
			}
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
							SetFocus(hDlg);
							break;
						}
						else {
							// Enable the Connect menu & close the dialogue
							EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_ENABLED);
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
	HMENU	hMenu;
	LPDWORD	pdwAddr;

	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_INITDIALOG:
			if ((void *)gIP != NULL) { // If previously input, place value in window
				SendMessage(GetDlgItem(hDlg, IDC_IP_ADDRESS), IPM_SETADDRESS, 0, gIP);
			}
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
							SetFocus(hDlg);
							break;
						}
						else {
							// Enable the Connect menu & close the dialogue
							EnableMenuItem(hMenu, ID_FILE_CONNECT, MF_ENABLED);
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