/*-----------------------------------------------------------------------------------
-- SOURCE FILE: connection.c - Contains functions responsible for the actual sending
--							   and receiving of information, as well as reading and
--							   writing the files involved.
--
-- PROGRAM: Transfer++
--
-- FUNCTIONS:
-- void read_socket(WPARAM wParam)
-- void write_socket(WPARAM wParam)
-- long delay (SYSTEMTIME t1, SYSTEMTIME t2)
--
-- DATE: February 26, 2009
--
-- REVISIONS: Feb. 20 - Created this file and added the WinMain() function
--					  - Added the establish_connection function and filled it with
--						the AsynchSelect code from milliways, and added the helper
--						functions for it, FreeSocketInformation, GetSocketInformation
--						and CreateSocket Information.
--			  Feb. 21 - Added the setup_server and setup_client functions and moved
--						the connections code from establish_connection.
--						establish_connection now just determines which kind of
--						connection to setup (tcp/udp, client/server)
--					  - Added the socket_handler function which handles the various
--						cases coming in through the wndProc list.
--                       Feb. 25 - Removed socket handler and added delay functions
--			  
--
-- DESIGNER: Jaymz Boilard
-- PROGRAMMER: Jaymz Boilard & Aman Abdulla & Various MSDN Contributers
--
-- NOTES: 
---------------------------------------------------------------------------------*/
#include "functions.h"
#include "resource.h"
extern HANDLE hFile;

/*---------------------------------------------------------------------------------
-- FUNCTION: write_socket
--
-- DATE: February 26, 2009
--
-- REVISIONS: Feb. 21 - Added this function and copied the code previously in 
--						establish_connection to it.
--
-- DESIGNER: Jaymz Boilard
-- PROGRAMMER: Jaymz Boilard & Aman Abdulla & Various MSDN Contributers
--
-- INTERFACE: void write_socket(WPARAM wParam)
--
-- RETURNS: void
--
-- NOTES: Called on FD_WRITE command, sent when we want to write to the socket.
------------------------------------------------------------------------------------*/
void write_socket(HWND hwnd, wndInfo * wInfo, SOCKET sd, WSADATA wsaData)
{
	struct hostent	*hp;
	struct sockaddr_in server;
	char sbuf[BUFSIZE], **pptr;
	SYSTEMTIME stStartTime, stEndTime;
	DWORD bytesRead;
	int i;

	// Initialize and set up the address structure
	memset((char *)&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(wInfo->port);

	if ((hp = gethostbyname(wInfo->host)) == NULL)
	{
		MessageBox(hwnd, TEXT("Unknown server address\n"), NULL, MB_OK);
		return;
	}

	memcpy((char *)&server.sin_addr, hp->h_addr, hp->h_length); // Copy the server address

	// Connecting to the server
	if(wInfo->protocol == TCP)
	{
		if (connect (sd, (struct sockaddr *)&server, sizeof(server)) == -1)
		{
			MessageBox(hwnd, TEXT("Can't connect to server\n"), NULL, MB_OK);
			return;
		}
	}
	MessageBox(hwnd, TEXT("Connected.n"), NULL, MB_OK);
	pptr = hp->h_addr_list;
	memset((char *)sbuf, 0, sizeof(sbuf));

	if(wInfo->firstTimer == 0)
	{
		GetSystemTime(&stStartTime);
		wInfo->firstTimer = 1;
	}
	for(i = 0; i < wInfo->TTS; i++)
	{
		while(1)		{
			ReadFile(hFile, &sbuf, wInfo->packetSize, &bytesRead, NULL);
			if(bytesRead == 0)
			{
				CancelIo(hFile);
				break;
			}
			if(wInfo->protocol == UDP)
			{
				if (sendto (sd, sbuf, bytesRead, 0, (struct sockaddr *)&server, sizeof(server)) == -1)
				{
					MessageBox(hwnd, TEXT("Failure to send\n"), NULL, MB_OK);
					break;
				}
			}
			else
				send(sd, sbuf, bytesRead, 0);
		}
	}	
	GetSystemTime(&stEndTime);
	wsprintf(wInfo->delayTime, "Delay: %ld", delay(stStartTime, stEndTime));
	closesocket (sd);
}

/*---------------------------------------------------------------------------------
-- FUNCTION: delay
--
-- DATE: February 26, 2009
--
-- REVISIONS: Feb. 21 - Added this function and copied the code previously in 
--						establish_connection to it.
--
-- DESIGNER: Aman Abdulla
-- PROGRAMMER: Aman Abdulla
--
-- INTERFACE: long delay (SYSTEMTIME t1, SYSTEMTIME t2)
--
-- RETURNS: the time between the first and second time
--
-- NOTES: Called on FD_READ command, sent when we want to read to the socket.  Upon
--		  successfully reading, it will open a file and write the data to it.
------------------------------------------------------------------------------------*/
long delay (SYSTEMTIME t1, SYSTEMTIME t2)
{
	long d;

	d = (t2.wSecond - t1.wSecond) * 1000;
	d += (t2.wMilliseconds - t1.wMilliseconds);
	return(d);
}

/*---------------------------------------------------------------------------------
-- FUNCTION: read_socket
--
-- DATE: February 26, 2009
--
-- REVISIONS: Feb. 21 - Added this function and copied the code previously in 
--						establish_connection to it.
--
-- DESIGNER: Jaymz Boilard
-- PROGRAMMER: Jaymz Boilard & Aman Abdulla
--
-- INTERFACE: void setup_server(HWND hwnd, wndInfo * wInfo)
--
-- RETURNS: void
--
-- NOTES: Called on FD_READ command, sent when we want to read to the socket.  Upon
--		  successfully reading, it will open a file and write the data to it.
------------------------------------------------------------------------------------*/
void read_socket(WPARAM wParam, wndInfo * wInfo)
{
	LPSOCKET_INFORMATION SocketInfo;
	DWORD RecvBytes;
    DWORD Flags;
	DWORD bytesWritten;
	OVERLAPPED lpOver;
	SYSTEMTIME stStartTime, stEndTime;

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
	SocketInfo->DataBuf.len = DATA_BUFSIZE;
	Flags = 0;
	
	GetSystemTime(&stStartTime);
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
			if(wInfo->protocol == UDP)
				break;
			SocketInfo->BytesRECV = RecvBytes;
		}
	}
	GetSystemTime(&stEndTime);
	wsprintf(wInfo->delayTime, "Delay: %ld", delay(stStartTime, stEndTime));
}
