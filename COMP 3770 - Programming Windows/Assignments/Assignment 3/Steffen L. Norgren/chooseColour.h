/*
	MODULE: chooseColor.h

	PURPOSE: Contains global definitions and variables

	AUTHOR: Steffen L. Norgren
*/

#ifndef _CHOOSECOLOUR_H_
#define _CHOOSECOLOUR_H_

#include <windows.h>

#define SELECTED_OBJECT	RGB(255,255,191)

// Global colour variables
static COLORREF gAcrCustClr[16];	// array of custom colors 
COLORREF gRGBCurrent;				// current color selection

// Global colour functions
void ChooseColour(HWND);

#endif