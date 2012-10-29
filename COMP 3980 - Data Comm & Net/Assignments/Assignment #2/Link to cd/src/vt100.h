#ifndef _VT100_H
#define _VT100_H

#define ASCII_ESC 0x1B
#define PRINTING_MODE 0
#define INTERPRETING_MODE 1
#define MAX_CODE_LENGTH 8
#define VALID 1
#define INVALID 0
#define PARTIAL -1

#define ASCII_CR	0x0D
#define ASCII_LF	0x0A
#define ASCII_BS	0x08
#define ASCII_BELL	0x07

char *ConstructCursorPositionReport();
char *ConstructStatusReport();

void interpretChar(char);
void resetCode();
int parseCode();
#endif