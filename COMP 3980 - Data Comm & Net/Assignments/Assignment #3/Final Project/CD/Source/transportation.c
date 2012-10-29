#include "packets.h"
#include "functions.h"

/*int WriteToPort(char* lpBuf)
*Purpose: Writes characters typed to the port.
*Arg 1 - Buffer for characters receivedfrom the port.
*/
int WriteToPort(char* lpBuf) {
   OVERLAPPED osWrite = {0};
   DWORD dwWritten;

   //Create this write operation's OVERLAPPED structure's hEvent.
   osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   if(osWrite.hEvent == NULL)
      // error creating overlapped event handle
      return FALSE;

   if(!WriteFile(hComm, lpBuf, 1, &dwWritten, &osWrite)) {
      if(GetLastError() != ERROR_IO_PENDING) {
		  WriteErrorMsg();
		  return FALSE;
      }
   }
   CloseHandle(osWrite.hEvent);
   return TRUE;
}

void send_byte(byte b) {
	WriteToPort(&b);
}

/*DWORD ReadThread(HWND hwnd)
*Purpose: Reads characters coming in from the port
*Arg 1 - Handle to the window procedure.
*/
DWORD ReadThread(HWND hwnd) {
	char inbuff[128];
	DWORD nBytesRead, dwEvent;
	COMSTAT comstat;
	COMMTIMEOUTS timeOuts;
	OVERLAPPED osRead = {0};
	osRead.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//Set the total timeout interval
	memset(&timeOuts, 0, sizeof(timeOuts));
	timeOuts.ReadTotalTimeoutMultiplier = 5;
	timeOuts.ReadTotalTimeoutConstant = 50;
	SetCommTimeouts(hComm, &timeOuts);

	SetCommMask(hComm, EV_RXCHAR);
	
	//Initialize packet
	packet.found = 0;
	packet.total = -1;
	packet.lrc = 0;
	while(mode == CONNECT) {
		if(WaitCommEvent(hComm, &dwEvent, NULL)) {
			ClearCommError(hComm, NULL, &comstat);
			if((dwEvent & EV_RXCHAR) && comstat.cbInQue) {
				if(!ReadFile(hComm, &inbuff, min(127, comstat.cbInQue), &nBytesRead, &osRead)) {
					break;
				}
				else {
					if(nBytesRead) {
						ParseBuffer(&inbuff[0], nBytesRead);
					}
				}
			}
		}
		ResetEvent(osRead.hEvent);
	}
	PurgeComm(hComm, PURGE_RXCLEAR);
	return 0L;
}

void Search() {
	Sleep(750);
	if (scanTags) {
		send_packet(0x01, 0x41, &timesToLook, 1);
	}
}

void send_message(char *p, int len) {
	int i;
	for(i=0; i<len; i++)
		WriteToPort(&p[i]);
}



/*int OpenPort(LPTSTR lpszCommName)
*Purpose: Opens the port to allow reading and writing between two emulators.
*Arg 1 - The name of the port to be opened.
*/
int OpenPort(LPTSTR lpszCommName) {
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

int ValidateCheckSum(char* packet) {
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
			packet.total = -1;
		}
		else if(packet.found == 2) { //If we are at the length-specifying byte
			packet.total = packet.p[1] + (256 * packet.p[2]);
			packet.p[packet.found] = inbuff[i];
			packet.found++;
		}
		else if(packet.found == (packet.total - 1)) {
			packet.p[packet.total] = inbuff[i];
			packet.found++;
			parse_packet();
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
	lrc ^= len+8;
	lrc ^= 0x03;
	lrc ^= cmd1;
	lrc ^= cmd2;
	for (i=0; i<len; i++) {
		lrc ^= data[i];
	}
	send_byte(SOF);
	send_byte((byte)(len+8));
	send_byte(0);
	send_byte(0x03);
	send_byte(cmd1);
	send_byte(cmd2);
	for (i=0; i < len; i++)
		send_byte(data[i]);
	send_byte(lrc);
	send_byte(0xFF-lrc);
}

void send_beepToggle() {
	size_t i;
	byte lrc = SOF;
	byte control = 0x03;

	lrc ^= 0x0A;
	lrc ^= 0x03;
	lrc ^= 0x01;
	lrc ^= 0x43;
	lrc ^= control;
	lrc ^= 0x03;

	send_byte(SOF);
	send_byte((byte)(0x0A));
	send_byte(0);
	send_byte(0x03);
	send_byte(0x01);
	send_byte(0x43);
	send_byte(control);
	send_byte(0x03);
	send_byte(lrc);
	send_byte(0xFF-lrc);
}