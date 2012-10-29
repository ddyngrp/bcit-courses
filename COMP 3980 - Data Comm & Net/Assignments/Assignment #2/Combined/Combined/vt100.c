#include <stdio.h>
#include "vt100.h"
#include "terminal.h"

void interpretChar(char c) {
	switch (engInfo.mode) {
		case PRINTING_MODE:
			switch (c) {
				case ASCII_ESC:
					engInfo.mode = INTERPRETING_MODE;
					break;
				case ASCII_CR:
					SetCursorPosition(ROW(TermInfo), 0);
					break;
				case ASCII_LF:
					NewLine();
					break;
				case ASCII_BS:
					BackSpace();
					break;
				case ASCII_BELL:
					Beep(750, 300);
					break;
				case 0x0F:
					// do nothing!
					break;

				default:
					PrintChar(c);
					break;
			}
			break;
		case INTERPRETING_MODE:
			engInfo.code[engInfo.codeLen] = c;
			switch (parseCode()) {
				case PARTIAL:
					engInfo.codeLen++;
					break;
				case VALID:
					resetCode();
					break;
				case INVALID:
					resetCode();
					break;
			}
	}
}

void resetCode() {
	int i;
	engInfo.codeLen = 0;
	for (i=0; i<MAX_CODE_LENGTH; i++) {
		engInfo.code[i] = '\0';
	}
	engInfo.mode = PRINTING_MODE;
}

int parseCode() {
	size_t l = strlen(engInfo.code);
	int i = 1, j = 1;	// used for generically collecting values using sscanf_s()
	switch (engInfo.code[0]) {
		case '[':
			switch (engInfo.code[l-1]) {
				case '[':
					return PARTIAL;
				case 'A': // move cursor up
					sscanf_s(engInfo.code, "[%dA", &i);
					MoveCursor(-1, 0);
					return VALID;
				case 'B': // move cursor down
					sscanf_s(engInfo.code, "[%dB", &i);
					MoveCursor(i, 0);
					return VALID;
				case 'C': // move cursor right
					sscanf_s(engInfo.code, "[%dC", &i);
					MoveCursor(0, i);
					return VALID;
				case 'D': // move cursor left
					sscanf_s(engInfo.code, "[%dD", &i);
					MoveCursor(0, -i);
					return VALID;
				case 'H': // set cursor position
					sscanf_s(engInfo.code, "[%d;%DH", &i, &j);
					SetCursorPosition(i - 1, j - 1);
					return VALID;
				case 'f': // set cursor position
					sscanf_s(engInfo.code, "[%d;%df", &i, &j);
					SetCursorPosition(i - 1, j - 1);
					return VALID;
				case 'K':
					switch (engInfo.code[1]) {
						case 'K': // erase from cursor to end of line
							EraseFromCursorToEOL();
							return VALID;
						case '1': // erase from start of line to cursor
							EraseFromSOLToCursor();
							return VALID;
						case '2': // erase entire line
							EraseLine();
							return VALID;
					}
					break;
				case 'J':
					switch (engInfo.code[1]) {
						case 'J':
							EraseFromCursorToEOS();
							return VALID;
						case '1':
							EraseFromSOSToCursor();
							return VALID;
						case '2':
							EraseEntireScreen();
							return VALID;
					}
					break;
				case 'm':
					switch (engInfo.code[1]) {
						case 'm': // clear format
							SetFormat(FORMAT_BOLD | FORMAT_UL | FORMAT_INV, FALSE);
							return VALID;
						case '1': // set bold
							SetFormat(FORMAT_BOLD, TRUE);
							return VALID;
						case '4': // set underline
							SetFormat(FORMAT_UL, TRUE);
							return VALID;
						case '7': // set invert
							SetFormat(FORMAT_INV, TRUE);
							return VALID;
						default:
							return INVALID;
					}
					return INVALID;
				case 'h':
				case 'l':
					switch (engInfo.code[l-2]) {
						case 1:
							//setCursorKeyMode(engInfo.code[l-1] == 'h');
							return VALID;
						case 4:
							//setSlowScroll(engInfo.code[l-1] == 'h');
							return VALID;
						case 5:
							//setReverseVideo(engInfo.code[l-1] == 'h');
							return VALID;
						case 6:
							//setOriginMode(engInfo.code[l-1] == 'h');
							return VALID;
						case 7:
							//setAutoWrapMode(engInfo.code[l-1] == 'h');
							return VALID;
						case 0:	// 20
							//setNewLineMode(engInfo.code[l-1] == 'h');
							return VALID;
						default:
							return INVALID;
					}
				case 'r':
					sscanf_s(engInfo.code, "[%d;%dr", &i, &j);
					SetScrollingRegion(i, j);
					return VALID;
				case 'g':
					switch (engInfo.code[1]) {
						case 'g':
							//clearTabAtCurrentColumn();
							return VALID;
						case '0':
							//clearTabAtCurrentColumn();
							return VALID;
						case '3':
							//clearAllTabs();
							return VALID;
					}
					break;

				case 'n':
					switch (engInfo.code[1]) {
						case '6':
							//PrintString(ConstructCursorPositionReport());
							return VALID;
						case '5':
							//PrintString(ConstructStatusReport());
							return VALID;
					}
					break;
			}
			return PARTIAL;
		case 'D':
			//index();
			return VALID;
		case 'E':
			NewLine();
			return VALID;
		case 'M':
			//reverseIndex();
			return VALID;
		case '7':
			//saveCursorAndAttributes();
			return VALID;
		case '8':
			//restoreCursorAndAttributes();
			return VALID;
		case '#':
			if (l > 1) {
				switch (engInfo.code[1]) {
					case '2':
						//doubleHeightTopHalf();
						return VALID;
					case '4':
						//doubleHeightBottomHalf();
						return VALID;
					case '5':
						SingleWidthLine();
						return VALID;
					case '7':
						DoubleWidthLine();
						return VALID;
					default:
						return INVALID;
				}
			}
			return PARTIAL;
		case '=':
			//setApplicationKeypadMode();
			return VALID;
		case '>':
			//resetApplicationkeypadMode();
			return VALID;
		case 'H':
			//setTabAtCurrentColumn();
			return VALID;
		default:
			if (isalpha(engInfo.code[l-1]))
				return INVALID;
	}
	return PARTIAL;
}

char *ConstructCursorPositionReport() {
	char *s = ".[##;##R";
	s[2] = (COLUMN(TermInfo)/10) + 48;
	s[3] = (COLUMN(TermInfo)%10) + 48;
	s[5] = (ROW(TermInfo)/10) + 48;
	s[6] = (ROW(TermInfo)%10) + 48;
	return s;
}

char *ConstructStatusReport() {
	char *s = ".[c";
	s[0] = ASCII_ESC;
	return s;
}