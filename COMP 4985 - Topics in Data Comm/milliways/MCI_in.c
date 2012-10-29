static MCIDEVICEID winDeviceID;

/******************************************************************
 * Function Name: MCIRecordToFile -- record waveform data to file
 *
 * Interface:  BOOL MCIRecordToFile(void);
 * Arguments
 *    None
 * Returns
 *    Boolean TRUE if successful
 *    FALSE if not successful
 ********************************************************************/
BOOL MCIRecordToFile(void) {
    MCI_WAVE_OPEN_PARMS  open;
    MCI_RECORD_PARMS     record;
    MCIERROR             mcierror;

    memset(&open, 0, sizeof(MCI_WAVE_OPEN_PARMS));
    open.lpstrDeviceType = "waveaudio";
    open.lpstrElementName = "";
    mcierror = mciSendCommand(0, MCI_OPEN, MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
                              (DWORD)&open);
    if (mcierror != 0) {
        comerror(WSAGetLastError(), "Unable to open MCI Device");
        return FALSE;
    } else {
        winDeviceID = open.wDeviceID;

        memset(&record, 0, sizeof(MCI_RECORD_PARMS));
        mcierror = mciSendCommand(winDeviceID, MCI_RECORD, 0, (DWORD)&record);
        if (mcierror != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/****************************************************************
 * Function Name: MCIPauseRecord - pauses MCI recording to audio file
 *
 * Interface:  BOOL MCIPauseRecord(void)
 * Arguments
 *    None
 * Returns
 *    Boolean TRUE if successful
 *    FALSE if not successful
 ********************************************************************/
BOOL MCIPauseRecord(void)
{
    MCI_GENERIC_PARMS pause;
    MCIERROR          mcierror;

    if (winDeviceID) {
        memset(&pause, 0, sizeof(MCI_GENERIC_PARMS));
        mcierror = mciSendCommand(winDeviceID, MCI_PAUSE, MCI_WAIT,
                                  (DWORD)&pause);
        if (mcierror != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/*******************************************************************
 * Function name:  MCIResumeRecord - resume MCI recording of audio data
 *
 * Interface:  BOOL MCIResumeRecord(void)
 * Arguments
 *    None
 * Returns
 *    Boolean TRUE if successful
 *    FALSE if not successful
 ************************************************************************/
BOOL MCIResumeRecord(void)
{
    MCI_GENERIC_PARMS resume;
    MCIERROR          mcierror;

    if (winDeviceID) {
        memset(&resume, 0, sizeof(MCI_GENERIC_PARMS));
        mcierror = mciSendCommand(winDeviceID, MCI_RESUME, MCI_WAIT,
                                  (DWORD)&resume);
        if (mcierror != 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/***************************************************************
 * Function name: MCIStopRecord - halts MCI recording of audio file
 *
 * Interface:   BOOL MCIStopRecord(char *filename)
 * Arguments
 *    filename - name of file to save audio data to
 * Returns
 *    Boolean TRUE if successful
 *    FALSE if not successful
 *******************************************************************/
BOOL MCIStopRecord(char *filename)
{
    MCI_GENERIC_PARMS stop;
    MCI_SAVE_PARMS    save;
    MCI_GENERIC_PARMS close;
    MCIERROR          mcierror;

    if (winDeviceID) {
        memset(&stop, 0, sizeof(MCI_GENERIC_PARMS));
        memset(&save, 0, sizeof(MCI_SAVE_PARMS));
        memset(&close, 0, sizeof(MCI_GENERIC_PARMS));

        mcierror = mciSendCommand(winDeviceID, MCI_STOP, MCI_WAIT,
                                  (DWORD)&stop);
        if (filename) {
            filename = RecordAudioFileDialog(filename);
            if (strlen(filename) > 0) {
                save.lpfilename = filename;
                mcierror = mciSendCommand(winDeviceID, MCI_SAVE,
                                          MCI_WAIT | MCI_SAVE_FILE, (DWORD)&save);
            }
        }
        mcierror = mciSendCommand(winDeviceID, MCI_CLOSE, MCI_WAIT,
                                  (DWORD)&close);
        winDeviceID = 0;
    }

    return TRUE;
}
