/*
	MODULE: linkedList.h

	PURPOSE: Contains global definitions and variables

	AUTHOR: Steffen L. Norgren
*/

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <windows.h>
#include <malloc.h>

/* WARNING: This is an ugly hack to prevent iterating outside
			the bounds of an array of pointers I used to deal
			with the fact that I can't get this linked list to
			become FIFO to save my life!!
*/
#define MAX_OBJECTS 100

// Global Struct Definitions
typedef struct _PROGRAM_ITEM {
	SLIST_ENTRY		ItemEntry;
	RECT			rect;		// Our rectangle co-ordinates
	POINT			line[2];		// Our line co-ordinates
	BOOL			fLine;		// Whether it is a line or a rectangle
	COLORREF		colour;		// The colour of the object
} PROGRAM_ITEM, *pPROGRAM_ITEM;

// Temporary Copy/Paste struct
typedef struct _CPDATA {
	RECT			rect;		// Our rectangle co-ordinates
	POINT			line[2];		// Our line co-ordinates
	BOOL			fLine;		// Whether it is a line or a rectangle
	COLORREF		colour;		// The colour of the object
} CPDATA;

// Global Variable Definitions
PSLIST_ENTRY	gpFirstEntry, gpListEntry;
PSLIST_HEADER	gpListHead;
pPROGRAM_ITEM	gpProgramItem;

// Global Function Definitions
void InitLinkedList();
void InsertObject(POINT pt[2], RECT, BOOL, COLORREF);
void ClearLinkedList();

#endif