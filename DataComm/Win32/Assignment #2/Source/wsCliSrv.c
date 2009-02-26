#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include "wsCliSrv.h"
#include "resource.h"
#include "winMain.h"

LPSOCKET_INFO SocketInfo;

void Client(void) {
}

void Server(void) {
	DWORD		Ret;
	SOCKET		Listen;
	SOCKADDR_IN	InetAddr;
	WSADATA		wsaData;
	LPSTR		psBuff;

	WORD wVersionRequested = MAKEWORD(2,2);

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);

	if ((Ret = WSAStartup(wVersionRequested, &wsaData)) != 0) {
		wsprintf(psBuff, (LPCTSTR)"WSAStartup failed with error %d", Ret);
		AppendLog(psBuff);
		return;
	}

	if ((Listen = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		wsprintf(psBuff, (LPCTSTR)"socket() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return;
	}

	// Create a window that simply deals with socket messages
	ghWndSocket = CreateDialog(ghInst, NULL, ghWndMain, ServerProc);

	if (ghWndOutput == NULL) {
		MessageBox(ghWndMain, TEXT("A child window failed to open."), NULL, MB_OK | MB_ICONSTOP);
	}

	WSAAsyncSelect(Listen, ghWndSocket, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

	InetAddr.sin_family = AF_INET;
	InetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	InetAddr.sin_port = htons(PORT);

	if (bind(Listen, (PSOCKADDR)&InetAddr, sizeof(InetAddr)) == SOCKET_ERROR) {
		wsprintf(psBuff, (LPCTSTR)"listen() failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
		return;
	}
}

BOOL CALLBACK ServerProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	SOCKET			Accept;
	LPSOCKET_INFO	SocketInfo;
	DWORD			RecvBytes, SendBytes;
	DWORD			Flags;
	LPSTR			psBuff;

	psBuff = (LPSTR)VirtualAlloc((LPVOID)NULL, (DWORD)(255),
					MEM_COMMIT, PAGE_READWRITE);
	
	if (WSAGETSELECTERROR(lParam)) {
		wsprintf(psBuff, (LPCTSTR)"Socket failed with error %d", WSAGetLastError());
		AppendLog(psBuff);
	}
	else {
		switch (WSAGETSELECTEVENT(lParam)) {
			case FD_ACCEPT:
				if ((Accept = accept(wParam, NULL, NULL)) == INVALID_SOCKET) {
					wsprintf(psBuff, (LPCTSTR)"accept() failed with error %d", WSAGetLastError());
					AppendLog(psBuff);
					break;
				}

				// Create a socket information structure to assiciate with the
				// socket for processing I/O
				CreateSocketInfo(Accept);

				// Add to log file
				wsprintf(psBuff, (LPCTSTR)"Socket number %d connected", Accept);
				AppendLog(psBuff);

				WSAAsyncSelect(Accept, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
				break;

			case FD_READ:
				SocketInfo = GetSocketInfo(wParam);

				// Read data only of the recieve buffer is empty
				if (SocketInfo->BytesRECV != 0) {
					SocketInfo->RecvPosted = TRUE;
					return FALSE;
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
							}
					}
					else { // Update the byte count
						SocketInfo->BytesRECV = RecvBytes;
					}
				}
				break; // TODO: Verify need for this

			case FD_WRITE:
				SocketInfo = GetSocketInfo(wParam);

				if (SocketInfo->BytesRECV > SocketInfo->BytesSEND) {
					SocketInfo->DataBuff.buf = SocketInfo->Buffer + SocketInfo->BytesSEND;
					SocketInfo->DataBuff.len = SocketInfo->BytesRECV - SocketInfo->BytesSEND;

					if (WSASend(SocketInfo->Socket, &(SocketInfo->DataBuff), 1, &SendBytes,
						0, NULL, NULL) == SOCKET_ERROR) {
							if (WSAGetLastError() != WSAEWOULDBLOCK) {
								wsprintf(psBuff, (LPCTSTR)"WSASend() failed with error %d", WSAGetLastError());
								AppendLog(psBuff);
								FreeSocketInfo(wParam);
							}
					}
					else { // Update the byte count
						SocketInfo->BytesSEND += SendBytes;
					}
				}

				if (SocketInfo->BytesSEND == SocketInfo->BytesRECV) {
					SocketInfo->BytesSEND = 0;
					SocketInfo->BytesRECV = 0;

					// If a RECV occurred during our SENDs, then we need to post an
					// FD_READ notification on the socket
					if (SocketInfo->RecvPosted == TRUE) {
						SocketInfo->RecvPosted = FALSE;
						PostMessage(ghWndMain, WM_SOCKET, wParam, FD_READ);
					}
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
	SOCKET_INFO *SI = SocketInfo;

	if (SI->Socket = s) {
		return SI;
	}

	return NULL;
}

void FreeSocketInfo(SOCKET s) {
	SOCKET_INFO *SI = SocketInfo;

	closesocket(SI->Socket);
	GlobalFree(SI);
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