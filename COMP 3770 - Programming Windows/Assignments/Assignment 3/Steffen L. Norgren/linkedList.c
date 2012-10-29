/*
	MODULE: linkedList.c

	PURPOSE: Manages the drawn object struct

	AUTHORS: Steffen L. Norgren
*/

#include <windows.h>
#include "winMain.h"
#include "linkedList.h"

/*
	FUNCTION: InitLinkedList()

	PURPOSE: Initializes the linked list

*/
void InitLinkedList() {
	// Initialize the list header
	gpListHead = (PSLIST_HEADER)_aligned_malloc(sizeof(SLIST_HEADER), MEMORY_ALLOCATION_ALIGNMENT);
	if (gpListHead == NULL) {
		MessageBox(NULL, TEXT("Memory allocation failed."),
			NULL, MB_OK | MB_ICONSTOP);
			PostMessage(ghWndMain, WM_QUIT, 0, 0);
	}
	InitializeSListHead(gpListHead);
}

/*
	FUNCTION: InsertObject(RECT, BOOL, COLORREF)

	PURPOSE: Inserts a drawn object into our linked list

	PARAMETERS:
		rect		- the dimensions of our object (lines only use 2 points of this)
		fLine		- whether it is a line or rectangle
		colour		- the colour of the drawn object

*/
void InsertObject(POINT pt[2], RECT rect, BOOL fLine, COLORREF colour) {
	gpProgramItem = (pPROGRAM_ITEM)_aligned_malloc(sizeof(PROGRAM_ITEM), MEMORY_ALLOCATION_ALIGNMENT);

	if (gpProgramItem == NULL) {
		MessageBox(NULL, TEXT("Memory allocation failed."),
			NULL, MB_OK | MB_ICONSTOP);
			PostMessage(ghWndMain, WM_QUIT, 0, 0);
	}

	gpProgramItem->line[0].x = pt[0].x;
	gpProgramItem->line[0].y = pt[0].y;
	gpProgramItem->line[1].x = pt[1].x;
	gpProgramItem->line[1].y = pt[1].y;
	gpProgramItem->rect = rect;
	gpProgramItem->fLine = fLine;
	gpProgramItem->colour = colour;

	gpFirstEntry = InterlockedPushEntrySList(gpListHead, &(gpProgramItem->ItemEntry));
}

/*
	FUNCTION: ClearLinkedList()

	PURPOSE: Clears the linked list and frees the memory

*/
void ClearLinkedList() {

	gpListEntry = InterlockedFlushSList(gpListHead);
	gpFirstEntry = InterlockedPopEntrySList(gpListHead);

	if (gpFirstEntry != NULL) {
		MessageBox(NULL, TEXT("Error: List is not empty."),
			NULL, MB_OK | MB_ICONSTOP);
	}

	_aligned_free(gpListHead);
}