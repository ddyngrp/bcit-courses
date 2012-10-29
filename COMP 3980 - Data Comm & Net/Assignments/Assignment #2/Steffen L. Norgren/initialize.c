/*
	MODULE: menu.c

	PURPOSE: Initializes global structures and variables.

	AUTHORS: Steffen L. Norgren
			 Doug Penner
*/

#include "terminal.h"

/*
	FUNCTION: ClearScreen()

	PURPOSE: Clears the screen buffer

*/
void ClearScreen() {
	// Fill the buffer with spaces
	FillMemory(SCREEN(TermInfo), MAXCOLS * MAXROWS, ' ');

	// Set our default format buffer
	FillMemory(FORMAT(TermInfo), MAXCOLS * MAXROWS, (BYTE)0);

	ROW(TermInfo) = 0;
	COLUMN(TermInfo) = 0;
}

/*
	FUNCTION: InitTermInfo()

	PURPOSE: Initializes the TermInfo default settings
*/
void InitTermInfo() {
	// Initialize general TermInfo
	XSIZE(TermInfo)			= 0;
	YSIZE(TermInfo)			= 0;
	COLUMN(TermInfo)		= 0;
	ROW(TermInfo)			= 0;
	FGCOLOUR(TermInfo)		= RGB_DKGREY;
	BGCOLOUR(TermInfo)		= RGB_WHITE;
	CURRENTFORMAT(TermInfo)	= 0;
	DOUBLELINE(TermInfo)	= 0;

	// Defalt font information
	LFSCREENFONT(TermInfo).lfHeight			= 16;
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
	strcpy(LFSCREENFONT(TermInfo).lfFaceName, "Courier New");

	InitNewFont(LFSCREENFONT(TermInfo), FGCOLOUR(TermInfo));

	ClearScreen();
}

/*------------------------------------------------------------------------------
	FUNCTION: InitTTYInfo()

	PURPOSE: Initializes TTY default settings

/*-----------------------------------------------------------------------------*/
void InitTTYInfo() {
	// Initialize general TTY info
	COMDEV(TTYInfo)		= NULL;
	CONNECTED(TTYInfo)	= FALSE;
	PORT(TTYInfo)		= '0';			// setting to 0 since we know nothing about
										// the current COM port configuration
	BAUDRATE(TTYInfo)	= CBR_9600;
	BYTESIZE(TTYInfo)	= 8;
	PARITY(TTYInfo)		= NOPARITY;
	STOPBITS(TTYInfo)	= ONESTOPBIT;
}

/*
	FUNCTION: DestroyTermInfo()

	PURPOSE: Frees objects associated with the TermInfo structure
*/
void DestroyTermInfo() {
	DeleteObject(HSCREENFONT(TermInfo));
}