/*
	MODULE: menu.c

	PURPOSE: Manages events associated with the menu.

	AUTHORS: Steffen L. Norgren
*/

#include "winMain.h"
#include "resource.h"

/*
	FUNCTION: MenuDispatch(int, HWND, LPARAM)

	PURPOSE: Responds to menu selections

	PARAMETERS:
		iMenuChoice	- ID of the menu choice (from resource file)
		hWnd		- window handle of menu owner
		lParam		- window message parameter (depends on message)

*/
void MenuDispatch(UINT iMenuChoice, HWND hWnd, LPARAM lParam) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	switch (iMenuChoice) {
		case ID_SYNC_TRUE:
			gfCritSects = TRUE;
			CheckMenuItem(hMenu, ID_SYNC_TRUE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SYNC_FALSE, MF_UNCHECKED);
			break;

		case ID_SYNC_FALSE:
			gfCritSects = FALSE;
			CheckMenuItem(hMenu, ID_SYNC_TRUE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SYNC_FALSE, MF_CHECKED);
			break;
	}
}