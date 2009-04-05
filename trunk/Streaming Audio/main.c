#include <winsock2.h>
#include "main.h"

#define PORT	7000		/* Default port */
#define HOST	"localhost"	/* Default server */

int main(int argc, char* argv[]) {
	HWAVEOUT		hWaveOut; /* device handle */
	WAVEFORMATEX	wfx; /* look this up in your documentation */
	char			buffer[BLOCK_SIZE]; /* intermediate buffer for reading */
	int				i;
	DWORD			outBytes = 0;

	/* TCP connection related variables */
	int		n, port = PORT;
	SOCKET	sd;
	struct	hostent	*hp;
	struct	sockaddr_in server;
	char	*host = HOST, **pptr;
	WSADATA	WSAData;
	WORD	wVersionRequested;

	/**
	 * initialise the module variables
	 */ 
	waveBlocks = allocateBlocks(BLOCK_SIZE, BLOCK_COUNT);
	waveFreeBlockCount = BLOCK_COUNT;
	waveCurrentBlock= 0;
	InitializeCriticalSection(&waveCriticalSection);

	/**
	 * set up the WAVEFORMATEX structure.
	 */
	wfx.nSamplesPerSec = 44100;	/* sample rate */
	wfx.wBitsPerSample = 16;	/* sample size */
	wfx.nChannels= 2;			/* channels*/
	wfx.cbSize = 0;				/* size of _extra_ info */
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nBlockAlign = (wfx.wBitsPerSample * wfx.nChannels) >> 3;
	wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec;

	/**
	 * try to open the default wave device. WAVE_MAPPER is
	 * a constant defined in mmsystem.h, it always points to the
	 * default wave device on the system (some people have 2 or
	 * more sound cards).
	 */
	if(waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, (DWORD_PTR)waveOutProc, (DWORD_PTR)&waveFreeBlockCount, 
		CALLBACK_FUNCTION) != MMSYSERR_NOERROR) {
			fprintf(stderr, "%s: unable to open wave mapper device\n", argv[0]);
			ExitProcess(1);
	}

	/* Connect to the server - DELETE */
	wVersionRequested = MAKEWORD( 2, 2 );
	WSAStartup( wVersionRequested, &WSAData );

	// Create the socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Cannot create socket");
		system("pause");
		exit(1);
	}

	// Initialize and set up the address structure
	memset((char *)&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	if ((hp = gethostbyname(host)) == NULL)
	{
		fprintf(stderr, "Unknown server address\n");
		exit(1);
	}

	// Copy the server address
	memcpy((char *)&server.sin_addr, hp->h_addr, hp->h_length);

	// Connecting to the server
	if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
	{
		fprintf(stderr, "Can't connect to server\n");
		perror("connect");
		system("pause");
		exit(1);
	}
	
	printf("Connected:    Server Name: %s\n", hp->h_name);
	pptr = hp->h_addr_list;
	printf("\t\tIP Address: %s\n", inet_ntoa(server.sin_addr));

	/**
	 * playback loop - read from socket
	 */
	while ((n = recv(sd, buffer, sizeof(buffer), 0)) != 0) {
		outBytes += n / 1000;
		printf("read %d KB\n", outBytes);

		if(n == 0) {
			break;
		}

		if(n < sizeof(buffer)) {
			printf("at end of buffer\n");
			memset(buffer + n, 0, sizeof(buffer) - n);
			printf("after memcpy\n");
		}

		writeAudio(hWaveOut, buffer, sizeof(buffer));
	}

	closesocket(sd);
	WSACleanup();

	/**
	 * wait for all blocks to complete
	 */
	while(waveFreeBlockCount < BLOCK_COUNT) {
		Sleep(10);
	}

	/**
	 * unprepare any blocks that are still prepared
	 */
	for(i = 0; i < waveFreeBlockCount; i++) {
		if(waveBlocks[i].dwFlags & WHDR_PREPARED) {
			waveOutUnprepareHeader(hWaveOut, &waveBlocks[i], sizeof(WAVEHDR));
		}
	}
	DeleteCriticalSection(&waveCriticalSection);
	freeBlocks(waveBlocks);
	waveOutClose(hWaveOut);

	system("pause");

	return 0;
}

static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg,
								 DWORD dwInstance, DWORD dwParam1, DWORD dwParam2) {
	 /**
	  * pointer to free block counter
	  */
	 int* freeBlockCounter = (int*)dwInstance;

	 /**
	  * ignore calls that occur due to openining and closing the
	  * device.
	  */
	 if(uMsg != WOM_DONE) {
		 return;
	 }

	 /* Critical Section */
	 EnterCriticalSection(&waveCriticalSection);
	 (*freeBlockCounter)++;
	 LeaveCriticalSection(&waveCriticalSection);
}

WAVEHDR* allocateBlocks(int size, int count) {
	unsigned char* buffer;
	int i;
	WAVEHDR* blocks;
	DWORD totalBufferSize = (size + sizeof(WAVEHDR)) * count;

	/**
	 * allocate memory for the entire set in one go
	 */
	if((buffer = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, totalBufferSize)) == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		ExitProcess(1);
	}

	/**
	 * and set up the pointers to each bit
	 */
	blocks = (WAVEHDR*)buffer;
	buffer += sizeof(WAVEHDR) * count;

	for(i = 0; i < count; i++) {
		blocks[i].dwBufferLength = size;
		blocks[i].lpData = buffer;
		buffer += size;
	}

	return blocks;
}

void freeBlocks(WAVEHDR* blockArray) {
	/** 
	 * and this is why allocateBlocks works the way it does
	 */ 
	HeapFree(GetProcessHeap(), 0, blockArray);
}

void writeAudio(HWAVEOUT hWaveOut, LPSTR data, int size) {
	WAVEHDR* current;
	int remain;
	current = &waveBlocks[waveCurrentBlock];

	while(size > 0) {
		/** 
		 * first make sure the header we're going to use is unprepared
		 */
		if(current->dwFlags & WHDR_PREPARED) {
			waveOutUnprepareHeader(hWaveOut, current, sizeof(WAVEHDR));
		}

		if(size < (int)(BLOCK_SIZE - current->dwUser)) {
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

		/**
		 * wait for a block to become free
		 */
		while(!waveFreeBlockCount) {
			Sleep(10);
		}

		/**
		 * point to the next block
		 */
		waveCurrentBlock++;
		waveCurrentBlock %= BLOCK_COUNT;
		current = &waveBlocks[waveCurrentBlock];
		current->dwUser = 0;
	}
}