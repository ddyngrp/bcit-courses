// Program WinMenu.cpp

#define STRICT

#include <windows.h>
#include <stdio.h>
#include "winmenu2.h"

TCHAR Name[] = TEXT("Comm Shell");
char str[80] = "";
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

#pragma warning (disable: 4096)

TCHAR	lpszCommName[] = TEXT("com1");
COMMCONFIG	cc;
HANDLE hComm;

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASSEX Wcl;

	Wcl.cbSize = sizeof (WNDCLASSEX);
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
	
	if (!RegisterClassEx (&Wcl))
		return 0;

	hwnd = CreateWindow (Name, Name, WS_OVERLAPPEDWINDOW, 10, 10,
   							600, 400, NULL, NULL, hInst, NULL);
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	if ((hComm = CreateFile (lpszCommName, GENERIC_READ | GENERIC_WRITE, 0,
   							NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL))
                        	== INVALID_HANDLE_VALUE)
	{
   		MessageBox (NULL, TEXT("Error opening COM port:"), TEXT(""), MB_OK);
		return FALSE;
	}

	while (GetMessage (&Msg, NULL, 0, 0))
	{
   		TranslateMessage (&Msg);
		DispatchMessage (&Msg);
	}

	return Msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT Message,
                          WPARAM wParam, LPARAM lParam)
{
	int response;
	HDC hdc;

	switch (Message)
	{
		case WM_COMMAND:
			switch (LOWORD (wParam))
			{
          		case IDM_COM1:
            		cc.dwSize = sizeof(COMMCONFIG);
					cc.wVersion = 0x100;
					GetCommConfig (hComm, &cc, &cc.dwSize);
            		if (!CommConfigDialog (lpszCommName, hwnd, &cc))
               			break;
				break;
				case IDM_COM2:
					cc.dwSize = sizeof(COMMCONFIG);
					cc.wVersion = 0x100;
					GetCommConfig (hComm, &cc, &cc.dwSize);
            		if (!CommConfigDialog (lpszCommName, hwnd, &cc))
               			break;
				break;
			}
		break;
   		case WM_RBUTTONDOWN:		// Process right button
      		response = MessageBox (hwnd, TEXT("Press One:"), TEXT("Right Button"),
         							  MB_ABORTRETRYIGNORE);
			switch (response)
			{
         		case IDABORT:
            		MessageBox (hwnd, TEXT(""), TEXT("Abort"), MB_OK);
				break;
				case IDRETRY:
            		MessageBox (hwnd, TEXT(""), TEXT("Retry"), MB_OK);
				break;
				case IDIGNORE:
					MessageBox (hwnd, TEXT(""), TEXT("Ignore"), MB_OK);
				break;
			}
		break;

		case WM_LBUTTONDOWN:		// Process left button
      		response = MessageBox (hwnd, TEXT("Continue?"), TEXT("Left Button"),
         							  MB_ICONHAND | MB_YESNO);
			switch (response)
			{
         		case IDYES:
            		MessageBox (hwnd, TEXT("Press Button"), TEXT("Yes"), MB_OK);
				break;
				case IDNO:
            		MessageBox (hwnd, TEXT("Press Button"), TEXT("No"), MB_OK);
				break;
			}
		break;
		
		case WM_CHAR:	// Process keystroke
			hdc = GetDC (hwnd);			 // get device context
			TextOut (hdc, 1, 1, TEXT(" "), 2); //erase old character
			sprintf (str, "%c", LPCWSTR(wParam)); // Convert char to string
			TextOut (hdc, 1, 1, (LPCWSTR)str, strlen (str)); // output character
			ReleaseDC (hwnd, hdc); // Release device context
		break;
		
		case WM_DESTROY:	// Terminate program
      		PostQuitMessage (0);
		break;
		default:
			return DefWindowProc (hwnd, Message, wParam, lParam);
	}
	return 0;
}