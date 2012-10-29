/*****************************************************************************
*  TestOpenOutputDevice
*
*
*
******************************************************************************/

BOOL TestOpenOutputDevice(HWND hWnd)
{
   WAVEOUTCAPS  woc;                                               
	WAVEFORMATEX wfx;
	UINT         nDevId;
	MMRESULT     rc;                                                
	UINT         nMaxDevices = waveOutGetNumDevs();                  
	
	hwo = NULL;
	nPlaybackBufferPos = 0L;  // position in playback buffer
   eStatus = StatusOkay;     // reset status                                                 
		                                                                
	for (nDevId = 0; nDevId < nMaxDevices; nDevId++)                         
	{                                                               
	   rc = waveOutGetDevCaps(nDevId, &woc, sizeof(woc));
	   if (rc == MMSYSERR_NOERROR)                                  
	   {
          // attempt 44.1 kHz stereo if device is capable

          if (woc.dwFormats & WAVE_FORMAT_4S16)
          {
              wfx.nChannels      = 2;      // stereo
              wfx.nSamplesPerSec = 44100;  // 44.1 kHz (44.1 * 1000)
          }
          else
          {   
              wfx.nChannels      = woc.wChannels;  // use DevCaps # channels
              wfx.nSamplesPerSec = 22050;  // 22.05 kHz (22.05 * 1000)
          }

          wfx.wFormatTag      = WAVE_FORMAT_PCM;                          
      	 wfx.wBitsPerSample  = 8;                                        
      	 wfx.nBlockAlign     = wfx.nChannels * wfx.wBitsPerSample / 8;   
      	 wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;     
      	 wfx.cbSize          = 0;                                        

	       rc = waveOutOpen(&hwo, nDevId, &wfx, (DWORD)hWnd, 0,                   
	                        CALLBACK_WINDOW);
	                                                  
	       if (rc == MMSYSERR_NOERROR)
          {
              DWORD dwVol;

              // set volume level to at least 80%

              rc = waveOutGetVolume( hwo, &dwVol );

              if (rc == MMSYSERR_NOERROR)
                  if ( LOWORD(dwVol) < 0xCCCC ||
                     ( wfx.nChannels == 2 && HIWORD(dwVol) < 0xCCCC )  )
                      rc = waveOutSetVolume( hwo, (DWORD)MAKELONG( 0xCCCC, 0xCCCC ) );
          }
	       
          if (rc != MMSYSERR_NOERROR)
	       {                                                        
	           waveOutGetErrorText(rc, msg, MSG_LEN),                    
	           MessageBox(hWnd, msg, NULL, MB_OK);
	           return(FALSE);
	       }
	       
	       break;                                                        
	   }                                                            
	}                                                               
	
   // device not found, error condition
   //..................................

	if (hwo == NULL)
	    return(FALSE);

   return(TRUE);
}