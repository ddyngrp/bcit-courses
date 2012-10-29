
#include "WndProc.h"

LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	static int  cxClient,cyClient;
	int iVertPos, iHorzPos;//IMPORTANT VARIABLES
	PAINTSTRUCT ps;
	HDC hdc;
	SCROLLINFO si;
	static int xpos=-1000;
	static int ypos=-1000;
	int scrollx, scrolly;

	switch (message){
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);

			si.cbSize = sizeof(si);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = 0;
			si.nMax = 2000;
			si.nPage = cyClient;
			SetScrollInfo(hwnd, SB_VERT, &si, TRUE);

			si.cbSize = sizeof(si);
			si.fMask = SIF_RANGE | SIF_PAGE;
			si.nMin = 0;
			si.nMax = 2000;
			si.nPage = cxClient;
			SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
			return 0;
		
		case WM_HSCROLL:
			si.cbSize = sizeof(si);
			si.fMask = SIF_ALL;

			GetScrollInfo(hwnd, SB_HORZ, &si);
			iHorzPos = si.nPos;

			switch (LOWORD(wParam))
			{
			case SB_LINELEFT:
				si.nPos -=1;
				break;

			case SB_LINERIGHT:
				si.nPos += 1;
				break;

			case SB_PAGELEFT:
				si.nPos -= si.nPage;
				break;

			case SB_PAGERIGHT:
				si.nPos += si.nPage;
				break;

			case SB_THUMBTRACK:
				si.nPos = si.nTrackPos;
				break;

			default:
				break;
			}

			si.fMask = SIF_POS;
			SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
			GetScrollInfo(hwnd, SB_HORZ, &si);

			if (si.nPos != iHorzPos)
			{
				ScrollWindow(hwnd, iHorzPos - si.nPos, 0, NULL, NULL);
				UpdateWindow(hwnd);
			}
			return 0;

			case WM_VSCROLL:

				si.cbSize = sizeof(si);
				si.fMask = SIF_ALL;
				GetScrollInfo(hwnd, SB_VERT, &si);
				iVertPos = si.nPos;

				switch(LOWORD(wParam)){
				case SB_TOP:
					si.nPos = si.nMin;
					break;

				case SB_BOTTOM:
					si.nPos = si.nMax;
					break;

				case SB_LINEUP:
					si.nPos--;
					break;

				case SB_LINEDOWN:
					si.nPos++;
					break;

				case SB_PAGEUP:
					si.nPos -= si.nPage;
					break;

				case SB_PAGEDOWN:
					si.nPos += si.nPage;
					break;

				case SB_THUMBTRACK:
					si.nPos = si.nTrackPos;
					break;

				default:
					break;
				}

				si.fMask = SIF_POS;
				SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
				GetScrollInfo(hwnd, SB_VERT, &si);

				if (si.nPos != iVertPos){
					ScrollWindow(hwnd, 0, iVertPos - si.nPos, NULL, NULL);
					UpdateWindow(hwnd);
				}
				return 0;

		case WM_LBUTTONDOWN :
			hdc = GetDC(hwnd);
			xpos = LOWORD(lParam);
			ypos = HIWORD(lParam);
			si.fMask = SIF_POS;
			si.cbSize = sizeof(si);
			GetScrollInfo(hwnd,SB_VERT,&si);
			scrolly = si.nPos;
			GetScrollInfo(hwnd,SB_HORZ,&si);
			scrollx = si.nPos;
			
			SelectObject(hdc,CreateSolidBrush(RGB((xpos+ypos+scrollx+scrolly)%255,(scrollx+xpos)%255,(scrolly+ypos)%255)));
			SelectObject(hdc,CreatePen(0,1,RGB(255,0,0)));
			Rectangle(hdc,xpos,ypos,xpos+WIDTH,ypos+HEIGHT);
			xpos += scrollx;
			ypos += scrolly;
			ReleaseDC(hwnd,hdc);
			return 0;

			case WM_RBUTTONDOWN :
				hdc = GetDC(hwnd);
				SetMapMode(hdc,MM_ANISOTROPIC);
				SetViewportOrgEx(hdc,cxClient/2, cyClient/2,NULL);
				SetWindowExtEx(hdc,3,3,NULL);
				SetViewportExtEx(hdc,5,-5,NULL);
				MoveToEx(hdc,0,0,NULL);
				LineTo(hdc,100,100);
				MoveToEx(hdc,0,0,NULL);
				LineTo(hdc,-100,100);
				ReleaseDC(hwnd,hdc);
				return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd,&ps);
			si.fMask = SIF_POS;
			si.cbSize = sizeof(si);
			GetScrollInfo(hwnd,SB_VERT,&si);
			scrolly = si.nPos;
			GetScrollInfo(hwnd,SB_HORZ,&si);
			scrollx = si.nPos;
			SelectObject(hdc,CreateSolidBrush(RGB((xpos+ypos)%255,xpos%255,ypos%255)));
			SelectObject(hdc,CreatePen(0,1,RGB(255,0,0)));

			Rectangle(hdc,xpos-scrollx,ypos-scrolly,xpos+WIDTH-scrollx,ypos+HEIGHT-scrolly);
			EndPaint(hwnd,&ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

