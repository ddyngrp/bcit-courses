#include "cases.h"
#include "functions.h"

#define NUMBEROFPORTS 9

/*void CommProperties(HWND hwnd, LPTSTR CommPort)
*Purpose: Prompts the user for the comm settings and saves them.
*Arg 1 - Handle to the window procedure.
*Arg 2 - The name of the port to be opened.
*/
void CommProperties(HWND hwnd, LPTSTR CommPort) {
	if(mode == CONNECT) {
		CntChngSettingsMsg();
		return;
	}
	commConfig.dwSize = sizeof(COMMCONFIG);
	commConfig.wVersion = 0x100;
	if(!CommConfigDialog(CommPort, hwnd, &commConfig)) {
        FailedPortMsg();
		return;
	}
	lpszCommName = CommPort;
}

void CheckAvailPorts(HWND hwnd) {
	int i;
	HMENU hmenu = GetMenu(hwnd);
	LPCWSTR CommPort = TEXT("com1");
	UINT portNumber = IDM_COM1;
	for(i = 0; i < NUMBEROFPORTS; i++) {
		switch(i) {
		case 1:
			CommPort = TEXT("com1");
			portNumber = IDM_COM1;
			break;
		case 2:
			CommPort = TEXT("com2");
			portNumber = IDM_COM2;
			break;
		case 3:
			CommPort = TEXT("com3");
			portNumber = IDM_COM3;
			break;
		case 4:
			CommPort = TEXT("com4");
			portNumber = IDM_COM4;
			break;
		case 5:
			CommPort = TEXT("com5");
			portNumber = IDM_COM5;
			break;
		case 6:
			CommPort = TEXT("com6");
			portNumber = IDM_COM6;
			break;
		case 7:
			CommPort = TEXT("com7");
			portNumber = IDM_COM7;
			break;
		case 8:
			CommPort = TEXT("com8");
			portNumber = IDM_COM8;
			break;
		case 9:
			CommPort = TEXT("com9");
			portNumber = IDM_COM9;
			break;
		}
		if((hComm = CreateFile(CommPort, GENERIC_READ | GENERIC_WRITE, 0,
			NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL))
			== INVALID_HANDLE_VALUE) {
			EnableMenuItem(hmenu, portNumber, MF_GRAYED);
			
		}
		CloseHandle(hComm);
	}
}
