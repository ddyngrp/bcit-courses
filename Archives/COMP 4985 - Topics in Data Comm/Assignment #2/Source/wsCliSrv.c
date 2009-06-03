#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include "wsCliSrv.h"
#include "resource.h"
#include "winMain.h"

BOOL Client(void) {
	DWORD		Ret;
	SOCKET		SendSocket;
	WSADATA		wsaData;
	LPSTR		psBuff;
	struct		sockaddr_in server;

	WORD wVersionRequested = MAKEWORD(2,2);

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	if ((Ret = WSAStartup(wVersionRequested, &wsaData)) != 0) {
		wsprintf(psBuff, (LPCTSTR)"WSAStartup failed with error %d", Ret);
		AppendLog(psBuff);
		return FALSE;
	}

	if ((SendSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)	{
		wsprintf(psBuff, (LPCTSTR)"socket() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}

	memset((char *)&server, 0, sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(gcIP);
	server.sin_port = htons(PORT);

	WSAAsyncSelect(SendSocket, ghWndMain, WM_SOCKET, FD_WRITE | FD_CONNECT | FD_READ | FD_CLOSE);

	if ((Ret == WSAConnect(SendSocket, (struct sockaddr *)&server, sizeof(server), 0, 0, 0, NULL)) != 0) {
		wsprintf(psBuff, (LPCTSTR)"WSAConnect() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}
	else {
		wsprintf(psBuff, (LPCTSTR)"Connecting to server %s on port %d", gcIP, PORT);
		AppendLog(psBuff);
		return TRUE;
	}
}

BOOL Server(void) {
	DWORD		Ret;
	SOCKET		ListenSocket;
	struct		sockaddr_in InetAddr;
	WSADATA		wsaData;
	LPSTR		psBuff;

	WORD wVersionRequested = MAKEWORD(2,2);

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	if ((Ret = WSAStartup(wVersionRequested, &wsaData)) != 0) {
		wsprintf(psBuff, (LPCTSTR)"WSAStartup failed with error %d", Ret);
		AppendLog(psBuff);
		return FALSE;
	}

	if ((ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) 	{
		wsprintf(psBuff, (LPCTSTR)"socket() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}

	WSAAsyncSelect(ListenSocket, ghWndMain, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

	wsprintf(psBuff, (LPCTSTR)"WM_SOCKET = %d", WM_SOCKET);
	AppendLog(psBuff);

	memset((char *)&InetAddr, 0, sizeof(struct sockaddr_in));
	InetAddr.sin_family = AF_INET;
	InetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InetAddr.sin_port = htons(PORT);

	if (bind(ListenSocket, (struct sockaddr *)&InetAddr, sizeof(InetAddr)) == SOCKET_ERROR) {
		wsprintf(psBuff, (LPCTSTR)"bind() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}

	if (listen(ListenSocket, 5)) {
		wsprintf(psBuff, (LPCTSTR)"listen() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return FALSE;
	}
	else {
		return TRUE;
	}
}

BOOL CALLBACK ClientProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	LPSOCKET_INFO	SocketInfo;
	DWORD			SendBytes;
	LPSTR			psBuff;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);
	
	if (WSAGETSELECTERROR(lParam)) {
		wsprintf(psBuff, (LPCTSTR)"Socket failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
	}
	else {
		switch (WSAGETSELECTEVENT(lParam)) {
			case FD_CONNECT:
				CreateSocketInfo(wParam);
				break;

			case FD_WRITE:
				SocketInfo = GetSocketInfo(wParam);

				if (SocketInfo->DataBuff.len == 0) {
					SocketInfo->DataBuff.buf = SocketInfo->Buffer;
					SocketInfo->DataBuff.len = 0;
				}

				if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuff), 1, &SendBytes,
					0, NULL, NULL) == SOCKET_ERROR) {
						if (WSAGetLastError() != WSAEWOULDBLOCK) {
							wsprintf(psBuff, (LPCTSTR)"WSASend() failed with error %d", WSAGetLastError());
							AppendLog(psBuff);
							//FreeSocketInfo(wParam);
						}
				}
				else { // Update the byte count
					SocketInfo->BytesSEND += SendBytes;
				}
				break;

			case FD_CLOSE:
				wsprintf(psBuff, (LPCTSTR)"Closing socket %d", wParam);
				AppendLog(psBuff);
				FreeSocketInfo(wParam);
				break;
		}
		return FALSE;
	}

	return FALSE;
}

BOOL CALLBACK ServerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	SOCKET			Accept;
	LPSOCKET_INFO	SocketInfo;
	DWORD			RecvBytes, SendBytes;
	DWORD			Flags;
	LPSTR			psBuff;
	struct			sockaddr_in client;
	int				client_len;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	memset((char *)&client, 0, sizeof(struct sockaddr_in));

	
	if (WSAGETSELECTERROR(lParam)) {
		wsprintf(psBuff, (LPCTSTR)"Socket failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
	}
	else {
		switch (WSAGETSELECTEVENT(lParam)) {
			case FD_ACCEPT:
				client_len = sizeof(client);

				if ((Accept = accept(wParam, (struct sockaddr *)&client, &client_len)) == INVALID_SOCKET) {
					wsprintf(psBuff, (LPCTSTR)"accept() failed with error %d", WSAGetLastError());
					AppendLog(psBuff);
					break;
				}

				// Create a socket information structure to assiciate with the
				// socket for processing I/O
				CreateSocketInfo(Accept);

				// Add to log file
				wsprintf(psBuff, (LPCTSTR)"Client IP %s connected to socket number %d", inet_ntoa(client.sin_addr), Accept);
				AppendLog(psBuff);

				WSAAsyncSelect(Accept, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
				break;

			case FD_READ:
				SocketInfo = GetSocketInfo(wParam);

				// Read data only if the receive buffer is empty.

				if (SocketInfo->BytesRECV != 0) {
					SocketInfo->RecvPosted = TRUE;
					return 0;
				}
				else {
					SocketInfo->DataBuff.buf = SocketInfo->Buffer;
					SocketInfo->DataBuff.len = DATA_BUFF_SIZE;

					Flags = 0;
					if (WSARecv(SocketInfo->Socket, &(SocketInfo->DataBuff), 1, &RecvBytes,
						&Flags, NULL, NULL) == SOCKET_ERROR) {
						if (WSAGetLastError() != WSAEWOULDBLOCK) {
							wsprintf(psBuff, (LPCTSTR)"WSARecv() failed with error %d", WSAGetLastError());
							AppendLog(psBuff);
							FreeSocketInfo(wParam);
							return 0;
						}
					} 
					else { // No error so update the byte count
						SocketInfo->BytesRECV = RecvBytes;
						wsprintf(psBuff, (LPCTSTR)"Received %d bytes", SocketInfo->BytesRECV);
					}
				}
				// Clear Buffer
				ZeroMemory(&(SocketInfo->Buffer), sizeof(SocketInfo));
				SocketInfo->DataBuff.buf = 0;
				SocketInfo->DataBuff.len = 0;
				SocketInfo->BytesRECV = 0;
					
				break;

			case FD_CLOSE:
				wsprintf(psBuff, (LPCTSTR)"Closing socket %d", wParam);
				AppendLog(psBuff);
				FreeSocketInfo(wParam);
				break;
		}
		return FALSE;
	}

	return FALSE;
}

void CreateSocketInfo(SOCKET s) {
	LPSOCKET_INFO	SI;
	LPSTR			psBuff;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	if ((SI = (LPSOCKET_INFO)GlobalAlloc(GPTR, sizeof(SOCKET_INFO))) == NULL) {
		wsprintf(psBuff, (LPCTSTR)"GlobalAlloc() failed with error %d", GetLastError());
		AppendLog(psBuff);
		return;
	}

	// Prepate SocketInfo structure for use
	SI->Socket = s;
	SI->RecvPosted = FALSE;
	SI->BytesSEND = 0;
	SI->BytesRECV = 0;

	SocketInfo = SI;
}

LPSOCKET_INFO GetSocketInfo(SOCKET s) {
	if (SocketInfo->Socket == s) {
		return SocketInfo;
	}

	return NULL;
}

void FreeSocketInfo(SOCKET s) {
	closesocket(SocketInfo->Socket);
	GlobalFree(SocketInfo);
	WSACleanup();
}

void AppendLog(char* str) {
	HWND list = GetDlgItem(ghWndOutput, IDC_LST_OUTPUT);

	ListBox_InsertString(list, -1,str);
	ListBox_SetCurSel(list, ListBox_GetCount(list) - 1);
	SetFocus(list);
}

void ClearLog(void) {
	HWND list = GetDlgItem(ghWndOutput, IDC_LST_OUTPUT);
	int count, i;

	count = ListBox_GetCount(list);
	for (i = 0; i < count; i++) {
		ListBox_DeleteString(list, 0);
	}
}

void FillBuffer(int size) {
	char * sendBuff = (char *)malloc(size);
	int i;

	memset((char *)&sendBuff[0], '0', size);

	SocketInfo->DataBuff.buf = sendBuff;
	SocketInfo->DataBuff.len = size;
}