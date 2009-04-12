#ifndef CRACKERS_H
#define CRACKERS_H

#include "win_main.h"
#include "resource.h"
#include "socket.h"

void OnClose(HWND hwnd);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hwnd);
void OnSize(HWND hwnd, UINT state, int cx, int cy);
void OnTCPSocket(HWND hwnd, WPARAM wParam, LPARAM lParam);
void OnUDPSocket(HWND hwnd, WPARAM wParam, LPARAM lParam);

#endif
