#include "buffers.h"

void AllocBuffers() {
	int i;

	// allocate two WAVEHDR buffer blocks
	//...................................
	for (i = 0; i < MAX_BUFFERS; i++) {
		wh[i] = HeapAlloc(GetProcessHeap(),
						  HEAP_ZERO_MEMORY,
						  sizeof(WAVEHDR));

		if (wh[i]) {
			wh[i]->lpData = HeapAlloc(GetProcessHeap(),
									  HEAP_ZERO_MEMORY,
									  DATABLOCK_SIZE);
			wh[i]->dwBufferLength = DATABLOCK_SIZE;
		}
	}

	// allocate playback buffer - enough space to hold
	// ten data buffer blocks of waveform sound data
	//................................................
	pPlaybackBuffer = HeapAlloc(GetProcessHeap(),
								HEAP_ZERO_MEMORY,
								PLAYBACK_BUFFER_SIZE);
} 

void CleanUpBuffers() {
	int i;

	// free the WAVEHDR buffer blocks
	//...............................
	for (i = 0; i < MAX_BUFFERS; i++) {
		if (wh[i] != NULL) {
			HeapFree(GetProcessHeap(), 0, wh[i]->lpData);
			HeapFree(GetProcessHeap(), 0, wh[i]);
			wh[i] = NULL;
		}
	}

	// free playback buffer
	//.....................
	HeapFree(GetProcessHeap(), 0, pPlaybackBuffer);
}