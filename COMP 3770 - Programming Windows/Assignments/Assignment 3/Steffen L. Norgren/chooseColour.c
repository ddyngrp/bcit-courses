/*
	MODULE: chooseColour.c

	PURPOSE: Manages the color chooser dialog

	AUTHORS: Steffen L. Norgren
*/

#include <windows.h>
#include <commdlg.h>
#include "chooseColour.h"
#include "winMain.h"

/*
	FUNCTION: ChooseColour(HWND)

	PURPOSE: Opens the standard colour chooser dialogue box

	PARAMETERS:
		hWnd		- window handle of menu owner

*/
void ChooseColour(HWND hWnd) {
	CHOOSECOLOR cc;	// common dialog box structure 

	// Initialize CHOOSECOLOR 
	cc.lStructSize	= sizeof(cc);
	cc.hwndOwner	= hWnd;
	cc.hInstance	= NULL;
	cc.rgbResult	= gRGBCurrent;
	cc.lpCustColors	= (LPDWORD)gAcrCustClr;
	cc.Flags		= CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE) 
	{
		gRGBCurrent = cc.rgbResult;
	}
}