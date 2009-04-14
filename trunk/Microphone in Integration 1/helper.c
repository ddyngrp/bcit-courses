/*-----------------------------------------------------------------------------
--	SOURCE FILE:	helper.c
--
--	PROGRAM:		CommAudio.exe
--
--	FUNCTIONS:		sendFileList(WPARAM wParam)
--					receiveFileList(WPARAM wParam, char buf[])
--					AppendList(char *str)
--					ClearList()
--					GetSelList(char * selItem)
--					browseFiles(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
--					fileInit(HWND hwnd)
--					initButtons()
--					initMenu()
--					connectActions()
--					disconnectActions()
--					setActions()
--					checkMenuItem(int item)
--					
--
--	DATE:			2009-03-30
--
--	DESIGNERS:		Jaymz Boilard
--	PROGRAMMERS:	Jaymz Boilard, Steffen L. Norgren
--
--	NOTES: Contains GUI helper functions that aid in managing buttons, menus,
--	and listboxes.
-----------------------------------------------------------------------------*/

#include "resource.h"
#include "win_main.h"
static OPENFILENAME ofn;

/*-----------------------------------------------------------------------------
--	FUNCTION:		sendFileList
--
--	DATE:			2009-04-10
--
--	REVISIONS:		
--
--	DESIGNER(S):	Jaymz Boilard
--	PROGRAMMER(S):	Jaymz Boilard
--
--	INTERFACE:		sendFileList(WPARAM wParam)
--						WPARAM wParam: The operating socket
--
--	RETURNS:		void
--
--	NOTES: Called on a download or single stream request.  It gets all the song
--	names from the current directory of the executable file and puts
--	them into a buffer, delimiting each song name with a colon, and
--	sends it to the client.
-----------------------------------------------------------------------------*/
void sendFileList(WPARAM wParam)
{
	char buf[FILE_BUFF_SIZE];
	WIN32_FIND_DATA wfd;
	HANDLE FF;
	memset(buf, '\0', FILE_BUFF_SIZE);
	strcpy_s(buf, sizeof(buf), "FILES:");
	
	/* Server Stuff */
	if ((FF = FindFirstFile("*.wav",&wfd)) == INVALID_HANDLE_VALUE) 
	{
		MessageBox(ghWndMain, (LPCSTR)"Unable to find any .wav files in current directory.",
			(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
		return;
	}

	do
	{
		strcat_s(buf, sizeof(buf), wfd.cFileName);
		strcat_s(buf, sizeof(buf), ":");
	}
	while(FindNextFile(FF,&wfd));

	if (ci.request != MULTI_STREAM) {
		if(send(wParam, buf, strlen(buf), 0) == -1)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(NULL, TEXT("send() failed with error \n"), NULL, MB_OK);
				closesocket(wParam);
			}
		}
	}
	else { /* Populate locally if in multicast mode */
		receiveFileList(wParam, buf);
	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		receiveFileList
--
--	DATE:			2009-03-30
--
--	REVISIONS:		
--
--	DESIGNER(S):	Jaymz Boilard
--	PROGRAMMER(S):	Jaymz Boilard
--
--	INTERFACE:		receiveFileList(WPARAM wParam, char buf[])
--						WPARAM wParam: The operating socket
--						char buf[]: The buffer to hold the file list
--
--	RETURNS:		void
--
--	NOTES: Called on a download or single stream operation.  It receives a list
--	of file names as a string, with each song delimited by a colon. This will
--	cycle through the string, sending each song name to the list in the GUI.
-----------------------------------------------------------------------------*/
void receiveFileList(WPARAM wParam, char buf[])
{
	char * pch, * nextToken;

	/* Client Stuff */
	pch = strtok_s(buf, ":", &nextToken);
	pch = strtok_s(NULL, ":", &nextToken);
	while(pch != NULL)
	{
		AppendList(pch);
		pch = strtok_s(NULL, ":", &nextToken);
	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		AppendList
--
--	DATE:			2009-04-08
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		AppendList(char *str)
--						chart *str: the string to append to the list.
--
--	RETURNS:		void
--
--	NOTES: Appends the playlist with a new string.
-----------------------------------------------------------------------------*/
void AppendList(char *str)
{
	HWND list = GetDlgItem(ghDlgMain, IDC_LST_PLAY);

	ListBox_InsertString(list, -1, str);
	ListBox_SetCurSel(list, ListBox_GetCount(list) -1);

	SetFocus(list);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		ClearList
--
--	DATE:			2009-04-13
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		ClearList()
--
--	RETURNS:		void
--
--	NOTES: Clears the playlist.
-----------------------------------------------------------------------------*/
void ClearList() {
	HWND list = GetDlgItem(ghDlgMain, IDC_LST_PLAY);
	int count, i;

	count = ListBox_GetCount(list);

	for (i = 0; i < count; i++) {
		ListBox_DeleteString(list, 0);
	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		GetSelList
--
--	DATE:			2009-04-06
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		GetSelList(char * selItem)
--						char *selItem: The selected item in the list.
--
--	RETURNS:		void
--
--	NOTES: Modifies the string parameter passed to it by setting it to the
--	currently selected list item.
-----------------------------------------------------------------------------*/
void GetSelList(char * selItem) {
	HWND list = GetDlgItem(ghDlgMain, IDC_LST_PLAY);

	ListBox_GetText(list, ListBox_GetCurSel(list), selItem);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		browseFiles
--
--	DATE:			2009-04-10
--
--	REVISIONS:		
--
--	DESIGNER(S):	Jaymz Boilard
--	PROGRAMMER(S):	Jaymz Boilard
--
--	INTERFACE:		browseFiles(HWND hwnd, PTSTR pstrFileName,
--								PTSTR pstrTitleName)
--						HWND hwnd: Handle to the calling window.
--						PTSTR ptstrFileName: File name
--						PTSTR pstrTitleName: File's title
--
--	RETURNS:		TRUE:	Success
--					FALSE:	Failure
--
--	NOTES: Pops open a file browser to let a user choose a song.
-----------------------------------------------------------------------------*/
BOOL browseFiles(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = pstrFileName;
	ofn.lpstrFileTitle = pstrTitleName;
	ofn.Flags = OFN_HIDEREADONLY | OFN_CREATEPROMPT;
	return GetOpenFileName(&ofn);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		fileInit
--
--	DATE:			2009-04-10
--
--	REVISIONS:		
--
--	DESIGNER(S):	Jaymz Boilard
--	PROGRAMMER(S):	Jaymz Boilard
--
--	INTERFACE:		fileInit(HWND hwnd)
--						HWND hwnd: Handle to the calling window
--
--	RETURNS:		void
--
--	NOTES: Initializes the OPENFILENAME structure for later use.
-----------------------------------------------------------------------------*/
void fileInit(HWND hwnd)
{
	static TCHAR szFilter[] = TEXT("All Files (*.*)\0*.*\0\0");
	
	ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner         = hwnd;
	ofn.hInstance         = NULL;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter    = 0;
	ofn.nFilterIndex      = 0;
	ofn.lpstrFile         = NULL;   
	ofn.nMaxFile          = MAX_PATH;
	ofn.lpstrFileTitle    = NULL;       
	ofn.nMaxFileTitle     = MAX_PATH;
	ofn.lpstrInitialDir   = NULL;
	ofn.lpstrTitle        = NULL;
	ofn.Flags             = 0;  
	ofn.nFileOffset       = 0;
	ofn.nFileExtension    = 0;
	ofn.lpstrDefExt       = TEXT("wav");
	ofn.lCustData         = 0L;
	ofn.lpfnHook          = NULL;
	ofn.lpTemplateName    = NULL;
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		initButtons
--
--	DATE:			2009-04-13
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		initButtons()
--
--	RETURNS:		void
--
--	NOTES: Initializes all the buttons in the main window to an enabled or
--	disabled state, depending on the application's current mode of operation.
-----------------------------------------------------------------------------*/
void initButtons() {
	if (ci.request == MULTI_STREAM) {
		SetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), (LPCSTR)"Mute");
	}
	else {
		SetWindowText(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), (LPCSTR)"Pause");
	}
	EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), FALSE);
	EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_BROADCAST), FALSE);

	if (ci.behaviour == SERVER) {
		if (ci.request == MULTI_STREAM) {
			EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_BROADCAST), TRUE);
		}
	}
	else if (ci.behaviour == CLIENT) {
		if (ci.request == SINGLE_DL) {
		}
		else if (ci.request == SINGLE_UP) {
		}
		else if (ci.request == SINGLE_STREAM) {
			EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), TRUE);
			EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_DOWNLOAD), TRUE);
		}
		else if (ci.request == MULTI_STREAM) {
			EnableWindow(GetDlgItem(ghDlgMain, IDC_BTN_PAUSE), TRUE);
		}
		else if (ci.request == MICROPHONE) {
		}
	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		initMenu
--
--	DATE:			2009-04-13
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		initMenu()
--
--	RETURNS:		void
--
--	NOTES: Initializes all the menu items in the main window to an enabled or
--	disabled state, depending on the application's current mode of operation.
-----------------------------------------------------------------------------*/
void initMenu() {
	EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_SINGLE_DL, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_SINGLE_UP, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_SINGLE_STREAM, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_MULTI_STREAM, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_2WAY_MICROPHONE, MF_GRAYED);
	checkMenuItem(0);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		connectActions
--
--	DATE:			2009-04-13
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		connectActions()
--
--	RETURNS:		void
--
--	NOTES: Enables the disconnect menu and disables the connect menu.
-----------------------------------------------------------------------------*/
void connectActions() {
	EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_ENABLED);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		disconnectActions
--
--	DATE:			2009-04-13
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		disconnectActions()
--
--	RETURNS:		void
--
--	NOTES: Enables the connect menu and disables the disconnect menu.
-----------------------------------------------------------------------------*/
void disconnectActions() {
	EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
	EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);

	checkMenuItem(0);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		setActions
--
--	DATE:			2009-04-13
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		setActions()
--
--	RETURNS:		void
--
--	NOTES: Enables or disables menu items based on the applications current
--	mode of operation.
-----------------------------------------------------------------------------*/
void setActions() {
	if (ci.behaviour == CLIENT) {
		CheckMenuItem(ghMenu, ID_MODE_CLIENT, MF_CHECKED);
		CheckMenuItem(ghMenu, ID_MODE_SERVER, MF_UNCHECKED);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);

		EnableMenuItem(ghMenu, ID_SINGLE_DL, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_SINGLE_UP, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_SINGLE_STREAM, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_MULTI_STREAM, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_2WAY_MICROPHONE, MF_ENABLED);
	}
	else if (ci.behaviour == SERVER) {
		CheckMenuItem(ghMenu, ID_MODE_CLIENT, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MODE_SERVER, MF_CHECKED);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);

		EnableMenuItem(ghMenu, ID_SINGLE_DL, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_SINGLE_UP, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_SINGLE_STREAM, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_MULTI_STREAM, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_2WAY_MICROPHONE, MF_GRAYED);
	}
	else {
		CheckMenuItem(ghMenu, ID_MODE_CLIENT, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MODE_SERVER, MF_UNCHECKED);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);

		EnableMenuItem(ghMenu, ID_SINGLE_DL, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_SINGLE_UP, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_SINGLE_STREAM, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_MULTI_STREAM, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_2WAY_MICROPHONE, MF_GRAYED);
	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		checkMenuItem
--
--	DATE:			2009-04-13
--
--	REVISIONS:		
--
--	DESIGNER(S):	Steffen L. Norgren
--	PROGRAMMER(S):	Steffen L. Norgren
--
--	INTERFACE:		checkMenuItem(int item)
--						int item: The menu item to be checked
--
--	RETURNS:		void
--
--	NOTES: Checks the indicated menu item and unchecks all other menu items.
-----------------------------------------------------------------------------*/
void checkMenuItem(int item) {
	CheckMenuItem(ghMenu, ID_SINGLE_DL, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_SINGLE_UP, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_SINGLE_STREAM, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_MULTI_STREAM, MF_UNCHECKED);
	CheckMenuItem(ghMenu, ID_2WAY_MICROPHONE, MF_UNCHECKED);

	if (item == 0) {
		CheckMenuItem(ghMenu, ID_MODE_CLIENT, MF_UNCHECKED);
		CheckMenuItem(ghMenu, ID_MODE_SERVER, MF_UNCHECKED);
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_GRAYED);
		EnableMenuItem(ghMenu, ID_FILE_DISCONNECT, MF_GRAYED);
	}
	else {
		EnableMenuItem(ghMenu, ID_FILE_CONNECT, MF_ENABLED);
		CheckMenuItem(ghMenu, item, MF_CHECKED);
	}
}