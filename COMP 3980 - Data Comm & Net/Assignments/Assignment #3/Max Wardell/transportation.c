#include "cases.h"
#include "functions.h"

/*BOOL WriteToPort(char* lpBuf)
*Purpose: Writes characters typed to the port.
*Arg 1 - Buffer for characters receivedfrom the port.
*/
BOOL WriteToPort(char* lpBuf) {
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

/*DWORD ReadThread(HWND hwnd)
*Purpose: Reads characters coming in from the port and calls
*the PaintRead function to print them.
*Arg 1 - Handle to the window procedure.
*/
DWORD ReadThread(HWND hwnd) {
	char message2[] = {0x01, 0x09, 0x00, 0x03, 0x01, 0x41, 0x0A, 0x41, 0xBE};
	char *inbuff = "";
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
				if(!ReadFile(hComm, &inbuff, comstat.cbInQue, &nBytesRead, &osRead)) {
					break;
				}
				else {
					if(nBytesRead)
						PaintRead(hwnd, inbuff, nBytesRead);
				}
			}
		}
		ResetEvent(osRead.hEvent);
	}
	PurgeComm(hComm, PURGE_RXCLEAR);
	return 0L;
}
