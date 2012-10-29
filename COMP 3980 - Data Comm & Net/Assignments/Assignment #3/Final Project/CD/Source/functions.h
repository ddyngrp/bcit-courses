#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

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
int scanTags;

HANDLE hComm, hThread;
int mode;
LPTSTR lpszCommName;
static char timesToLook = 10;

/*Function prototypes*/
int OpenPort(LPTSTR lpszCommName);
int WriteToPort(char* lpBuf);

DWORD ReadThread();

void ChoosePortMsg();
void FailedConnectionMsg();
void FailedPortMsg();
void ErrorFailedPortMsg();
void FailedSavePortMsg();
void ReadErrorMsg();
void HelpAbout();
void WriteErrorMsg();
void ConnectMsg();
void DConnectMsg();
void ReadThreadErrorMsg();
void CntChngSettingsMsg();

void InitPacket(char message[]);
char* CreatePacket();
void send_packet(byte cmd1, byte cmd2, char *data, size_t packetlength);
void send_byte(byte b);
void send_beepToggle();

byte GetCheckSum(char* packet);
int ValidateCheckSum(char* packet);
void SendCheckSum(char* packet);

void Search();
void send_message(char *p, int len);
void ParseBuffer(char *inbuff, DWORD nBytesRead);

//GLOBALS FOR ASSN3
struct packetstruct {
	size_t found;
	int total;
	byte lrc;
	char p[128];
} packet;

#endif
