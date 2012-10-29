/*------------------------------------------------------------------------------
	MODULE: commConfig.c

	PURPOSE: Handle all communications port configuration settings as well
			 as any dialog box associated with configuring the COM port.

	AUTHORS: Steffen L. Norgren
			 Doug Penner

/*-----------------------------------------------------------------------------*/

#include "terminal.h"

#define MAXLEN_TEMPSTR	20

// Function prototypes
BOOL CALLBACK ConfigureComPortDlg(HWND, UINT, WPARAM, LPARAM);
void PopulateCOMPorts(HWND);
void PopulateCOMSettings(HWND);
void FillComboBox(HWND, char **, DWORD *, WORD, DWORD);
void UpdateTTYInfo(HWND);
DWORD GetdwTTYITem(HWND, int, char **, DWORD *, int);
BYTE GetbTTYITem(HWND, int, char **, DWORD *, int);

// GLOBALS settings
char * szBaud[] = {"300", "1200", "2400", "4800",
				   "9600", "19200", "38400", "57600",
				   "115200", "128000", "256000"};
DWORD	BaudTable[] = {CBR_300, CBR_1200, CBR_2400, CBR_4800,
					   CBR_9600, CBR_19200, CBR_38400, CBR_57600,
					   CBR_115200, CBR_128000, CBR_256000};

char * szParity[] = {"None", "Even", "Odd", "Mark", "Space"};
DWORD	ParityTable[] = {NOPARITY, EVENPARITY, ODDPARITY, MARKPARITY, SPACEPARITY};

char * szStopBits[] = {"1", "1.5", "2"};
DWORD	StopBitsTable[] = {ONESTOPBIT, ONE5STOPBITS, TWOSTOPBITS};


/*------------------------------------------------------------------------------
	FUNCTION: CmdPort(HWND)

	PURPOSE: Creates the modal Select COM Port dialog

	PARAMETERS:
		hwnd	- window handle

/*-----------------------------------------------------------------------------*/
void CmdPort(HWND hwnd) {
	DialogBox(ghInst, MAKEINTRESOURCE(IDD_DLG_CONFIG), hwnd, ConfigureComPortDlg);
}

/*------------------------------------------------------------------------------
	FUNCTION: ConfigureComPortDlg(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Responds to actions within the COM Port config dialog window

	PARAMETERS:
		hDlg	- dialog handle
		message	- dialog message
		wParam	- dialog message parameter (depends on message)
		lParam	- dialog message parameter (depends on message)

	RETURN:
		If the message was processed, the return value is 0
		If the message was not processed and passed to DefWindowProc
		and the return value depends on the value of that function.

/*-----------------------------------------------------------------------------*/
BOOL CALLBACK ConfigureComPortDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;

	switch (message) {
		case WM_INITDIALOG:
			PopulateCOMPorts(hDlg);	
			PopulateCOMSettings(hDlg);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDOK:
					EndDialog(hDlg, 0);
					UpdateTTYInfo(hDlg);

					hMenu = GetMenu(ghWndMain);	// get the menu handle

					EnableMenuItem(hMenu,
						ID_FILE_CONNECT, MF_ENABLED); // enable the connect menu
					EnableMenuItem(hMenu,
						ID_FILE_DISCONNECT, MF_GRAYED | MF_DISABLED); // disable the connect menu
					return TRUE;

				case IDCANCEL:
					EndDialog(hDlg, 0);
					return TRUE;
			}
			break;

		case WM_SETFOCUS:
			return TRUE;
	}
	return FALSE;
}

/*------------------------------------------------------------------------------
	FUNCTION: PopulateCOMPorts(HWND)

	PURPOSE: Populates the COM Port list-box with a list of all the available
			 COM ports on the system.

	PARAMETERS:
		hDlg	- dialog handle

/*-----------------------------------------------------------------------------*/
void PopulateCOMPorts(HWND hDlg) {
	char szBuffer[MAXLEN_TEMPSTR], szTemp[MAXLEN_TEMPSTR]; // character buffers to deal with string concats
	WORD wCount;
	BOOL bSuccess;
	HANDLE hPort;

	strcpy(szTemp, "COM");

	// Cycle through up to MAXPORTS COM ports
	for (wCount = 1; wCount < MAXPORTS + 1; wCount++) {
		wsprintf(szBuffer, "%s%d", (LPSTR)szTemp, wCount);

		// try to open the port
		bSuccess = FALSE;
		hPort = CreateFile(szBuffer,
			GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

		if (hPort == INVALID_HANDLE_VALUE) {
			DWORD dwError = GetLastError();

			// Check to see if the error was because the port was in use or a general failure
			if (dwError == ERROR_ACCESS_DENIED || dwError == ERROR_GEN_FAILURE) {
				bSuccess = TRUE;
			}
		}
		else {
			// The port was opened successfully
			bSuccess = TRUE;

			// Release the port handle
			CloseHandle(hPort);
		}

		// Add the COM port to the combo-box
		if (bSuccess) {
			SendDlgItemMessage(hDlg, IDC_COMPORT_COMBO, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
		}
	}

	// Select the first COM port in the list
	SendDlgItemMessage(hDlg, IDC_COMPORT_COMBO, CB_SETCURSEL, (WPARAM)0, 0L);

	// Update global COM port setting
	GetDlgItemText(hDlg, IDC_COMPORT_COMBO, gszPort, sizeof(gszPort));
}

/*------------------------------------------------------------------------------
	FUNCTION: PopulateCOMSettings(HWND)

	PURPOSE: Initialize the COM Port settings dialog controls.

	PARAMETERS:
		hDlg	- Dialog window handle

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for use in this assignment.

/*-----------------------------------------------------------------------------*/
void PopulateCOMSettings(HWND hDlg) {
	char szBuffer[MAXLEN_TEMPSTR];
	WORD wCount, wPosition;

	// Fill baud combo box and make initial selection
	FillComboBox(GetDlgItem(hDlg, IDC_BPS_COMBO),
		szBaud, BaudTable, 
		sizeof(BaudTable) / sizeof(BaudTable[0]),
		BAUDRATE(TTYInfo));

	// Fill data bits combo box and make initial selection
	for (wCount = 5; wCount < 9; wCount++) {
		wsprintf(szBuffer, "%d", wCount);
		wPosition = LOWORD(SendDlgItemMessage(hDlg,
			IDC_DATABITS_COMBO, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer));
	
		if (wCount == BYTESIZE(TTYInfo)) {
			SendDlgItemMessage(hDlg,
				IDC_DATABITS_COMBO, CB_SETCURSEL, (WPARAM)wPosition, 0L);
		}
	}

	// Fill parity combo box and make initial selection
	FillComboBox(GetDlgItem(hDlg, IDC_PARITY_COMBO),
		szParity, ParityTable, 
		sizeof(ParityTable) / sizeof(ParityTable[0]),
		PARITY(TTYInfo));

	// Fill stop bits combo box and make initial selection
	FillComboBox(GetDlgItem(hDlg, IDC_STOPBITS_COMBO),
		szStopBits, StopBitsTable, 
		sizeof(StopBitsTable) / sizeof(StopBitsTable[0]),
		STOPBITS(TTYInfo));
}

/*------------------------------------------------------------------------------
	FUNCTION: FillComboBox(HWND, char **, DWORD *, WORD, DWORD)

	PURPOSE: Populates a dialog control with strings

	PARAMETERS:
		hCtrlWnd			- the window handle of the control being populated
		szString			- string table that we're using to fill the control
		npTable				- table of control values that corespond to the strings
		wTableLen			- length of the table of strings
		dwCurrentSetting	- initialize combo box selection

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for use in this assignment.

/*-----------------------------------------------------------------------------*/
void FillComboBox(HWND hCtrlWnd, char ** szString, DWORD * npTable,
				  WORD wTableLen, DWORD dwCurrentSetting) {
	WORD wCount, wPosition;

	for (wCount = 0; wCount < wTableLen; wCount++) {
		wPosition = LOWORD(SendMessage(hCtrlWnd, CB_ADDSTRING, 0,
			(LPARAM)(LPSTR)szString[wCount]));

		// Use item data to store the actual table value
		SendMessage(hCtrlWnd, CB_SETITEMDATA, (WPARAM)wPosition,
			(LPARAM) *(npTable + wCount));

		// If this is the current setting, select it
		if (*(npTable + wCount) == dwCurrentSetting) {
			SendMessage(hCtrlWnd, CB_SETCURSEL, (WPARAM)wPosition, 0L);
		}
	}
}

/*------------------------------------------------------------------------------
	FUNCTION: UpdateTTYInfo(HWND hDlg)

	PURPOSE: Updates the info in the TTYInfo struct with that which was
			 entered within the dialog box.

	PARAMETERS:
		hDlg	- Dialog window handle

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for use in this assignment.

/*-----------------------------------------------------------------------------*/
void UpdateTTYInfo(HWND hDlg) {
	GetDlgItemText(hDlg, IDC_COMPORT_COMBO, gszPort, sizeof(gszPort));

	BAUDRATE(TTYInfo) = GetdwTTYITem(hDlg, IDC_BPS_COMBO,
		szBaud, BaudTable, sizeof(BaudTable) / sizeof(BaudTable[0]));

	PARITY(TTYInfo) = GetbTTYITem(hDlg, IDC_PARITY_COMBO,
		szParity, ParityTable, sizeof(ParityTable) / sizeof(ParityTable[0]));

	STOPBITS(TTYInfo) = GetbTTYITem(hDlg, IDC_STOPBITS_COMBO,
		szStopBits, StopBitsTable, sizeof(StopBitsTable) / sizeof(StopBitsTable[0]));

	BYTESIZE(TTYInfo) = GetDlgItemInt(hDlg, IDC_DATABITS_COMBO, NULL, FALSE);
}

/*------------------------------------------------------------------------------
	FUNCTION: GetdwTTYITem(HWND, int, char **, DWORD *, int)

	PURPOSE: Populates a dialog control with strings

	PARAMETERS:
		hDlg		- Dialog window handle
		idControl	- ID of control from which to retrieve data
		szString	- table of strings that the control displays
		pTable		- table of data associated with the strings
		iNumItems	- size of the table

	RETURN:
		DWORD item corresponding to control selection
		0 if item is not found

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for use in this assignment.

/*-----------------------------------------------------------------------------*/
DWORD GetdwTTYITem(HWND hDlg, int idControl, char ** szString,
				   DWORD * pTable, int iNumItems) {
	int i;
	char szItem[MAXLEN_TEMPSTR];

	// Get the current selection
	GetDlgItemText(hDlg, idControl, szItem, sizeof(szItem));

	// Compare current selection with the table to find index.
	for (i = 0; i < iNumItems; i++) {
		if (strcmp(szString[i], szItem) == 0) {
			return pTable[i];
		}
	}

	return 0;
}

/*------------------------------------------------------------------------------
	FUNCTION: GetbTTYITem(HWND, int, char **, DWORD *, int)

	PURPOSE: Populates a dialog control with strings

	PARAMETERS:
		hDlg		- Dialog window handle
		idControl	- ID of control from which to retrieve data
		szString	- table of strings that the control displays
		pTable		- table of data associated with the strings
		iNumItems	- size of the table

	RETURN:
		BYTE item corresponding to control selection
		0 if item is not found

	NOTE: This function was originally found in the Win32 MTTTY sample
		  written by AllenD. Modified for use in this assignment.

/*-----------------------------------------------------------------------------*/
BYTE GetbTTYITem(HWND hDlg, int idControl, char ** szString,
				 DWORD * pTable, int iNumItems) {
	int i;
	char szItem[MAXLEN_TEMPSTR];

	// Get the current selection
	GetDlgItemText(hDlg, idControl, szItem, sizeof(szItem));

	// Compare current selection with the table to find index.
	for (i = 0; i < iNumItems; i++) {
		if (strcmp(szString[i], szItem) == 0) {
			return (BYTE)pTable[i];
		}
	}

	return 0;
}