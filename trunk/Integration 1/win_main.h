#ifndef _WIN_MAIN_H_
#define _WIN_MAIN_H_

#include <winsock2.h>
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdio.h>
#include <conio.h>

// Global Definitions
#define X_SIZE			380
#define Y_SIZE			240
#define X_MIN_SIZE		450
#define Y_MIN_SIZE		200
#define NUMCONNECTIONS	5
#define WM_SOCKET		10000
#define DEFAULT_PORT	9000
#define EDITSIZE		50
#define BUFSIZE			4096
#define BLOCK_SIZE		44100
#define BLOCK_COUNT		2000

#define FILEBUFSIZE		120
#define MAXBUFSIZE		8000
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

/* Custom Message Cracker Definition */
#define HANDLE_WM_SOCKET(hwnd, wParam, lParam, fn) \
	((fn)((hwnd), (wParam), (lParam)), 0L)

/* Connection Information */
typedef struct _CONNECTINFO
{
	char ip[EDITSIZE];  //just used for client to store the data entered in dialogue box
	int port;
	int behavior;  //server or client
	int request;	//DL, UP, stream, multi stream
	int protocol;
	char DLfileName[200]; //the name of the file to create when we download a song
	SOCKET			tcpSocket;
} connectInfo;

typedef struct _SOCKET_INFORMATION {
	BOOL RecvPosted;
	CHAR Buffer[BUFSIZE];
	WSABUF DataBuf;
	SOCKET Socket;
	DWORD BytesSEND;
	DWORD BytesRECV;
	struct _SOCKET_INFORMATION *Next;
} SOCKET_INFORMATION, * LPSOCKET_INFORMATION;

// Global Variables
HINSTANCE	ghInst;				// Main application's global instance
HWND		ghWndMain,			// Main window's global handle
			ghDlgMain;			// Main dialogue window's global handle
HMENU		ghMenu;				// Main window's menu handle
HACCEL		ghAccel;			// Keyboard accelerator
SOCKADDR_IN	remote,				// Server socket information
			local;				// Client socket information
connectInfo	ci;					// Connection information

int					busyFlag;
static				WAVEFORMATEX pwfx;
static				HWAVEOUT hwo;

// Global Functions
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
void writeAudio(HWAVEOUT hWaveOut, LPSTR data, int size);
void freeBlocks(WAVEHDR* blockArray);
WAVEHDR* allocateBlocks(int size, int count);
static void CALLBACK waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2);
void receiveStream(WPARAM sd);
void sendStream(WPARAM sd, PTSTR fileName);

/* Services */
void server_download(WPARAM wParam, PTSTR	fileName);
void client_download(WPARAM wParam);
void FreeSocketInformation(SOCKET s);
LPSOCKET_INFORMATION GetSocketInformation(SOCKET s);

/* Helper Functions */
void sendFileList(WPARAM wParam);
void receiveFileList(WPARAM wParam, char buf[]);
void AppendList(char * str);
char* GetSelList(void);

#endif
