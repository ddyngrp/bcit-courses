#include "cases.h"
#include "functions.h"

TCHAR Name[] = TEXT("COMM++");

/*void RegisterInstance(HINSTANCE hInst)
*Purpose: Intitializes all of the windclass components and registers the class.
*Arg 1 - Handle to the instance.
*/
void RegisterInstance(HINSTANCE hInst) {
	WNDCLASSEX Wcl;

	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style
	
	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = Name;
	
	Wcl.lpszMenuName = TEXT("MYMENU"); // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0; 
	
	if(!RegisterClassEx(&Wcl))
		return;
}

/*void MakeWindow(int nCmdShow, HINSTANCE hInst)
*Purpose: Creates the physical window.
*Arg 1 - Decides whether the window will be normal, maximized or minimized.
*Arg 2 - Handle to the instance.
*/
void MakeWindow(int nCmdShow, HINSTANCE hInst) {
	HWND hwnd;
	hwnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, 10, 10,
		(9*80) + 5, 452, NULL, NULL, hInst, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
}

/*BOOL CreateReadThread(HWND hwnd)
*Purpose: Creates an additional thread for reading.
*Arg 1 - Decides whether the window will be normal, maximized or minimized.
*/
BOOL CreateReadThread(HWND hwnd) {
	if((hThread = CreateThread(NULL, 0,
		(LPTHREAD_START_ROUTINE) ReadThread, hwnd,
		0, NULL)) == INVALID_HANDLE_VALUE) {
		ReadThreadErrorMsg();
		CloseHandle (hComm);
		return FALSE;
	}
	return TRUE;
}
