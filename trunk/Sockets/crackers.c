#include "crackers.h"

/*------------------------------------------------------------------------
--		FUNCTION:		OnClose
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnClose(HWND hwnd)
--							HWND hwnd: Handle to the window to close
--
--		RETURNS:		void
--
--		NOTES:			Used to close a window.
------------------------------------------------------------------------*/
void OnClose(HWND hwnd)
{
	PostQuitMessage(0);
}

/*------------------------------------------------------------------------
--		FUNCTION:		OnCommand
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnCommand(HWND hwnd, int id, HWND hwndCtl,
--						UINT codeNotify)
--							HWND hwnd: Handle to the current window
--							int id: The message ID
--							HWND hwndCtl: Handle to the window control
--							UINT codeNotify: Notify code
--
--		RETURNS:		void
--
--		NOTES:			This function performs actions based on the
--						message ID.  Currently, only menu items are
--						processed here.
------------------------------------------------------------------------*/
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	int iRc;
	/* HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE); */

	switch(id)
	{
	case ID_FILE_CONNECT:
		if(ghSocket == INVALID_SOCKET)
		{
			MessageBox(NULL, "Invalid Socket!", "ERROR", MB_OK);
			break;
		}

		iRc = connect(ghSocket, (SOCKADDR *)&remote, sizeof(remote));

		if(iRc == INVALID_SOCKET)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
				MessageBox(NULL, "Unable to connect to server!", "ERROR", MB_OK);
		}
		break;

	case ID_FILE_DISCONNECT:
		sockClose(hwnd, ghSocket, 0);
		break;

	case ID_FILE_EXIT:
		PostMessage(hwnd, WM_CLOSE, 0, 0);
		break;

	case ID_MODE_CLIENT:
		DialogBox(ghInst, MAKEINTRESOURCE(IDD_CLIENT), hwnd, (DLGPROC)ClientProc);
		client(hwnd);
		break;

	case ID_MODE_SERVER:
		DialogBox(ghInst, MAKEINTRESOURCE(IDD_SERVER), hwnd, (DLGPROC)ServerProc);
		server(hwnd);
		break;

	case ID_VIEW_CONNECTEDCLIENTS:
		break;

	case ID_HELP_ABOUT:
		break;

	case ID_HELP_DOCUMENTATION:
		break;

	default:
		break;
	}
}

/*------------------------------------------------------------------------
--		FUNCTION:		OnCreate
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		int OnCreate(HWND hwnd,
--						LPCREATESTRUCT lpCreateStruct)
--							HWND hwnd: Handle to the window to close
--							LPCREATESTRUCT lpCreateStruct: Initialization
--							parameters for the window
--
--		RETURNS:		TRUE if the window was created successfully,
--						FALSE otherwise
--
--		NOTES:			When called, sets up the window.
------------------------------------------------------------------------*/
int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	InitWindow(hwnd);
	memset((char *)&ci, 0, sizeof(connectInfo));
	ci.port	= DEFAULT_PORT;

	ghMenu = GetMenu(hwnd);
	return TRUE;
}

/*------------------------------------------------------------------------
--		FUNCTION:		OnDestroy
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnDestroy(HWND hwnd)
--							HWND hwnd: Handle to the window to close
--
--		RETURNS:		void
--
--		NOTES:			Destroys the window, killing the program.
------------------------------------------------------------------------*/
void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

/*------------------------------------------------------------------------
--		FUNCTION:		OnPaint
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnPaint(HWND hwnd)
--							HWND hwnd: Handle to the window to paint
--
--		RETURNS:		void
--
--		NOTES:			Redraws the window.
------------------------------------------------------------------------*/
void OnPaint(HWND hwnd)
{
	HDC hdc;
	PAINTSTRUCT ps;

	hdc = BeginPaint(hwnd, &ps);
	EndPaint(hwnd, &ps);
}

/*------------------------------------------------------------------------
--		FUNCTION:		OnSize
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnSize(HWND hwnd, UINT state, int cx, int cy)
--							HWND hwnd: Handle to the window to paint
--							UINT state: State of the window
--							int cx: width of the client window
--							int cy: height of the client window
--
--		RETURNS:		void
--
--		NOTES:			Operations to perform when the window is resized.
------------------------------------------------------------------------*/
void OnSize(HWND hwnd, UINT state, int cx, int cy)
{
	// Main window size has changed, need to resize child windows
	WORD wTop = 0;
	WORD wHeight = cx;
	WORD wWidth = cy;
	RECT wRect;

	GetWindowRect(ghWndMain, &wRect);

	// Put Window in the middle
	MoveWindow(ghDlgMain, 0, wTop, wWidth, wHeight, TRUE);
}

/*------------------------------------------------------------------------
--		FUNCTION:		OnSocket
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnSocket(HWND hwnd, WPARAM wParam,
--						LPARAM lParam)
--							HWND hwnd: Handle to the window to paint
--							WPARAM wParam: Socket descriptor
--							LPARAM lParam: Operation flags
--
--		RETURNS:		void
--
--		NOTES:			Performs flag specific socket operations.
------------------------------------------------------------------------*/
void OnSocket(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
		sockAccept(hwnd, wParam, lParam);
		break;

	case FD_CLOSE:
		sockClose(hwnd, wParam, lParam);
		break;
	
	case FD_CONNECT:
		sockConnect(hwnd, wParam, lParam);
		break;

	case FD_READ:
		sockRead(hwnd, wParam, lParam);
		break;

	case FD_WRITE:
		sockWrite(hwnd, wParam, lParam);
		break;

	default:
		break;
	}
}
