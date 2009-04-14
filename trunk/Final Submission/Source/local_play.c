/*-----------------------------------------------------------------------------
--	SOURCE FILE:	local_play.c
--
--	PROGRAM:		CommAudio.exe
--
--	FUNCTIONS:		localSong_Init(HWND hwnd, char * fileName)
--					localSong_Pause()
--					localSong_Play()
--					localSong_Stop()
--
--
--	DESIGNERS:		Brendan Neva
--	PROGRAMMERS:	Brendan Neva
--
--	NOTES:	
-----------------------------------------------------------------------------*/

#include "win_main.h"
static MCIDEVICEID deviceID;

/*-----------------------------------------------------------------------------
--	FUNCTION:		localSong_Init
--
--	DATE:			2009-04-03
--
--	REVISIONS:		
--
--	DESIGNER(S):	Brendan Neva
--	PROGRAMMER(S):	Brendan Neva
--
--	INTERFACE:		localSong_Init(HWND hwnd, char * fileName)
--
--	RETURNS:		TRUE:	Success
--					FALSE:	Failure
--
--	NOTES: Initializes all the variables necessary to play a song locally,
--	using the MCI interface.
-----------------------------------------------------------------------------*/
BOOL localSong_Init(HWND hwnd, char * fileName)
{
    MCI_WAVE_OPEN_PARMS	openParams;
    MCI_PLAY_PARMS		playParams;
    int					errno;

    memset(&openParams, 0, sizeof(MCI_WAVE_OPEN_PARMS));
    openParams.lpstrDeviceType = "waveaudio";
    openParams.lpstrElementName = fileName;
    errno = mciSendCommand(0, MCI_OPEN, MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
                              (DWORD_PTR)&openParams);
    if (errno != 0) 
    {
		MessageBox(ghWndMain, (LPCSTR)"Unable to open file.",
			(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
        return FALSE;
    }
    else 
    {
        deviceID = openParams.wDeviceID;
        memset(&playParams, 0, sizeof(playParams));
        playParams.dwCallback = (DWORD_PTR) hwnd;
        errno = mciSendCommand(deviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playParams);
        if (errno != 0)
            return FALSE;
    }

	return TRUE;
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		localSong_Pause
--
--	DATE:			2009-04-03
--
--	REVISIONS:		
--
--	DESIGNER(S):	Brendan Neva
--	PROGRAMMER(S):	Brendan Neva
--
--	INTERFACE:		localSong_Pause()
--
--	RETURNS:		TRUE:	Success
--					FALSE:	Failure
--
--	NOTES: Pause the playback via MCI library.
-----------------------------------------------------------------------------*/
BOOL localSong_Pause(void)
{
    MCI_GENERIC_PARMS pause;
    int          errno;

    if (deviceID) 
    {
        memset(&pause, 0, sizeof(MCI_GENERIC_PARMS));
        errno = mciSendCommand(deviceID, MCI_PAUSE, MCI_WAIT, (DWORD_PTR)&pause);
        if (errno != 0)
            return FALSE;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		localSong_Play
--
--	DATE:			2009-04-03
--
--	REVISIONS:		
--
--	DESIGNER(S):	Brendan Neva
--	PROGRAMMER(S):	Brendan Neva
--
--	INTERFACE:		localSong_Play()
--
--	RETURNS:		TRUE:	Success
--					FALSE:	Failure
--
--	NOTES: Play the playback via MCI library.
-----------------------------------------------------------------------------*/
BOOL localSong_Play(void)
{
    MCI_GENERIC_PARMS resume;
    int          errno;

    if (deviceID)
    {
        memset(&resume, 0, sizeof(MCI_GENERIC_PARMS));
        errno = mciSendCommand(deviceID, MCI_RESUME, MCI_WAIT, (DWORD_PTR)&resume);
        if (errno != 0)
            return FALSE;
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		localSong_Stop
--
--	DATE:			2009-04-03
--
--	REVISIONS:		
--
--	DESIGNER(S):	Brendan Neva
--	PROGRAMMER(S):	Brendan Neva
--
--	INTERFACE:		localSong_Stop(void)
--
--	RETURNS:		TRUE:	Success
--					FALSE:	Failure
--
--	NOTES: Stop the playback via MCI library.
-----------------------------------------------------------------------------*/
BOOL localSong_Stop(void)
{
    MCI_GENERIC_PARMS stop;
    MCI_GENERIC_PARMS close;
    int          errno;

    if (deviceID)
    {
        memset(&stop, 0, sizeof(MCI_GENERIC_PARMS));
        memset(&close, 0, sizeof(MCI_GENERIC_PARMS));

        errno = mciSendCommand(deviceID, MCI_STOP, MCI_WAIT, (DWORD_PTR)&stop);
        errno = mciSendCommand(deviceID, MCI_CLOSE, MCI_WAIT, (DWORD_PTR)&close);
        deviceID = 0;
    }
    return TRUE;
}
