/*
	MODULE: wndProc.c

	PURPOSE: Handles program's window.

	AUTHORS: Steffen L. Norgren
*/

#include "winMain.h"
#include "resource.h"

// Private Definitions
#define ID_REDCAR		0x8801

#define BUTTONCLASS		TEXT("Button")
#define BUTTONWIDTH		100
#define BUTTONHEIGHT	25
#define BUTTONOFFSET	10
#define BUTTONDISTANCE	100

#define THREADCOUNT	5

// Private Variables
HWND	hWndBttn[THREADCOUNT];
POINT	ptBttn[THREADCOUNT];
LPSTR	szCarName[] = {"Red Car", "Blue Car", "Green Car", "Orange Car", "Black Car"};
DWORD	id[THREADCOUNT];
HANDLE	hThread[THREADCOUNT];
BOOL	fPressed = FALSE;
BOOL	fWinner = FALSE;
HANDLE	hMutex;

// Private function prototypes
int NEAR PaintWindow(HWND);
void CreateCars(HWND);
DWORD WINAPI ThreadProc(LPVOID);
BOOL isWinner(int);
void StartRace();
void MoveCar(int);

/*
	FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)

	PURPOSE: Windows procedure for the main window

	PARAMETERS:
		hWnd	- window handle
		message	- window message
		wParam	- window message parameter (depends on message)
		lParam	- window message parameter (depends on message)

	RETURN:
		If the message was processed, the return value is 0
		If the message was not processed and passed to DefWindowProc
		and the return value depends on the value of that function.

*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		case WM_CREATE: // case for when the window is created
			gfCritSects = FALSE;
			CreateCars(hWnd);
			break;

		case WM_DESTROY: // case for when the window is closed
			SetEvent(ghEvent);
			PostQuitMessage(0);
			break;

		case WM_COMMAND: // case for menu commands
			MenuDispatch(LOWORD(wParam), hWnd, lParam);
			break;

		case WM_LBUTTONDOWN:
			if (!fPressed) {
				fPressed = TRUE;
				StartRace();
			}
			break;

		case WM_PAINT:
			PaintWindow(hWnd);
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		default:
			return (int)DefWindowProc(hWnd, message, wParam, lParam);
	}
	
	return 0;
}

/*
	FUNCTION: StartRace()

	PURPOSE: Starts our lovely race!

*/
void StartRace() {
	int carNum[] = {1, 2, 3, 4, 5};

	if (gfCritSects) {
		hMutex = CreateMutex(NULL, FALSE, NULL);
	}

	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)0, 0, &id[0]);
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)1, 0, &id[1]);
	hThread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)2, 0, &id[2]);
	hThread[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)3, 0, &id[3]);
	hThread[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, (LPVOID)4, 0, &id[4]);
}

/*
	FUNCTION: CreateCars(HWND)

	PURPOSE: Creates our car buttons within the window

	PARAMETERS:
		hWnd	- Handle to the window

*/
void CreateCars(HWND hWnd) {
	int i;

	for (i = 0; i < THREADCOUNT; i++) {
		hWndBttn[i] = CreateWindow(BUTTONCLASS, szCarName[i],
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					BUTTONOFFSET,
					BUTTONOFFSET + (i * BUTTONDISTANCE), BUTTONWIDTH,
					BUTTONHEIGHT, hWnd,
					(HMENU)ID_REDCAR,
					ghInst, NULL);
		ptBttn[i].x = BUTTONOFFSET;
		ptBttn[i].y = BUTTONOFFSET + (i * BUTTONDISTANCE);
	}
}

/*
	FUNCTION: MoveCar(int)

	PURPOSE: Moves a car across the screen

	PARAMETERS:
		carNum	- The car to be moved

*/
void MoveCar(int carNum) {
	ptBttn[carNum].x = ptBttn[carNum].x + 5;
			
	MoveWindow(hWndBttn[carNum], ptBttn[carNum].x, ptBttn[carNum].y, BUTTONWIDTH, BUTTONHEIGHT, TRUE);

	InvalidateRect(ghWndMain, NULL, TRUE);
}

/*
	FUNCTION: PaintWindow(HWND)

	PURPOSE: Paints the rectangle determined by the paint struct of the DC.

	PARAMETERS:
		hWnd	- Handle to the window

*/
int NEAR PaintWindow(HWND hWnd) {
	PAINTSTRUCT	ps;
	HDC			hDC;
	HPEN		hPen;
	RECT		rcClient;

	hDC = BeginPaint(hWnd, &ps);

	GetClientRect(ghWndMain, &rcClient);

	hDC = GetDC(ghWndMain);

	hPen = (HPEN)SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0,0,0)));

	SelectObject(hDC, CreatePen(PS_SOLID, 1, RGB(0,0,0)));
	
	MoveToEx(hDC, rcClient.right/2, 0, NULL);
	LineTo(hDC, rcClient.right/2, rcClient.bottom);

	DeleteObject(SelectObject(hDC, hPen));

	EndPaint(hWnd, &ps);
	ReleaseDC(ghWndMain, hDC);

	return TRUE;
}

/*
	FUNCTION: ThreadProc(HWND)

	PURPOSE: Moves a button across the client area

	PARAMETERS:
		iValue	- The car's array position

*/
DWORD WINAPI ThreadProc(LPVOID iValue) {
	int		carNum = (int)iValue;
	int		workLoop;
	DWORD	dwWaitResult;

	while(!fWinner) {
		for (workLoop = 0; workLoop < 100000; workLoop++) {
		}
		if (gfCritSects) {
			dwWaitResult = WaitForSingleObject(hMutex, INFINITE);
			switch(dwWaitResult) {
				case WAIT_OBJECT_0:
					MoveCar(carNum);
					if (isWinner(carNum)) {
						MessageBox(NULL, szCarName[carNum], TEXT("WINNER"), MB_OK);
						InvalidateRect(ghWndMain, NULL, TRUE);
						return 0;
					}
					Sleep(3);
					ReleaseMutex(hMutex);
					break;

				case WAIT_ABANDONED:
					break;
			}
		}
		else {
			MoveCar(carNum);
			if (isWinner(carNum)) {
				MessageBox(NULL, szCarName[carNum], TEXT("WINNER"), MB_OK);
				InvalidateRect(ghWndMain, NULL, TRUE);
				return 0;
			}
			Sleep(3);
		}

	}
	return 0;
}

/*
	FUNCTION: isWinner(HWND, int)

	PURPOSE: Checks to see if a button is across the centre of the screen

	PARAMETERS:
		carNum	- The car's array position

	RETURNS:
		TRUE	- If the car won
		FALSE	- If the car hasn't won yet

*/
BOOL isWinner(int carNum) {
	RECT rcClient;

	GetClientRect(ghWndMain, &rcClient);

	if (ptBttn[carNum].x > (rcClient.right / 2)) {
		fWinner = TRUE;
		return TRUE;
	}
	return FALSE;
}