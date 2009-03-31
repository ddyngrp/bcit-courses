#include "win_main.h"
#include "resource.h"

#define INP_BUFFER_SIZE 16384

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

		MessageBox(ghWndMain, szMemError, szAppName, MB_ICONEXCLAMATION | MB_OK);

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
		MessageBox(ghWndMain, szOpenError, szAppName, MB_ICONEXCLAMATION | MB_OK);
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

	pWaveHdr2->lpData			= pBuffer1;
	pWaveHdr2->dwBufferLength	= INP_BUFFER_SIZE;
	pWaveHdr2->dwBytesRecorded	= 0;
	pWaveHdr2->dwUser			= 0;
	pWaveHdr2->dwFlags			= 0;
	pWaveHdr2->dwLoops			= 1;
	pWaveHdr2->lpNext			= NULL;
	pWaveHdr2->reserved			= 0;
	waveInPrepareHeader(hWaveIn, pWaveHdr2, sizeof(WAVEHDR));
}

void mic_record_end()
{
	bEnding = TRUE;
	waveInReset(hWaveIn);
}


void mic_play_beg()
{
	waveform.wFormatTag			= WAVE_FORMAT_PCM;
	waveform.nChannels			= 1;
	waveform.nSamplesPerSec		= 11025;
	waveform.nAvgBytesPerSec	= 11025;
	waveform.nBlockAlign		= 1;
	waveform.wBitsPerSample		= 8;
	waveform.cbSize				= 0;

	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveform, (DWORD)ghWndMain, 0, CALLBACK_WINDOW))
		MessageBox(ghWndMain, szOpenError, szAppName, MB_OK);
}

