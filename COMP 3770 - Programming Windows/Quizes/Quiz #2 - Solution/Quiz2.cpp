#include "WndProc.h"


/*********************************************************************
Comp3770 Quiz#3 (Max 10 marks)

Submit your solution to the sharein Quiz folder. Your solution should
be placed in a file with the .h and .cpp files.
DO NOT ZIP/RAR your files.
The folder name should be "LastName FirstName Set" 
e.g. "Richards Dennis B"

Do NOT delete any code provided.

There are two parts:

1. When the right mouse button is clicked two lines are drawn from
(0,0) and out to (100,100) and (-100,100). YOU CANNOT CHANGE THIS!
You need to ADD code to change the ORIGIN to the centre of the
window and the logical:actual ratio of drawing to be 3:5
The Y-axis should be set such that +ve = moving toward the top of
the window, -ve = moving toward the bottom of the window.

2. When the left mouse button is clicked a rectangle is drawn. It
is filled with a colour and outlined in RED. You are NOT required
to get your rectangles to colour like mine.
When the scroll bars move the LAST rectangle is redrawn properly.
Note: for full marks you'll need to figure out how to maintain a
rectangle that was drawn after the scroll bars were moved then
moved again. Hint: it's all about the relative position of the
scrollbars. First time it's drawn you do not include the position,
for future redrawing you need to recall where it was drawn.


Useful functions

GetDC();
GetClientRect();
SetMapMode();
SetViewportOrgEx();
SetViewportExtEx();
SetWindowExtEx();
SelectObject();
CreateSolidBrush()
CreatePen()
DeleteObject()
DeleteDC()


Marking Guidelines:

Functionality														Max
Correct outline														1
Coloured rectangle other than default colours						1
Correct Org															2
Correct Ratio														2 
Scrolls last rectangle correctly when drawn in initial window		2
Scrolls last rectangle correctly when drawn after scrolling			2

Total 10

Note: Code must cleanup as required (-1 otherwise)

*********************************************************************/


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					PSTR szCMLine, int iCmdShow){
	static TCHAR szAppName[] = TEXT ("HelloApplication");
	static HWND	hwnd;
	MSG		msg;
	WNDCLASS wndclass;

	wndclass.style		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;
	wndclass.cbClsExtra	= 0;
	wndclass.cbWndExtra = sizeof(long)*2;
	wndclass.hInstance	= hInstance;
	wndclass.hIcon		= LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor	= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass (&wndclass)){
		MessageBox (NULL, TEXT ("This program requires Windows 95/98/NT"),
					szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,		
						TEXT("Quiz 2"), 
						WS_OVERLAPPEDWINDOW,	
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						800,		
						600,		
						NULL,				
						NULL,				
						hInstance,			
						NULL);			
	SetWindowLong(hwnd,0,0);
	SetWindowLong(hwnd,4,0);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while (TRUE){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
		}
	}

	return msg.wParam;
}
