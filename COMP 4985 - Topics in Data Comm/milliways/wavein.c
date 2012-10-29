/*****************************************************************************
*  TestOpenInputDevice
*
*
*
******************************************************************************/

BOOL TestOpenInputDevice(HWND hWnd)
{
   WAVEINCAPS   wic;
	WAVEFORMATEX wfx;
	UINT         nDevId;
	MMRESULT     rc;
	UINT         nMaxDevices = waveInGetNumDevs();

	hwi = NULL;
	nPlaybackBufferPos = 0L;  // position in playback buffer
   nPlaybackBufferLen = 0L;  // total data in playback buffer
   eStatus = StatusOkay;     // reset status

	for (nDevId = 0; nDevId < nMaxDevices; nDevId++)
	{
	   rc = waveInGetDevCaps(nDevId, &wic, sizeof(wic));
	   if (rc == MMSYSERR_NOERROR)
	   {
          // attempt 44.1 kHz stereo if device is capable

          if (wic.dwFormats & WAVE_FORMAT_4S16)
          {
              wfx.nChannels      = 2;      // stereo
              wfx.nSamplesPerSec = 44100;  // 44.1 kHz (44.1 * 1000)
          }
          else
          {
              wfx.nChannels      = wic.wChannels;  // use DevCaps # channels
              wfx.nSamplesPerSec = 22050;  // 22.05 kHz (22.05 * 1000)
          }

	       wfx.wFormatTag      = WAVE_FORMAT_PCM;
       	 wfx.wBitsPerSample  = 8;
      	 wfx.nBlockAlign     = wfx.nChannels * wfx.wBitsPerSample / 8;
      	 wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
      	 wfx.cbSize          = 0;

          // open waveform input device
          //...........................

	       rc = waveInOpen(&hwi, nDevId, &wfx, (DWORD)(VOID*)waveInProc, (DWORD)hWnd,
	                       CALLBACK_FUNCTION);

	       if (rc == MMSYSERR_NOERROR)
	           break;
	       else
	       {
	           waveInGetErrorText(rc, msg, MSG_LEN),
	           MessageBox(hWnd, msg, NULL, MB_OK);
	           return(FALSE);
	       }
	   }
	}

   // device not found, error condition
   //..................................

	if (hwi == NULL)
	{
       eStatus = StatusError;
	    return(FALSE);
   }


   return(TRUE);
}
