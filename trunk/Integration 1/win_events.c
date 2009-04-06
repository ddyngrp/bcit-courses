/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	win_events.c - A general purpose event handler for menus and dialogs.
--
--	PROGRAM:		music_streamer.exe
--
--	FUNCTIONS:		MenuDispatch(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--					Dlg_Main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
--
--	DATE:			March 16, 2009
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
#include "win_main.h"
#include "resource.h"

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	Dlg_Main
-- 
--	DATE:		March 16
--
--	REVISIONS:	March 23 - Added code for local song play corresponding to the WM_COMMAND
--						   messages: IDC_BTN_PLAY, IDC_BTN_PAUSE, & IDC_BTN_STOPS
-- 
--	DESIGNER:	Steffen L. Norgren
--	PROGRAMMER:	Steffen L. Norgren & Jaymz Boilard
-- 
--	INTERFACE:	Dlg_Main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
BOOL CALLBACK Dlg_Main(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;
	char * fileName;
    
    fileName = "meow.wav";
	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_INITDIALOG:
			return FALSE;

		case WM_SETFOCUS:
			break;

		case WM_COMMAND: // Process user input
			switch (LOWORD(wParam))
			{
				case IDC_BTN_PLAY:
                    if(busyFlag == LOCALPLAY)
                        localSong_Play();
                    else if (busyFlag == NETWORKPLAY)
					    waveOutRestart(hwo);
					return FALSE;

                case IDC_BTN_PAUSE:
                    if(busyFlag == LOCALPLAY)
                        localSong_Pause();
					return FALSE;

				case IDC_BTN_STOP:
                    if(busyFlag == LOCALPLAY)
                        localSong_Stop();
                    else
                        waveOutClose(hwo);
                    busyFlag = 0;
					//EnableMenuItem(ghMenu, ID_FILE_LOCAL, MF_ENABLED);
                    return FALSE;

                //button should be disabled when we're not in client mode
                case IDC_BTN_DOWNLOAD:
                    /* Send our file name then wait for the WAVEFORMATEX structure 
                    send(SocketInfo->Socket, fileName, sizeof(fileName), 0);
                    recv(SocketInfo->Socket, buf, sizeof(buf), 0);
                    memcpy(pwfx, SocketInfo->DataBuf, RecvBytes);
                    waveOutOpen(&hwo, WAVE_MAPPER, pwfx, 0, NULL, CALLBACK_NULL);

                    //Create UDP socket
                    WaveLib_CreateThread(pWaveLib);*/
                    return FALSE;

                //button should be disabled when we're not in server mode
                /* connection has already been set up after connect was pressed, so we can start
                   sending right away. */
                case IDC_BTN_BROADCAST:
                    //serv_broadcast(fileName);
                    return FALSE;

				default:
					return FALSE;
			}
			return TRUE;
	}
	return FALSE;
}
