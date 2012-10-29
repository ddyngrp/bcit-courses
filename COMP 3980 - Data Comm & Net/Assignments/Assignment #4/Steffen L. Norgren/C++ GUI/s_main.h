/*
	MODULE: main.h

	PURPOSE: Main WinProc definitions

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
 */

#if !defined MAIN_H
#define MAIN_H

#include <windows.h>

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ChatDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
DWORD WINAPI TimerThread(LPVOID);

#endif

