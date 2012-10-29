/*
	MODULE: menuDialog.c

	PURPOSE: Manages events associated with menu and dialog controls.

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#include "s_winMain.h"
#include "s_resource.h"
#include "s_foreign.h"

// Private Variables
BOOL	fConnected = FALSE;	// Whether we're currently connected

/*
	FUNCTION: MenuDispatch(int, HWND, LPARAM)

	PURPOSE: Responds to menu selections

	PARAMETERS:
		iMenuChoice	- ID of the menu choice (from resource file)
		hWnd		- window handle of menu owner
		lParam		- window message parameter (depends on message)

*/
void MenuDispatch(UINT iMenuChoice, HWND hWnd, LPARAM lParam) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	switch (iMenuChoice) {
		// File Menu
		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		
		// Edit Menu
		case ID_EDIT_COPYSEL:
			break;
		case ID_EDIT_PASTESEL:
			break;

		// View Menu
		case ID_VIEW_CLEAR:
			ClearText(GetDlgItem(ghWndChat, IDC_SNT_TEXT)); // Clears Sent Text
			ClearText(GetDlgItem(ghWndChat, IDC_SND_TEXT)); // Clears Sending Text
			ClearText(GetDlgItem(ghWndChat, IDC_RCVD_TEXT)); // Clears Received Text
			break;

		// Help Menu
		case ID_HELP_ABOUT:
			break;
		case ID_HELP_USAGE:
			break;
	}
}

/*
	FUNCTION: DialogDispatch(HWND, WPARAM)

	PURPOSE: Responds to dialog actions

	PARAMETERS:
		hWnd		- window handle of menu owner
		wParam		- window message parameter (depends on message)

*/
void DialogDispatch(HWND hWnd, WPARAM wParam) {
	switch (LOWORD(wParam)) {
		case IDC_BTN_CONDIS:
			if (!fConnected) {
				if (foreign_Connect(gszPort)) {
					ToggleConnect();
				}
			}
			else {
				foreign_Disconnect();
				ToggleConnect();
			}
			break;
		
		case IDC_BTN_SEND:
			if (GetWindowTextLength(GetDlgItem(hWnd,IDC_SND_TEXT)) != 0) {
				SendText(hWnd);
			}
			break;
	}
}

/*
	FUNCTION: SendText(hWnd)

	PURPOSE: Sends text to the output buffer and adds it
			 to the sent text window.

	PARAMETERS:
		hWnd		- handle to the window

*/
void SendText(HWND hWnd) {
	PSTR	pSntText;
	int		iSntTextLen;

	iSntTextLen = GetWindowTextLength(GetDlgItem(hWnd,IDC_SND_TEXT)); 

	// Allocate memory for the extracted text
	pSntText = (PSTR) VirtualAlloc((LPVOID) NULL, (DWORD) (iSntTextLen + 1),
		MEM_COMMIT, PAGE_READWRITE);

	GetWindowText(GetDlgItem(hWnd,IDC_SND_TEXT), pSntText, iSntTextLen + 1);

	SetText(GetDlgItem(hWnd, IDC_SNT_TEXT), pSntText);
	foreign_SendText(pSntText);

	VirtualFree(pSntText, 0, MEM_RELEASE);
	ClearText(GetDlgItem(hWnd,IDC_SND_TEXT));
}

/*
	FUNCTION: SetText(HWND, char *)

	PURPOSE: Adds text to a window.

	PARAMETERS:
		hDlg		- handle dialog object
		text		- the text sent

*/
void SetText(HWND hDlg, char * text) {
	// Check to see if the dialog is empty, if not, send CRLF.
	if (GetWindowTextLength(hDlg) == 0) {
		SendMessage(hDlg, EM_SETSEL, -1, 0);					// Select zero chars from the edit of the current text  
		SendMessage(hDlg, EM_REPLACESEL, FALSE, (LPARAM)"> "); // Replace no chars at the end with text specified
		SendMessage(hDlg, EM_SETSEL, -1, 0);
		SendMessage(hDlg, EM_REPLACESEL, FALSE, (LPARAM)text);
	}
	else {
		SendMessage(hDlg, EM_SETSEL, -1, 0);
		SendMessage(hDlg, EM_REPLACESEL, FALSE, (LPARAM)"\r\n> ");
		SendMessage(hDlg, EM_SETSEL, -1, 0);
		SendMessage(hDlg, EM_REPLACESEL, FALSE, (LPARAM)text);
	}
}

/*
	FUNCTION: ClearText(HWND)

	PURPOSE: Clears text from the specified dialog

	PARAMETERS:
		hDlg		- handle dialog object

*/
void ClearText(HWND hDlg) {
	SetWindowText(hDlg, NULL);
}

/*
	FUNCTION: DialogDispatch()

	PURPOSE: Toggles the connect button from Connect to Disconnect

*/
void ToggleConnect() {
	if (!fConnected) {
		SendDlgItemMessage(ghWndChat, IDC_BTN_CONDIS, WM_SETTEXT, (WPARAM)0, (LPARAM)TEXT("Disconnect"));
		fConnected = TRUE;
	}
	else {
		SendDlgItemMessage(ghWndChat, IDC_BTN_CONDIS, WM_SETTEXT, (WPARAM)0, (LPARAM)TEXT("Connect"));
		fConnected = FALSE;
	}

	// Reset timer state
	gwSeconds = 0;
}

/*
	FUNCTION: ToggleSending()

	PURPOSE: Toggles sending radio button

*/
void ToggleSending() {
	if (IsDlgButtonChecked(ghWndChat, IDC_RAD_SND)) {
		CheckDlgButton(ghWndChat, IDC_RAD_SND, 0);
	}
	else {
		CheckDlgButton(ghWndChat, IDC_RAD_SND, 1);
	}

	// Reset timer state
	gwSeconds = 0;
}

/*
	FUNCTION: ToggleReceiving()

	PURPOSE: Toggles receiving radio button

*/
void ToggleReceiving() {
	if (IsDlgButtonChecked(ghWndChat, IDC_RAD_RCV)) {
		CheckDlgButton(ghWndChat, IDC_RAD_RCV, 0);
	}
	else {
		CheckDlgButton(ghWndChat, IDC_RAD_RCV, 1);
	}

	// Reset timer state
	gwSeconds = 0;
}

/*
	FUNCTION: TimerThread(BOOL)

	PURPOSE: Simple timer thread to manage updating the activity timer

*/
void TimerThread() {
	char szBuffer[20], szTemp[20]; // character buffers to deal with string concats
	BOOL loop = TRUE;

	gwSeconds = 0;

	while (loop) {
		strcpy_s(szTemp, 20, " s");
		wsprintf(szBuffer, "%d%s", gwSeconds, szTemp);
		SetWindowText(GetDlgItem(ghWndChat,IDC_LBL_TIMER), szBuffer);
		gwSeconds++;
		Sleep(1000);
	}
}