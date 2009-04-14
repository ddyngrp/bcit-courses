/*-----------------------------------------------------------------------------
--	SOURCE FILE:	socket.c
--
--	PROGRAM:		CommAudio.exe
--
--	FUNCTIONS:		
--
--
--	DATE:			
--
--	DESIGNERS:		Jerrod Hudson
--	PROGRAMMERS:	Jerrod Hudson, Jaymz Boilard, Steffen L. Norgren
--
--	NOTES:	
-----------------------------------------------------------------------------*/

#include "socket.h"

/*-----------------------------------------------------------------------------
--	FUNCTION:		sockClose
--
--	DATE:			2009-03-29
--
--	REVISIONS:		2009-04-13 - Steffen, added thread termination.
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson, Steffen L. Norgren
--
--	INTERFACE:		sockClose(HWND hwnd, WPARAM wParam, LPARAM lParam)
--						HWND hwnd: The handle to the calling window.
--						WPARAM wParam: The socket we wish to close
--						LPARAM lParam: -1 if we're not in multicast.
--
--	RETURNS:		void
--
--	NOTES: Closes the socket and terminates any associated threads if we're
--	in multicast mode.
-----------------------------------------------------------------------------*/
void sockClose(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	if (lParam != -1) {
		shutdown(wParam, 2);
		closesocket(wParam);
	}
	else if (ci.request != MULTI_STREAM) { /* End our currently running thread */
		if(streamThread != NULL)
			TerminateThread(streamThread,0);

		ci.request = 0;

		Sleep(200);
	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		tcp_sockAccept
--
--	DATE:			2009-03-29
--
--	REVISIONS:		
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson, Steffen L. Norgren
--
--	INTERFACE:		tcp_sockAccept(HWND hwnd, WPARAM wParam, LPARAM lParam)
--						HWND hwnd: The handle to the calling window.
--						WPARAM wParam: The socket we wish to close
--						LPARAM lParam: unused
--						
--
--	RETURNS:		void
--
--	NOTES: Used by the server to accept an incoming request by a client.
-----------------------------------------------------------------------------*/
void tcp_sockAccept(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	SOCKET sd_acc;

	if(wParam == INVALID_SOCKET)
		return;

	sd_acc = accept(wParam, NULL, NULL);

	if(sd_acc == INVALID_SOCKET) {
		MessageBox(ghWndMain, (LPCSTR)"Unable to create accept socket!",
			(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		tcp_sockConnect
--
--	DATE:			2009-03-29
--
--	REVISIONS:		
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson
--
--	INTERFACE:		tcp_sockConnect(HWND hwnd, WPARAM wParam, LPARAM lParam)
--						HWND hwnd: The handle to the calling window.
--						WPARAM wParam: The socket we wish to close
--						LPARAM lParam: unused
--
--	RETURNS:		void
--
--	NOTES: Checks for an error on connection and prints it in a MessageBox.
-----------------------------------------------------------------------------*/
void tcp_sockConnect(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	int errNum;
	char *error;

	if((errNum = WSAGETSELECTERROR(lParam)) == 0)
		return;

	switch(errNum)
	{
	case WSAECONNREFUSED:
		error = "Server full.  Try again later.\0";
		break;

	case WSAEISCONN:
		error = "Already connected!\0";
		break;

	case WSAETIMEDOUT:
		error = "Connection attempt timed out.\0";
		break;

	default:
		error = "Connection error!\0";
		break;
	}

	MessageBox(ghWndMain, error, (LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		tcp_sockRead
--
--	DATE:			2009-03-29
--
--	REVISIONS:		2009-04-06 - Jaymz, Added the SINGLE_STREAM case which will
--								 call the function receiveStream().
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson, Jaymz Boilard, Steffen L. Norgren
--
--	INTERFACE:		tcp_sockRead(HWND hwnd, WPARAM wParam, LPARAM lParam)
--						HWND hwnd: The handle to the calling window.
--						WPARAM wParam: The socket we wish to close
--						LPARAM lParam: unused
--
--	RETURNS:		void
--
--	NOTES: Reads from a socket asyncronously when we get a message in.
-----------------------------------------------------------------------------*/
void tcp_sockRead(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	char buffer[FILE_BUFF_SIZE];
	int bytesRead;
	int cSize;
	static BOOL firstTime = TRUE;
	ci.tcpSock2 = wParam;

	if(wParam == INVALID_SOCKET)
		return;

	cSize = sizeof(SOCKADDR);
	memset(buffer, '\0', FILE_BUFF_SIZE);

	if(ci.behaviour == SERVER)
	{
		if(ci.request == SINGLE_UP)
		{
			strcpy_s(ci.DLfileName, sizeof(ci.DLfileName), "upload_file.wav");
			client_download(wParam); /* The client's download is the inverse of the server's upload */
			return;
		}

		/* First packet we get in, which specifies the type of operation that the user wants to perform */
		if(recv(wParam, buffer, sizeof(buffer), 0) == -1)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(ghWndMain, (LPCSTR)"recv() failed.",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				closesocket(wParam);
			}
		}

		if(ci.request == SINGLE_DL) //need to set request to 0 when we click on server & gray the other request items
			server_download(wParam, buffer); /* Go right to sending the file. */
		else if(ci.request == SINGLE_STREAM)
		{
			strcpy_s(ci.DLfileName, sizeof(ci.DLfileName), buffer);

			if(streamThread != NULL)
				TerminateThread(streamThread,0);

			streamThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)sendStream, (LPVOID)wParam, 0, 0);
			if(streamThread == NULL)
			{
				MessageBox(ghWndMain, (LPCSTR)"Thread creation failed",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				ExitProcess(1);
			}
		}
		else if(ci.request == MICROPHONE) {
			waveOutWrite(hWaveOut, (WAVEHDR *)buffer, sizeof(WAVEHDR));
		}

		/* Set the type according to the first packet */
		if (ci.request != MULTI_STREAM) {
			if(strcmp(buffer, "Single Download") == 0)
			{
				ci.request = SINGLE_DL;
				sendFileList(wParam);
			}
			else if(strcmp(buffer, "Single Upload") == 0) {
				ci.request = SINGLE_UP;
			}
			else if(strcmp(buffer, "Stream") == 0)
			{
				ci.request = SINGLE_STREAM;
				sendFileList(wParam);
			}
			else if(strcmp(buffer, "Microphone") == 0)
			{
				ci.request = MICROPHONE;
				mic_record_beg();
				streamThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)receiveMicThread,
					(LPVOID)wParam, 0, 0);
			}
		}
		else {
			if (strcmp(buffer, "Multicast") == 0)
			{
				ci.request = MULTI_STREAM;
			}
			else {
				strcpy_s(buffer, FILE_BUFF_SIZE, "NO");
				send(wParam, buffer, strlen(buffer) /*sizeof(buffer)*/, 0);
			}
		}
	}
	else if (ci.behaviour == CLIENT)
	{
		if(ci.request == SINGLE_DL)
		{
			Sleep(1);
			client_download(wParam);
		}
		else if (ci.request == SINGLE_UP) {
			if((bytesRead = recv(wParam, buffer, FILE_BUFF_SIZE, 0)) == -1)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					MessageBox(ghWndMain, (LPCSTR)"WSARecv() failed.",
						(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
					closesocket(wParam);
				}
			}
			if (strncmp(buffer, "NO", 2) == 0) {
				MessageBox(ghWndMain, (LPCSTR)"Server says NO!",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				ExitProcess(1);
			}
		}
		else if(ci.request == SINGLE_STREAM)
		{
			if((bytesRead = recv(wParam, buffer, FILE_BUFF_SIZE, 0)) == -1)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					MessageBox(ghWndMain, (LPCSTR)"WSARecv() failed.",
						(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
					closesocket(wParam);
				}
			}
			if (strncmp(buffer, "NO", 2) == 0) {
				MessageBox(ghWndMain, (LPCSTR)"Server says NO!",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				ExitProcess(1);
			}
			receiveFileList(wParam, buffer);
		}
		else if(ci.request == MICROPHONE)
		{
			if((bytesRead = recv(wParam, buffer, FILE_BUFF_SIZE, 0)) == -1)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					MessageBox(ghWndMain, (LPCSTR)"WSARecv() failed.",
						(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
					closesocket(wParam);
				}
			}
			if (strncmp(buffer, "NO", 2) == 0) {
				MessageBox(ghWndMain, (LPCSTR)"Server says NO!",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				ExitProcess(1);
			}
		}	
	}
	initButtons();
}


/*-----------------------------------------------------------------------------
--	FUNCTION:		tcp_sockWrite
--
--	DATE:			2009-03-29
--
--	REVISIONS:		2009-03-26 - Jerrod, Added a check for the request type, which changes the
--								 the outbound buffer correspondingly.
--							   - Jaymz, Changed the name to tcp_sockWriteet, since we will only
--								 be using this one for sending control messages.  A
--								 separate one will be used for UDP transfers.
--					2009-04-06 - Jaymz, Added a memset to clear all the buffers due to an error.
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson, Jaymz Boilard, Steffen L. Norgren
--
--	INTERFACE:		tcp_sockWrite(HWND hwnd, WPARAM wParam, LPARAM lParam)
--						HWND hwnd: The handle to the calling window.
--						WPARAM wParam: The socket we wish to close
--						LPARAM lParam: unused
--
--	RETURNS:		void
--
--	NOTES: Writes to a socket, used for the control channel.
-----------------------------------------------------------------------------*/
void tcp_sockWrite(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	char	buffer[FILE_BUFF_SIZE];
	TCHAR	fileName[FILE_PATH_SIZE], pathName[FILE_PATH_SIZE];

	memset(buffer, '\0', FILE_BUFF_SIZE);
	memset(fileName, '\0', FILE_PATH_SIZE);
	memset(pathName, '\0', FILE_PATH_SIZE);

	if(ci.behaviour == CLIENT)
	{
		if(ci.request == SINGLE_DL)
		{
			strcpy_s(buffer, FILE_BUFF_SIZE, "Single Download");
			Sleep(10);
		}
		else if(ci.request == SINGLE_UP)
		{
			strcpy_s(buffer, FILE_BUFF_SIZE, "Single Upload");
			Sleep(10);
			browseFiles(hwnd, fileName, pathName);
		}
		else if(ci.request == SINGLE_STREAM)
			strcpy_s(buffer, FILE_BUFF_SIZE, "Stream");
		else if(ci.request == MULTI_STREAM)
			strcpy_s(buffer, FILE_BUFF_SIZE, "Multicast");
		else if(ci.request == MICROPHONE)
			strcpy_s(buffer, FILE_BUFF_SIZE, "Microphone");

		if(send(wParam, buffer,strlen(buffer) /*sizeof(buffer)*/, 0) == -1)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(ghWndMain, (LPCSTR)"send() failed.",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				closesocket(wParam);
			}
		}

		if(ci.request == SINGLE_UP)
		{
			Sleep(1);
			server_download(wParam, fileName); /* Client's upload is inverse of server's download */
		}
		else if(ci.request == MICROPHONE) /* We should only get here once, the data sends are non-async */
		{
			/* Start Microphone Input */
			mic_record_beg();
			streamThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)receiveMicThread,
				(LPVOID)wParam, 0, 0);
		}
	}
	else if (ci.behaviour == SERVER) {
		MessageBox(ghWndMain,
			(LPCSTR)"Warning: Asyncronous TCP write called by the serverk (should not happen).\n",
			(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
	}
}
