#include "win_main.h"
#include "resource.h"

#define INP_BUFFER_SIZE 44100

/*------------------------------------------------------------------------
--		FUNCTION:		mic_record_beg
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void mic_record_beg()
--
--		RETURNS:		void
--
--		NOTES:			Prepares the headers for recording wave data
--						from a microphone
------------------------------------------------------------------------*/
void mic_record_beg()
{
	pWaveHdr1 = malloc(sizeof(WAVEHDR));
	pWaveHdr2 = malloc(sizeof(WAVEHDR));

	pSaveBuffer = malloc(1);

	pBuffer1 = malloc(INP_BUFFER_SIZE);
	pBuffer2 = malloc(INP_BUFFER_SIZE);

	if(!pBuffer1 || !pBuffer2)
	{
		if(pBuffer1)
			free(pBuffer1);
		if(pBuffer2)
			free(pBuffer2);

		MessageBox(ghWndMain, szMemError, NULL, MB_ICONEXCLAMATION | MB_OK);

		return;
	}

	waveform.wFormatTag			= WAVE_FORMAT_PCM;
	waveform.nChannels			= 1;
	waveform.nSamplesPerSec		= 11025;
	waveform.nAvgBytesPerSec	= 11025;
	waveform.nBlockAlign		= 1;
	waveform.wBitsPerSample		= 8;
	waveform.cbSize				= 0;

	if(waveInOpen(&hWaveIn, WAVE_MAPPER, &waveform, (DWORD)ghWndMain, 0, CALLBACK_WINDOW))
	{
		free(pBuffer1);
		free(pBuffer2);
		MessageBox(ghWndMain, szOpenError, NULL, MB_ICONEXCLAMATION | MB_OK);
	}

	/* set up headers and prepare them */
	pWaveHdr1->lpData			= pBuffer1;
	pWaveHdr1->dwBufferLength	= INP_BUFFER_SIZE;
	pWaveHdr1->dwBytesRecorded	= 0;
	pWaveHdr1->dwUser			= 0;
	pWaveHdr1->dwFlags			= 0;
	pWaveHdr1->dwLoops			= 1;
	pWaveHdr1->lpNext			= NULL;
	pWaveHdr1->reserved			= 0;
	waveInPrepareHeader(hWaveIn, pWaveHdr1, sizeof(WAVEHDR));

	pWaveHdr2->lpData			= pBuffer2;
	pWaveHdr2->dwBufferLength	= INP_BUFFER_SIZE;
	pWaveHdr2->dwBytesRecorded	= 0;
	pWaveHdr2->dwUser			= 0;
	pWaveHdr2->dwFlags			= 0;
	pWaveHdr2->dwLoops			= 1;
	pWaveHdr2->lpNext			= NULL;
	pWaveHdr2->reserved			= 0;
	waveInPrepareHeader(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));
}

/*------------------------------------------------------------------------
--		FUNCTION:		mic_record_end
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void mic_record_end()
--
--		RETURNS:		void
--
--		NOTES:			Stops reading input from microphone
------------------------------------------------------------------------*/
void mic_record_end()
{
	bEnding = TRUE;
	waveInReset(hWaveIn);
}

/*------------------------------------------------------------------------
--		FUNCTION:		mic_play_beg
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void mic_play_beg()
--
--		RETURNS:		void
--
--		NOTES:			Sets up wave format structure and attempts to
--						open output device
------------------------------------------------------------------------*/
void mic_play_beg()
{
	waveform.nSamplesPerSec = 44100; /* sample rate */
	waveform.wBitsPerSample = 16; /* sample size */
	waveform.nChannels= 2; /* channels*/
	waveform.cbSize = 0; /* size of _extra_ info */
	waveform.wFormatTag = WAVE_FORMAT_PCM;
	waveform.nBlockAlign = (waveform.wBitsPerSample * waveform.nChannels) >> 3;
	waveform.nAvgBytesPerSec = waveform.nBlockAlign * waveform.nSamplesPerSec;

	waveOutClose(hWaveOut);
	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveform, (DWORD)ghWndMain, 0, CALLBACK_WINDOW))
		MessageBox(ghWndMain, szOpenError,NULL, MB_OK);
}

/*------------------------------------------------------------------------
--		FUNCTION:		mic_play_end
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void mic_play_end()
--
--		RETURNS:		void
--
--		NOTES:			Stops sending data to output device
------------------------------------------------------------------------*/
void mic_play_end()
{
	bEnding = TRUE;
	waveOutReset(hWaveOut);
}

/*------------------------------------------------------------------------
--		FUNCTION:		open_mic_device
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void open_mic_device()
--
--		RETURNS:		void
--
--		NOTES:			Registers buffers to input device and begins
--						reading input
------------------------------------------------------------------------*/
void open_mic_device()
{
	pSaveBuffer = realloc(pSaveBuffer, 1);

	/* Enable & Disable buttons */

	/* Add buffers to device */
	waveInAddBuffer(hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
	waveInAddBuffer(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));

	/* Begin Sampling */
	bRecording		= TRUE;
	bEnding			= FALSE;
	dwDataLength	= 0;

	waveInStart(hWaveIn);
}

/*------------------------------------------------------------------------
--		FUNCTION:		read_mic_data
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void read_mic_data(HWND hwnd, LPARAM buffer)
--							HWND hwnd: handle for current window
--							LPARAM buffer: sound data we want to send
--
--		RETURNS:		void
--
--		NOTES:			Copies mic data to an output buffer and sends
--						across network
------------------------------------------------------------------------*/
void read_mic_data(LPARAM buffer)
{
	pNewBuffer = realloc(pSaveBuffer, dwDataLength + ((PWAVEHDR)buffer)->dwBytesRecorded);

	if(pNewBuffer == NULL)
	{
		waveInClose(hWaveIn);
		MessageBox(ghWndMain, szMemError, (LPCSTR)"Error!", MB_OK | MB_ICONSTOP);

		return;
	}

	pSaveBuffer = pNewBuffer;
	CopyMemory(pSaveBuffer + dwDataLength, ((PWAVEHDR)buffer)->lpData, ((PWAVEHDR)buffer)->dwBytesRecorded);

	dwDataLength += ((PWAVEHDR)buffer)->dwBytesRecorded;

	if(bEnding)
	{
		waveInClose(hWaveIn);
		return;
	}
	/* call network streaming function here */
	send(ci.tcpSock2,((PWAVEHDR)buffer)->lpData, ((PWAVEHDR)buffer)->dwBytesRecorded,0);
	/* Send new buffer to input device */
	waveInAddBuffer(hWaveIn, (PWAVEHDR)buffer, sizeof(WAVEHDR));
}

/*------------------------------------------------------------------------
--		FUNCTION:		close_mic
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void close_mic(HWND hwnd)
--
--		RETURNS:		void
--
--		NOTES:			Unregister headers with device and free resources
------------------------------------------------------------------------*/
void close_mic()
{
	/* Free buffer memory */
	waveInUnprepareHeader(hWaveIn, pWaveHdr1, sizeof(WAVEHDR));
	waveInUnprepareHeader(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));

	free(pBuffer1);
	free(pBuffer2);

	/* Enable buttons here */

	bRecording = FALSE;

	if(bTerminating)
		SendMessage(ghWndMain, WM_SYSCOMMAND, SC_CLOSE, 0L);
}

/*------------------------------------------------------------------------
--		FUNCTION:		open_output_device
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void open_output_device()
--
--		RETURNS:		void
--
--		NOTES:			Prepares the headers and plays audio data from
--						remote microphone
------------------------------------------------------------------------*/
void open_output_device(char buffer[])
{
	/* Set up header */
	pWaveHdr1->lpData			= buffer;
	pWaveHdr1->dwBufferLength	= dwDataLength;
	pWaveHdr1->dwBytesRecorded	= 0;
	pWaveHdr1->dwUser			= 0;
	pWaveHdr1->dwFlags			= WHDR_BEGINLOOP | WHDR_ENDLOOP;
	pWaveHdr1->dwLoops			= 0;
	pWaveHdr1->lpNext			= NULL;
	pWaveHdr1->reserved			= 0;

	/* Prepare and write */
	waveOutPrepareHeader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));

	bEnding = FALSE;
	bPlaying = TRUE;
}

/*------------------------------------------------------------------------
--		FUNCTION:		close_output
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void close_output()
--
--		RETURNS:		void
--
--		NOTES:			Stops playing output
------------------------------------------------------------------------*/
void close_output()
{
	/* Enable buttons here */

	bPlaying = FALSE;

	if(bTerminating)
		SendMessage(ghWndMain, WM_SYSCOMMAND, SC_CLOSE, 0L);
}

/*------------------------------------------------------------------------
--		FUNCTION:		terminate_mic_session
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void terminate_mic_session()
--
--		RETURNS:		void
--
--		NOTES:			Stops recording from mic or playing from device
--						and frees resources.
------------------------------------------------------------------------*/
void terminate_mic_session()
{
	if(bRecording)
	{
		bTerminating = TRUE;
		bEnding = TRUE;
		waveInReset(hWaveIn);
		return;
	}

	if(bPlaying)
	{
		bTerminating = TRUE;
		bEnding = TRUE;
		waveOutReset(hWaveOut);
		return;
	}

	free(pWaveHdr1);
	free(pWaveHdr2);
	free(pSaveBuffer);
}

/*------------------------------------------------------------------------
--		FUNCTION:		output_done
--
--		DATE:			March 31, 2009
--
--		REVISIONS:		(Date & Revisions)
--
--		DESIGNER:		Charles Petzold
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void output_done()
--
--		RETURNS:		void
--
--		NOTES:			Unprepare header and close output device
------------------------------------------------------------------------*/
void output_done()
{
	waveOutUnprepareHeader(hWaveOut, pWaveHdr1, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
