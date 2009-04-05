#ifndef _MAIN_H_
#define _MAIN_H_

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>

#define BLOCK_SIZE	1024
#define BLOCK_COUNT	20

/* Function prototypes */
static void CALLBACK waveOutProc(HWAVEOUT, UINT, DWORD, DWORD, DWORD);
WAVEHDR* allocateBlocks(int, int);
void freeBlocks(WAVEHDR*);
void writeAudio(HWAVEOUT, LPSTR, int);

/* Global Variables */
static CRITICAL_SECTION waveCriticalSection;
static WAVEHDR* waveBlocks;
static volatile int waveFreeBlockCount;
static int waveCurrentBlock;

#endif