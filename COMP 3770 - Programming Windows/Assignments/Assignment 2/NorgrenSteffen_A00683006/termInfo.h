/*
	MODULE: termInfo.h

	PURPOSE: Contains global definitions and variables relating
			 to the display of information within the terminal.

	AUTHOR: Steffen L. Norgren
			A00683006
*/

// Constant Definitions
#define MAXROWS		100	// limit on the number of buffered rows
#define MAXCOLS		100	// limit on the number of buffered columns

#define ASCII_BS	0x08
#define ASCII_LF	0x0A
#define ASCII_CR	0x0D
#define ASCII_UP	0x30
#define ASCII_DOWN	0x31
#define ASCII_LEFT	0x29
#define ASCII_RIGHT	0x28

// Data Structures
struct TermInfoStruct {
	CHAR	Screen[MAXCOLS * MAXROWS];
	WORD	wCursorState;
	BOOL	fLocalEcho;
	HFONT	hFont;
	LOGFONT	lfFont;
	DWORD	rgbFGColour, rgbBGColour;
	int		xSize, ySize, xScroll, yScroll, xOffset, yOffset,
			nColumn, nRow, xChar, yChar, nCharPos;
} TermInfo;

// Macros
#define SCREEN(x)				(x.Screen)
#define LOCALECHO(x)			(x.fLocalEcho)
#define HSCREENFONT(x)			(x.hFont)
#define LFSCREENFONT(x)			(x.lfFont)
#define FGCOLOUR(x)				(x.rgbFGColour)
#define BGCOLOUR(x)				(x.rgbBGColour)
#define XSIZE(x)				(x.xSize)
#define YSIZE(x)				(x.ySize)
#define XSCROLL(x)				(x.xScroll)
#define YSCROLL(x)				(x.yScroll)
#define XOFFSET(x)				(x.xOffset)
#define YOFFSET(x)				(x.yOffset)
#define COLUMN(x)				(x.nColumn)
#define ROW(x)					(x.nRow)
#define XCHAR(x)				(x.xChar)
#define YCHAR(x)				(x.yChar)
#define SCREENCHAR(x, col, row) (x.Screen[row * MAXCOLS + col])
