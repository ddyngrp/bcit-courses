/*
	MODULE: termInfo.h

	PURPOSE: Contains global definitions and variables relating
			 to the display of information within the terminal.

	AUTHOR: Steffen L. Norgren
			A00683006
*/

#ifndef _TERMINFO_H
#define _TERMINFO_H

// Constant Definitions
#define MAXROWS		24	// limit on screen rows
#define MAXCOLS		80	// limit on screen columns

#define MAXPORTS	255

#define RGB_BLACK	RGB(0,0,0)
#define RGB_WHITE	RGB(255,255,255)
#define RGB_LTGREY	RGB(200,200,200)
#define RGB_DKGREY	RGB(125,125,125)

#define FORMAT_NORM	0x00
#define FORMAT_BOLD 0x01
#define FORMAT_UL	0x02
#define FORMAT_INV	0x04


// Data Structures
struct TermInfoStruct {
	CHAR	Screen[MAXROWS][MAXCOLS];
	BYTE	Format[MAXROWS][MAXCOLS];
	WORD	wCursorState;
	HFONT	hFont;
	LOGFONT	lfFont;
	DWORD	rgbFGColour, rgbBGColour;
	int		xSize, ySize, nCurrentFormat, nNewFormat,
			nColumn, nRow, xChar, yChar, nCharPos;
	BOOL	fDoubleLine;
} TermInfo;

// Macros for TermInfo
#define SCREEN(x)				(x.Screen)
#define FORMAT(x)				(x.Format)
#define CURRENTFORMAT(x)		(x.nCurrentFormat)
#define HSCREENFONT(x)			(x.hFont)
#define LFSCREENFONT(x)			(x.lfFont)
#define FGCOLOUR(x)				(x.rgbFGColour)
#define BGCOLOUR(x)				(x.rgbBGColour)
#define XSIZE(x)				(x.xSize)
#define YSIZE(x)				(x.ySize)
#define COLUMN(x)				(x.nColumn)
#define ROW(x)					(x.nRow)
#define XCHAR(x)				(x.xChar)
#define YCHAR(x)				(x.yChar)
#define DOUBLELINE(x)			(x.fDoubleLine)
#define SCREENCHAR(x, row, col) (x.Screen[row][col])
#define FORMATCODE(x, row, col) (x.Format[row][col])

// Struct to handle COM port configuration
struct TTYInfoStruct {
	HANDLE	hCommPort, hThread;
	BOOL	fConnected, fThreadDone;
	BYTE	bPort, bByteSize, bParity, bStopBits;
	DWORD	dwBaudRate;
} TTYInfo;

// Macros for TTYInfo
#define COMDEV(x)				(x.hCommPort)
#define CONNECTED(x)			(x.fConnected)
#define PORT(x)					(x.bPort)
#define BYTESIZE(x)				(x.bByteSize)
#define PARITY(x)				(x.bParity)
#define STOPBITS(x)				(x.bStopBits)
#define BAUDRATE(x)				(x.dwBaudRate)

#endif