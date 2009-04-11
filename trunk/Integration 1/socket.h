#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include "win_main.h"

/* Universal Socket Functions */
void sockClose(HWND hwnd, WPARAM wParam, LPARAM lParam);

/* TCP Socket Functions */
void tcp_sockAccept(HWND hwnd, WPARAM wParam, LPARAM lParam);
void tcp_sockConnect(HWND hwnd, WPARAM wParam, LPARAM lParam);
void tcp_sockRead(HWND hwnd, WPARAM wParam, LPARAM lParam);
void tcp_sockWrite(HWND hwnd, WPARAM wParam, LPARAM lParam);

#endif
