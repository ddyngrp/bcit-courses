#include "win_main.h"
static MCIDEVICEID deviceID;
static OPENFILENAME ofn;
int busyFlag;

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
    MCI_WAVE_OPEN_PARMS  openParams;
    MCI_PLAY_PARMS      playParams;
    int           errno;

    memset(&openParams, 0, sizeof(MCI_WAVE_OPEN_PARMS));
    openParams.lpstrDeviceType = "waveaudio";
    openParams.lpstrElementName = fileName;
    errno = mciSendCommand(0, MCI_OPEN, MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
                              (DWORD_PTR)&openParams);
    if (errno != 0) 
    {
        MessageBox(hwnd,"Unable to open file.","Error", MB_OK);
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
    busyFlag = 0;
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
    MCIERROR          errno;

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
    MCIERROR          errno;

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

/*---------------------------------------------------------------------------------
-- FUNCTION: browseFiles
--
-- REVISIONS:
--
--	DESIGNER:	Jaymz Boilard
--	PROGRAMMER:	Jaymz Boilard
--
-- INTERFACE: BOOL browseFiles(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
--
-- RETURNS: The status of GetOpenFileName(), as a boolean
--
-- NOTES: Pops open a file browser to let a user choose a song.
------------------------------------------------------------------------------------*/
BOOL browseFiles(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = pstrFileName;
	ofn.lpstrFileTitle = pstrTitleName;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
	return GetOpenFileName(&ofn);
}

/*---------------------------------------------------------------------------------
-- FUNCTION: fileInit
--
-- REVISIONS:
--
--	DESIGNER:	Jaymz Boilard
--	PROGRAMMER:	Jaymz Boilard
--
-- INTERFACE: void fileInit(HWND hwnd)
--
-- RETURNS: void
--
-- NOTES: Initializes the OPENFILENAME structure for later use.
------------------------------------------------------------------------------------*/
void fileInit(HWND hwnd)
{
	static TCHAR szFilter[] = TEXT("All Files (*.*)\0*.*\0\0");
	
	ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner         = hwnd;
	ofn.hInstance         = NULL;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter    = 0;
	ofn.nFilterIndex      = 0;
	ofn.lpstrFile         = NULL;   
	ofn.nMaxFile          = MAX_PATH;
	ofn.lpstrFileTitle    = NULL;       
	ofn.nMaxFileTitle     = MAX_PATH;
	ofn.lpstrInitialDir   = NULL;
	ofn.lpstrTitle        = NULL;
	ofn.Flags             = 0;  
	ofn.nFileOffset       = 0;
	ofn.nFileExtension    = 0;
	ofn.lpstrDefExt       = TEXT("wav");
	ofn.lCustData         = 0L;
	ofn.lpfnHook          = NULL;
	ofn.lpTemplateName    = NULL;
}
