// Program: sem.cpp
//	Programmer: A. Abdulla & C. Calvert
// Description:	Thread Synchronization
// Date:				January, 1997

#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Sem.h"

#pragma warning (disable: 4096)

// Function Prototypes

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
BOOL Register (HINSTANCE hInst);
HWND Create (HINSTANCE hInst, int nCmdShow);


// Thread Classes

#define	Sem_DefProc	DefWindowProc
BOOL Sem_OnCreate (HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void Sem_OnDestroy (HWND hwnd);
void Sem_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Sem_OnPaint (HWND hwnd);

static char szAppName[] = "Semaphores";
static HWND MainWindow;
static HINSTANCE hInstance;
static int GlobalData;
static BOOL CritSects;
static HANDLE hSem;

// The main program
#pragma argsused

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPrevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow)
{
   MSG Msg;

   if (!hPrevInstance)
   	if (!Register(hInst))
      	return FALSE;

   MainWindow = Create (hInst, nCmdShow);
   	if (!MainWindow)
      	return FALSE;


  	while (GetMessage (&Msg, NULL, 0, 0))
   {
   	TranslateMessage (&Msg);
      DispatchMessage (&Msg);
   }

	return Msg.wParam;
}


// Register the Window
BOOL Register (HINSTANCE hInst)
{
   WNDCLASS W;

   memset (&W, 0, sizeof(WNDCLASS));
   W.style = CS_HREDRAW | CS_VREDRAW;
   W.lpfnWndProc = WndProc;
   W.hInstance = hInst;
   W.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   W.lpszClassName = szAppName;
   W.cbClsExtra = 0;
   W.cbWndExtra = 0;
   W.hIcon = LoadIcon (hInst, "ThreadsIcon");
   W.hCursor = LoadCursor (NULL, IDC_ARROW);
   W.lpszMenuName = "ThreadMenu";

   return (RegisterClass (&W) != 0);
 }

// Create the Window
HWND Create (HINSTANCE hInst, int nCmdShow)
{
 	hInstance = hInst;

   HWND hwnd = CreateWindow (szAppName, szAppName, WS_OVERLAPPEDWINDOW,
   						CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                     CW_USEDEFAULT, NULL, NULL, hInst, NULL);

   if (hwnd == NULL)
   	return hwnd;

   nCmdShow = SW_SHOWMAXIMIZED;

   ShowWindow (hwnd, nCmdShow);
   UpdateWindow (hwnd);

   return hwnd;
}

// WndProc and Implementation
LRESULT CALLBACK WndProc (HWND hwnd, UINT Message,
                          WPARAM wParam, LPARAM lParam)
{
	switch (Message)
   {
   	HANDLE_MSG (hwnd, WM_CREATE, Sem_OnCreate);
      HANDLE_MSG (hwnd, WM_DESTROY, Sem_OnDestroy);
      HANDLE_MSG (hwnd, WM_COMMAND, Sem_OnCommand);
      HANDLE_MSG (hwnd, WM_PAINT, Sem_OnPaint);

      default:
      	return Sem_DefProc (hwnd, Message, wParam, lParam);
   }
}


// Create and Initialize the critical sections
#pragma argsused
BOOL Sem_OnCreate (HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	 CreateWindow ("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
   						12, 50, 200, 180, hwnd, HMENU(ID_LISTBOX1),
                     hInstance, NULL);

    CreateWindow ("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
   						215, 50, 200, 180, hwnd, HMENU(ID_LISTBOX2),
                     hInstance, NULL);

    hSem = CreateSemaphore (NULL, 1, 1,"OneSem");
    CritSects = FALSE;
    return TRUE;
}


// Handle the WM_DESTROY message
#pragma argsused
void Sem_OnDestroy (HWND hwnd)
{
	CloseHandle(hSem);
   PostQuitMessage(0);
}


// The first thread routine
unsigned long _stdcall ThreadFunc1 (LPVOID)
{
	int i, j;
   char S[100];

   ListBox_ResetContent (GetDlgItem (MainWindow, ID_LISTBOX1));

   for (j=0; j < 10; j++)
   {
   	if (CritSects)
      	WaitForSingleObject (hSem, INFINITE);
      Sleep (0);
      GlobalData +=3;
      i = GlobalData - 3;

      sprintf (S, "Information: %d", i);
      ListBox_AddString (GetDlgItem (MainWindow, ID_LISTBOX1), S);
      GlobalData -= 3;
      if (CritSects)
      	ReleaseSemaphore (hSem, 1, NULL);
   }
   return 0;
}


// The second thread routine
unsigned long _stdcall ThreadFunc2 (LPVOID)
{
	int i, j;
   char S[100];

   ListBox_ResetContent (GetDlgItem (MainWindow, ID_LISTBOX2));

   for (j=0; j < 10; j++)
   {
   	if (CritSects)
      	WaitForSingleObject (hSem, INFINITE);
      Sleep (1);
      GlobalData -=3;
      i = GlobalData + 3;

      sprintf (S, "Information: %d", i);
      ListBox_AddString (GetDlgItem (MainWindow, ID_LISTBOX2), S);
      GlobalData += 3;
      if (CritSects)
      	ReleaseSemaphore (hSem, 1, NULL);
   }
   return 0;
}


// Get both threads executing concurrently
void RunThread (HWND hwnd)
{
	DWORD ThreadID1;
   DWORD ThreadID2;
   HANDLE ThreadHandles[2];

   GlobalData = 100;

   ThreadHandles[0] = CreateThread (NULL, 0, ThreadFunc1, NULL, 0, &ThreadID1);
   ThreadHandles[1] = CreateThread (NULL, 0, ThreadFunc2, NULL, 0, &ThreadID2);

   if (!ThreadHandles[0] || !ThreadHandles[1])
   	MessageBox (hwnd, "No Thread", NULL, MB_OK);
}


// Handle the WM_COMMAND message
#pragma argsused
void Sem_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch(id)
   {
   	case ID_GOTHREAD:
      	RunThread (hwnd);
      break;

      case ID_CRITSECTS:
      	CritSects = !CritSects;
      break;
   }
}


// handle the WM_PAINT message
void Sem_OnPaint (HWND hwnd)
{
	PAINTSTRUCT PaintStruct;

   HDC PaintDC = BeginPaint (hwnd, &PaintStruct);
   TextOut (PaintDC, 1, 1, "Test", 4);
   EndPaint (hwnd, &PaintStruct);
}


