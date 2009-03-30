#include "socket.h"

void sockAccept(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	SOCKET sd_acc;

	if(wParam == INVALID_SOCKET)
		return;

	sd_acc = accept(wParam, NULL, NULL);

	if(sd_acc == INVALID_SOCKET)
		MessageBox(NULL, "Unable to create accept socket!", "ERROR", MB_OK);
}

void sockClose(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	shutdown(wParam, 2);
	closesocket(wParam);
}

void sockConnect(HWND hwnd, WPARAM wParam, LPARAM lParam)
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

	MessageBox(NULL, error, "ERROR", MB_OK);
}

void sockRead(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	char buffer[BUFSIZE];
	int cSize;

	if(wParam == INVALID_SOCKET)
		return;

	cSize = sizeof(SOCKADDR);
	memset(buffer, '\0', BUFSIZE);

	if(ci.behavior == SERVER)
	{
		if(ci.request == SINGLE_UP)
		{
			client_download(wParam); /* The client's download is the inverse of the server's upload */
			return;
		}

		if(recv(wParam, buffer, sizeof(buffer), 0) == -1)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(NULL, TEXT("WSARecv() failed with error \n"), NULL, MB_OK);
				closesocket(wParam);
			}
		}

		/* Set the type according to the first packet */
		if(strcmp(buffer, "Single Download") == 0)
		{
			ci.request = SINGLE_DL;
			server_download(wParam); /* Go right to sending the file. */
		}
		else if(strcmp(buffer, "Single Upload") == 0)
			ci.request = SINGLE_UP;
			
	}
	else if (ci.behavior == CLIENT)
	{
		if(ci.request == SINGLE_DL)
			client_download(wParam);
	}
	
}


/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	writeTCPsock
-- 
--	REVISIONS:	March 26 - Added a check for the request type, which changes the
--						   the outbound buffer correspondingly.
--						 - Changed the name to writeTCPsocket, since we will only
--						   be using this one for sending control messages.  A
--						   separate one will be used for UDP transfers.
-- 
--	DESIGNER:	Jerrod Hudson, Jaymz Boilard
--	PROGRAMMER:	Jerrod Hudson, Jaymz Boilard
-- 
--	INTERFACE:	void writeTCPsock(HWND hwnd, WPARAM wParam, LPARAM lParam)
-- 
--	RETURNS:	void
-- 
--	NOTES:	Writes to a socket, used for the control channel.
---------------------------------------------------------------------------------------*/
void writeTCPsock(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	char				buffer[BUFSIZE];
	extern SOCKADDR_IN	remote;
	extern connectInfo	ci;

	memset(buffer, '\0', BUFSIZE);
	if(ci.behavior == CLIENT)
	{
		if(ci.request == SINGLE_DL)
			strcpy_s(buffer, BUFSIZE, "Single Download");
		else if(ci.request == SINGLE_UP)
			strcpy_s(buffer, BUFSIZE, "Single Upload");
		else if(ci.request == SINGLE_STREAM)
			strcpy_s(buffer, BUFSIZE, "Stream");
		else if(ci.request == MULTI_STREAM)
			strcpy_s(buffer, BUFSIZE, "Multicast");

		if(send(wParam, buffer, sizeof(buffer), 0) == -1)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				MessageBox(NULL, TEXT("send() failed with error \n"), NULL, MB_OK);
				closesocket(wParam);
			}
		}
		//Sleep(1); prompt for file choice

		if(ci.request == SINGLE_UP)
			server_download(wParam); /* Client's upload is inverse of server's download */
	}
	else if (ci.behavior == SERVER)
		MessageBox(NULL, TEXT("Warning: Asyncronous TCP write called by the serverk (should not happen).\n"), NULL, MB_OK);
}
