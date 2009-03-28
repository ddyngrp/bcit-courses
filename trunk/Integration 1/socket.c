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
	static int count = 0;
	SOCKADDR from;
	char buffer[BUFSIZE];
	int cSize;

	if(wParam == INVALID_SOCKET)
		return;

	cSize = sizeof(SOCKADDR);
	memset(buffer, '\0', BUFSIZE);

	recvfrom(wParam, buffer, sizeof(buffer), 0, &from, &cSize);
	count++;

	/* Set the type according to the first packet */
	if(strcmp(buffer, "Single Download") == 0)
		server_download();

	MessageBox(NULL, buffer, "Data Received!", MB_OK);
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
	if(ci.request == SINGLE_DL)
	{
		strcpy_s(buffer, BUFSIZE, "Single Download");
		sendto(wParam, buffer, BUFSIZE, 0, (SOCKADDR *)&remote, sizeof(remote));
		client_download();
		return;
	}
	else if(ci.request == SINGLE_UP)
		strcpy_s(buffer, BUFSIZE, "Single Upload");
	else if(ci.request == SINGLE_STREAM)
		strcpy_s(buffer, BUFSIZE, "Stream");
	else if(ci.request == MULTI_STREAM)
		strcpy_s(buffer, BUFSIZE, "Multicast");

	sendto(wParam, buffer, BUFSIZE, 0, (SOCKADDR *)&remote, sizeof(remote));
}
