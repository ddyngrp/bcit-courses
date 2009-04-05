#ifndef _BUFFERS_H_
#define _BUFFERS_H_

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#define PLAYBACK_BUFFER_SIZE	327680L
#define DATABLOCK_SIZE			32768L
#define MAX_BUFFERS				2  // double buffer
#define MSG_LEN					128

static WAVEHDR* wh[MAX_BUFFERS];

// temp buffer for this example
//.............................
static VOID*    pPlaybackBuffer;  
static DWORD    nPlaybackBufferPos = 0L;  // position in playback buffer  
static DWORD    nPlaybackBufferLen = 0L;  // total data in playback buffer

void AllocBuffers();
void CleanUpBuffers();

#endif