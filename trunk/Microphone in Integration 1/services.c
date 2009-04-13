#include "win_main.h"


/*------------------------------------------------------------------------
--		FUNCTION:		server_download
--
--		REVISIONS:		March 29 - Added a sleep after each packet send so 
--									that the client can keep up with us.
--
--		DESIGNER:		Jaymz Boilard
--		PROGRAMMER:		Jaymz Boilard & Jerrod Hudson
--
--		INTERFACE:		server_download(WPARAM wParam)
--
--		RETURNS:		void
--
--		NOTES:			The server's response when prompted by the client
--						to service a download request.  It opens the file,
--						reading & sending packets until we reach end of
--						file.
------------------------------------------------------------------------*/
void server_download(WPARAM wParam, PTSTR	fileName)
{
	char outBuf[FILE_BUFF_SIZE];
	DWORD bytesRead;
	HANDLE hFile;
	DWORD Flags = 0;

	/* Open the file */
	if((hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(ghWndMain, (LPCSTR)"Error opening file!",
			(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
		return;
	}
	while(1)
	{
		memset(outBuf,'\0',FILE_BUFF_SIZE);
		ReadFile(hFile, outBuf, FILE_BUFF_SIZE, &bytesRead, NULL);
		if(bytesRead == 0)
		{
			/* End of file, close & exit. */
			send(wParam, "Last Pkt\0", 9, 0);
			CancelIo(hFile);
			break;
		}

		if(send(wParam, outBuf, bytesRead, 0) == -1)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(ghWndMain, (LPCSTR)"send() failed.",
					(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
				closesocket(wParam);
			}
		}
		Sleep(1); /* Give the client some time to catch up with us */
	}
}

/*------------------------------------------------------------------------
--		FUNCTION:		client_download
--
--		REVISIONS:
--
--		DESIGNER:		Jaymz Boilard
--		PROGRAMMER:		Jaymz Boilard & Jerrod Hudson
--
--		INTERFACE:		client_download(WPARAM wParam)
--
--		RETURNS:		void
--
--		NOTES:			Called asyncronously when the request type is set 
--						to download & the connection has already been
--						established.  It opens the file and writes the
--						incoming packet to the end of it, and displays a
--						message when we are done transferring.
------------------------------------------------------------------------*/
void client_download(WPARAM wParam)
{
	char buffer[FILE_BUFF_SIZE];
	DWORD bytesWritten;
	HANDLE hFile;
	OVERLAPPED lpOver;
	int bytesRead;
	DWORD Flags = 0;

	/* Final parameter of WriteFile() which tells it to append the data to the end */
	memset(&lpOver, 0, sizeof(OVERLAPPED));
	lpOver.Offset = lpOver.OffsetHigh = 0xFFFFFFFF;
	/* Clear the buffer */
	memset(buffer, 0, sizeof(buffer));

	if((bytesRead = recv(wParam, buffer, FILE_BUFF_SIZE, 0)) == -1)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			MessageBox(ghWndMain, (LPCSTR)"WSARecv() failed.",
				(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
			closesocket(wParam);
		}
	}
	else
	{
		if(strncmp(buffer, "FILE", 4) == 0)
		{
			receiveFileList(wParam, buffer);
			//CloseHandle(hFile);
			return;
		}

		if((hFile = CreateFile(ci.DLfileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
		{
			MessageBox(ghWndMain, (LPCSTR)"Error opening file!",
				(LPCSTR)"Error!", MB_OK | MB_ICONSTOP);
			return;
		}

		/* Append the data to the end of the file & close it */
		WriteFile(hFile, buffer, bytesRead, &bytesWritten, &lpOver);
		CloseHandle(hFile);
	}
	if(!strcmp(buffer,"Last Pkt")) { /* Last packet, but not an empty packet. Needs to be fixed. */
		MessageBox(ghWndMain, (LPCSTR)"File download completed!",
			(LPCSTR)"Operation Completed", MB_OK | MB_ICONINFORMATION);
	}
}
