/*
	MODULE: chooseFont.c

	PURPOSE: Allows the user to change fixed-width font settings.

	AUTHORS: Steffen L. Norgren
			 Doug Penner
*/

#include "terminal.h"

/*
	FUNCTION: ChooseFixedFont(HWND)

	PURPOSE: Changes the terminal font and appropriately resizes the window.

	PARAMETERS:
		hWnd		- window handle of menu owner

	NOTE: There is a bug whereby when you choose the same font but set it to
		  italic, it doesn't register the change.

*/
void ChooseFixedFont(HWND hWnd) {
	CHOOSEFONT	cf = {0};
	LOGFONT		lf;

	lf = LFSCREENFONT(TermInfo);

	cf.lStructSize	= sizeof(CHOOSEFONT);
	cf.hwndOwner	= hWnd;
	cf.lpLogFont	= &lf;
	cf.Flags		= CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS | CF_FIXEDPITCHONLY | CF_NOSCRIPTSEL;
	cf.rgbColors	= FGCOLOUR(TermInfo);
	
	if (!ChooseFont(&cf)) {
		// We'll do something I'm sure!
	}

	InitNewFont(lf, cf.rgbColors);

	ResizeTerm(hWnd);
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

	LFSCREENFONT(TermInfo) = LogFont;
	HSCREENFONT(TermInfo) = CreateFontIndirect(&(LFSCREENFONT(TermInfo)));
	FGCOLOUR(TermInfo) = rgbColour;

	hDC = GetDC(ghWndMain);
	SelectObject(hDC, HSCREENFONT(TermInfo));
	GetTextMetrics(hDC, &tm);
	ReleaseDC(ghWndMain, hDC);

	// Character width and height
	XCHAR(TermInfo) = tm.tmAveCharWidth;
	YCHAR(TermInfo) = tm.tmHeight + tm.tmExternalLeading;

	// Set the terminal height and width based on the current font
	XSIZE(TermInfo) = tm.tmAveCharWidth * MAXCOLS;
	YSIZE(TermInfo) = (tm.tmHeight + tm.tmExternalLeading) * MAXROWS;

}