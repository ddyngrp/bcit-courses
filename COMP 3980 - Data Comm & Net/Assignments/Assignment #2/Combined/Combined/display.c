#include "terminal.h"

void FormatOutput(HDC hDC, int format) {

	switch (format) {
		case FORMAT_NORM:
			SetTextColor(hDC, RGB_DKGREY);
			SetBkColor(hDC, RGB_WHITE);
			break;

		case FORMAT_BOLD:
			SetTextColor(hDC, RGB_BLACK);
			SetBkColor(hDC, RGB_WHITE);
			break;

		case FORMAT_UL:
			// we do nothing!
			break;

		case FORMAT_UL | FORMAT_BOLD:
			SetTextColor(hDC, RGB_BLACK);
			SetBkColor(hDC, RGB_WHITE);
			break;

		case FORMAT_INV:
			SetTextColor(hDC, RGB_LTGREY);
			SetBkColor(hDC, RGB_BLACK);
			break;

		case FORMAT_INV | FORMAT_BOLD:
			SetTextColor(hDC, RGB_WHITE);
			SetBkColor(hDC, RGB_BLACK);
			break;

		case FORMAT_INV | FORMAT_UL:
			SetTextColor(hDC, RGB_LTGREY);
			SetBkColor(hDC, RGB_BLACK);
			break;

		case FORMAT_INV | FORMAT_UL | FORMAT_BOLD:
			SetTextColor(hDC, RGB_WHITE);
			SetBkColor(hDC, RGB_BLACK);
			break;

		default:
			break;
	}
}

void SetFormat(int format, BOOL enable) {
	if (enable) {
		CURRENTFORMAT(TermInfo) = CURRENTFORMAT(TermInfo) | format;
	}
	else {
		CURRENTFORMAT(TermInfo) = CURRENTFORMAT(TermInfo) & (!format);
	}
}

void PrintChar(char c) {
	int memMove, i;

	// Update our buffer
	SCREENCHAR(TermInfo, ROW(TermInfo), COLUMN(TermInfo)) = c;

	// Set the format for the current position
	FORMATCODE(TermInfo, ROW(TermInfo), COLUMN(TermInfo)) = CURRENTFORMAT(TermInfo);

	if (COLUMN(TermInfo) == MAXCOLS - 1) {
		if (ROW(TermInfo) == MAXROWS - 1 || (DOUBLELINE(TermInfo) && ROW(TermInfo) >= MAXROWS - 2)) {
			COLUMN(TermInfo) = 0;

			if (DOUBLELINE(TermInfo)) {
				memMove = 2;
			}
			else {
				memMove = 1;
			}
			
			for (i = 0; i < memMove; i++) {
				MoveBuffer();
			}
		}
		else {
			if (DOUBLELINE(TermInfo)) {
				ROW(TermInfo) = ROW(TermInfo) + 2;
				COLUMN(TermInfo) = 0;
			}
			else {
				ROW(TermInfo)++;
				COLUMN(TermInfo) = 0;
			}
		}
	}
	else {
		COLUMN(TermInfo)++;
	}

	InvalidateRect(ghWndTerm, NULL, TRUE);
}

void SetCursorPosition(int x, int y) {
	ROW(TermInfo) = x;
	COLUMN(TermInfo) = y;
}

void MoveCursor(int x, int y) {
	ROW(TermInfo) = ROW(TermInfo) + x;
	COLUMN(TermInfo) = COLUMN(TermInfo) + y;
}

void EraseFromCursorToEOL() {
	int i;

	for (i = COLUMN(TermInfo); i < MAXCOLS; i++) {
		SCREENCHAR(TermInfo, ROW(TermInfo), i) = ' ';
		FORMATCODE(TermInfo, ROW(TermInfo), i) = CURRENTFORMAT(TermInfo);
	}
	InvalidateRect(ghWndTerm, NULL, TRUE);
}

void EraseFromSOLToCursor() {
	int i;

	for (i = 0; i < COLUMN(TermInfo); i++) {
		SCREENCHAR(TermInfo, ROW(TermInfo), i) = ' ';
		FORMATCODE(TermInfo, ROW(TermInfo), i) = FORMATCODE(TermInfo, ROW(TermInfo), 0);
	}
	InvalidateRect(ghWndTerm, NULL, TRUE);
}

void EraseFromCursorToEOS() {
	int i, k;

	EraseFromCursorToEOL();

	for (i = ROW(TermInfo) + 1; i < MAXROWS - ROW(TermInfo); i++) {
		for (k = 0; k < MAXCOLS; k++) {
			SCREENCHAR(TermInfo, i, k) = ' ';
			FORMATCODE(TermInfo, i, k) = FORMATCODE(TermInfo, ROW(TermInfo), 0);
		}
	}
	InvalidateRect(ghWndTerm, NULL, TRUE);
}

void EraseFromSOSToCursor() {
	int i, k;

	EraseFromSOLToCursor();

	for (i = 0; i < MAXROWS - ROW(TermInfo); i++) {
		for (k = 0; k < MAXCOLS; k++) {
			SCREENCHAR(TermInfo, i, k) = ' ';
			FORMATCODE(TermInfo, i, k) = FORMATCODE(TermInfo, ROW(TermInfo), 0);
		}
	}
	InvalidateRect(ghWndTerm, NULL, TRUE);
}

void EraseLine() {
	int i;

	for (i = 0; i < MAXCOLS; i++) {
		SCREENCHAR(TermInfo, ROW(TermInfo), i) = ' ';
		FORMATCODE(TermInfo, ROW(TermInfo), i) = FORMATCODE(TermInfo, ROW(TermInfo), 0);
	}
	InvalidateRect(ghWndTerm, NULL, TRUE);
}

void EraseEntireScreen() {
	ClearScreen();
}

void NewLine() {
	int memMove, i;

	if (DOUBLELINE(TermInfo)) {
		ROW(TermInfo) = ROW(TermInfo) + 2;
		if (ROW(TermInfo) > MAXROWS - 1) {
			memMove = ROW(TermInfo) - (MAXROWS - 1);
			for (i = 0; i < memMove; i++) {
				MoveBuffer();
			}
		}
		ROW(TermInfo) = MAXROWS - 1;
	}
	else {
		memMove = 1;
		ROW(TermInfo)++;
		if (ROW(TermInfo) > MAXROWS - 1) {
			memMove = ROW(TermInfo) - (MAXROWS - 1);
			for (i = 0; i < memMove; i++) {
				MoveBuffer();
			}
			ROW(TermInfo) = MAXROWS - 1;
		}
	}
}

void SaveCursorAttributes() {

}

void RestoreCursorAttributes() {

}

void SingleWidthLine() {
	DOUBLELINE(TermInfo) = FALSE;
}

void DoubleWidthLine() {
	DOUBLELINE(TermInfo) = TRUE;
}

void BackSpace() {
	if (COLUMN(TermInfo) != 0) {
		COLUMN(TermInfo) = COLUMN(TermInfo) - 1;
		SCREENCHAR(TermInfo, ROW(TermInfo), COLUMN(TermInfo)) = ' ';
	}
	InvalidateRect(ghWndTerm, NULL, TRUE);
}

void SetScrollingRegion(int x1, int x2) {
	SCROLLTOP(TermInfo) = x1;
	SCROLLBOTTOM(TermInfo) = x2;
}

void MoveBuffer() {
	MoveMemory((LPSTR)(SCREEN(TermInfo)), (LPSTR)(SCREEN(TermInfo)) + MAXCOLS, (MAXROWS - 1) * MAXCOLS);
	FillMemory((LPSTR)(SCREEN(TermInfo) + (MAXROWS - 1)), MAXCOLS, ' ');

	MoveMemory((LPBYTE)(FORMAT(TermInfo)), (LPBYTE)(FORMAT(TermInfo)) + MAXCOLS, (MAXROWS - 1) * MAXCOLS);
	FillMemory((LPBYTE)(FORMAT(TermInfo) + (MAXROWS - 1)), MAXCOLS, CURRENTFORMAT(TermInfo));
}