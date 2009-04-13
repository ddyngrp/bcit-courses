/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	network_play.c - Contains all the function calls for sending and
--									 receiving an audio stream.
--
--	PROGRAM:		music_streamer.exe
--
--	FUNCTIONS:		void receiveStream(WPARAM sd)
--					static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, 
--													 DWORD dwInstance, DWORD dwParam1, 
--													 DWORD dwParam2)
--					WAVEHDR* allocateBlocks(int size, int count)
--					void freeBlocks(WAVEHDR* blockArray)
--					void writeAudio(LPSTR data, int size)
--
--	REVISIONS:		April 6 - Took the code from our test program and functionized it
--							  to use here.
--
--	DESIGNERS:		Jaymz Boilard & Steffen L. Norgren
--	PROGRAMMER:		Jaymz Boilard & Steffen L. Norgren
--
--	NOTES:
---------------------------------------------------------------------------------------*/
#include "win_main.h"

/* Global Variables */
static CRITICAL_SECTION waveCriticalSection;
static WAVEHDR*			waveBlocks;
static volatile int		waveFreeBlockCount;
static int				waveCurrentBlock;

/*------------------------------------------------------------------------
--		FUNCTION:		receiveStream - The main function to receive a TCP 
--						stream data and process that information.
--
--		REVISIONS:		April 6 - Took out the TCP connection stuff since we
--								  already have that at this point.  Also added
--								  a parameter WPARAM sd, which is the socket
--								  from which we are receiving the data.
--								- Miscellaneous code touch-ups (mainly
--								  formatting and removing of test printf()'s)
--
--		DESIGNER:		Steffen L. Norgren
--		PROGRAMMER:		Jaymz Boilard & Steffen L. Norgren
--
--		INTERFACE:		void receiveStream(
--								  WPARAM sd) //the socket to be used
--
--		RETURNS:		void
--
--		NOTES:			
------------------------------------------------------------------------*/
void receiveStream(WPARAM sd)
{
	WAVEFORMATEX	wfx;				/* look this up in your documentation */
	char			buffer[BLOCK_SIZE]; /* intermediate buffer for reading */
	int				i, n, remote_len;
	DWORD			outBytes = 0;
	char * play_byte = "1";

	remote_len = sizeof(udp_remote);

	/* initialise the module variables */ 
	waveBlocks			= allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
	waveFreeBlockCount	= BLOCK_COUNT;
	waveCurrentBlock	= 0;
	InitializeCriticalSection(&waveCriticalSection);
	
	/* playback loop - read from socket */
	while (TRUE) 
	{
		/* send play signal */
		sendto(ci.udpSocket, play_byte, sizeof(play_byte), 0, (struct sockaddr *)&udp_remote, remote_len);

		/* Gets blocked here forever */
		if ((n = recvfrom(ci.udpSocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&udp_remote, &remote_len)) <= 0)
		{
			MessageBox(NULL, "No Server!", "Error", MB_OK);
			waveOutClose(hWaveOut);
			ExitThread(0);
		}

		/* first 4 bytes in a file, so set the header information */
		if(strncmp(buffer, "RIFF", 4) == 0)
		{
			waveOutClose(hWaveOut);
			memcpy(&wfx, buffer+20, sizeof(wfx));
			if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)waveOutProc,
				(DWORD_PTR)&waveFreeBlockCount, CALLBACK_FUNCTION) != MMSYSERR_NOERROR)
			{
					MessageBox(NULL, "Unable to open mapper device.", "Error", MB_OK);
					ExitProcess(1);
			}
		}

		if(n == 0)
			break;
		else if(n < sizeof(buffer))
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

/*------------------------------------------------------------------------
--		FUNCTION:		sendStream - The main function to send read the 
--						file & send the streaming data.
--
--		REVISIONS:		April 6 - Took out the TCP connection stuff since we
--								  already have that at this point.  Also added
--								  a parameter WPARAM sd, which is the socket
--								  from which we are receiving the data.
--								- Miscellaneous code touch-ups (mainly
--								  formatting and removing of test printf()'s)
--
--		DESIGNER:		Steffen L. Norgren
--		PROGRAMMER:		Jaymz Boilard & Steffen L. Norgren
--
--		INTERFACE:		void receiveStream(
--								  WPARAM sd //the socket to be used
--								  PTSTR fileName //pointer to the name of a file to send
--
--		RETURNS:		void
--
--		NOTES:			
------------------------------------------------------------------------*/
void sendStream(WPARAM sd)
{
	HANDLE hFile;
	int		remote_len;
	DWORD readBytes;

	/* TCP connection related variables */
	char	buffer[BLOCK_SIZE]; /* intermediate buffer for reading */

	/* try and open the file */
	if((hFile = CreateFile(ci.DLfileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL,"Unable to open file.","Error", MB_OK);
		ExitProcess(1);
	}

	remote_len = sizeof(udp_local); 

	/* Wait for client to send initial UDP packet to determine the address */
	recvfrom(ci.udpSocket, 0, 0, 0, (struct sockaddr *)&udp_remote, &remote_len);

	while (TRUE)
	{
		if(!ReadFile(hFile, buffer, sizeof(buffer), &readBytes, NULL))
		{
			closesocket(ci.udpSocket);
			CloseHandle(hFile);
			ExitThread(0);
		}
		if(readBytes == 0)
		{
			/* Send EOF notification to the client */
			//sendto(sd, "EOF", sizeof("EOF"), 0, (struct sockaddr *)&client, client_len);
			CloseHandle(hFile);
			ExitThread(0);
		}
		if(readBytes < sizeof(buffer)) /* We're at the end of file */
			memset(buffer + readBytes, 0, sizeof(buffer) - readBytes);

		sendto(ci.udpSocket, buffer, BLOCK_SIZE, 0, (struct sockaddr *)&udp_remote, remote_len);

		/* Wait for signal from client before sending next block */
		recvfrom(ci.udpSocket, 0, 0, 0, (struct sockaddr *)&udp_remote, &remote_len);
	}
	ExitThread(0);
}

/*------------------------------------------------------------------------
--		FUNCTION:		waveOutProc
--
--		REVISIONS:		
--
--		DESIGNER:		Steffen L. Norgren
--		PROGRAMMER:		Steffen L. Norgren
--
--		INTERFACE:		static void CALLBACK waveOutProc(
--								HWAVEOUT hWaveOut,         //audio device being used
--								UINT uMsg,				   //type of message to process
--								DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
--
--		RETURNS:		void
--
--		NOTES:			The callback function which is passed into the
--						asyncronous call to play the audio.  (ie. it performs
--						its work as a separate thread).
------------------------------------------------------------------------*/
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

/*------------------------------------------------------------------------
--		FUNCTION:		allocateBlocks - Allocates a buffer to receive data in.
--
--		REVISIONS:		
--
--		DESIGNER:		Steffen L. Norgren
--		PROGRAMMER:		Steffen L. Norgren
--
--		INTERFACE:		WAVEHDR* allocateBlocks(int size, int count)
--
--		RETURNS:		A pointer to the wave header that will be used for
--						our audio playback.
--
--		NOTES:			
------------------------------------------------------------------------*/
WAVEHDR* allocateBlocks(int size, int count)
{
	unsigned char* buffer;
	int i;
	WAVEHDR* blocks;
	DWORD totalBufferSize = (size + sizeof(WAVEHDR)) * count;

	/* allocate memory for the entire set in one go */
	if((buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, totalBufferSize)) == NULL)
	{
		MessageBox(NULL, "Memory allocation error.", "Error", MB_OK);
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

/*------------------------------------------------------------------------
--		FUNCTION:		freeBlocks - As the name implies.
--
--		REVISIONS:		
--
--		DESIGNER:		Steffen L. Norgren
--		PROGRAMMER:		Steffen L. Norgren
--
--		INTERFACE:		void freeBlocks(
--						WAVEHDR* blockArray) //pointer to the array to be free'd
--
--		RETURNS:		void
--
--		NOTES:			Prevents memory leeks by freeing the data we
--						allocated to the heap.
------------------------------------------------------------------------*/
void freeBlocks(WAVEHDR* blockArray)
{
	/* and this is why allocateBlocks works the way it does */ 
	HeapFree(GetProcessHeap(), 0, blockArray);
}

/*------------------------------------------------------------------------
--		FUNCTION:		writeAudio - Takes in our buffer of data and writes
--						it to the audio device for playback.
--
--		REVISIONS:		
--
--		DESIGNER:		Steffen L. Norgren
--		PROGRAMMER:		Steffen L. Norgren
--
--		INTERFACE:		void writeAudio(
--							LPSTR data,	//pointer to our buffer to be played
--							int size)	//length of the buffer
--
--		RETURNS:		void
--
--		NOTES:			
------------------------------------------------------------------------*/
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
