// ScrollBars.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include <stdlib.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SCROLLBARS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_SCROLLBARS);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SCROLLBARS);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_SCROLLBARS;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int  cxClient,cyClient;
	int iVertPos, iHorzPos;//IMPORTANT VARIABLES
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);
	SCROLLINFO si;
	char *cBuffer = (char*)malloc(sizeof(char)*8);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			si.cbSize = sizeof(si);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = 0;
			si.nMax = 2000;
			si.nPage = cyClient;
			SetScrollInfo(hWnd, SB_VERT, &si, TRUE);

			si.cbSize = sizeof(si);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = 0;
			si.nMax = 2000;
			si.nPage = cxClient;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			return 0;
		
		case WM_HSCROLL:
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;

			GetScrollInfo(hWnd, SB_HORZ, &si);
			iHorzPos = si.nPos;

			switch (LOWORD(wParam))
			{
			case SB_LINELEFT:
				si.nPos -=1;
				break;

			case SB_LINERIGHT:
				si.nPos += 1;
				break;

			case SB_PAGELEFT:
				si.nPos -= si.nPage;
				break;

			case SB_PAGERIGHT:
				si.nPos += si.nPage;
				break;

			case SB_THUMBTRACK:
				si.nPos = si.nTrackPos;
				break;

			default:
				break;
			}

			si.fMask = SIF_POS;
			SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
			GetScrollInfo(hWnd, SB_HORZ, &si);

			if (si.nPos != iHorzPos)
			{
				ScrollWindow(hWnd, iHorzPos - si.nPos, 0, NULL, NULL);
				UpdateWindow(hWnd);
			}
			return 0;

			case WM_VSCROLL:

				si.cbSize = sizeof(si);
				si.fMask = SIF_ALL;
				GetScrollInfo(hWnd, SB_VERT, &si);
				iVertPos = si.nPos;

				switch(LOWORD(wParam)){
				case SB_TOP:
					si.nPos = si.nMin;
					break;

				case SB_BOTTOM:
					si.nPos = si.nMax;
					break;

				case SB_LINEUP:
					si.nPos--;
					break;

				case SB_LINEDOWN:
					si.nPos++;
					break;

				case SB_PAGEUP:
					si.nPos -= si.nPage;
					break;

				case SB_PAGEDOWN:
					si.nPos += si.nPage;
					break;

				case SB_THUMBTRACK:
					si.nPos = si.nTrackPos;
					break;

				default:
					break;
				}

				si.fMask = SIF_POS;
				SetScrollInfo(hWnd, SB_VERT, &si, TRUE);
				GetScrollInfo(hWnd, SB_VERT, &si);

				if (si.nPos != iVertPos){
					ScrollWindow(hWnd, 0, iVertPos - si.nPos, NULL, NULL);
					UpdateWindow(hWnd);
				}
				return 0;

		case WM_PAINT:
/******************************************************************************
When scrolling, you are moving the stuff you've drawn (text, lines, bitmaps, etc.)
i.e. they are changing location thus you cannot draw your stuff in the same place -
it must reflect where it now resides on the screen. To this end, you get the vertical
and horizontal positions of the scroll bars and use this information to draw your
stuff in it's correct location. If possible you can take advantage of the clipping
area and draw only within it's boundaries. In this example I cannot since I'm drawing
a rectangle (it would not be efficient to try and draw just the portion of the rectangle
that can be seen - I'll leave that to the clipping area).

  For example, if I set the rectangle to a static position of
  100,100,400,300 the scroll routine will scroll the rectangle away (to the right)as desired
  however when I scroll it back into view it will not reappear (or the parts that left the client
  area) because the clipping area is a small window to the left (1 pixel wide in my case, x=0)
  yet I tell it to draw at start x value 100 (which is not in the clipping area). This stems
  from the confusion that occurs from the ScrollWindow routine that "takes care" of this
  position issue for the portion of the stuff that can be seen but does not "take care" of
  this for the new stuff that is now to be redrawn.

*************************************************************************************/

			hdc = BeginPaint(hWnd, &ps);

			si.cbSize = sizeof(si);
			si.fMask = SIF_POS;
			GetScrollInfo(hWnd, SB_VERT, &si);
			iVertPos = si.nPos;//current vertical position

			GetScrollInfo(hWnd, SB_HORZ, &si);
			iHorzPos = si.nPos;//current horizontal position

			//see how I use the positions of the two scroll bars to adjust the
			//rectangle's position. That's all there is to it.
			Rectangle(hdc, 100-iHorzPos, 100-iVertPos, 400-iHorzPos, 300-iVertPos);
		
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
