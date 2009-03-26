#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include "win_main.h"

void sockAccept(HWND hwnd, WPARAM wParam, LPARAM lParam);
void sockClose(HWND hwnd, WPARAM wParam, LPARAM lParam);
void sockConnect(HWND hwnd, WPARAM wParam, LPARAM lParam);
void sockRead(HWND hwnd, WPARAM wParam, LPARAM lParam);
void sockWrite(HWND hwnd, WPARAM wParam, LPARAM lParam);

#endif
