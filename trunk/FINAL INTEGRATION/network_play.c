// FIX Headers

/*-----------------------------------------------------------------------------
--	SOURCE FILE:	network_play.c
--
--	PROGRAM:		CommAudio.exe
--
--	FUNCTIONS:		receiveStream(WPARAM sd)
--					waveOutProc(HWAVEOUT hWaveOut,
--								UINT uMsg, 
--								DWORD dwInstance,
--								DWORD dwParam1, 
--								DWORD dwParam2)
--					allocateBlocks(int size, int count)
--					freeBlocks(WAVEHDR* blockArray)
--					writeAudio(LPSTR data, int size)
--
--
--	DATE:			2009-04-06
--
--	DESIGNERS:		David Overton
--	PROGRAMMERS:	David Overton, Jaymz Boilard, Steffen L. Norgren
--
--	NOTES:	
-----------------------------------------------------------------------------*/
#include "win_main.h"

/* Global Variables */
static CRITICAL_SECTION waveCriticalSection;
static WAVEHDR*			waveBlocks;
static volatile int		waveFreeBlockCount;
static int				waveCurrentBlock;

/*-----------------------------------------------------------------------------
--	FUNCTION:		receiveStream
--
--	DATE:			2009-04-06
--
--	REVISIONS:		2009-04-06 - Jaymz, Took out the TCP connection stuff since
--								 we already have that at this point. Also added
--								 a parameter WPARAM sd, which is the socket
--								 from which we are receiving the data.
--							   - Jaymz, Miscellaneous code touch-ups (mainly
--								 formatting and removing of test printf()'s)
--
--	DESIGNER(S):	David Overton
--	PROGRAMMER(S):	David Overton, Jaymz Boilard, Steffen L. Norgren
--
--	INTERFACE:		receiveStream(LPVOID iValue)
--
--	RETURNS:		void
--
--	NOTES: The main function to receive a UDP stream of data and process
--	that information.
-----------------------------------------------------------------------------*/
DWORD WINAPI receiveStream(LPVOID iValue)
{
	WAVEFORMATEX	wfx;
	char			buffer[BLOCK_SIZE]; /* intermediate buffer for reading */
	int				i, n, remote_len;
	DWORD			outBytes = 0;
	char			* play_byte = "1";
	BOOL			firstRun = TRUE;

	remote_len = sizeof(udp_remote);

	/* initialise the module variables */
	waveBlocks			= allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
	waveFreeBlockCount	= BLOCK_COUNT;
	waveCurrentBlock	= 0;
	InitializeCriticalSection(&waveCriticalSection);
	
	/* playback loop - read from socket */
	while (TRUE) 
	{
		if (ci.request != MULTI_STREAM) {
			/* send play signal */
			sendto(ci.udpSocket, play_byte, sizeof(play_byte), 0, (struct sockaddr *)&udp_remote, remote_len);
		}

		if ((n = recvfrom(ci.udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&udp_remote, &remote_len)) <= 0)
		{
			waveOutClose(hWaveOut);
			ExitThread(0);
		}

		/* first 4 bytes in a file, so set the header information */
		if(strncmp(buffer, "RIFF", 4) == 0)
		{
			memcpy(&wfx, buffer+20, sizeof(wfx));

			if (ci.request != MULTI_STREAM || firstRun == TRUE) {
				waveOutClose(hWaveOut);
			
				if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)waveOutProc,
					(DWORD_PTR)&waveFreeBlockCount, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
				{
						MessageBox(NULL, "Unable to open mapper device.", "Error", MB_OK);
						ExitProcess(1);
				}
				firstRun = FALSE;
			}
		}

		if(n == 0)
			break;
		else if(n < sizeof(buffer) && n != WAVE_HEAD_SIZE)
		{
			memset(buffer + n, 0, sizeof(buffer) - n);
			writeAudio(buffer, n);
			break;
		}

		writeAudio(buffer, n);
	}

	/* wait for all blocks to complete */
	while(waveFreeBlockCount < BLOCK_COUNT)
		Sleep(10);

	/* unprepare any blocks that are still prepared */
	for(i = 0; i < waveFreeBlockCount; i++)
	{
		if(waveBlocks[i].dwFlags & WHDR_PREPARED)
			waveOutUnprepareHeader(hWaveOut, &waveBlocks[i], sizeof(WAVEHDR));
	}
	DeleteCriticalSection(&waveCriticalSection);
	freeBlocks(waveBlocks);
	waveOutClose(hWaveOut);
	streamInProgress = FALSE;
	ExitThread(0);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		sendStream
--
--	DATE:			2009-04-06
--
--	REVISIONS:		2009-04-06 - Jaymz, Took out the TCP connection stuff since
--								 we already have that at this point. Also added
--								 a parameter WPARAM sd, which is the socket
--								 from which we are receiving the data.
--							   - Jaymz, Miscellaneous code touch-ups (mainly
--								 formatting and removing of test printf()'s)
--
--	DESIGNER(S):	David Overton
--	PROGRAMMER(S):	David Overton, Jaymz Boilard, Steffen L. Norgren
--
--	INTERFACE:		sendStream(LPVOID iValue)
--
--	RETURNS:		void
--
--	NOTES: The main function to read a file & send streaming data over UDP.
-----------------------------------------------------------------------------*/
DWORD WINAPI sendStream(LPVOID iValue)
{
	HANDLE	hFile;
	int		remote_len;
	DWORD	readBytes;

	/* TCP connection related variables */
	char	buffer[BLOCK_SIZE]; /* intermediate buffer for reading */

	/* try and open the file */
	if((hFile = CreateFile(ci.DLfileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(ghWndMain, (LPCSTR)"Unable to open file.",
			(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
		ExitProcess(1);
	}

	remote_len = sizeof(udp_local); 

	if (ci.request != MULTI_STREAM) {
		/* Wait for client to send initial UDP packet to determine the address */
		recvfrom(ci.udpSocket, 0, 0, 0, (struct sockaddr *)&udp_remote, &remote_len);
	}

	while (TRUE)
	{
		if(!ReadFile(hFile, buffer, sizeof(buffer), &readBytes, NULL))
		{
			closesocket(ci.udpSocket);
			CloseHandle(hFile);
			ExitThread(0);
		}

		/* first 4 bytes in a file, so set the header information */
		if(strncmp(buffer, "RIFF", 4) == 0)
		{
			memcpy(&ci.waveFormat, buffer, sizeof(WAVEFORMATEX)+20);
		}

		/* send wave header information for new clients */
		if (ci.newClient == TRUE) {
			ci.newClient = FALSE;
			sendto(ci.udpSocket, ci.waveFormat, sizeof(ci.waveFormat), 0, (struct sockaddr *)&udp_local, remote_len);
		}

		if(readBytes == 0)
		{
			CloseHandle(hFile);
			ExitThread(0);
		}
		if(readBytes < sizeof(buffer)) /* We're at the end of file */
			memset(buffer + readBytes, 0, sizeof(buffer) - readBytes);


		if (ci.request == MULTI_STREAM) {
			sendto(ci.udpSocket, buffer, BLOCK_SIZE, 0, (struct sockaddr *)&udp_local, remote_len);
			Sleep(225);
		}
		else {
			sendto(ci.udpSocket, buffer, BLOCK_SIZE, 0, (struct sockaddr *)&udp_remote, remote_len);

			/* Wait for signal from client before sending next block */
			recvfrom(ci.udpSocket, 0, 0, 0, (struct sockaddr *)&udp_remote, &remote_len);
		}
	}
	ExitThread(0);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		waveOutProc
--
--	DATE:			2009-04-06
--
--	REVISIONS:		
--
--	DESIGNER(S):	David Overton
--	PROGRAMMER(S):	David Overton, Steffen L. Norgren
--
--	INTERFACE:		waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance,
--								DWORD dwParam1, DWORD dwParam2)
--						HWAVEOUT hWaveOut: Handle to the audio output device
--						UINT uMesg: Message that the procedure handles
--						DWORD dwInstance: The procedure's instance
--						DWORD dwParam1 & dwParam2: Unknown and forgotten.
--
--	RETURNS:		void
--
--	NOTES: The callback function which is passed into the asyncronous call to
--	play the audio (i.e. it performs its work as a separate thread).
-----------------------------------------------------------------------------*/
static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, 
								 DWORD dwParam1, DWORD dwParam2)
{
	/* pointer to free block counter */
	 int* freeBlockCounter = (int*)dwInstance;

	  /* ignore calls that occur due to openining and closing the device */
	 if(uMsg != WOM_DONE)
		 return;

	 /* Critical Section */
	 EnterCriticalSection(&waveCriticalSection);
	 (*freeBlockCounter)++;
	 LeaveCriticalSection(&waveCriticalSection);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		allocateBlocks
--
--	DATE:			2009-04-06
--
--	REVISIONS:		
--
--	DESIGNER(S):	David Overton
--	PROGRAMMER(S):	David Overton, Steffen L. Norgren
--
--	INTERFACE:		allocateBlocks(int size, int count)
--						int size: The size of each block
--						int count: The amount of blocks
--
--	RETURNS:		WAVEHDR *: Pointer to the allocated blocks.
--
--	NOTES: Allocates a buffer to receive data in.
-----------------------------------------------------------------------------*/
WAVEHDR* allocateBlocks(int size, int count)
{
	unsigned char* buffer;
	int i;
	WAVEHDR* blocks;
	DWORD totalBufferSize = (size + sizeof(WAVEHDR)) * count;

	/* Free any current memory blocks */
	freeBlocks(waveBlocks);

	/* allocate memory for the entire set in one go */
	if((buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, totalBufferSize)) == NULL)
	{
		MessageBox(ghWndMain, (LPCSTR)"Memory allocation error.",
			(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
		ExitProcess(1);
	}

	/*  and set up the pointers to each bit */
	blocks = (WAVEHDR*)buffer;
	buffer += sizeof(WAVEHDR) * count;

	for(i = 0; i < count; i++)
	{
		blocks[i].dwBufferLength = size;
		blocks[i].lpData = buffer;
		buffer += size;
	}

	return blocks;
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		freeBlocks
--
--	DATE:			2009-04-06
--
--	REVISIONS:		
--
--	DESIGNER(S):	David Overton
--	PROGRAMMER(S):	David Overton, Steffen L. Norgren
--
--	INTERFACE:		freeBlocks(WAVEHDR* blockArray)
--						WAVEHDR* blockArray: The array that we wish to free.
--
--	RETURNS:		void
--
--	NOTES: Prevents memory leeks by freeing the data ww allocated to the heap.
-----------------------------------------------------------------------------*/
void freeBlocks(WAVEHDR* blockArray)
{
	/* and this is why allocateBlocks works the way it does */ 
	HeapFree(GetProcessHeap(), 0, blockArray);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		writeAudio
--
--	DATE:			2009-04-06
--
--	REVISIONS:		
--
--	DESIGNER(S):	David Overton
--	PROGRAMMER(S):	David Overton, Steffen L. Norgren
--
--	INTERFACE:		writeAudio(LPSTR data, int size)
--						LPSTR data: The buffer we're playing
--						int size: The size of the buffer
--
--	RETURNS:		void
--
--	NOTES: Takes in our buffer of data and writes it to the audio device
--	for playback.
-----------------------------------------------------------------------------*/
void writeAudio(LPSTR data, int size)
{
	WAVEHDR* current;
	int remain;
	current = &waveBlocks[waveCurrentBlock];

	while(size > 0)
	{
		/* first make sure the header we're going to use is unprepared */
		if(current->dwFlags & WHDR_PREPARED)
			waveOutUnprepareHeader(hWaveOut, current, sizeof(WAVEHDR));

		if(size < (int)(BLOCK_SIZE - current->dwUser))
		{
			memcpy(current->lpData + current->dwUser, data, size);
			current->dwUser += size;
			break;
		}

		remain = BLOCK_SIZE - current->dwUser; /* Comment out? */
		memcpy(current->lpData + current->dwUser, data, remain);
		size -= remain;
		data += remain;
		current->dwBufferLength = BLOCK_SIZE;
		waveOutPrepareHeader(hWaveOut, current, sizeof(WAVEHDR));
		waveOutWrite(hWaveOut, current, sizeof(WAVEHDR));
		
		/* Critical section */
		EnterCriticalSection(&waveCriticalSection);
		waveFreeBlockCount--;
		LeaveCriticalSection(&waveCriticalSection);
		
		
		/* wait for a block to become free */
		while(!waveFreeBlockCount)
			Sleep(10);

		/* point to the next block */
		waveCurrentBlock++;
		waveCurrentBlock %= BLOCK_COUNT;
		current = &waveBlocks[waveCurrentBlock];
		current->dwUser = 0;
	}
}

void prepareMicPlay()
{
	waveBlocks			= allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
	waveFreeBlockCount	= BLOCK_COUNT;
	waveCurrentBlock	= 0;
	InitializeCriticalSection(&waveCriticalSection);
}

void unprepareMicPlay()
{
	DeleteCriticalSection(&waveCriticalSection);
	freeBlocks(waveBlocks);
	waveOutClose(hWaveOut);
}

DWORD WINAPI receiveMicThread(LPVOID iValue) {
	char micBuffer[BLOCK_SIZE];
	int remote_len;
	char * play_byte = "1";

	prepareMicPlay();

	remote_len = sizeof(udp_remote); 
				
	mic_play_beg();

	for (;;) {
		if (1 != 1) {
			continue;
		}
		recvfrom(ci.udpSocket, micBuffer, BLOCK_SIZE, 0, (struct sockaddr *)&udp_remote, &remote_len);

		writeAudio(micBuffer, sizeof(micBuffer));
	}
}