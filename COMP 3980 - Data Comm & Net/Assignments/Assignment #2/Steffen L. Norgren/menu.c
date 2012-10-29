/*
	MODULE: menu.c

	PURPOSE: Manages events associated with menu choices.

	AUTHORS: Steffen L. Norgren
			 Doug Penner
*/

#include "terminal.h"

/*
	FUNCTION: MenuDispatch(int, HWND, LPARAM)

	PURPOSE: Responds to menu selections

	PARAMETERS:
		iMenuChoice	- ID of the menu choice (from resource file)
		hWnd		- window handle of menu owner
		lParam		- window message parameter (depends on message)

*/
void MenuDispatch(int iMenuChoice, HWND hWnd, LPARAM lParam) {
	CHOOSEFONT	cf = {0};
	LOGFONT		lf;

	switch (iMenuChoice) {
		case ID_FILE_CONNECT:
			break;

		case ID_FILE_DISCONNECT:
			break;

		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		case ID_EDIT_FONT:
			ChooseFixedFont(ghWndTerm);
			break;

		case ID_EDIT_SETTINGS:
			CmdPort(hWnd);
			break;

		case ID_VIEW_CLEARSCREEN:
			EraseEntireScreen();
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_HELP_ABOUT:
			MessageBox(hWnd, "COMP 3770 - Assignment #2\n\nAuthor:\tSteffen L. Norgren\nSet F\tA00683006",
				"About Terminal", MB_OK | MB_ICONINFORMATION);
			break;

		case ID_TESTING_ERASEFROMSOL:
			EraseFromSOLToCursor();
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_TESTING_ERASETOEOL:
			EraseFromCursorToEOL();
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		case ID_TESTING_NEWLINE:
			NewLine();
			break;

		case ID_TESTING_SETCURSOR:
			SetCursorPosition(5,5);
			break;

		case ID_TESTING_MOVECURSOR:
			MoveCursor(5,5);
			break;

		case ID_TESTING_SINGLELINE:
			SingleWidthLine();
			break;

		case ID_TESTING_DOUBLELINE:
			DoubleWidthLine();
			break;

		case ID_TESTING_NORMAL:
			SetFormat(FORMAT_NORM, FALSE);
			break;

		case ID_TESTING_BOLD:
			SetFormat(FORMAT_BOLD, TRUE);
			break;

		case ID_TESTING_UNDERLINE:
			SetFormat(FORMAT_UL, TRUE);
			break;

		case ID_TESTING_INVERT:
			SetFormat(FORMAT_INV, TRUE);
			break;
	}
	return;
}