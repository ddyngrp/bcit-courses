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

	MessageBox(NULL, buffer, "Data Received!", MB_OK);
}

void sockWrite(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	char				buffer[BUFSIZE];
	extern SOCKADDR_IN	remote;
	extern connectInfo	ci;

	memset(buffer, '\0', BUFSIZE);
	strcpy_s(buffer, BUFSIZE, "This is a test");

	sendto(wParam, buffer, BUFSIZE, 0, (SOCKADDR *)&remote, sizeof(remote));
}