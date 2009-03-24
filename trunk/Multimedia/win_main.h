#ifndef _WIN_MAIN_H_
#define _WIN_MAIN_H_

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdio.h>
#include <conio.h>
#include "wavelib.h"
// Global Definitions
#define X_SIZE		380
#define Y_SIZE		240
#define X_MIN_SIZE	450
#define Y_MIN_SIZE	200
#define MAXBUFSIZE 8000

#define LOCALPLAY 500
#define NETWORKPLAY 501

// Global Variables
HINSTANCE		ghInst;				// Main application's global instance
HWND			ghWndMain,			// Main window's global handle
				ghDlgMain;			// Main dialogue window's global handle
HACCEL			ghAccel;			// Keyboard accelerator

// Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MenuDispatch(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlg_Main(HWND, UINT, WPARAM, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();

/* Local Play */
BOOL localSong_Init(HWND hwnd, char * filename);
BOOL localSong_Pause(void);
BOOL localSong_Play(void);
BOOL localSong_Stop(void);
BOOL browseFiles(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
void fileInit(HWND hwnd);

/* Network Play */
void clnt_recv_udp(char buf[]);
void serv_broadcast_clicked(char fileName[80]);
void clnt_recv_tcp(char buf[]);
void serv_recv_tcp(char buf[]);

#endif