// Program WinMenu.cpp

#define STRICT

#include <windows.h>
#include <stdio.h>
#include "winmenu2.h"

char Name[] = "Text Window";
char str[255];	//output buffer
int X = 0, Y = 0; // Current coordinates

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

#pragma warning (disable: 4096)

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASSEX Wcl;

	Wcl.cbSize = sizeof (WNDCLASSEX);
	Wcl.style = 0;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style
	
	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = Name;
	
	Wcl.lpszMenuName = NULL; // The menu Class
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0; 
	
	if (!RegisterClassEx (&Wcl))
		return 0;

	hwnd = CreateWindow (Name, Name, WS_OVERLAPPEDWINDOW, 10, 10,
   							600, 400, NULL, NULL, hInst, NULL);
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

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
	HDC hdc;
	PAINTSTRUCT paintstruct;
	TEXTMETRIC tm;
	SIZE size;

	switch (Message)
	{
		case WM_PAINT:		// Process a repaint message
			hdc = BeginPaint (hwnd, &paintstruct); // Acquire DC
			GetTextMetrics(hdc, &tm);		// get text metrics 

			X = Y = 0;

			sprintf(str, "This is on the first line.");
			TextOut(hdc, X, Y, str, strlen(str)); 
			Y = Y + tm.tmHeight + tm.tmExternalLeading; // next line

			strcpy(str, "This is on the second line. ");
			TextOut(hdc, X, Y, str, strlen(str)); 
			Y = Y + tm.tmHeight + tm.tmExternalLeading; // next line 

			strcpy(str, "This is on the third line. ");
			TextOut(hdc, X, Y, str, strlen(str)); 

			// compute length of a string 
			GetTextExtentPoint32(hdc, str, strlen(str), &size);
			sprintf(str, "The preceding sentence is %ld units long", size.cx);
			X = size.cx; // advance to end of previous string 
			TextOut(hdc, X, Y, str, strlen(str));
			Y = Y + tm.tmHeight + tm.tmExternalLeading; // next line
			X = 0; // return to start of line 

			sprintf(str, "The space between lines is %ld pixels.", tm.tmExternalLeading+tm.tmHeight);
			TextOut(hdc, X, Y, str, strlen(str)); 
			Y = Y + tm.tmHeight + tm.tmExternalLeading; // next line 
 
			sprintf(str, "Average character width is %ld pixels", tm.tmAveCharWidth);
			TextOut(hdc, X, Y, str, strlen(str));
			Y = Y + tm.tmHeight + tm.tmExternalLeading; // next line 

			// set text color to red 
			SetTextColor(hdc, RGB(255, 0, 0));
			
			// set background color to blue 
			SetBkColor(hdc, RGB(0, 0, 255));

			sprintf(str, "This line is red on blue background.");
			TextOut(hdc, X, Y, str, strlen(str));
			Y = Y + tm.tmHeight + tm.tmExternalLeading; // next line

			// switch to transparent mode
			SetBkMode(hdc, TRANSPARENT);
			sprintf(str, "This line is red. The background is unchanged.");
			TextOut(hdc, X, Y, str, strlen(str));

			EndPaint(hwnd, &paintstruct);
		break;

		

		case WM_DESTROY:	// Terminate program
      		PostQuitMessage (0);
		break;
		
		default:
			return DefWindowProc (hwnd, Message, wParam, lParam);
	}
	return 0;
}