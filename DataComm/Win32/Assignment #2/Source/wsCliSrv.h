#ifndef _WSCLISRV_H_
#define _WSCLISRV_H_

#define PORT			9000
#define DATA_BUFF_SIZE	8192
#define WM_SOCKET		(WM_USER +5)

#include <winsock2.h>

typedef struct _SOCKET_INFO {
	BOOL	RecvPosted;
	CHAR	Buffer[DATA_BUFF_SIZE];
	WSABUF	DataBuff;
	SOCKET	Socket;
	DWORD	BytesSEND,
			BytesRECV;
} SOCKET_INFO, * LPSOCKET_INFO;

void Server(void);
void Client(void);
BOOL CALLBACK ServerProc(HWND, UINT, WPARAM, LPARAM);
void CreateSocketInfo(SOCKET);
LPSOCKET_INFO GetSocketInfo(SOCKET);
void FreeSocketInfo(SOCKET);
void AppendLog(char* str);
void ClearLog(void);

HWND ghWndSocket;	// Invisible window for the socket

#endif