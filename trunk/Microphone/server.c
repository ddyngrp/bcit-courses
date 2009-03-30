#include "win_main.h"

/*------------------------------------------------------------------------
--		FUNCTION:		server
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void server(HWND hwnd, serverInfo si)
--							HWND hwnd: Handle to the window to paint
--							serverInfo si: User defined port and protocol
--
--		RETURNS:		void
--
--		NOTES:
--		Creates a socket, binds an address to it, sets the total number
--		of clients, and listens for connections.
------------------------------------------------------------------------*/
void server(HWND hwnd)
{
	WSADATA				wsaData;
	char				arg;

	if((WSAStartup(MAKEWORD(2, 2), &wsaData)) == -1)
	{
		MessageBox(NULL, "WSAStartup failed!", "ERROR", MB_OK);
		WSACleanup();
	}

	/* Create TCP socket */
	if((ci.tcpSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		MessageBox(NULL, "Unable to create TCP socket!", "ERROR", MB_OK);

	/* Set SO_REUSEADDR for port reuseability */
	if(setsockopt(ci.tcpSocket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1)
		MessageBox(NULL, "Unable to set SO_REUSEADDR", "ERROR", MB_OK);

	memset((char *)&local, 0, sizeof(SOCKADDR_IN));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(ci.port);

	/* Bind address to socket */
	if(bind(ci.tcpSocket, (SOCKADDR *)&local, sizeof(SOCKADDR)) == SOCKET_ERROR)
		MessageBox(NULL, "Unable to bind address to socket!", "ERROR", MB_OK);

	/* Set max number of connections */
	if(listen(ci.tcpSocket, NUMCONNECTIONS))
		MessageBox(NULL, "Unable to set number of connections!", "ERROR", MB_OK);

	WSAAsyncSelect(ci.tcpSocket, hwnd, WM_SOCKET, FD_READ | FD_ACCEPT | FD_CLOSE);
}
