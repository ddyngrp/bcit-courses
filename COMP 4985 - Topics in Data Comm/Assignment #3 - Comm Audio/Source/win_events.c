#include "win_events.h"

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
	TCHAR fileName[FILE_BUFF_SIZE], pathName[FILE_BUFF_SIZE];
	char ipAddr[TEMP_BUFF_SIZE] = "IP: ";

	switch(id)
	{
	case ID_FILE_CONNECT:
		if(ci.behaviour == SERVER)
		{
			setup_server(hwnd, SOCK_STREAM);
			setup_server(hwnd, SOCK_DGRAM);

			if (ci.request == MULTI_STREAM) {
				sendFileList(0);
			}

			if(ci.tcpSocket == INVALID_SOCKET)
			{
				MessageBox(ghWndMain, (LPCSTR)"Invalid Socket!",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
			}
		}
		else if(ci.behaviour == CLIENT) 
		{
			setup_client(hwnd, SOCK_STREAM);
			setup_client(hwnd, SOCK_DGRAM);

			if (ci.request == MULTI_STREAM) {
				if(streamThread != NULL) {
					TerminateThread(streamThread,0);
				}

				Sleep(100);

				if((streamThread = CreateThread(NULL, 0, 
					(LPTHREAD_START_ROUTINE)receiveStream, (LPVOID)ci.udpSocket, 0, 0)) == NULL)
				{
					MessageBox(NULL,"Thread creation failed",NULL,MB_OK);
					ExitProcess(1);
				}
			}
			else {
				connect(ci.tcpSocket, (SOCKADDR *)&remote, sizeof(remote));

				if(ci.tcpSocket == INVALID_SOCKET)
				{
					if(WSAGetLastError() != WSAEWOULDBLOCK) {
						MessageBox(ghWndMain, (LPCSTR)"Unable to connect to server!",
							(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
					}
				}
			}
		}

		connectActions();
		initButtons();
		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[0],(LPARAM)"Status: Connected");
		break;

	case ID_FILE_DISCONNECT:
		/* Stop running threads */
		if(streamThread != NULL)
			TerminateThread(streamThread,0);

		Sleep(200);

		/* Close open sockets */
		sockClose(hwnd, ci.tcpSocket, 0);
		sockClose(hwnd, ci.udpSocket, 0);

		ci.behaviour = 0;
		ci.request = 0;

		disconnectActions();
		setActions();
		initButtons();
		ClearList();

		SendMessage(ghStatus, SB_SETTEXT, (WPARAM)parts[0], (LPARAM)"Status: Disconnected");
		SendMessage(ghStatus, SB_SETTEXT, (WPARAM)parts[1], (LPARAM)"Mode: ");
		SendMessage(ghStatus, SB_SETTEXT, (WPARAM)parts[2], (LPARAM)"IP: ");
		break;

	case ID_FILE_EXIT:
		PostMessage(hwnd, WM_CLOSE, 0, 0);
		break;

	case ID_MODE_CLIENT:
		DialogBox(ghInst, MAKEINTRESOURCE(IDD_CLIENT), hwnd, (DLGPROC)ClientProc);
		ci.behaviour = CLIENT;

		checkMenuItem(0);
		setActions();

		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[1],(LPARAM)"Mode: Client");
		strcat_s(ipAddr, sizeof(ipAddr), ci.ip);
		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[2],(LPARAM)ipAddr);
		break;

	case ID_MODE_SERVER:
		DialogBox(ghInst, MAKEINTRESOURCE(IDD_SERVER), hwnd, (DLGPROC)ServerProc);
		ci.behaviour = SERVER;

		checkMenuItem(0);
		setActions();

		SendMessage(ghStatus,SB_SETTEXT,(WPARAM)parts[1],(LPARAM)"Mode: Server");
		break;

	/* Note: These menu item checks can be put into a loop within a function */
	case ID_SINGLE_DL:
		checkMenuItem(ID_SINGLE_DL);
		ci.request = SINGLE_DL;
		break;
	case ID_SINGLE_UP:
		checkMenuItem(ID_SINGLE_UP);
		ci.request = SINGLE_UP;
		break;
	case ID_SINGLE_STREAM:
		checkMenuItem(ID_SINGLE_STREAM);
		ci.request = SINGLE_STREAM;
		break;
	case ID_MULTI_STREAM:
		checkMenuItem(ID_MULTI_STREAM);
		ci.request = MULTI_STREAM;
		break;
	
	case ID_2WAY_MICROPHONE:
		checkMenuItem(ID_2WAY_MICROPHONE);
		ci.request = MICROPHONE;
		break;

	case ID_FILE_LOCAL:
		localSong_Stop();
		EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), TRUE);
		SetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), (LPCSTR)"Pause");
        busyFlag = LOCALPLAY;
        memset(fileName, 0, FILE_BUFF_SIZE);
	    memset(pathName, 0, FILE_BUFF_SIZE);
        browseFiles(hwnd, fileName, pathName);
		if(localSong_Init(hwnd, fileName) == FALSE) {
            busyFlag = 0; /* if we failed to open file */
		}
        break;

	case ID_HELP_ABOUT:
		MessageBox(ghWndMain, (LPCSTR)"COMP 4985 - Assignment #3, Comm Audio\n\n"
			"Programmers:\n"
			"\tJaymz Boilard\n"
			"\tJerrod Hudson\n"
			"\tBrendan Neva\n"
			"\tSteffen L. Norgren\n",
			(LPCSTR)"About CommAudio", MB_OK | MB_ICONINFORMATION);
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
	initMenu();

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
		sockClose(hwnd, wParam, -1);
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