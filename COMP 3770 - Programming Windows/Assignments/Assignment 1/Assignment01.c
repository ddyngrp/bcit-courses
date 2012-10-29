/************************************************************************
 *	Assignment01.c -- Program that allows user inut using 4 windows		*
 *					  Steffen L. Norgren								*
 *					  Septmber 21, 2008									*
 *					  A00683006 - Set F									*
 ************************************************************************/

#include <windows.h> // header file for the C programming language. It contains all function
					 // declarations in the API, all common macros and all the data types.

#define BUFFER(x,y) *(wInfo->pBuffer + y * wInfo->cxBuffer + x) // a macro to simplify dealing with a character buffer
#define X_SIZE 496	// default horizontal size for a window
#define Y_SIZE 395	// default vertical size for a window

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Default constructor for the main window

typedef struct _wndInfo {	// struct for holding window-specific data
	int	cxClient, cyClient,	// client window size in pixels
		cxBuffer, cyBuffer,	// size of the character buffer in characters
		xCaret, yCaret;		// x & y position of the caret, in characters
	TCHAR *	pBuffer;		// initialize the character buffer
} wndInfo, *PWndInfo;

/*
	Purpose: This is the user-provided entry point into our multi-window program.
			 This initializes our application, displays the main window, and enters a
			 message retrieval-and-dispatch loop that is the top level control structure
			 for our program.
	Parameters: hInstance - Handle to the current instance of the application
				hPrevInstance - Handle to the previous instance of the application.
				szCmdLine - Pointer to a null-terminated string specifying the command-line
							for the application, excluding the program name.
				iCmdShow - Specifies how the window is to be shown.
	Side Effects: None
	Return Value: If the function succeeds, terminating with a WM_QUIT message, it should return
				  the exit value contained in that message's wParam.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
	TCHAR		szAppName[] = TEXT("Assignment #1");	// set the name of the application
	HWND		hwnd;									// holds handle to the main window
	HWND		hwndChild[3];							// create handles for 3 child windows
	MSG			msg;									// holds any message retrieved from the message queue
	WNDCLASS	wndclass;								// wnd class for thegistration
	
	wndclass.style			= CS_HREDRAW | CS_VREDRAW;				// redraw on refresh for horizontal/verticle
	wndclass.lpfnWndProc	= WndProc;								// points to the window procedure that processes messages for the windows in the class.
	wndclass.cbClsExtra		= 0;									// amount of extra memory, in bytes, reserved for the class.
	wndclass.cbWndExtra		= sizeof(PWndInfo);						// amount of extra memory, in bytes, reserved for each window in the class.
	wndclass.hInstance		= hInstance;							// application instance handle
	wndclass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);		// Set the icon for the application
	wndclass.hCursor		= LoadCursor(NULL, IDC_ARROW);			// Set the cursor for the application
	wndclass.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);	// color  used to paint the client area of the window
	wndclass.lpszMenuName	= NULL;									// default menu for windows in the class that do not explicitly define menus.
	wndclass.lpszClassName	= szAppName;							// Identifies the name of the class/application

	// register wndclass to OS so appropriate window messages are sent to the application.
	if (!RegisterClass(&wndclass)) {
		// Display an error if minimum OS requirements are not met
		MessageBox(NULL, TEXT("This program requires Windows NT or higher."), szAppName, MB_ICONERROR);
		return 0;
	}

	// main window parameters
	hwnd = CreateWindow(szAppName,				// window class name
						TEXT("Window #1"),		// window caption
						WS_OVERLAPPEDWINDOW,	// window style
						0,0,X_SIZE,Y_SIZE,		// Window size/position (x,y position, x, y size)
						NULL,					// parent window handle
						NULL,					// window menu handle
						hInstance,				// program instance handle
						NULL);					// creation parameters

	// first chile window parameters
	hwndChild[0] = CreateWindow(szAppName,				// window class name
								TEXT("Window #2"),		// window caption
								WS_OVERLAPPEDWINDOW,	// window style
								X_SIZE,0,X_SIZE,Y_SIZE,	// Window size/position (x,y position, x, y size)
								hwnd,					// parent window handle
								NULL,					// window menu handle
								hInstance,				// program instance handle
								NULL);					// creation parameters

	// first chile window parameters
	hwndChild[1] = CreateWindow(szAppName,				// window class name
								TEXT("Window #3"),		// window caption
								WS_OVERLAPPEDWINDOW,	// window style
								0,Y_SIZE,X_SIZE,Y_SIZE,	// Window size/position (x,y position, x, y size)
								hwnd,					// parent window handle
								NULL,					// window menu handle
								hInstance,				// program instance handle
								NULL);					// creation parameters

	// first chile window parameters
	hwndChild[2] = CreateWindow(szAppName,					// window class name
								TEXT("Window #4"),			// window caption
								WS_OVERLAPPEDWINDOW,		// window style
								X_SIZE,Y_SIZE,X_SIZE,Y_SIZE,// Window size/position (x,y position, x, y size)
								hwnd,						// parent window handle
								NULL,						// window menu handle
								hInstance,					// program instance handle
								NULL);						// creation parameters

	// Shows the main window
	ShowWindow(hwnd, iCmdShow); // set window to be drawn
	UpdateWindow(hwnd); // force an update so window is drawn

	// Shows the first child window
	ShowWindow(hwndChild[0], iCmdShow); // set window to be drawn
	UpdateWindow(hwndChild[0]); // force an update so window is drawn

	// Shows the second child window
	ShowWindow(hwndChild[1], iCmdShow); // set window to be drawn
	UpdateWindow(hwndChild[1]); // force an update so window is drawn

	// Shows the third child window
	ShowWindow(hwndChild[2], iCmdShow); // set window to be drawn
	UpdateWindow(hwndChild[2]); // force an update so window is drawn

	SetFocus(hwnd); // set the focus back to the first window

	// message loop
	while (GetMessage(&msg, NULL, 0, 0)) {	// get message form queue
		TranslateMessage(&msg);				// for keystroke translation
		DispatchMessage(&msg);				// pass message back to the windows for processing
											/* note that this is to put windows O/S in control,
											   rather than this application */
	}
	return msg.wParam;	// exit parameter to be returned to the OS
}

/*
	Purpose: This creates our main program window, which will allow user keyboard input
			 to be entered and displayed within the window.
	Parameters: hwnd - This is the unique handle of the window.
				message - Whenever anything happens to the window, Windows will call this
						  function, telling the application what has happened.
	Side Effects: None
	Return Value: Returns a message to be placed into the message stack.
 */
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static DWORD	dwCharSet = DEFAULT_CHARSET;// sets the character set to windows default
	static int		cxChar, cyChar;				// size of each characer in pixels
	int				x, y, i;					// initialize variables for the various for loops
	HDC				hdc;						// handle for the display DC to be used for painting
	PAINTSTRUCT		ps;							// device context for handling painting to the window
	TEXTMETRIC		tm;							// holds information about a physical font

	wndInfo *wInfo = GetWindowLongPtr(hwnd, 0);	// grab the pointer to the data structure from the window's memory

	// handle specific messages from the message queue
	switch (message) {
		case WM_INPUTLANGCHANGE:	// what to do if the input language has changed
			dwCharSet = wParam;		// set the character set to windows default
			return 0;

		case WM_CREATE:	// additional things to do when the window is created
			hdc		= GetDC(hwnd);				// gets the display Device Context for the current window
			wInfo	= malloc(sizeof(wndInfo));	// allocate memory for the data struct
			
			wInfo->pBuffer = NULL;						// make sure the buffer is set to null
			SetWindowLongPtr(hwnd, 0, (LONG_PTR)wInfo);	// add wInfo pointer to window memory slot

			// selects a font object into the current device context
			SelectObject(hdc, CreateFont(0,				// font height
										 0,				// font width
										 0,				// font angle of escapement
										 0,				// font base-line orientation angle
										 0,				// font weight
										 0,				// italic attribute option
										 0,				// underline attribute option
										 0,				// strikeout attribute option
										 dwCharSet,		// character set identifier
										 0,				// output precision
										 0,				// clipping precision
										 0,				// output quality
										 FIXED_PITCH,	// pitch and family
										 NULL));		// typeface name
														/* Note: for any value set to 0, it uses the default value */

			GetTextMetrics(hdc, &tm);	// retrieve the font information for the current device context
			cxChar = tm.tmAveCharWidth;	// sets the character width for the current font, in pixels
			cyChar = tm.tmHeight;		// sets the character height for the current font, in pixels

			DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));	// deletes the handle for the font object
			ReleaseDC(hwnd, hdc);											// release this window's device context
			return 0;

		case WM_SIZE: // what happens when the window is resized
			if (message == WM_SIZE) {		// obtain the window size in pixels
				wInfo->cxClient = LOWORD(lParam);	// x size in pixels
				wInfo->cyClient = HIWORD(lParam);	// y size in pixels
			}

			// calculate window size in characters
			wInfo->cxBuffer = max(1, wInfo->cxClient / cxChar);	// how many characters can fit in the x axis
			wInfo->cyBuffer = max(1, wInfo->cyClient / cyChar);	// how many characters can fit in the y axis

			if (wInfo->pBuffer != NULL) {	// check to see if the character buffer has data
				free(wInfo->pBuffer);		// free the memory allocated to the character buffer
			}

			// allocate memory for the character buffer
			wInfo->pBuffer = (TCHAR *) malloc(wInfo->cxBuffer * wInfo->cyBuffer * sizeof(TCHAR));

			ClearBuffer(hwnd); // fills the buffer with spaces

			wInfo->xCaret = 0;	// set the caret's position to the beginning of the line
			wInfo->yCaret = 0;	// set the caret's position to the top of the page

			if (hwnd == GetFocus()) { // check to see if the window has focus
				SetCaretPos(wInfo->xCaret * cyChar, wInfo->yCaret * cyChar);	// set the caret's position within the window
			}

			InvalidateRect(hwnd, NULL, TRUE);	// force a redraw of the current window
			return 0;

		case WM_SETFOCUS:	// what happens when the window gains focus
			CreateCaret(hwnd, NULL, cxChar, cyChar);					// create a caret for the current window
			SetCaretPos(wInfo->xCaret * cxChar, wInfo->yCaret * cyChar);// set the caret's position within the window
			ShowCaret(hwnd);											// make the caret visible
			return 0;

		case WM_KILLFOCUS:	// what happens when the window loses focus
			HideCaret(hwnd);// make the caret invisible
			DestroyCaret();	// remove the caret from the current DC
			return 0;

		case WM_KEYDOWN:	// what happens when a key is depressed
			switch (wParam) { // switch through to see what type of key is being pressed
				case VK_HOME:	// case for when the HOME key is pressed
					wInfo->xCaret = 0;	// the caret is moved to the beginning of the line
					break;

				case VK_END:	// case for when the End key is pressed
					wInfo->xCaret = wInfo->cxBuffer - 1;	// the caret is moved to the end of the line
					break;

				case VK_PRIOR:	// case for when the PageUp key is pressed
					wInfo->yCaret = 0;	// set the caret's position to the first line
					break;

				case VK_NEXT:	// case for when the PageDown key is pressed
					wInfo->yCaret = wInfo->cyBuffer - 1;	// set the caret's position to the last line
					break;

				case VK_LEFT:	// case for when the left arrow is pressed
					wInfo->xCaret = max(wInfo->xCaret - 1, 0);	// move the caret one position to the left
					break;

				case VK_RIGHT:	// case for when the right arrow is pressed
					wInfo->xCaret = min(wInfo->xCaret + 1, wInfo->cxBuffer - 1);	// move the caret one position to the right
					break;

				case VK_UP:		// case for when the up arrow is pressed
					wInfo->yCaret = max(wInfo->yCaret - 1, 0);	// move the caret one position up
					break;

				case VK_DOWN:	// case for when the down arrow is pressed
					wInfo->yCaret = min(wInfo->yCaret + 1, wInfo->cyBuffer - 1);	// move the caret one position down
					break;

				case VK_DELETE:	// case for when the delete key is pressed
					for (x = wInfo->xCaret; x < wInfo->cxBuffer - 1; x++) {	// cycle through the buffer for the current line,
																			// starting at the caret's position
						BUFFER(x, wInfo->yCaret) = BUFFER(x + 1, wInfo->yCaret);	// replace current character with next character
					}

					BUFFER(wInfo->cxBuffer - 1, wInfo->yCaret) = ' ';	// fill the last character on the line with a space

					HideCaret(hwnd);	// make the caret invisible
					hdc = GetDC(hwnd);	// retrieve the Device Context for the current window

					// selects a font object into the current device context
					SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
						dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

					// reoutput the current line of text
					TextOut (hdc, wInfo->xCaret * cxChar, wInfo->yCaret * cyChar,
							 & BUFFER(wInfo->xCaret, wInfo->yCaret),
							 wInfo->cxBuffer - wInfo->xCaret);

					DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT))); // deletes the handle for the font object
					ReleaseDC(hwnd, hdc);	// release the device context
					ShowCaret(hwnd);		// make the caret visible again
					break;
			}

			SetCaretPos(wInfo->xCaret * cxChar, wInfo->yCaret * cyChar); // set the caret's position within the current window
			return 0;

		case WM_CHAR:	// case for dealing with character input
			for (i = 0; i < (int)LOWORD(lParam); i++) {	// continue looping until input has ceased
				switch (wParam) {	// switch through the cases for the current character input
					case '\b':	// case for when the backspace key is pressed
						if (wInfo->xCaret > 0) {	// check to see if the caret is not at the beginning of the line
							wInfo->xCaret--;		// move the caret one position to the left
							SendMessage(hwnd, WM_KEYDOWN, VK_DELETE, 1);	// send message to the stack to call the case for VK_DELETE
						}
						break;

					case '\t':	// case for when the tab key is pressed
						do {	// enter a loop to convert a tab into the appropriate number of spaces
							SendMessage(hwnd, WM_CHAR, ' ', 1);	// send message to the stack to call the case for WM_CHAR
						} while (wInfo->xCaret % 8 != 0);	// continue the loop until 8 spaces have been input
						break;

					case '\n':	// case for a line feed
						if (++wInfo->yCaret == wInfo->cyBuffer) {	// check to see if a new line would be the bottom of the window
							wInfo->yCaret -= 1;	// set the yCaret's position back to the bottom of the window
							MoveBuffer(hwnd); // move the entire window contents up one line
						}

						InvalidateRect(hwnd, NULL, FALSE);	// invalidate the drawing area to force a redraw
						break;

					case '\r':	// case for carriage return
						wInfo->xCaret = 0;	// set the xCaret to the beginning of the line

						if (++wInfo->yCaret == wInfo->cyBuffer) {	// check to see if a new line would be the bottom of the window
							wInfo->yCaret -= 1;			// set the yCaret's position back to the bottom of the window
							MoveBuffer(hwnd); // move the entire window contents up one line
						}

						InvalidateRect(hwnd, NULL, FALSE);	// invalidate the drawing area to force a redraw
						break;

					case '\x1B':	// case for when the Escape key is pressed
						ClearBuffer(hwnd);	// clear the buffer by filling it with spaces

						wInfo->xCaret = 0;	// set the caret's position to the beginning of the line
						wInfo->yCaret = 0; // set the caret's position to the top of the window

						InvalidateRect(hwnd, NULL, FALSE);	// invalidate the drawing area to force a redraw
						break;

					default:	// case for any other type of caracter input
						BUFFER(wInfo->xCaret, wInfo->yCaret) = (TCHAR)wParam;	// set the current buffer position to the input character

						HideCaret(hwnd);	// make the caret invisible
						hdc = GetDC(hwnd);	// retrieve the current window's device context

						// selects a font object into the current device context
						SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0, 0, 0,
									 dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

						// reoutput the current line of text
						TextOut(hdc, wInfo->xCaret * cxChar, wInfo->yCaret * cyChar,
								& BUFFER(wInfo->xCaret, wInfo->yCaret), 1);


						DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT))); // deletes the handle for the font object
						ReleaseDC(hwnd, hdc);	// release the device context
						ShowCaret(hwnd);		// make the caret visible again

						// what happens when the caret reaches bottom right of the window
						if (++wInfo->xCaret == wInfo->cxBuffer) {		// check to see if the caret's x position is at the end of the line
							wInfo->xCaret = 0;					// set the caret's position to the beginning of the line
							if (++wInfo->yCaret == wInfo->cyBuffer) {	// check to see if the caret's y position is at the end of the window
								wInfo->yCaret -= 1;			// set the yCaret's position back to the bottom of the window
								SendMessage(hwnd, WM_CHAR, '\r', 1);	// send a message to the stack to create a carriage return
							}
						}
						break;
				}
			}

			SetCaretPos(wInfo->xCaret * cxChar, wInfo->yCaret * cyChar); // set the caret's position within the current window
			return 0;

		case WM_PAINT: // what to do when the window contents are invalidated
			hdc = GetDC(hwnd);			// get the window's device context
			hdc = BeginPaint(hwnd, &ps);// clears the window and fills in the fields for the ps struct

			// selects a font object into the current device context
			SelectObject(hdc, CreateFont (0, 0, 0, 0, 0, 0, 0, 0,
						 dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

			for (y = 0; y < wInfo->cyBuffer; y++) {	// cycle through the lines in the buffer
				TextOut(hdc, 0, y * cyChar, & BUFFER(0,y), wInfo->cxBuffer);	// reoutput the text for the selected line in the buffer
			}

			DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));	// deletes the handle for the font object
			EndPaint(hwnd, &ps);											// releases the device context and validates the window
			return 0;

		case WM_DESTROY: // how to handle a destroy (close the window) message
			PostQuitMessage(0); // inserts a "quit" message into the message queue
			return 0;
	}
	// return the message to windows for further processing
	return DefWindowProc(hwnd, message, wParam, lParam);
}

/*
	Purpose: To 'clear' the contents of the character buffer by filling it with spaces
	Parameters: pBuffer - the character buffer we're working with
				cxBuffer - size of the horizontal character buffer in characters
				cyBuffer - size of the vertical character buffer in characters
	Side Effects: None
	Return Value: An integer value representing whether the function succeeded or failed
 */
int ClearBuffer(HWND hwnd) {
	int x, y;	// initialize variables for the various for loops
	wndInfo *wInfo = GetWindowLongPtr(hwnd, 0);

	for (y = 0; y < wInfo->cyBuffer; y++) {	// cycles through each line of the buffer
		for (x = 0; x < wInfo->cxBuffer; x++) {// cycles through each character on a line of the buffer
			BUFFER(x, y) = ' ';			// replaces the current character on the current line with a space
		}
	}
	return 0;
}

/*
	Purpose: To shift the contents of the buffer up one line
	Parameters: pBuffer - the character buffer we're working with
				cxBuffer - size of the horizontal character buffer in characters
				cyBuffer - size of the vertical character buffer in characters
	Side Effects: None
	Return Value: An integer value representing whether the function succeeded or failed
 */
int MoveBuffer(HWND hwnd) {
	int	x, y, i;	// initialize variables for the various for loops
	wndInfo *wInfo = GetWindowLongPtr(hwnd, 0);

	for (y = 0; y < wInfo->cyBuffer; y++) {		// cycle through all of the lines in the buffer
		for (x = 0; x < wInfo->cxBuffer; x++) {	// cycles through all the characters in a line
			if (y + 1 != wInfo->cyBuffer) {		// only process the next line if it exists
				BUFFER(x,y) = BUFFER(x,(y+1));	// set the current line's contents to be the next line
			}
			else {	// if the next line is the end of the buffer
				BUFFER(x,y) = ' ';	// set the new end line to be blank
			}
		}
	}
	return 0;
}