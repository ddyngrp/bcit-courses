/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	winProc.c -   Handles the program's main window and associated events
--
--	PROGRAM:		music_streamer.exe
--
--	FUNCTIONS:		WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
--					InitWindow(HWND hWnd)
--					PaintWindow(HWND hWnd)
--
--
--	DATE:			March 16, 2009
--
--	REVISIONS:		
--
--	DESIGNERS:		Steffen L. Norgren
--	PROGRAMMER:		Steffen L. Norgren
--
--	NOTES:	This is a simple menu event handler. It responds to user menu selections
--			and takes appropriate action depending on the user's selection.
--			Remember to add "WS2_32.Lib" to the project source list.
---------------------------------------------------------------------------------------*/

#include "win_main.h"
#include "win_events.h"

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	WndProc
-- 
--	DATE:		March 16, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hWnd:		Window handle
--					UINT message:	Window message
--					WPARAM wParam:	Window message parameter (depends on message)
--					LPARAM lParam:	Window message parameter (depends on message)
-- 
--	RETURNS:	0: If message was processed
--				Otherwise it will return the value of DefWindowProc
-- 
--	NOTES:	Windows procedure for the main window.
--
---------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_SIZE, OnSize);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hWnd, WM_TCP_SOCKET, OnTCPSocket);
		HANDLE_MSG(hWnd, WM_UDP_SOCKET, OnTCPSocket);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		
		case MM_WIM_OPEN:  //called on waveInOpen()
			/* start recording */
			open_mic_device();
			break;

		case MM_WIM_DATA:
			/*num = send(ci.tcpSocket,((PWAVEHDR)lParam)->lpData, ((PWAVEHDR)lParam)->dwBytesRecorded,0);
			num = WSAGetLastError();
			res = HRESULT_FROM_WIN32(num);

			waveInAddBuffer(hWaveIn, (PWAVEHDR)lParam->lpdata, sizeof(WAVEHDR));*/
			read_mic_data(lParam);
			break;

		case MM_WIM_CLOSE:
			close_mic();
			break;

		case MM_WOM_OPEN: //called on waveOutOpen()
			open_output_device();
			break;

		case MM_WOM_DONE:
			output_done();
			break;

		case MM_WOM_CLOSE:
			//close_output();
			break;

		case WM_SYSCOMMAND:
			switch(LOWORD(lParam))
			{
			case SC_CLOSE:
				terminate_mic_session();

			default:
				break;
			}

			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*------------------------------------------------------------------------
--		FUNCTION:		ClientProc
--
--		DATE:			February 20, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		LRESULT CALLBACK WndProc(HWND hwnd,
--						UINT message, WPARAM wParam, LPARAM lParam)
--							HWND hwnd: Handle to the client dialog
--							UINT message: Current message ID
--							WPARAM wParam: Message parameter
--							LPARAM lParam: Message parameter
--
--		RETURNS:		The result of the processed message
--
--		NOTES:			This is the message handler for the client
--						dialog box.
------------------------------------------------------------------------*/
BOOL CALLBACK ClientProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:
		return FALSE;

	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			GetDlgItemText(hDlg, IDC_EDT_IPADDR, ci.ip, 26);

			if(ci.ip[0] != '\0')
				EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);

			EndDialog(hDlg, TRUE);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, FALSE);
			return TRUE;
		}

		break;
	}

	return FALSE;
}

/*------------------------------------------------------------------------
--		FUNCTION:		ServerProc
--
--		DATE:			February 20, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		LRESULT CALLBACK WndProc(HWND hwnd,
--						UINT message, WPARAM wParam, LPARAM lParam)
--							HWND hwnd: Handle to the server dialog
--							UINT message: Current message ID
--							WPARAM wParam: Message parameter
--							LPARAM lParam: Message parameter
--
--		RETURNS:		The result of the processed message
--
--		NOTES:			This is the message handler for the server
--						dialog box.
------------------------------------------------------------------------*/
BOOL CALLBACK ServerProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_INITDIALOG:
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDOK:
				/* Use this method to find checked items */
				if (SendMessage(GetDlgItem(hDlg, IDC_MULTICAST), BM_GETCHECK, 0, 0) == BST_CHECKED) {
					MessageBox(ghWndMain, (LPCSTR)"Checked!", (LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				}

				EndDialog(hDlg, TRUE);
				return TRUE;

			case IDCANCEL:
				EndDialog(hDlg, FALSE);
				return TRUE;
			}
	}

	return FALSE;
}
