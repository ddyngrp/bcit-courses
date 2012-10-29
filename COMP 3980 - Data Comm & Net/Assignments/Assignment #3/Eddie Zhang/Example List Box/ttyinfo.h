/*------------------------------------------------------------------------------
	MODULE: ttyinfo.h

	PURPOSE: Contains global definitions and variables

	AUTHOR: Steffen L. Norgren
		A00683006

/*-----------------------------------------------------------------------------*/

// Constant Definitions

// Maximum number of ports to search through
#define MAXPORTS	255

// Terminal Size
#define MAXROWS		25
#define MAXCOLS		80

// ASCII Definitions
#define ASCII_BEL	0x07
#define ASCII_BS	0x08
#define ASCII_LF	0x0A
#define ASCII_CR	0x0D

// Data Structures

// Struct to handle COM port configuration
struct TTYInfoStruct {
	HANDLE	hCommPort, hReader;
	CHAR	Screen[MAXCOLS * MAXROWS];
	BOOL	fConnected, fNewLine, fThreadDone;
	BYTE	bPort, bByteSize, bParity, bStopBits;
	DWORD	dwBaudRate;
	WORD	wCursorState;
	int		xSize, ySize, xOffset, yOffset, nColumn,
			nRow, xChar, yChar, nCharPos;
} TTYInfo;

// Macros
#define COMDEV(x)				(x.hCommPort)
#define SCREEN(x)				(x.Screen)
#define CONNECTED(x)			(x.fConnected)
#define PORT(x)					(x.bPort)
#define BYTESIZE(x)				(x.bByteSize)
#define PARITY(x)				(x.bParity)
#define STOPBITS(x)				(x.bStopBits)
#define BAUDRATE(x)				(x.dwBaudRate)
#define XSIZE(x)				(x.xSize)
#define YSIZE(x)				(x.ySize)
#define COLUMN(x)				(x.nColumn)
#define ROW(x)					(x.nRow)
#define XCHAR(x)				(x.xChar)
#define YCHAR(x)				(x.yChar)
#define XOFFSET(x)				(x.xOffset)
#define YOFFSET(x)				(x.yOffset)
#define READTHREAD(x)			(x.hReader)
#define THREADDONE(x)			(x.fThreadDone)
#define SCREENCHAR(x, col, row)	(x.Screen[row * MAXCOLS + col])