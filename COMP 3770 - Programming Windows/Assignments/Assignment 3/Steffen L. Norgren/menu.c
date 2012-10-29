/*
	MODULE: menu.c

	PURPOSE: Manages events associated with menu choices.

	AUTHORS: Steffen L. Norgren
*/

#include <windowsx.h>
#include "winMain.h"
#include "chooseColour.h"
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
		// File Menu
		case ID_FILE_EXIT:
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			break;

		// Edit Menu
		case ID_EDIT_COPYSEL:
			if (!EditCopy()) {
				MessageBox(NULL, TEXT("Error copying to clipboard."),NULL, MB_OK | MB_ICONSTOP);
			}
			break;
		case ID_EDIT_PASTESEL:
			if (!EditPaste()) {
				MessageBox(NULL, TEXT("Error pasting from clipboard."),NULL, MB_OK | MB_ICONSTOP);
			}
			break;

		// Tools Menu
		case ID_TOOLS_LINE:
			CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_UNCHECKED);

			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_LINE), TRUE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_RECTANGLE), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_POLYGON), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_SELECT), FALSE);
			break;
		case ID_TOOLS_RECTANGLE:
			CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_UNCHECKED);

			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_LINE), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_RECTANGLE), TRUE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_POLYGON), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_SELECT), FALSE);
			break;
		case ID_TOOLS_POLYGON:
			CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_CHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_UNCHECKED);

			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_LINE), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_RECTANGLE), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_POLYGON), TRUE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_SELECT), FALSE);
			break;
		case ID_TOOLS_SELECT:
			CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_CHECKED);

			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_LINE), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_RECTANGLE), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_POLYGON), FALSE);
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_SELECT), TRUE);
			break;

		// Format Menu
		case ID_FORMAT_TOOLBOX:
			OpenToolBox(hWnd);
			break;
		case ID_FORMAT_COLOUR:
			ChooseColour(hWnd);
			break;
	}
	return;
}