#include "win_main.h"
LPSOCKET_INFORMATION SocketInfoList;

void server_download(WPARAM wParam)
{
	char outBuf[BUFSIZE];
	DWORD bytesRead;
	DWORD Flags = 0;
	HANDLE hFile;
	int d;

	/* Open the file */
	if((hFile = CreateFile("testOut.wav", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("Error opening file!"), NULL, MB_ICONERROR);
		return;
	}
	while(1)
	{
		ReadFile(hFile, outBuf, BUFSIZE, &bytesRead, NULL);
		
		if(bytesRead == 0)
		{
			//MessageBox(NULL, TEXT("Finished reading file.\n"), NULL, MB_OK);
			CancelIo(hFile);
			break;
		}

		/*if (sendto (ci.tcpSocket, outBuf, bytesRead, 0, (struct sockaddr *)&local, sizeof(local)) == -1)
		{
			MessageBox(NULL, TEXT("Failure to send\n"), NULL, MB_OK);
			break;
		}*/
		if(send(wParam, outBuf, bytesRead, 0) == -1)
		{
			d = WSAGetLastError();
		}
		//break;
	}

}

/*void client_download(WPARAM wParam)
{
	LPSOCKET_INFORMATION SocketInfo;
	DWORD RecvBytes;
    DWORD Flags;
	DWORD bytesWritten;
	OVERLAPPED lpOver;
	HANDLE hFile;

	if((hFile = CreateFile("testIn.wav", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("Error opening file!"), NULL, MB_ICONERROR);
		return;
	}

	memset(&lpOver, 0, sizeof(OVERLAPPED));
	lpOver.Offset = lpOver.OffsetHigh = 0xFFFFFFFF;

	SocketInfo = GetSocketInformation(wParam);
	SocketInfo->BytesRECV = 0;
	SocketInfo->BytesSEND = 0;
	SocketInfo->DataBuf.buf = 0;
	SocketInfo->DataBuf.len = 0;
	SocketInfo->RecvPosted = 0;
	SocketInfo->Buffer[0] = '\0';

	if (SocketInfo->BytesRECV != 0)
	{
		SocketInfo->RecvPosted = TRUE;
		return;
	}

	SocketInfo->DataBuf.buf = SocketInfo->Buffer;
	SocketInfo->DataBuf.len = BUFSIZE;
	Flags = 0;

	while(1)
	{
		if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(NULL, TEXT("WSARecv() failed with error \n"), NULL, MB_OK);
				FreeSocketInformation(wParam);
			}
		} 
		else // No error so update the byte count
		{
			SocketInfo->BytesRECV = RecvBytes;
			WriteFile(hFile, SocketInfo->DataBuf.buf, RecvBytes, &bytesWritten, &lpOver);
			if(SocketInfo->BytesRECV == 0)
				break;
			SocketInfo->BytesRECV = RecvBytes;
		}
	}
}*/

void client_download(WPARAM wParam)
{
	WSABUF inBuf;
	char buffer[BUFSIZE];
	DWORD RecvBytes, bytesWritten;
	HANDLE hFile;
	//int cSize;
	OVERLAPPED lpOver;
	DWORD Flags = 0;

	/* Final parameter of WriteFile() which tells it to append the data to the end */
	memset(&lpOver, 0, sizeof(OVERLAPPED));
	lpOver.Offset = lpOver.OffsetHigh = 0xFFFFFFFF;

	//cSize = sizeof(SOCKADDR);

	memset(buffer, 0, sizeof(buffer));

	if((hFile = CreateFile("testIn.wav", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("Error opening file!"), NULL, MB_ICONERROR);
		return;
	}
	//recvfrom(ci.tcpSocket, inBuf, sizeof(inBuf), 0, &from, &cSize);
	/*if (WSARecv(wParam, &inBuf, 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			MessageBox(NULL, TEXT("WSARecv() failed with error \n"), NULL, MB_OK);
			break;
		}
	}*/
		
	if(recv(wParam, buffer, BUFSIZE, 0) == -1)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			MessageBox(NULL, TEXT("WSARecv() failed with error \n"), NULL, MB_OK);
			FreeSocketInformation(wParam);
		}
	}

	WriteFile(hFile, buffer, sizeof(buffer), &bytesWritten, &lpOver);
	CloseHandle(hFile);
}


/*---------------------------------------------------------------------------------
-- FUNCTION: FreeSocketInformation
--
-- DATE: February 26, 2009
--
-- REVISIONS: 
--
-- DESIGNER: Aman Abdulla
-- PROGRAMMER: Aman Abdulla
--
-- INTERFACE: void FreeSocketInformation(SOCKET s)
--
-- RETURNS: void
--
-- NOTES: Accepts a socket and frees the memory of the data structure of it
------------------------------------------------------------------------------------*/
void FreeSocketInformation(SOCKET s)
{
	SOCKET_INFORMATION *SI = SocketInfoList;
	SOCKET_INFORMATION *PrevSI = NULL;

	while(SI)
	{
		if (SI->Socket == s)
		{
			if (PrevSI)
			PrevSI->Next = SI->Next;
			else
			SocketInfoList = SI->Next;

			closesocket(SI->Socket);
			GlobalFree(SI);
			return;
		}

		PrevSI = SI;
		SI = SI->Next;
	}
}

/*---------------------------------------------------------------------------------
-- FUNCTION: GetSocketInformation
--
-- DATE: February 26, 2009
--
-- REVISIONS: 
--
-- DESIGNER: Aman Abdulla
-- PROGRAMMER: Aman Abdulla
--
-- INTERFACE: void FreeSocketInformation(SOCKET s)
--
-- RETURNS: A pointer to the data structure containing the socket's information, or
--		    NULL on error.
------------------------------------------------------------------------------------*/
LPSOCKET_INFORMATION GetSocketInformation(SOCKET s)
{
	SOCKET_INFORMATION *SI = SocketInfoList;

	while(SI)
	{
		if (SI->Socket == s)
			return SI;
		SI = SI->Next;
	}

	return NULL;
}
