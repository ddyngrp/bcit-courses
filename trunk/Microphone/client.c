#include "win_main.h"

/*------------------------------------------------------------------------
--		FUNCTION:		client
--
--		DATE:			February 24, 2009
--
--		REVISIONS:		(Date and Description)
--
--		DESIGNER:		Jerrod Hudson
--
--		PROGRAMMER:		Jerrod Hudson
--
--		INTERFACE:		void client(HWND hwnd, clientInfo ci)
--							HWND hwnd: Handle to the window to paint
--							clientInfo ci: User defined client options,
--							including IP, port, protocol, packetsize, etc.
--
--		RETURNS:		void
--
--		NOTES:
--		Creates a socket, binds it to a port, 
------------------------------------------------------------------------*/
void client(HWND hwnd)
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

	WSAAsyncSelect(ci.tcpSocket, hwnd, WM_SOCKET, FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE);

	memset((char *)&remote, 0, sizeof(SOCKADDR_IN));
	remote.sin_family = AF_INET;
	remote.sin_addr.s_addr = inet_addr(ci.ip);
	remote.sin_port = htons(ci.port);
}
