#ifndef _WIN_MAIN_H_
#define _WIN_MAIN_H_

#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdio.h>
#include <conio.h>
#include "commctrl.h"
/* Removes the requirement to link to the libraries manually */
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"winmm.lib")

/* GUI Definitions */
#define X_SIZE			380
#define Y_SIZE			295
#define STATUS_BAR		2001

/* Connection Definitions */
#define NUMCONNECTIONS	5
#define WM_TCP_SOCKET	10000
#define WM_UDP_SOCKET	10001
#define TCP_PORT		9000
#define	UDP_PORT		7000
#define	MULTICAST_GROUP	"237.137.137.137"

/* Buffer Definitions */
#define BLOCK_SIZE		44100
#define BLOCK_COUNT		20
#define TEMP_BUFF_SIZE	200
#define FILE_PATH_SIZE	255
#define FILE_BUFF_SIZE	4096

/* Flag Definitions */
#define LOCALPLAY		500
#define NETWORKPLAY		501

/* Mode macros  (we start at 1 so that 0 is assumed to be unset, thus we can find uninitialized variables easily) */
#define SERVER			1
#define CLIENT			2
#define TCP				1
#define IDP				2
#define SINGLE_DL		1
#define SINGLE_UP		2
#define SINGLE_STREAM	3
#define MULTI_STREAM	4
#define MICROPHONE		5

/* Custom Message Cracker Definition */
#define HANDLE_WM_TCP_SOCKET(hwnd, wParam, lParam, fn) \
	((fn)((hwnd), (wParam), (lParam)), 0L)
#define HANDLE_WM_UDP_SOCKET(hwnd, wParam, lParam, fn) \
	((fn)((hwnd), (wParam), (lParam)), 0L)

/* Connection Information */
typedef struct _CONNECTINFO
{
			/* just used for client to store the data entered in dialogue box */
	char	ip[TEMP_BUFF_SIZE];
	int		tcp_port,
			udp_port,
			behaviour,	/* server or client */
			request,	/* DL, UP, stream, multi stream */
			protocol;
			/* the name of the file to create when we download a song */
	char	DLfileName[FILE_PATH_SIZE];
	SOCKET	tcpSocket,
			udpSocket,
			tcpSock2;
} connectInfo;

typedef struct _SOCKET_INFORMATION {
	BOOL	RecvPosted;
	CHAR	Buffer[FILE_BUFF_SIZE];
	WSABUF	DataBuf;
	SOCKET	Socket;
	DWORD	BytesSEND,
			BytesRECV;
	struct	_SOCKET_INFORMATION *Next;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;

typedef struct _customWaveFmt
{
    WORD	wFormatTag;			/* format type */
    WORD	nChannels;			/* number of channels 
								   (i.e. mono, stereo...) */
    DWORD	nSamplesPerSec;		/* sample rate */
    DWORD	nAvgBytesPerSec;	/* for buffer estimation */
    WORD	nBlockAlign;		/* block size of data */
    WORD	wBitsPerSample;		/* number of bits per */
} cWAVEFMT;

// Global Variables
HINSTANCE	ghInst;		/* Main application's global instance */
HWND		ghWndMain,	/* Main window's global handle */
			ghDlgMain,
			ghStatus;	/* Main dialogue window's global handle */
HMENU		ghMenu;		/* Main window's menu handle */
HACCEL		ghAccel;	/* Keyboard accelerator */
SOCKADDR_IN	remote,		/* Server socket information */
			local,
			udp_remote,
			udp_local;	/* Client socket information */
connectInfo	ci;			/* Connection information */

int			busyFlag;
static		WAVEFORMATEX pwfx;
HWAVEOUT	hWaveOut;
static BOOL	streamInProgress;
static HANDLE streamThread;

/* Microphone Globals */
static BOOL			bRecording, bPlaying, bEnding, bTerminating;
static DWORD		dwDataLength;
static HWAVEIN		hWaveIn;
static PBYTE		pBuffer1, pBuffer2, pSaveBuffer, pOutBuffer, pNewBuffer;
static PWAVEHDR		pWaveHdr1, pWaveHdr2, pWaveHdr3, pWaveHdr4;
static TCHAR		szOpenError[] = "Error opening waveform audio!";
static TCHAR		szMemError[] = "Error allocating memory!";
static WAVEFORMATEX	waveform;
static HANDLE		micSend, micRecv;

/* Status Bar Information */
static int nParts = 3;
static int width[] = {115,225,-1};
static int parts[] = {0, 1, 2};

/* Global Functions */
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK Dlg_Main(HWND, UINT, WPARAM, LPARAM);
int InitApp(HINSTANCE, int);
int VersionCheck();

/* Jerrod's stuff */
void InitWindow(HWND);
BOOL CALLBACK ServerProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ClientProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
void setup_client(HWND hwnd, int type);
void setup_server(HWND hwnd, int type);

/* Local Play */
BOOL localSong_Init(HWND hwnd, char * filename);
BOOL localSong_Pause(void);
BOOL localSong_Play(void);
BOOL localSong_Stop(void);
BOOL browseFiles(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
void fileInit(HWND hwnd);

/* Network Play */
void writeAudio(LPSTR data, int size);
void freeBlocks(WAVEHDR* blockArray);
WAVEHDR* allocateBlocks(int size, int count);
static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
DWORD WINAPI receiveStream(LPVOID iValue);
DWORD WINAPI sendStream(LPVOID iValue);
DWORD WINAPI receiveMicThread(LPVOID iValue);

/* Services */
void server_download(WPARAM wParam, PTSTR	fileName);
void client_download(WPARAM wParam);
void FreeSocketInformation(SOCKET s);
LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);

/* Helper Functions */
void sendFileList(WPARAM wParam);
void receiveFileList(WPARAM wParam, char buf[]);
void AppendList(char * str);
void ClearList(void);
void GetSelList(char * selItem);
void initMenu(void);
void initButtons(void);
void disconnectActions(void);
void connectActions(void);
void setActions(void);
void checkMenuItem(int);

/* Microphone */
void mic_record_beg(void);
void mic_record_end(void);
void mic_play_beg(void);
void mic_play_end(void);
void terminate_mic_session(void);
void output_done(void);
void open_output_device(void);
void close_mic(void);
void read_mic_data(LPARAM);
void open_mic_device(void);
void close_output(void);

void prepareMicPlay(void);
void unprepareMicPlay(void);

#endif
