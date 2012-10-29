/*------------------------------------------------------------------------------
	MODULE: commConfig.c

	PURPOSE: Handle all communications port configuration settings as well
			 as any dialog box associated with configuring the COM port.

	AUTHORS: Steffen L. Norgren
			 Doug Penner

/*-----------------------------------------------------------------------------*/

#include "s_winMain.h"
#include "s_resource.h"

#define MAXLEN_TEMPSTR	20 // Maximum buffer length
#define MAXPORTS		255 // Maximum number of possible COM Ports

/*------------------------------------------------------------------------------
	FUNCTION: PopulateCOMPorts(HWND)

	PURPOSE: Populates the COM Port list-box with a list of all the available
			 COM ports on the system.

	PARAMETERS:
		hDlg	- dialog handle

/*-----------------------------------------------------------------------------*/
void PopulateCOMPorts(HWND hDlg) {
	char	szBuffer[20], szTemp[20]; // character buffers to deal with string concats
	int		maxPorts = 255;
	WORD	wCount;
	BOOL	bSuccess;
	HANDLE	hPort;

	strcpy_s(szTemp, MAXLEN_TEMPSTR, "COM");

	// Cycle through up to MAXPORTS COM ports
	for (wCount = 1; wCount < MAXPORTS + 1; wCount++) {
		wsprintf(szBuffer, "%s%d", szTemp, wCount);

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
			SendDlgItemMessage(hDlg, IDC_CMB_COMPORT, CB_ADDSTRING, 0, (LPARAM)(LPSTR)szBuffer);
		}
	}

	// Select the first COM port in the list
	SendDlgItemMessage(hDlg, IDC_CMB_COMPORT, CB_SETCURSEL, (WPARAM)0, 0L);

	// Update global COM port setting
	GetDlgItemText(hDlg, IDC_CMB_COMPORT, gszPort, sizeof(gszPort));
}