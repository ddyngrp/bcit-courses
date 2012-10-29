/* 
* File:   printing.h
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#ifndef _PRINTING_H
#define	_PRINTING_H

#include <windows.h>
#include "main.h"

void printChar(HWND , wndInfo *,TCHAR);
void printString(HWND , wndInfo *,TCHAR *);
void printLine(HWND, wndInfo *, TCHAR *);

#endif
