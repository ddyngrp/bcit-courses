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
	FORMATCODE(TermInfo, ROW(TermInfo), COLUMN(TermInfo)) = CURRENTFORMAT(TermInfo);
}

void PrintChar(char c) {
	int memMove, i;

	SCREENCHAR(TermInfo, ROW(TermInfo), COLUMN(TermInfo)) = c;
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
				MoveMemory((LPSTR)(SCREEN(TermInfo)), (LPSTR)(SCREEN(TermInfo)) + MAXCOLS, (MAXROWS - 1) * MAXCOLS);
				FillMemory((LPSTR)(SCREEN(TermInfo) + (MAXROWS - 1)), MAXCOLS, ' ');

				MoveMemory((LPBYTE)(FORMAT(TermInfo)), (LPBYTE)(FORMAT(TermInfo)) + MAXCOLS, (MAXROWS - 1) * MAXCOLS);
				FillMemory((LPBYTE)(FORMAT(TermInfo) + (MAXROWS - 1)), MAXCOLS, CURRENTFORMAT(TermInfo));
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
	COLUMN(TermInfo) = x;
	ROW(TermInfo) = y;
}

void MoveCursor(int x, int y) {
	COLUMN(TermInfo) = COLUMN(TermInfo) + x;
	ROW(TermInfo) = ROW(TermInfo) + y;
}

void EraseFromCursorToEOL() {
	int i;

	for (i = COLUMN(TermInfo); i < MAXCOLS; i++) {
		SCREENCHAR(TermInfo, ROW(TermInfo), i) = ' ';
		FORMATCODE(TermInfo, ROW(TermInfo), i) = CURRENTFORMAT(TermInfo);
	}
}

void EraseFromSOLToCursor() {
	int i;

	for (i = 0; i < COLUMN(TermInfo); i++) {
		SCREENCHAR(TermInfo, ROW(TermInfo), i) = ' ';
		FORMATCODE(TermInfo, ROW(TermInfo), i) = FORMATCODE(TermInfo, ROW(TermInfo), 0);
	}
}

void EraseEntireScreen() {
	ClearScreen();
}

void NewLine() {
	if (DOUBLELINE(TermInfo)) {
		ROW(TermInfo) = ROW(TermInfo) + 2;
	}
	else {
		ROW(TermInfo)++;
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