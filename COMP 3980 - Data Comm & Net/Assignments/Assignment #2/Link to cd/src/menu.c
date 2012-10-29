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
	switch (iMenuChoice) {
		case ID_FILE_CONNECT:
			commConnect();
			break;

		case ID_FILE_DISCONNECT:
			commDisconnect();
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
			MessageBox(hWnd, "COMP 3980 - Assignment #2\n\nAuthors:\tSteffen L. Norgren\n\tDoug Penner",
				"About Terminal", MB_OK | MB_ICONINFORMATION);
			break;

		case ID_HELP_INSTRUCTIONS:
			MessageBox(hWnd, "Welcome to a deliciously lovely VT-100 partial emulator. Unfortunately due to time constraints,\nwe are unable to bring you scrolling regions at this time. However, we look forward to implmenting\nthis feature at some future date.\n\nInstructions:\n\nTo use this program, you must first have a working serial connection to another computer that is ready \nto communicate via the VT-100 protocol.\n\n1. Set up your serial port! To do this, simply select 'Edit -> Settings' or you can press Ctrl+O. From\nhere you select your serial port as well as all the associated communications parameters. When you\nare done, simply press ok.\n\nIf you wish, you can also change the on-screen font at any time by selecting 'Edit -> Font'. I highly\nsuggest, if available, that you use the “Bitstream Vera Sans Mono font”, it has lovely anti-aliasing!\n\n2. To connect to the VT-100 server, select 'File -> Connect'. If everything went as planned, you\nshould now be greeted with a login prompt. If you don't see anything, there may be a session that was\nalready in progress. In this case, you can try pressing enter a few times to get the display to output.\n\n3. Once you have finished your fantastic journey into the land of serial VT-100 communications, you\nmay wish to terminate your connection. To do so, simply select 'File -> Disconnect'.\n\nAlternatively, if you're really anxious to run away screaming, you can select 'File -> Exit' or simply\npress Ctrl+Q to exit the program immediately.",
				"User Instructions", MB_OK | MB_ICONINFORMATION);
			break;
	}
	return;
}