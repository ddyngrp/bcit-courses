// Program WinMenu.cpp

#define STRICT

#include <windows.h>
#include <stdio.h>
#include "winmenu2.h"

char Name[] = "Comm Shell";
char str[80] = "";
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

#pragma warning (disable: 4096)

LPCSTR	lpszCommName = "com1";
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
	
	Wcl.lpszMenuName = "MYMENU"; // The menu Class
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
   		MessageBox (NULL, "Error opening COM port:", "", MB_OK);
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
	PAINTSTRUCT paintstruct;
	static unsigned k = 0;

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
      		response = MessageBox (hwnd, "Press One:", "Right Button",
         							  MB_ABORTRETRYIGNORE);
			switch (response)
			{
         		case IDABORT:
            		MessageBox (hwnd, "", "Abort", MB_OK);
				break;
				case IDRETRY:
            		MessageBox (hwnd, "", "Retry", MB_OK);
				break;
				case IDIGNORE:
					MessageBox (hwnd, "", "Ignore", MB_OK);
				break;
			}
		break;

		case WM_LBUTTONDOWN:		// Process left button
      		response = MessageBox (hwnd, "Conitnue?", "Left Button",
         							  MB_ICONHAND | MB_YESNO);
			switch (response)
			{
         		case IDYES:
            		MessageBox (hwnd, "Press Button", "Yes", MB_OK);
				break;
				case IDNO:
            		MessageBox (hwnd, "Press Button", "No", MB_OK);
				break;
			}
		break;
		
		case WM_CHAR:	// Process keystroke
			hdc = GetDC (hwnd);			 // get device context
			sprintf (str, "%c", (char) wParam); // Convert char to string
			TextOut (hdc, 10*k, 0, str, strlen (str)); // output character	
			k++; // increment the screen x-coordinate
			ReleaseDC (hwnd, hdc); // Release device context
		break;
		
		case WM_PAINT:		// Process a repaint message
			hdc = BeginPaint (hwnd, &paintstruct); // Acquire DC
			TextOut (hdc, 0, 0, str, strlen (str)); // output character
			EndPaint (hwnd, &paintstruct); // Release DC
		break;

		case WM_DESTROY:	// Terminate program
      		PostQuitMessage (0);
		break;
		default:
			return DefWindowProc (hwnd, Message, wParam, lParam);
	}
	return 0;
}