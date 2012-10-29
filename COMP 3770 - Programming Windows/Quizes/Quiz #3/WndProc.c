
#include "WndProc.h"

LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC		hdc;
	static POINT point[10];
	static int iCount=0;
	static RECT rect;

	switch (message){
		case WM_CREATE:
			point[0].x = point[0].y = 50;
			point[1].x = 50;
			point[1].y = 300;
			point[2].x = 300; 
			point[2].y = 500;
			point[3].x = 400;
			point[3].y = 200;
			point[4].x = 500;
			point[4].y = 0;
			iCount=5;
			rect.left = 300;
			rect.top = 50;
			rect.bottom = rect.right = 600;
			return 0;

		case WM_SIZE:
			hdc = GetDC(hwnd);
			SelectObject(hdc,CreateSolidBrush(RGB(255,0,0)));
			Rectangle(hdc,0,0,LOWORD(lParam),HIWORD(lParam));
			ReleaseDC(hwnd,hdc);
			return 0;



		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}