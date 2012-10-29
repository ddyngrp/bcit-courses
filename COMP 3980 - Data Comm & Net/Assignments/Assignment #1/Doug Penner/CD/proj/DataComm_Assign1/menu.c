/* 
* File:   menu.c
* Author: Doug Penner
*
* Created on September 21, 2008
*/

#include <windows.h>
#include "main.h"
#include "menu.h"
#include "resource.h"
#include "serial.h"

// handles menu events
void menuProcessor(HANDLE hwnd, wndInfo *wInfo, WPARAM wParam) {
	switch (LOWORD (wParam)) {	// check which menu item was hit
		case ID_FILE_QUIT:			// quit program
			PostQuitMessage (0);	// tell OS to close program
			break;
		case ID_FILE_CONNECT:		// connect to serial port
			commConnect(hwnd, &wInfo->serCon);
			break;
		case ID_FILE_DISCONNECT:	// disconnect from serial port
			commDisconnect(hwnd, &wInfo->serCon);
			break;
		case ID_FILE_RECONNECT:		// reconnect to serial port (if connected)
			commReconnect(hwnd, &wInfo->serCon);
			break;
		case ID_COMPORT_COM1:		// specify COM1 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 1);
			break;
		case ID_COMPORT_COM2:		// specify COM2 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 2);
			break;
		case ID_COMPORT_COM3:		// specify COM3 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 3);
			break;
		case ID_COMPORT_COM4:		// specify COM4 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 4);
			break;
		case ID_COMPORT_COM5:		// specify COM5 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 5);
			break;
		case ID_COMPORT_COM6:		// specify COM6 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 6);
			break;
		case ID_COMPORT_COM7:		// specify COM7 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 7);
			break;
		case ID_COMPORT_COM8:		// specify COM8 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 8);
			break;
		case ID_COMPORT_COM9:		// specify COM9 (reconnects if connected)
			commSetNumber(hwnd, &wInfo->serCon, 9);
			break;
	}
}
