static MCIDEVICEID woutDeviceID;

/**********************************************************
 * Function Name: MCIPlayLocalFile - uses MCI to play a file instead of
 *													PlaySound()
 * Interface: BOOL MCIPlayLocalFile(char * filename)
 * Arguments:
 *    filename - name of audio file
 * RETURNS
 *    Boolean TRUE if successful
 *    FALSE if not successful
 ******************************************************************/
BOOL MCIPlayLocalFile(char * filename)
{
    MCI_WAVE_OPEN_PARMS  open;
    MCI_PLAY_PARMS      play;
    MCIERROR            mcierror;

    memset(&open, 0, sizeof(MCI_WAVE_OPEN_PARMS));
    open.lpstrDeviceType = "waveaudio";
    open.lpstrElementName = filename;
    mcierror = mciSendCommand(0, MCI_OPEN, MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
                              (DWORD)&open);
    if (mcierror != 0) {
        comerror(WSAGetLastError(), "Unable to open MCI Device");
        return FALSE;
    } else {
        woutDeviceID = open.wDeviceID;

        memset(&play, 0, sizeof(MCI_PLAY_PARMS));
        play.dwCallback = (DWORD)hMainWnd;
        mcierror = mciSendCommand(woutDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&play);
        if (mcierror != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/***********************************************************
 * Function Name: MCIPausePlayback - pauses MCI playback of audio file
 *
 * Interface: BOOL MCIPausePlayback(void)
 * Arguments
 *    None
 * Returns
 *    Boolean TRUE if successful
 *    FALSE if not successful
 *************************************************************/
BOOL MCIPausePlayback(void)
{
    MCI_GENERIC_PARMS pause;
    MCIERROR          mcierror;

    if (woutDeviceID) {
        memset(&pause, 0, sizeof(MCI_GENERIC_PARMS));
        mcierror = mciSendCommand(woutDeviceID, MCI_PAUSE, MCI_WAIT,
                                  (DWORD)&pause);
        if (mcierror != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/**************************************************************
 * Function Name:  MCIResumePlayback - resume MCI playback of audio file
 *
 * Interface: BOOL MCIResumePlayback(void)
 * Arguments
 *    None
 * Returns
 *    Boolean TRUE if successful
 *    FALSE if not successful
 *****************************************************************/
BOOL MCIResumePlayback(void)
{
    MCI_GENERIC_PARMS resume;
    MCIERROR          mcierror;

    if (woutDeviceID) {
        memset(&resume, 0, sizeof(MCI_GENERIC_PARMS));
        mcierror = mciSendCommand(woutDeviceID, MCI_RESUME, MCI_WAIT,
                                  (DWORD)&resume);
        if (mcierror != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/********************************************************
 * Function name: MCIStopPlayback - halts MCI playback of audio file
 *
 * Interface: BOOL MCIStopPlayback(void)
 * Arguments
 *    None
 * Returns
 *    Boolean TRUE if successful
 *    FALSE if not successful
 ************************************************************/
BOOL MCIStopPlayback(void)
{
    MCI_GENERIC_PARMS stop;
    MCI_GENERIC_PARMS close;
    MCIERROR          mcierror;

    if (woutDeviceID) {
        memset(&stop, 0, sizeof(MCI_GENERIC_PARMS));
        memset(&close, 0, sizeof(MCI_GENERIC_PARMS));

        mcierror = mciSendCommand(woutDeviceID, MCI_STOP, MCI_WAIT,
                                  (DWORD)&stop);
        mcierror = mciSendCommand(woutDeviceID, MCI_CLOSE, MCI_WAIT,
                                  (DWORD)&close);
        woutDeviceID = 0;
    }

    return TRUE;
}
