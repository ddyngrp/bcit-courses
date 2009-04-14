/*-----------------------------------------------------------------------------
--	SOURCE FILE:	win_proc.c
--
--	PROGRAM:		CommAudio.exe
--
--	FUNCTIONS:		
--
--
--	DATE:			
--
--	DESIGNERS:		
--	PROGRAMMERS:	
--
--	NOTES:	
-----------------------------------------------------------------------------*/
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

static int received = FALSE;

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
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		
		case MM_WIM_OPEN:  //called on waveInOpen()
			/* start recording */
			open_mic_device();
			break;

		case MM_WIM_DATA:
			if (received == FALSE) {
				received = TRUE;
				sendto(ci.udpSocket, "1", sizeof("1"), 0, (struct sockaddr *)&udp_remote, 0);
				Sleep(100);
			}
			read_mic_data(lParam);
			break;

		case MM_WIM_CLOSE:
			close_mic();
			break;

		case MM_WOM_OPEN: /* called on waveOutOpen() */
			open_output_device();
			break;

		case MM_WOM_DONE:
			/* output_done(); */
			break;

		case MM_WOM_CLOSE:
			/* close_output(); */
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
			if (ci.request == MULTI_STREAM) {
				SendMessage(GetDlgItem(hDlg, IDC_MULTICAST), BM_SETCHECK, BST_CHECKED, 0);
			}
			return TRUE;

		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case IDOK:
				if (SendMessage(GetDlgItem(hDlg, IDC_MULTICAST), BM_GETCHECK, 0, 0) == BST_CHECKED) {
					ci.request = MULTI_STREAM;
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

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	MainDlgProc
-- 
--	DATE:		March 16
--
--	REVISIONS:	March 23 - Added code for local song play corresponding to the WM_COMMAND
--						   messages: IDC_BTN_PLAY, IDC_BTN_PAUSE, & IDC_BTN_STOPS
--				April 10 - Added up/down button handlers
-- 
--	DESIGNER:	Steffen L. Norgren
--	PROGRAMMER:	Steffen L. Norgren & Jaymz Boilard
-- 
--	INTERFACE:	MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					HWND hDlg:		Dialogue handle
--					UINT message:	Dialogue message
--					WPARAM wParam:	Dialogue message parameter (depends on message)
--					LPARAM lParam:	Dialogue message parameter (depends on message)
-- 
--	RETURNS:	0:	the message was processed
--				!0:	the message was not processed and passed to DefWindowProc
-- 
--	NOTES:	This function simply deals with dialogue events caused by user input and
--			calls the appropriate function based on the user's input.
--
---------------------------------------------------------------------------------------*/
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;
	char	fileName[FILE_BUFF_SIZE];
	char	outBuf[TEMP_BUFF_SIZE];
	DWORD	errNo;
	static	HANDLE streamThread;
	char	play_pause[10];
    
	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_INITDIALOG:
			return FALSE;

		case WM_SETFOCUS:
			break;

		case WM_COMMAND: // Process user input
			switch (LOWORD(wParam))
			{
                case IDC_BTN_PAUSE:
					GetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), play_pause, sizeof(play_pause));
					if (ci.request != MULTI_STREAM) {
						if(strcmp(play_pause, "Pause") == 0) {
							SetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), (LPCSTR)"Play");
							if(busyFlag == LOCALPLAY)
								localSong_Pause();
							else if(ci.request == SINGLE_STREAM)
							{
								if(waveOutPause(hWaveOut) != MMSYSERR_NOERROR)
								{
									errNo = GetLastError();
									MessageBox(NULL, "Can't pause", "Error", 0);
									
									return FALSE;
								}
							}
						}
						else {
							SetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), (LPCSTR)"Pause");
							if(busyFlag == LOCALPLAY)
								localSong_Play();
							else if (busyFlag == NETWORKPLAY)
								waveOutRestart(hWaveOut);
							else if(ci.request == SINGLE_STREAM)
								waveOutRestart(hWaveOut);
						}
					}
					else {
						if(strcmp(play_pause, "Mute") == 0) {
							SetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), (LPCSTR)"Un-mute");
							waveOutSetVolume(hWaveOut, 0x00000000);
						}
						else {
							SetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), (LPCSTR)"Mute");
							waveOutSetVolume(hWaveOut, 0xFFFFFFFF);
						}
					}
					return FALSE;

				case IDC_BTN_DOWNLOAD:

					if (ci.behaviour == CLIENT && (ci.request == SINGLE_STREAM
						|| ci.request == SINGLE_DL)) {

						/* Disable the button until the previous thread is terminated */
						EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_DOWNLOAD), FALSE);

						GetSelList(fileName);
						memset(outBuf, '\0', TEMP_BUFF_SIZE);
						strcpy_s(outBuf, sizeof(outBuf), fileName);
						strcpy_s(ci.DLfileName, sizeof(ci.DLfileName), fileName);

						if(send(ci.tcpSocket, outBuf, strlen(outBuf), 0) == -1)
						{
							if (WSAGetLastError() != WSAEWOULDBLOCK)
							{
								MessageBox(ghWndMain, (LPCSTR)"send() failed.",
									(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
								closesocket(wParam);
							}
						}

						if (ci.request == SINGLE_STREAM) {
							if(streamThread != NULL)
								TerminateThread(streamThread,0);

							Sleep(200);

							streamThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)receiveStream, (LPVOID)wParam, 0, 0);
							if(streamThread == NULL)
							{
								MessageBox(ghWndMain, (LPCSTR)"Thread creation failed.",
									(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
								ExitProcess(1);
							}

							SetFocus(GetDlgItem(ghDlgMain, IDC_LST_PLAY));

							/* Re-enable the button now */
							Sleep(400);
						}
						EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_DOWNLOAD), TRUE);
					}
                    return FALSE;

                case IDC_BTN_BROADCAST:
					GetSelList(ci.DLfileName);

					if(streamThread != NULL) {
						TerminateThread(streamThread,0);
						Sleep(200);
					}

					if((streamThread = CreateThread(NULL, 0, 
						(LPTHREAD_START_ROUTINE)sendStream, (LPVOID)wParam, 0, 0)) == NULL)
					{
						MessageBox(NULL, "Thread creation failed", NULL,MB_OK);
						ExitProcess(1);
					}

					SetFocus(GetDlgItem(ghDlgMain, IDC_LST_PLAY));
                    return FALSE;

				default:
					return FALSE;
			}
			return TRUE;
	}
	return FALSE;
}