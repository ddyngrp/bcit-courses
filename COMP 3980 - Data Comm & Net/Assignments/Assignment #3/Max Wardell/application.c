#include "cases.h"
#include "functions.h"

/*int WinMessageLoop()
*Purpose: The message loop to process all messages the instance of the program receives.
*As long as the message is not WM_QUIT, this loop will not return 0. Therefore, keep going.
*/
int WinMessageLoop() {
	MSG Msg;

	while(GetMessage(&Msg, NULL, 0, 0)) {
   		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return (int) Msg.wParam;
}

/*LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
*Purpose: Determines what the window displays in its client area and how the window responds to user input.
*Arg 1 - Handle to the window procedure.
*Arg 2 - Specifies the message.
*Arg 3 - Additional message-specific information.
*Arg 4 - Additional message-specific information.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
						 WPARAM wParam, LPARAM lParam) {
	char buffer;
	char escCode = 27, bracketCode = 91, oCode = 79;
	char initMsg[] = {0x01, 0x08, 0x00, 0x03, 0x01, 0x40, 0x4B, 0xB4};

	HMENU hmenu = GetMenu(hwnd);
	switch(Message) {
		case WM_COMMAND:
			switch(LOWORD(wParam)) {
				case IDM_COM1:
					CommProperties(hwnd, TEXT("com1"));
					break;
				case IDM_COM2:
					CommProperties(hwnd, TEXT("com2"));
					break;
				case IDM_COM3:
					CommProperties(hwnd, TEXT("com3"));
					break;
				case IDM_COM4:
					CommProperties(hwnd, TEXT("com4"));
					break;
				case IDM_COM5:
					CommProperties(hwnd, TEXT("com5"));
					break;
				case IDM_COM6:
					CommProperties(hwnd, TEXT("com6"));
					break;
				case IDM_COM7:
					CommProperties(hwnd, TEXT("com7"));
					break;
				case IDM_COM8:
					CommProperties(hwnd, TEXT("com8"));
					break;
				case IDM_COM9:
					CommProperties(hwnd, TEXT("com9"));
					break;
				case IDM_CONNECT:
					mode = CONNECT;
					if(OpenPort(lpszCommName)) {
						CreateReadThread(hwnd);
						EnableMenuItem(hmenu, IDM_DCONNECT, MF_ENABLED);
						EnableMenuItem(hmenu, IDM_CONNECT, MF_GRAYED);
						//Send the initial packet to the RFID
						InitPacket(initMsg);
					}
					else
						mode = COMMAND;
					break;

				case IDM_DCONNECT:
					if(CloseHandle(hThread) && CloseHandle(hComm)) {
						mode = COMMAND;
						hComm = NULL;
						hThread = NULL;
						EnableMenuItem(hmenu, IDM_CONNECT, MF_ENABLED);
						EnableMenuItem(hmenu, IDM_DCONNECT, MF_GRAYED);
					}
					break;

				case IDM_HELP:
					HelpMsg();
					break;

				case IDM_EXIT:
					PostQuitMessage(0);
					break;
			}
			break;

		case WM_CHAR:
			if(mode != CONNECT)
				break;
			if(wParam == '\x1B') {
				SendMessage(hwnd, WM_COMMAND, IDM_DCONNECT, lParam);
				break;
			}
			buffer = (char) wParam;
			WriteToPort(&buffer);
			InvalidateRect(hwnd, NULL, FALSE);
			break;

		case WM_KEYDOWN:
			break;

		case WM_CREATE:
			wasEsc = FALSE, wasBracket = FALSE;
			escDigit1 = 100, escDigit2 = 100, escDigit3 = 100, escDigit4 = 100;
			CheckAvailPorts(hwnd);
			CreateText(hwnd);
			ResizeWindow(hwnd, Message, lParam);

		case WM_PAINT:
			PaintText(hwnd);
			break;

		case WM_SETFOCUS: /*Received when a window is put into focus.*/
			SetWindowFocus(hwnd, cxChar, cyChar);
			break;

		case WM_KILLFOCUS: /*Received when a window is taken out of focus.*/
			KillWindowFocus(hwnd);
			break;
		
		case WM_DESTROY:
      		PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/*void CreateText(HWND hwnd)
*Purpose: Initializes the buffer and sets the size of characters.
*Arg 1 - Handle to the window procedure.
*/
void CreateText(HWND hwnd) {
	HDC hdc = GetDC(hwnd);
	HMENU hmenu = GetMenu(hwnd);
	pBuffer = NULL;

	EnableMenuItem(hmenu, IDM_DCONNECT, MF_GRAYED);
	SelectObject(hdc, CreateFont(0, 0, 0, 0, 0, 0,
		0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));
	GetTextMetrics(hdc, &textMetric);
	cxChar = textMetric.tmAveCharWidth;
	cyChar = textMetric.tmHeight;
	DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT)));
	ReleaseDC(hwnd, hdc);
}

/*void ResizeWindow(HWND hwnd, UINT Message, LPARAM lParam)
*Purpose: Resizes the window when the window is dragged.
*Arg 1 - Handle to the window procedure to receive the message.
*Arg 2 - The current message on the message queue.
*Arg 3 - Additional message-specific information.
*/
void ResizeWindow(HWND hwnd, UINT Message, LPARAM lParam) {
	pBuffer = NULL;

	cxClient = LOWORD(lParam);
	cyClient = HIWORD(lParam);

	cxBuffer = 80;
	cyBuffer = 25;

	if(pBuffer != NULL)
		free(pBuffer);
	pBuffer = (TCHAR *) malloc(cxBuffer * cyBuffer * sizeof(TCHAR));
	for(y = 0; y < cyBuffer; y++) {
		for(x = 0; x < cxBuffer; x++) {
			BUFFER(x, y) = ' ';
		}
	}
	xCaret = 0;
	yCaret = 0;
	wasSemi = FALSE;
	InvalidateRect(hwnd, NULL, FALSE);
}

/*BOOL OpenPort(LPTSTR lpszCommName)
*Purpose: Opens the port to allow reading and writing between two emulators.
*Arg 1 - The name of the port to be opened.
*/
BOOL OpenPort(LPTSTR lpszCommName) {
	if(lpszCommName == NULL) {
		ChoosePortMsg();
		return FALSE;
	}
	if((hComm = CreateFile(lpszCommName, GENERIC_READ | GENERIC_WRITE, 0,
			NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL))
			== INVALID_HANDLE_VALUE) {
		ErrorFailedPortMsg();
		return FALSE;
	}
	if(!SetCommState(hComm, &commConfig.dcb)) {
		FailedSavePortMsg();
		return FALSE;
	}
	if(!SetupComm(hComm, 8, 8)) {
		FailedConnectionMsg();
		return FALSE;
	}
	if(!GetCommProperties(hComm, &commProp)) {
		FailedConnectionMsg();
		return FALSE;
	}
	return TRUE;
}

/*void PaintRead(HWND hwnd, char inbuff[], DWORD nBytesRead)
*Purpose: Takes characters sent from the port to the buffer.
*Arg 1 - Handle to the window procedure.
*Arg 2 - Buffer to receive 100 characters at a time.
*Arg 3 - The actual character received.
*/
void PaintRead(HWND hwnd, char inbuff[], DWORD nBytesRead) {
	int row = 0, column = 0;

	InvalidateRect(hwnd, NULL, FALSE);
	return;
}

/*void PaintText(HWND hwnd)
*Purpose: Takes the characters from the buffer and outputs them to the client area.
*Arg 1 - Handle to the window procedure.
*/
void PaintText(HWND hwnd) {
	PAINTSTRUCT paintStruct;
	HDC hdc = BeginPaint(hwnd, &paintStruct);

	SelectObject(hdc, CreateFont (0, 0, 0, 0, 0, 0,
		0, 0, dwCharSet, 0, 0, 0, FIXED_PITCH, NULL));

	SetCaretPos(xCaret * cxChar, yCaret * cyChar);
	DeleteObject(SelectObject(hdc, GetStockObject (SYSTEM_FONT)));
	EndPaint (hwnd, &paintStruct);
}

/*void SetWindowFocus(HWND hwnd, sWndStore *wndStore, int cxChar, int cyChar)
*Purpose: Sets the focus of the window when called.
*Arg 1 - Handle to the window procedure to receive the message.
*Arg 2 - A structure with stored data about the window.
*Arg 3 - Width of the current caret location.
*Arg 4 - Height of the current caret location.
*Return: N/A
*/
void SetWindowFocus(HWND hwnd, int cxChar, int cyChar) {
    CreateCaret(hwnd, NULL, cxChar, cyChar);
    SetCaretPos(xCaret * cxChar, yCaret * cyChar);
    ShowCaret(hwnd);
}

/*void KillWindowFocus(HWND hwnd)
*Purpose: Kills the focus of the window when called.
*Arg 1 - Handle to the window procedure to receive the message.
*Return: N/A
*/
void KillWindowFocus(HWND hwnd) {
    HideCaret(hwnd);
    DestroyCaret();
}

void InitPacket(char message[]) {
	int i;
	for(i = 0; i < 8; i++)
		WriteToPort(&message[i]);
}

byte GetCheckSum(char* packet) {
	int length = (packet[1] * 256) + packet[2];
	int checksum = packet[0];
	int i;
	for(i = 1; i < length - 2; i++)
		checksum^= packet[i];
	return checksum;
}

BOOL ValidateCheckSum(char* packet) {
	int length = (packet[1] * 256) + packet[2];
	if((packet[length - 2] != GetCheckSum(packet)) || (packet[length - 1] + packet[length - 2] != 0xFF))
		return FALSE;
	return TRUE;
}

void SendCheckSum(char* packet) {
	int length = (packet[1] * 256) + packet[2];
	packet[length - 2] = GetCheckSum(packet);
	packet[length - 1] = 0xFF - packet[length - 2];
}

void ParseBuffer(char *inbuff, DWORD nBytesRead) {
	DWORD i;
	for(i = 0; i < nBytesRead; i++) {
		if(packet.found == 0) {
			packet.p[packet.found] = inbuff[i];
			packet.found++;
		}
		else if(packet.found == 2) { //If we are at the length-specifying byte
			//packet.total = str_to_int(&inbuff[i], 2);
			packet.p[packet.found] = inbuff[i];
			packet.found++;
		}
		else if(packet.found == (packet.total - 1)) {
			packet.p[packet.total] = inbuff[i];
			packet.found++;
			//parse_packet(&packet.p, &packet.found);
			packet.found = 0;
		}
		else {
			packet.p[packet.found] = inbuff[i];
			packet.found++;
		}
	}
}

void send_packet(byte cmd1, byte cmd2, char *data, size_t len) {
	size_t i;
	byte lrc = SOF;
	byte lrc2;
	byte t = SOF;
	byte t2 = 0x03;
	size_t packetLength = len + 8;
	lrc ^= packetLength;
	lrc ^= 0x03;
	lrc ^= cmd1;
	lrc ^= cmd2;
	lrc2 = !lrc;
	WriteToPort(&t);
	WriteToPort(&packetLength);
	WriteToPort(&t2);
	WriteToPort(&cmd1);
	WriteToPort(&cmd2);
	WriteToPort(&data);
	WriteToPort(&lrc);
	WriteToPort(&lrc2);
}


