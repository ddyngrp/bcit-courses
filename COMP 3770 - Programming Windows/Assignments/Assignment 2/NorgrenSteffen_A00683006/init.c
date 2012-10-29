/*
	MODULE: init.c

	PURPOSE: Initializes global data structures

	AUTHOR: Steffen L. Norgren
			A00683006
*/

#include "terminal.h"

/*
	FUNCTION: ClearScreen()

	PURPOSE: Clears the screen buffer

*/
void ClearScreen() {
	// Fill the buffer with spaces
	FillMemory(SCREEN(TermInfo), MAXCOLS * MAXROWS, ' ');
	ROW(TermInfo) = 0;		// set the current row to the top row
	COLUMN(TermInfo) = 0;	// set the current column to the leftmost
}

/*
	FUNCTION: InitNewFont(LOGFONT, COLORREF)

	PURPOSE: Prepares a new font for use in the terminal screen

	PARAMETERS:
		LogFont		- New logical font for the screen
		rgbColour	- New colour for screen painting

*/
void InitNewFont(LOGFONT LogFont, COLORREF rgbColour) {
	TEXTMETRIC	tm;
	HDC			hDC;

	// If an old font exits, delete it
	if (HSCREENFONT(TermInfo)) {
		DeleteObject(HSCREENFONT(TermInfo));
	}

	// Ugly hack to force our fonts to work properly. =p
	//LogFont.lfWidth = LogFont.lfHeight;

	LFSCREENFONT(TermInfo) = LogFont;
	HSCREENFONT(TermInfo) = CreateFontIndirect(&(LFSCREENFONT(TermInfo)));
	FGCOLOUR(TermInfo) = rgbColour;

	hDC = GetDC(ghWnd);
	SelectObject(hDC, HSCREENFONT(TermInfo));
	GetTextMetrics(hDC, &tm);
	ReleaseDC(ghWnd, hDC);

	// Character width and height
	//XCHAR(TermInfo) = (tm.tmAveCharWidth + tm.tmMaxCharWidth) / 2;
	XCHAR(TermInfo) = tm.tmAveCharWidth;
	YCHAR(TermInfo) = tm.tmHeight + tm.tmExternalLeading;

	XOFFSET(TermInfo) = 0;
	YOFFSET(TermInfo) = YCHAR(TermInfo) * ROW(TermInfo);
}

/*
	FUNCTION: InitTermInfo()

	PURPOSE: Initializes the TermInfo default settings
*/
void InitTermInfo() {
	// Initialize general TermInfo
	XSIZE(TermInfo)			= 0;
	YSIZE(TermInfo)			= 0;
	XSCROLL(TermInfo)		= 0;
	YSCROLL(TermInfo)		= 0;
	COLUMN(TermInfo)		= 0;
	ROW(TermInfo)			= 0;
	BGCOLOUR(TermInfo)		= RGB(255,255,255);
	
	// Defalt font information
	LFSCREENFONT(TermInfo).lfHeight			= 12;
	LFSCREENFONT(TermInfo).lfWidth			= 0;
	LFSCREENFONT(TermInfo).lfEscapement		= 0;
	LFSCREENFONT(TermInfo).lfOrientation	= 0;
	LFSCREENFONT(TermInfo).lfWeight			= 0;
	LFSCREENFONT(TermInfo).lfItalic			= 0;
	LFSCREENFONT(TermInfo).lfUnderline		= 0;
	LFSCREENFONT(TermInfo).lfStrikeOut		= 0;
	LFSCREENFONT(TermInfo).lfCharSet		= ANSI_CHARSET;
	LFSCREENFONT(TermInfo).lfOutPrecision	= OUT_DEFAULT_PRECIS;
	LFSCREENFONT(TermInfo).lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	LFSCREENFONT(TermInfo).lfQuality		= DEFAULT_QUALITY;
	LFSCREENFONT(TermInfo).lfPitchAndFamily	= FIXED_PITCH | FF_MODERN;
	strcpy(LFSCREENFONT(TermInfo).lfFaceName, "FixedSys");

	InitNewFont(LFSCREENFONT(TermInfo), RGB(0,0,0));

	ClearScreen();
}

/*
	FUNCTION: DestroyTermInfo()

	PURPOSE: Frees objects associated with the TermInfo structure
*/
void DestroyTermInfo() {
	DeleteObject(HSCREENFONT(TermInfo));
}