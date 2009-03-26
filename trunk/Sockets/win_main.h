#ifndef _WIN_MAIN_H_
#define _WIN_MAIN_H_

#include <windows.h>
#include <windowsx.h>

// Global Definitions
#define X_SIZE			380
#define Y_SIZE			240
#define X_MIN_SIZE		450
#define Y_MIN_SIZE		200
#define NUMCONNECTIONS	5
#define WM_SOCKET		10000
#define DEFAULT_PORT	9000
#define EDITSIZE		50
#define BUFSIZE			4096

/* Custom Message Cracker Definition */
#define HANDLE_WM_SOCKET(hwnd, wParam, lParam, fn) \
	((fn)((hwnd), (wParam), (lParam)), 0L)

/* Connection Information */
typedef struct _CONNECTINFO
{
	char ip[EDITSIZE];
	int port;
} connectInfo;

// Global Variables
HINSTANCE		ghInst;				// Main application's global instance
HWND			ghWndMain,			// Main window's global handle
				ghDlgMain;			// Main dialogue window's global handle
HMENU			ghMenu;				// Main window's menu handle
HACCEL			ghAccel;			// Keyboard accelerator
SOCKET			ghSocket;			// Connection socket's global handle
SOCKADDR_IN		remote,				// Server socket information
				local;				// Client socket information
connectInfo		ci;					// Connection information

// Global Functions
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MenuDispatch(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlg_Main(HWND, UINT, WPARAM, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();
void InitWindow(HWND);
BOOL CALLBACK ServerProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ClientProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void client(HWND hwnd);
void server(HWND hwnd);

#endif