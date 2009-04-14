/*-----------------------------------------------------------------------------
--	SOURCE FILE:	connection_setup.c
--
--	PROGRAM:		CommAudio.exe
--
--	FUNCTIONS:		setup_client(HWND hwnd, int type)
--					setup_server(HWND hwnd, int type)
--
--
--	DATE:			2009-02-24
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson, Steffen L. Norgren
--
--	NOTES:	Sets up a socket connection for the client or server.
-----------------------------------------------------------------------------*/

#include "win_main.h"

/*-----------------------------------------------------------------------------
--	FUNCTION:		setup_client
--
--	DATE:			2009-02-24
--
--	REVISIONS:		2009-03-30 - Jerrod, Added a type int which will allow us
--								 to create either a TCP or UDP connections.
--					2009-04-10 - Steffen, modified to allow for both TCP and 
--								 UDP connection types.
--					2009-04-13 - Steffen, modified to allow for UDP
--								 multicast sessions.
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson, Steffen L. Norgren
--
--	INTERFACE:		setup_client(HWND hwnd, clientInfo ci)
--						HWND hwnd: Handle to the window to paint
--						int type: SOCK_STREAM or SOCK_DGRAM
--
--	RETURNS:		void
--
--	NOTES: Creates a socket, binds it to a port, allow asyncronous
--	message passing.
-----------------------------------------------------------------------------*/
void setup_client(HWND hwnd, int type)
{
	WSADATA	wsaData;
	char	arg, yes = 1;
	struct	ip_mreq mreq;

	if((WSAStartup(MAKEWORD(2, 2), &wsaData)) == -1)
	{
		MessageBox(NULL, "WSAStartup failed!", "ERROR", MB_OK);
		WSACleanup();
	}

	if (type == SOCK_STREAM) {
		/* Create TCP socket */
		if((ci.tcpSocket = socket(AF_INET, type, IPPROTO_TCP)) == INVALID_SOCKET)
			MessageBox(NULL, "Unable to create TCP socket!", "ERROR", MB_OK);

		/* Set SO_REUSEADDR for port reuseability */
		if(setsockopt(ci.tcpSocket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1)
			MessageBox(NULL, "Unable to set SO_REUSEADDR", "ERROR", MB_OK);

		memset((char *)&remote, 0, sizeof(SOCKADDR_IN));
		remote.sin_family = AF_INET;
		remote.sin_addr.s_addr = inet_addr(ci.ip);
		remote.sin_port = htons(ci.tcp_port);

		WSAAsyncSelect(ci.tcpSocket, hwnd, WM_TCP_SOCKET, FD_CONNECT | FD_WRITE | FD_READ | FD_CLOSE);
	}
	else if (type == SOCK_DGRAM) {
		/* Create UDP socket */
		if((ci.udpSocket = socket(AF_INET, type, IPPROTO_UDP)) == INVALID_SOCKET)
			MessageBox(NULL, "Unable to create UDP socket!", "ERROR", MB_OK);

		memset((char *)&udp_remote, 0, sizeof(SOCKADDR_IN));
		udp_remote.sin_family = AF_INET;
		udp_remote.sin_port = htons(ci.udp_port);

		/* Check if we're multicasting and set appropriate connection settings */
		if (ci.request == MULTI_STREAM) {
			/* allow multiple sockets to use the same PORT number */
			if (setsockopt(ci.udpSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
				MessageBox(NULL, "Reusing ADDR failed", "ERROR", MB_OK);
				ExitProcess(1);
			}
			udp_remote.sin_addr.s_addr = htonl(INADDR_ANY);

			/* bind to receive address */
			if (bind(ci.udpSocket, (struct sockaddr *)&udp_remote, sizeof(udp_remote)) < 0) {
				MessageBox(NULL, "Multicast bind() error!", "ERROR", MB_OK);
				ExitProcess(1);
			}

			/* use setsockopt() to request that the kernel join a multicast group */
			mreq.imr_multiaddr.s_addr=inet_addr(MULTICAST_GROUP);
			mreq.imr_interface.s_addr=htonl(INADDR_ANY);

			if (setsockopt(ci.udpSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq)) < 0) {
				MessageBox(NULL, "Multicast: Reusing ADDR failed", "ERROR", MB_OK);
				ExitProcess(1);
			}
		}
		else {
			udp_remote.sin_addr.s_addr = inet_addr(ci.ip);
		}

	}
}

/*-----------------------------------------------------------------------------
--	FUNCTION:		setup_server
--
--	DATE:			2009-02-24
--
--	REVISIONS:		2009-03-30 - Jerrod, Added a type int which will allow us
--								 to create either a TCP or UDP connections.
--					2009-04-10 - Steffen, modified to allow for both TCP and 
--								 UDP connection types.
--					2009-04-13 - Steffen, modified to allow for UDP
--								 multicast sessions.
--
--	DESIGNER(S):	Jerrod Hudson
--	PROGRAMMER(S):	Jerrod Hudson, Steffen L. Norgren
--
--	INTERFACE:		setup_server(HWND hwnd, clientInfo ci)
--						HWND hwnd: Handle to the window to paint
--						int type: SOCK_STREAM or SOCK_DGRAM
--
--	RETURNS:		void
--
--	NOTES: Creates a socket, binds an address to it, sets the total number
--	of clients, and listens for connections.
-----------------------------------------------------------------------------*/
void setup_server(HWND hwnd, int type)
{
	WSADATA	wsaData;
	char	arg;
	HOSTENT *thisHost;
	char	*ip;
	char	ipStatus[TEMP_BUFF_SIZE];

	memset(&ipStatus, '\0', sizeof(ipStatus));

	if((WSAStartup(MAKEWORD(2, 2), &wsaData)) == -1)
	{
		MessageBox(NULL, "WSAStartup failed!", "ERROR", MB_OK);
		WSACleanup();
	}

	thisHost = gethostbyname("");
	ip = inet_ntoa(*(struct in_addr *)*thisHost->h_addr_list);

	strcat(ipStatus, "IP: ");
	strcat(ipStatus, ip);

	SendMessage(ghStatus, SB_SETTEXT, (WPARAM)parts[2], (LPARAM)ipStatus);

	if (type == SOCK_STREAM) {
		/* Create TCP socket */
		if((ci.tcpSocket = socket(AF_INET, type, IPPROTO_TCP)) == INVALID_SOCKET)
			MessageBox(NULL, "Unable to create TCP socket!", "ERROR", MB_OK);

		/* Set SO_REUSEADDR for port reuseability */
		if(setsockopt(ci.tcpSocket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1)
			MessageBox(NULL, "Unable to set SO_REUSEADDR", "ERROR", MB_OK);

		memset((char *)&local, 0, sizeof(SOCKADDR_IN));
		local.sin_family = AF_INET;
		local.sin_addr.s_addr = INADDR_ANY;
		local.sin_port = htons(ci.tcp_port);

		/* Bind address to socket */
		if(bind(ci.tcpSocket, (SOCKADDR *)&local, sizeof(SOCKADDR)) == SOCKET_ERROR)
			MessageBox(NULL, "Unable to bind address to socket!", "ERROR", MB_OK);

		/* Set max number of connections */
		if(listen(ci.tcpSocket, NUMCONNECTIONS))
			MessageBox(NULL, "Unable to set number of connections!", "ERROR", MB_OK);

		WSAAsyncSelect(ci.tcpSocket, hwnd, WM_TCP_SOCKET, FD_READ | FD_ACCEPT | FD_CLOSE);
	}
	else if (type == SOCK_DGRAM) {
		/* Create TCP socket */
		if((ci.udpSocket = socket(AF_INET, type, IPPROTO_UDP)) == INVALID_SOCKET)
			MessageBox(NULL, "Unable to create UDP socket!", "ERROR", MB_OK);

		memset((char *)&udp_local, 0, sizeof(SOCKADDR_IN));
		udp_local.sin_family = AF_INET;
		udp_local.sin_port = htons(ci.udp_port);

		/* Check if we're multicasting and set appropriate connection settings */
		if (ci.request == MULTI_STREAM) {
			udp_local.sin_addr.s_addr = inet_addr(MULTICAST_GROUP);
		}
		else {
			udp_local.sin_addr.s_addr = INADDR_ANY;
			/* Bind address to socket */
			if(bind(ci.udpSocket, (SOCKADDR *)&udp_local, sizeof(SOCKADDR)) == SOCKET_ERROR)
				MessageBox(NULL, "Unable to bind address to socket!", "ERROR", MB_OK);
		}
	}
}