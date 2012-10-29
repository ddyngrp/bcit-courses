/*------------------------------------------------------------------------------
	MODULE: toolBox.c

	PURPOSE: Handles all tool box functions.

	AUTHORS: Steffen L. Norgren

/*-----------------------------------------------------------------------------*/

#include <windowsx.h>
#include "winMain.h"
#include "chooseColour.h"
#include "resource.h"

BOOL CALLBACK ToolBoxDlg(HWND, UINT, WPARAM, LPARAM);

/*------------------------------------------------------------------------------
	FUNCTION: OpenToolBox(HWND)

	PURPOSE: Creates the modal Select COM Port dialog

	PARAMETERS:
		hWnd	- window handle

/*-----------------------------------------------------------------------------*/
BOOL OpenToolBox(HWND hWnd) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	// Make sure the window isn't already open
	if (!GetWindow(ghWndToolBox,GW_HWNDFIRST)) {
		ghWndToolBox = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_DLG_TOOLBOX), ghWndCanvas, (DLGPROC)ToolBoxDlg);
		ShowWindow(ghWndToolBox, SW_SHOW);

		CheckMenuItem(hMenu, ID_FORMAT_TOOLBOX, MF_CHECKED);

		// Make sure the correct radio button is checked
		if (GetMenuState(hMenu, ID_TOOLS_LINE, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_LINE), TRUE);
		}
		else if (GetMenuState(hMenu, ID_TOOLS_RECTANGLE, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_RECTANGLE), TRUE);
		}
		else if (GetMenuState(hMenu, ID_TOOLS_POLYGON, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_POLYGON), TRUE);
		}
		else if (GetMenuState(hMenu, ID_TOOLS_SELECT, MF_BYCOMMAND) == MF_CHECKED) {
			Button_SetCheck(GetDlgItem(ghWndToolBox, IDC_RAD_SELECT), TRUE);
		}
	}
	else {
		// Close the window if it was already open
		DestroyWindow(ghWndToolBox);

		CheckMenuItem(hMenu, ID_FORMAT_TOOLBOX, MF_UNCHECKED);
	}



	return TRUE;
}

/*------------------------------------------------------------------------------
	FUNCTION: ToolBoxDlg(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Responds to actions within the tool box dialog window

	PARAMETERS:
		hDlg	- dialog handle
		message	- dialog message
		wParam	- dialog message parameter (depends on message)
		lParam	- dialog message parameter (depends on message)

	RETURN:
		If the message was processed, the return value is 0
		If the message was not processed and passed to DefWindowProc
		and the return value depends on the value of that function.

/*-----------------------------------------------------------------------------*/
BOOL CALLBACK ToolBoxDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	HMENU hMenu;

	hMenu = GetMenu(ghWndMain);

	switch (message) {
		case WM_INITDIALOG:
			SetFocus(hDlg);
			break;

		case WM_COMMAND:
			switch (LOWORD(wParam)) {
				case IDC_RAD_LINE:
					CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_CHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_UNCHECKED);
					break;

				case IDC_RAD_RECTANGLE:
					CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_CHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_UNCHECKED);
					break;

				case IDC_RAD_POLYGON:
					CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_CHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_UNCHECKED);
					break;

				case IDC_RAD_SELECT:
					CheckMenuItem(hMenu, ID_TOOLS_LINE, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_RECTANGLE, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_POLYGON, MF_UNCHECKED);
					CheckMenuItem(hMenu, ID_TOOLS_SELECT, MF_CHECKED);
					break;
	
				case IDC_BTN_COLOUR:
					ChooseColour(hDlg);
					return TRUE;

				case IDCANCEL:
					CheckMenuItem(hMenu, ID_FORMAT_TOOLBOX, MF_UNCHECKED);
					EndDialog(hDlg, 0);
					DestroyWindow(ghWndToolBox);
					return TRUE;
			}
			break;
	}
	return FALSE;
}