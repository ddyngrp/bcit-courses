


/*********************************************************************
Comp3770 Quiz#3 (Max 10 marks) 

Submit your solution to the sharein Quiz folder. Your solution should
be placed in a file with the project file,.h and .cpp files. The folder
name should be "LastName FirstName Set" e.g. "Richards Dennis B"

Examine the example exe file.

The program creates a clipping region (using a polygon and an ellipse
the points of which are defined for you they are combined).
The clipping region is CLEARED (white - not painted) while the rest of the client area
is painted red (set for you in WM_SIZE).
The clipping area is set so no line drawn can be SEEN outside the
clipping area even while drawing.
Every 10s the clipping area is cleared (use only 1 line of code).
Lines are drawn using the mouse - colour is yellow and lines
are made 10pixels thick.
User clicks left mouse button to start line then drags mouse.
Line is completed when left mouse button released.
Lines are drawn using R2_NOTXORPEN mode during dragging then
R2_COPYPEN mode when the user releases the left mouse button.
Make sure you release any resouces made.
All code needed to add goes in Wndproc.cpp

Marking Guide

Function				Max
Region setup			2
Region clipping			1
Region clearing			1
Timer setup/use			2
Line drawing XOR mode	4 (incl mouse use, drawing etc.)

Total 10 marks

Useful functions:
GetDC()
ReleaseDC()
CreateRectRgn()
CreateSolidBrush()
CreatePolygonRgn()
CreateEllipticRgnIndirect()
CombineRgn()
FillRgn()
DeleteObject()
SetROP2()
LOWORD()
HIWORD()
SelectClipRgn()
MoveToEx()
LineTo()
SelectClipRgn()
KillTimer()
SetTimer()
InvalidateRgn()
*********************************************************************/
#include "WndProc.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					PSTR szCMLine, int iCmdShow){
	static TCHAR szAppName[] = TEXT ("HelloApplication");
	HWND	hwnd;
	MSG		msg;
	WNDCLASS wndclass;

	wndclass.style		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;
	wndclass.cbClsExtra	= sizeof(long);
	wndclass.cbWndExtra = 0;
	wndclass.hInstance	= hInstance;
	wndclass.hIcon		= LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor	= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass (&wndclass)){
		MessageBox (NULL, TEXT ("This program requires Windows 95/98/NT"),
					szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,		
						TEXT("Hello World for Windows"), 
						WS_OVERLAPPEDWINDOW,	
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						NULL,				
						NULL,				
						hInstance,			
						NULL);				
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
