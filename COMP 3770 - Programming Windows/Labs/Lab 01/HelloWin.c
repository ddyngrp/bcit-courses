/**
 *	HelloWin.c -- Displays "Hello, Awful OS!" in client area
**/

#include <windows.h> // header file for the C programming language. It contains all function
					 // declarations in the API, all common macros and all the data types.

/**
 * WndProc: The function you write to receive all input directed at your window. You will have already told
 *			Windows to call this function with messages by supplying a pointer to this function in the
 *			class structure (it is a callback function).
 * 
 * HWND hwnd: This is the unique handle of the window. Remember that many windows could be created from the same
 *			  window class definition you previously registered. So if you created two windows from the class each
 *			  will have a different handle but each will call this function with messages.
 * UINT message: Whenever anything happens to your window, Windows will call this function telling you what has
 *				 happened. The message parameter contains the message sent. You don't want to have to handle all
 *				 the messages but just the ones you are interested in so any messages you decide not to handle
 *				 should be passed back to Windows to handle in a default way. You do this by calling:
 *				 DefWindowProc(...)
 * W/LPARAM w/lParam: Each message sent to your window can have a number of extra values, e.g. if the message is
 *					  that the mouse has been moved over your window then the extra parameters include the x, y
 *					  screen position of the mouse.
**/
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // This can be considered a default constructor.
LRESULT CALLBACK Child1WndProc(HWND, UINT, WPARAM, LPARAM);	// default ctor for a 2nd window
LRESULT CALLBACK Child2WndProc(HWND, UINT, WPARAM, LPARAM);	// default ctor for a 3rd window

TCHAR szChild1[] = TEXT("HelloWin Child #1");	// set the name of the first child window
TCHAR szChild2[] = TEXT("HelloWin Child #2");	// set the name of the second child window

/**
 * WINAPI: We're telling WinMain that we're using the Windows API.
 * WinMain: Conventional name for the user-provided entry point for a Microsoft Windows-based application.
 *
 * HINSTANCE hInstance: Handle to the current instance of the application (the .exe in memory).
 * HINSTANCE hPrevInstance: Handle to the previous instance of the application. This parameter is always NULL.
 *							It is a legacy from 16-bit Windows.
 * LPSTR lpCmdLine: Pointer to a null-terminated string specifying the command line for the application,
 *					excluding the program name.
 * int nCmdShow: Specifies how the window is to be shown.
**/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	static TCHAR szAppName[] = TEXT("HelloWin");	// set the name of the application
	HWND hwnd, hwndChild1, hwndChild2;				// holds handle to the main window and child windows
	MSG	msg;										// holds any message retrieved from the message queue
	WNDCLASS wndclass;								// wnd class for thegistration
	
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;				// redraw on refresh for horizontal/verticle
	wndclass.lpfnWndProc	= WndProc;								// points to the window procedure that processes messages for the windows in the class.
	wndclass.cbClsExtra		= 0;									// amount of extra memory, in bytes, reserved for the class.
	wndclass.cbWndExtra		= 0;									// amount of extra memory, in bytes, reserved for each window in the class.
	wndclass.hInstance		= hInstance;							// application instance handle
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// Set the icon for the application
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Set the cursor for the application
	wndclass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);	// color  used to paint the client area of the window
	wndclass.lpszMenuName	= NULL;									// default menu for windows in the class that do not explicitly define menus.
	wndclass.lpszClassName	= szAppName;							// Identifies the name of the class/application

	// register wndclass to OS so appropriate window messages are sent to the application.
	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, TEXT("This program requires an awful OS"), szAppName, MB_ICONERROR);
		return 0;
	}

	wndclass.lpfnWndProc	= Child1WndProc;	// points to the window procedure that processes messages for the window
	wndclass.cbWndExtra		= sizeof(long);		// amount of extra memory reserved for cach window
	wndclass.lpszClassName	= szChild1;			// identifies the name of the class/application
	RegisterClass(&wndclass);	// register the wndclass to the OS for the 1st child window

	wndclass.lpfnWndProc	= Child2WndProc;	// points to the window procedure that processes messages for the window
	wndclass.cbWndExtra		= sizeof(long);		// amount of extra memory reserved for cach window
	wndclass.lpszClassName	= szChild2;			// identifies the name of the class/application
	RegisterClass(&wndclass);	// register the wndclass to the OS for the 2nd child window

	// main window parameters
	hwnd = CreateWindow(szAppName,					// window class name
						TEXT("The Hello Program"),	// window caption
						WS_OVERLAPPEDWINDOW,		// window style
						0,							// initial x position
						0,							// initial y position
						300,						// initial x size
						200,						// initial y size
						NULL,						// parent window handle
						NULL,						// window menu handle
						hInstance,					// program instance handle
						NULL);						// creation parameters

	// first child window parameters
	hwndChild1 = CreateWindow(szChild1,	TEXT("2nd Hello Window"),
							  WS_OVERLAPPEDWINDOW,				// the window style
							  300, 0, 300, 200,					// initial x,y positions and size
							  hwnd,								// parent window handle
							  NULL,								// window menu handle
							  NULL,								// program instance handle
							  NULL);							// creation parameters

	// second child window parameters
	hwndChild2 = CreateWindow(szChild2,	TEXT("3rd Hello Window"),
							  WS_OVERLAPPEDWINDOW,				// the window style
							  0, 200, 300, 200,					// initial x,y positions and size
							  hwnd,								// parent window handle
							  NULL,								// window menu handle
							  NULL,								// program instance handle
							  NULL);							// creation parameters

	// Shows the main window
	ShowWindow(hwnd, iCmdShow); // set window to be drawn
	UpdateWindow(hwnd); // force an update so window is drawn

	// Shows 1st child window
	ShowWindow(hwndChild1, iCmdShow); // set window to be drawn
	UpdateWindow(hwndChild1); // force an update so window is drawn

	// Shows 2nd child window
	ShowWindow(hwndChild2, iCmdShow); // set window to be drawn
	UpdateWindow(hwndChild2); // force an update so window is drawn

	SetFocus(hwnd);	// sets the focus back to the main window

	// message loop
	while (GetMessage(&msg, NULL, 0, 0)) {	// get message form queue
		TranslateMessage(&msg);				// for keystroke translation
		DispatchMessage(&msg);				// pass message back to the windows for processing
											/* note that this is to put windows O/S in control,
											   rather than this application */
	}
	return msg.wParam;
}


/** 
 * Purpose: To handle windows messages for specific cases including when
 *			the windows is first created, refreshing (painting), and closing
**/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;		// handle for the display DC to be used for painting
	PAINTSTRUCT ps;	// used to paint the client area of a window owned by the application
	RECT rect;		// defines the coordinates of the upper-left and lower-right corners of a rectangle
	
	// handle specific messages from the message queue
	switch (message) {
		case WM_CREATE: // additional things to do when the window is created
			// PlaySound requires WINMM.LIB
			PlaySound(TEXT("C:\Program Files\Messenger\newemail.wav"), NULL, SND_FILENAME | SND_ASYNC);
			return 0;

		case WM_PAINT: // what to do when a paint message occurs
			hdc = BeginPaint(hwnd, &ps); // creates a handle for the painting area

			// obtains the dimensions of the window's client area
			GetClientRect(hwnd, &rect); // define drawing area for clipping

			// displays a text string
			DrawText(hdc, TEXT("Hello, this is the first window."), -1, &rect,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps); // release the device context, ends window painting
			return 0;

		case WM_DESTROY: // how to handle a destroy (close the window) message
			PostQuitMessage(0); // inserts a "quit" message into the message queue
			return 0;
	}
	// return the message to windows for further processing
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK Child1WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;		// handle for the display DC to be used for painting
	PAINTSTRUCT ps;	// used to paint the client area of a window owned by the application
	RECT rect;		// defines the coordinates of the upper-left and lower-right corners of a rectangle
	
	// handle specific messages from the message queue
	switch (message) {
		case WM_CREATE: // additional things to do when the window is created
			return 0;

		case WM_PAINT: // what to do when a paint message occurs
			hdc = BeginPaint(hwnd, &ps); // creates a handle for the painting area

			// obtains the dimensions of the window's client area
			GetClientRect(hwnd, &rect); // define drawing area for clipping

			// displays a text string
			DrawText(hdc, TEXT("Hello, this is the second window."), -1, &rect,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps); // release the device context, ends window painting
			return 0;

		case WM_DESTROY: // how to handle a destroy (close the window) message
			PostQuitMessage(0); // inserts a "quit" message into the message queue
			return 0;
	}
	// return the message to windows for further processing
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK Child2WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hdc;		// handle for the display DC to be used for painting
	PAINTSTRUCT ps;	// used to paint the client area of a window owned by the application
	RECT rect;		// defines the coordinates of the upper-left and lower-right corners of a rectangle
	
	// handle specific messages from the message queue
	switch (message) {
		case WM_CREATE: // additional things to do when the window is created
			return 0;

		case WM_PAINT: // what to do when a paint message occurs
			hdc = BeginPaint(hwnd, &ps); // creates a handle for the painting area

			// obtains the dimensions of the window's client area
			GetClientRect(hwnd, &rect); // define drawing area for clipping

			// displays a text string
			DrawText(hdc, TEXT("Hello, this is the third window."), -1, &rect,
				DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps); // release the device context, ends window painting
			return 0;

		case WM_DESTROY: // how to handle a destroy (close the window) message
			PostQuitMessage(0); // inserts a "quit" message into the message queue
			return 0;
	}
	// return the message to windows for further processing
	return DefWindowProc(hwnd, message, wParam, lParam);
}