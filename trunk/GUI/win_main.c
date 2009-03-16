/*---------------------------------------------------------------------------------------
--	SOURCE FILE:	winMain.c -   Program's main entry point.
--
--	PROGRAM:		music_streamer.exe
--
--	FUNCTIONS:		WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
--							LPSTR lpCmdLine, int nCmdShow)
--					VersionCheck()
--					InitApp(HINSTANCE hInst, int nCmdShow)
--
--
--	DATE:			March 16, 2009
--
--	REVISIONS:		
--
--	DESIGNERS:		Steffen L. Norgren
--
--	PROGRAMMER:		Steffen L. Norgren
--
--	NOTES:	Program's main entry point. This is where the application loads all
--			its necessary resources and sets up the initial parameters.
---------------------------------------------------------------------------------------*/

#include "win_main.h"
#include "resource.h"

// Private variables
TCHAR	szAppName[] = TEXT("Comm Audio - Music Streamer");


/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	WinMain
-- 
--	DATE:		March 16, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
--						 LPSTR lpCmdLine, int nCmdShow)
--					HINSTANCE hInstance:		this application's instance
--					HINSTANCE hPrevInstance:	previous instance of this application
--					LPSTR lpCmdLine:			command line parameters
--					int nCmdShow:				code for showing the window
-- 
--	RETURNS:	0: for failure to start the application
--				1: for success
-- 
--	NOTES:	Start application and process all window messages.
--
---------------------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	MSG msg;

	// Verify that the program can run on this version of windows
	if (!VersionCheck()) {
		MessageBox(NULL, (LPCSTR)"Program cannot run on this version of Windows.",
			NULL, MB_OK | MB_ICONSTOP);
		return 0;
	}

	// Attempt to initialize the application and create the main window and class
	if (!InitApp(hInstance, nCmdShow)) {
		MessageBox(NULL, (LPCSTR)"Program couldn't start! We don't know why, it just couldn't!",
			NULL, MB_OK | MB_ICONSTOP);
	}

	// Main message loop
	while (GetMessage(&msg, NULL, 0, 0)) {	// Get message from queue
		// Send message to accelerator to check if it is a keyboard command
		if (!TranslateAccelerator(ghWndMain, ghAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;	// Exit parameter to be returned to the OS
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	VersionCheck
-- 
--	DATE:		March 16, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	VersionCheck()
-- 
--	RETURNS:	TRUE:	this version of windows is sufficient
--				FALSE:	this version of windows does not meet the requirements
-- 
--	NOTES:	Verifies that this version of Windows will support running the application.
--
---------------------------------------------------------------------------------------*/
int VersionCheck() {
	OSVERSIONINFO	osv;		// Operating System Version Info

	osv.dwOSVersionInfoSize = sizeof(osv);
	if (!GetVersionEx(&osv)) {
		return FALSE;
	}

	if (osv.dwPlatformId == VER_PLATFORM_WIN32s) {
		return FALSE;
	}

	return TRUE;
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	InitApp
-- 
--	DATE:		March 16, 2009
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Steffen L. Norgren
-- 
--	PROGRAMMER:	Steffen L. Norgren
-- 
--	INTERFACE:	InitApp(HINSTANCE hInst, int nCmdShow)
					HINSTANCE hInst:	HINSTANCE for this application
					int nCmdShow:		Code for showing this window
-- 
--	RETURNS:	TRUE:	successful initialization of this application
--				FALSE:	failure to initialize application
-- 
--	NOTES:	Register window classes and create the main window
--
---------------------------------------------------------------------------------------*/
int InitApp(HINSTANCE hInst, int nCmdShow) {
	WNDCLASS	wc = {0};
	RECT		rect;
	POINT		ptWindow;

	// Setup the program's main window class
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc		= (WNDPROC)WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInst;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName		= MAKEINTRESOURCE(IDR_MENU);
	wc.lpszClassName	= szAppName;
	wc.hIcon			= LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON));

	// Register wndclass to OS so appropriate window messages are sent to the application.
	if (!RegisterClass(&wc)) {
		return FALSE;
	}
	
	// Get the size of our work area (anything not obscured by the taskbar
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
	ptWindow.x = (rect.right / 2) - (X_SIZE / 2);
	ptWindow.y = (rect.bottom / 2) - (Y_SIZE / 2);

	// Create the main window
	ghWndMain = CreateWindow(szAppName, szAppName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_BORDER,
		ptWindow.x, ptWindow.y,
		X_SIZE, Y_SIZE,
		NULL, NULL, hInst, NULL);

	// Show the main window
	ShowWindow(ghWndMain, nCmdShow);
	UpdateWindow(ghWndMain);

	ghInst = hInst;	// set the global instance for this program

	// set the global instance for the keyboard accelerator
	ghAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_ACCELERATOR));

	return TRUE;
}