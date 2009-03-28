#include "win_main.h"

void server_download()
{
	char outBuf[BUFSIZE];
	DWORD RecvBytes, bytesRead;
	DWORD Flags = 0;
	HANDLE hFile;

	/* Open the file */
	if((hFile = CreateFile("testOut.wav", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("Error opening file!"), NULL, MB_ICONERROR);
		return;
	}
	while(1)
	{
		if(ReadFile(hFile, outBuf, &RecvBytes, &bytesRead, NULL) == 0)
			break;

		if (sendto (ci.tcpSocket, outBuf, bytesRead, 0, NULL, NULL) == -1)
		{
			MessageBox(NULL, TEXT("Failure to send\n"), NULL, MB_OK);
			break;
		}
	}
}

void client_download()
{
	char inBuf[BUFSIZE];
	DWORD RecvBytes, bytesWritten;
	DWORD Flags = 0;
	HANDLE hFile;
	int cSize;
	SOCKADDR from;
	cSize = sizeof(SOCKADDR);

	/* Open the file */
	if((hFile = CreateFile("testIn.wav", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL)) == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, TEXT("Error opening file!"), NULL, MB_ICONERROR);
		return;
	}
	while(1)
	{
		recvfrom(ci.tcpSocket, inBuf, sizeof(inBuf), 0, &from, &cSize);
		/*if (WSARecv(ci.tcpSocket, inBuf, 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(NULL, TEXT("WSARecv() failed with error \n"), NULL, MB_OK);
				break;
			}
		}*/

		WriteFile(hFile, inBuf, sizeof(inBuf), &bytesWritten, NULL);

		if(bytesWritten == 0) //we're done
			break;
	}
}
