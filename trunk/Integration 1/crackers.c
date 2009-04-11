#include "crackers.h"
#include "win_main.h"

/*------------------------------------------------------------------------
--		FUNCTION:		OnClose
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
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
--		REVISIONS:		March 26 - Added code to make the menu items properly
--								   gray, ungray, and add check marks as needed.
--						March 29 - Moved the code for ID_FILE_LOCAL from
--								   Menu_Dispatch to here.
--						April 4  - 
--
--		DESIGNER:		Jerrod Hudson
--		PROGRAMMER:		Jerrod Hudson & Jaymz Boilard
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
	TCHAR fileName[FILEBUFSIZE], pathName[FILEBUFSIZE];
	int iRc;
	char ipAddr[EDITSIZE] = "IP: ";

	switch(id)
	{
	case ID_FILE_CONNECT:
		if(ci.behaviour == SERVER)
		{
			setup_server(hwnd, SOCK_STREAM);
			setup_server(hwnd, SOCK_DGRAM);
			SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[0],(LPARAM)"Status: Connected");
			SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[2],(LPARAM)"IP: 127.0.0.1");
			break;
		}
		else if(ci.behaviour == CLIENT) 
		{
			setup_client(hwnd, SOCK_STREAM);
			setup_client(hwnd, SOCK_DGRAM);
		}

		if(ci.tcpSocket == INVALID_SOCKET)
		{
			MessageBox(NULL, "Invalid Socket!", "ERROR", MB_OK);
			break;
		}

		iRc = connect(ci.tcpSocket, (SOCKADDR *)&remote, sizeof(remote));

		if(iRc == INVALID_SOCKET)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
				MessageBox(NULL, "Unable to connect to server!", "ERROR", MB_OK);
		}
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[0],(LPARAM)"Status: Connected");
		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[2],(LPARAM)ipAddr);
		break;

	case ID_FILE_DISCONNECT:
		sockClose(hwnd, ci.tcpSocket, 0);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);
		CheckMenuItem(ghMenu, ID_MODE_SERVER, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MODE_CLIENT, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_DL, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_UP, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_STREAM, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MULTI_STREAM, MF_UNCHECKED);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);
		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[0],(LPARAM)"Status: Disconnected");
		break;

	case ID_FILE_EXIT:
		PostMessage(hwnd, WM_CLOSE, 0, 0);
		break;

	case ID_MODE_CLIENT:
		DialogBox(ghInst, MAKEINTRESOURCE(IDD_CLIENT), hwnd, (DLGPROC)ClientProc);
		ci.behaviour = CLIENT;
		CheckMenuItem(ghMenu, ID_MODE_CLIENT, MF_CHECKED);
		CheckMenuItem(ghMenu, ID_MODE_SERVER, MF_UNCHECKED);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_ENABLED);

		/* Let client specify the request type */
		EnableMenuItem(ghMenu, ID_SINGLE_DL, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_SINGLE_UP, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_SINGLE_STREAM, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_MULTI_STREAM, MF_ENABLED);

		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[1],(LPARAM)"Mode: Client");
		strcat(ipAddr, ci.ip);
		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[2],(LPARAM)ipAddr);
		break;

	case ID_MODE_SERVER:
		DialogBox(ghInst, MAKEINTRESOURCE(IDD_SERVER), hwnd, (DLGPROC)ServerProc);
		ci.behaviour = SERVER;

		CheckMenuItem(ghMenu, ID_MODE_CLIENT, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MODE_SERVER, MF_CHECKED);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_ENABLED);

		/* Don't want to know request type if we're server, the client has to specify */
		EnableMenuItem(ghMenu, ID_SINGLE_DL, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_SINGLE_UP, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_SINGLE_STREAM, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_MULTI_STREAM, MF_GRAYED);
		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[1],(LPARAM)"Mode: Server");
		ci.request = 0;
		break;

	/* Note: These menu item checks can be put into a loop within a function */
	case ID_SINGLE_DL:
		CheckMenuItem(ghMenu, ID_SINGLE_DL, MF_CHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_UP, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_STREAM, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MULTI_STREAM, MF_UNCHECKED);
		ci.request = SINGLE_DL;
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);
		break;
	case ID_SINGLE_UP:
		CheckMenuItem(ghMenu, ID_SINGLE_DL, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_UP, MF_CHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_STREAM, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MULTI_STREAM, MF_UNCHECKED);
		ci.request = SINGLE_UP;
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);
		break;
	case ID_SINGLE_STREAM:
		CheckMenuItem(ghMenu, ID_SINGLE_DL, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_UP, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_STREAM, MF_CHECKED);
		CheckMenuItem(ghMenu, ID_MULTI_STREAM, MF_UNCHECKED);
		ci.request = SINGLE_STREAM;
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);
		break;
	case ID_MULTI_STREAM:
		CheckMenuItem(ghMenu, ID_SINGLE_DL, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_UP, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_SINGLE_STREAM, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MULTI_STREAM, MF_CHECKED);
		ci.request = MULTI_STREAM;
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);
		break;

	case ID_FILE_LOCAL:
        if(busyFlag > 0) //we're already busy
            break;
		EnableMenuItem(ghMenu, ID_FILE_LOCAL, MF_GRAYED);
        busyFlag = LOCALPLAY;
        memset(fileName, 0, FILEBUFSIZE);
	    memset(pathName, 0, FILEBUFSIZE);
        browseFiles(hwnd, fileName, pathName);
        if(localSong_Init(hwnd, fileName) == FALSE)
            busyFlag = 0; //if we failed to open file
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
	fileInit(hwnd); //set up file browsing
	busyFlag = 0;
	memset((char *)&ci, 0, sizeof(connectInfo));
	ci.tcp_port	= TCP_PORT;
	ci.udp_port = UDP_PORT;

	ghMenu = GetMenu(hwnd);

	/* We can't connect or disconnect until connection settings chosen */
	EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);
	/* Don't want to know request type if we're server, the client has to specify */
	EnableMenuItem(ghMenu, ID_SINGLE_DL, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_SINGLE_UP, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_SINGLE_STREAM, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_MULTI_STREAM, MF_GRAYED);

	/* Create status bar & initialize fields */
	ghStatus = CreateStatusWindow(WS_CHILD|WS_VISIBLE, "Status: Disconnected", hwnd, STATUS_BAR);
	SendMessage(ghStatus,SB_SETPARTS,(WPARAM)nParts,(LPARAM)&width);
	SendMessage(ghStatus, SB_SETTEXT,(WPARAM)parts[1],(LPARAM)"Mode:");
	SendMessage(ghStatus, SB_SETTEXT,(WPARAM)parts[2],(LPARAM)"IP:");
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
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnSize(HWND hwnd, UINT state, int cy, int cx)
--							HWND hwnd: Handle to the window to paint
--							UINT state: State of the window
--							int cy: height of the client window
--							int cx: width of the client window
--
--		RETURNS:		void
--
--		NOTES:			Operations to perform when the window is resized.
------------------------------------------------------------------------*/
void OnSize(HWND hwnd, UINT state, int cy, int cx)
{
	/* Main window size has changed, need to resize child windows */
	WORD wTop = 0;
	WORD wHeight = cx;
	WORD wWidth = cy;
	RECT wRect;

	GetWindowRect(ghWndMain, &wRect);

	/* Put Window in the middle */
	MoveWindow(ghDlgMain, 0, wTop, wWidth, wHeight, TRUE);
}

/*------------------------------------------------------------------------
--		FUNCTION:		OnTCPSocket
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void OnTCPSocket(HWND hwnd, WPARAM wParam,
--						LPARAM lParam)
--						HWND hwnd: Handle to the window to paint
--						WPARAM wParam: Socket descriptor
--						LPARAM lParam: Operation flags
--
--		RETURNS:		void
--
--		NOTES:			Performs flag specific socket operations.
------------------------------------------------------------------------*/
void OnTCPSocket(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
		tcp_sockAccept(hwnd, wParam, lParam);
		break;

	case FD_CLOSE:
		sockClose(hwnd, wParam, lParam);
		break;
	
	case FD_CONNECT:
		tcp_sockConnect(hwnd, wParam, lParam);
		break;

	case FD_READ:
		tcp_sockRead(hwnd, wParam, lParam);
		break;

	case FD_WRITE:
		tcp_sockWrite(hwnd, wParam, lParam);
		break;

	default:
		break;
	}
}