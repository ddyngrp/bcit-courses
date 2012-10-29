/*
	MODULE: menu.c

	PURPOSE: Manages events associated with menu choices.

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#include "winMain.h"

/*
	FUNCTION: MenuDispatch(int, HWND, LPARAM)

	PURPOSE: Responds to menu selections

	PARAMETERS:
		iMenuChoice	- ID of the menu choice (from resource file)
		hWnd		- window handle of menu owner
		lParam		- window message parameter (depends on message)

*/
void MenuDispatch(int iMenuChoice, HWND hWnd, LPARAM lParam) {
	switch (iMenuChoice) {
		default:
			break;
	}
	return;
}