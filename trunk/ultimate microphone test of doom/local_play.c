#include "win_main.h"
static MCIDEVICEID deviceID;

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	localSong_Init
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Brendan Neva
--	PROGRAMMER:	Brendan Neva
-- 
--	INTERFACE:	BOOL localSong_Init(HWND hwnd, char * fileName)
-- 
--	RETURNS:	void
-- 
--	NOTES:	Initializes all the variables necessary to play a song locally,
--          using the MCI interface.
---------------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	localSong_Pause
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Brendan Neva
--	PROGRAMMER:	Brendan Neva
-- 
--	INTERFACE:	BOOL localSong_Pause(void)
-- 
--	RETURNS:	void
-- 
--	NOTES:	    Pause the playback via MCI library.
---------------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	localSong_Play
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Brendan Neva
--	PROGRAMMER:	Brendan Neva
-- 
--	INTERFACE:	BOOL localSong_Pause(void)
-- 
--	RETURNS:	void
-- 
--	NOTES:	    Play the playback via MCI library.
---------------------------------------------------------------------------------------*/
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

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	localSong_Stop
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Brendan Neva
--	PROGRAMMER:	Brendan Neva
-- 
--	INTERFACE:	BOOL localSong_Pause(void)
-- 
--	RETURNS:	void
-- 
--	NOTES:	    Stop the playback via MCI library.
---------------------------------------------------------------------------------------*/
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
