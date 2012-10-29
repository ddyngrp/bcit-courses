#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*Represents being in Connect or Command mode.*/
#define COMMAND 0 
#define CONNECT 1
#define PACKETLENGTH 8

#define SOF 0x01

#define BUFFER(x, y) *(pBuffer + y * cxBuffer + x)/*Converts the pBuffer from one big string into a
                                                    table with an x and y axis. Think battleships.
                                                    From there, changes can be made to the table.*/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")

/*Global structures*/
COMMCONFIG commConfig;
COMMPROP commProp;
TEXTMETRIC textMetric;
DCB dcb;

HANDLE hComm, hThread;
BOOL mode;
LPTSTR lpszCommName;
static int cxChar, cyChar,
           cxClient, cyClient,
		   cxBuffer, cyBuffer,
		   xCaret, yCaret;
static TCHAR *pBuffer;
static DWORD dwCharSet = DEFAULT_CHARSET;
static int y, x;

static BOOL wasEsc, wasBracket, wasSemi;
static int escDigit1, escDigit2, escDigit3, escDigit4, invertColor;
void defaultCharHandle(char inChar);
void nonEscapedChars(HWND hwnd, char processedChar);

/*Function prototypes*/
LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
void RegisterInstance(HINSTANCE hInst);
void MakeWindow(int nCmdShow, HINSTANCE hInst);
BOOL OpenPort(LPTSTR lpszCommName);
int WinMessageLoop();
BOOL WriteToPort(char* lpBuf);
DWORD ReadThread();
void CommProperties(HWND hwnd, LPTSTR CommPort);
BOOL CreateReadThread(HWND hwnd);
void PaintRead(HWND hwnd, char *inbuff, DWORD nBytesRead);
void CreateText(HWND hwnd);
void PaintText(HWND hwnd);
void ResizeWindow(HWND hwnd, UINT Message, LPARAM lParam);

void CheckAvailPorts(HWND hwnd);

void SetWindowFocus(HWND hwnd, int cxChar, int cyChar);
void KillWindowFocus(HWND hwnd);

void ChoosePortMsg();
void FailedConnectionMsg();
void FailedPortMsg();
void ErrorFailedPortMsg();
void FailedSavePortMsg();
void ReadErrorMsg();
void HelpMsg();
void WriteErrorMsg();
void ConnectMsg();
void DConnectMsg();
void ReadThreadErrorMsg();
void CntChngSettingsMsg();

//GLOBALS FOR ASSN3
static struct packet_ {
	int found;
	int total;
	byte lrc;
	char p[128];
} packet;

void InitPacket(char message[]);
char* CreatePacket();
void send_packet(byte cmd1, byte cmd2, char *data, size_t packetlength);

byte GetCheckSum(char* packet);
BOOL ValidateCheckSum(char* packet);
void SendCheckSum(char* packet);

#endif
