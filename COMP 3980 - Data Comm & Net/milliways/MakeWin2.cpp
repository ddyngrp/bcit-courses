// Program MakeWin.cpp

#define STRICT

#include <windows.h>

static TCHAR Name[] = TEXT("MakeWin");
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

#pragma warning (disable: 4096)

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hprevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASSEX Wcl;

	// Define a Window class
	Wcl.cbSize = sizeof (WNDCLASSEX);
	Wcl.style = 0; // default style
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION); // large icon 
	Wcl.hIconSm = NULL; // use small version of large icon
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);  // cursor style

	Wcl.lpfnWndProc = WndProc; // window function
	Wcl.hInstance = hInst; // handle to this instance
	Wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); //white background
	Wcl.lpszClassName = Name; // window class name
	
	Wcl.lpszMenuName = NULL; // no class menu 
	Wcl.cbClsExtra = 0;      // no extra memory needed
	Wcl.cbWndExtra = 0; 
	
	// Register the class
	if (!RegisterClassEx (&Wcl))
		return 0;

	hwnd = CreateWindow (
		Name, // name of window class
		Name, // title 
		WS_OVERLAPPEDWINDOW, // window style - normal
		CW_USEDEFAULT,	// X coord
		CW_USEDEFAULT, // Y coord
   		CW_USEDEFAULT, // width
		CW_USEDEFAULT, // height
		NULL, // no parent window
		NULL, // no menu
		hInst, // instance handle
		NULL // no additional arguments
	);
	
	// Display the window
	ShowWindow (hwnd, nCmdShow);
	UpdateWindow (hwnd);

	// Create the message loop
	while (GetMessage (&Msg, NULL, 0, 0))
	{
   		TranslateMessage (&Msg); // translate keybpard messages
		DispatchMessage (&Msg); // dispatch message and return control to windows
	}

	return Msg.wParam;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT Message,
                          WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		case WM_DESTROY:		// message to terminate the program
			PostQuitMessage (0);
		break;
		
		default: // Let Win32 process all other messages
			return DefWindowProc (hwnd, Message, wParam, lParam);
	}
	return 0;	
}