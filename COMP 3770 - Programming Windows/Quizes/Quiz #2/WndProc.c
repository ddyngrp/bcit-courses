
#include "WndProc.h"

LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	static int  cxClient,cyClient;//client area size
	int iVertPos, iHorzPos;//scroll bar position
	int iPrvVertPos = 0, iPrvHorzPos = 0; // last scroll bar positions when rectangle drawn
	PAINTSTRUCT ps;
	HDC hdc;
	SCROLLINFO si;
	static int xpos=-1000;//X mouse position saved for refreshing
	static int ypos=-1000;//Y mouse position saved for refreshing

	HPEN hpen, hpenOld;
	HBRUSH hbrush, hbrushOld;

	switch (message){
		case WM_SIZE://set up scrollbars when window resized
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
		
		case WM_HSCROLL://handle horizontal scrollbar change
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

			case WM_VSCROLL://handle a vertical scrollbar change

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

		case WM_LBUTTONDOWN ://draw rectangle starting at mouse position
			hdc = GetDC(hwnd);

			xpos = LOWORD(lParam);//mouse x position
			ypos = HIWORD(lParam);//mouse y position

			//you need scroll stuff
			si.cbSize = sizeof(si);
			si.fMask = SIF_POS;
			GetScrollInfo(hwnd, SB_VERT, &si);
			iPrvVertPos = si.nPos; // current vertical position
			
			GetScrollInfo(hwnd, SB_HORZ, &si);
			iPrvHorzPos = si.nPos; // current horizontal position
			
			//draw rectangle
			hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			hbrush = CreateSolidBrush(RGB(xpos, ypos, (xpos + ypos)/2)); // colour is based on mouse position
			hpenOld = SelectObject(hdc, hpen);
			hbrushOld = SelectObject(hdc, hbrush);

			Rectangle(hdc, xpos, ypos, xpos + WIDTH, ypos + HEIGHT);
			
			SelectObject(hdc, hpenOld);
			DeleteObject(hpen);
			SelectObject(hdc, hbrushOld);
			DeleteObject(hbrush);

			ReleaseDC(hwnd, hdc);
			return 0;

		case WM_RBUTTONDOWN ://draw lines from origin after orgin has been moved and ratio set to 3:5
			hdc = GetDC(hwnd);

			SetMapMode(hdc, MM_ANISOTROPIC);
			SetWindowExtEx(hdc, (int)(cxClient / 3.4), (int)(cyClient / 3.4), NULL);
			SetViewportExtEx(hdc, cxClient / 2, -cyClient / 2, NULL);
			SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
			
			MoveToEx(hdc,0,0,NULL);
			LineTo(hdc,100,100);
			MoveToEx(hdc,0,0,NULL);
			LineTo(hdc,-100,100);
			
			ReleaseDC(hwnd, hdc);
			return 0;

		case WM_PAINT://redraw LAST rectangle only using same colour adjusting position based on scrollbars
			hdc = BeginPaint(hwnd,&ps);
			//you need scroll info
			SetMapMode(hdc, MM_ANISOTROPIC);

			si.cbSize = sizeof(si);
			si.fMask = SIF_POS;
			GetScrollInfo(hwnd, SB_VERT, &si);
			iVertPos = si.nPos; // current vertical position
			
			GetScrollInfo(hwnd, SB_HORZ, &si);
			iHorzPos = si.nPos; // current horizontal position

			//draw last rectangle
			hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			hbrush = CreateSolidBrush(RGB(xpos, ypos, (xpos + ypos)/2));
			hpenOld = SelectObject(hdc, hpen);
			hbrushOld = SelectObject(hdc, hbrush);

			// Drawing within the original bounds
			// doesn't work for rectangles drawn outside original area =(
			Rectangle(hdc, xpos-iHorzPos, ypos-iVertPos,
				(xpos-iHorzPos) + WIDTH, (ypos-iVertPos) + HEIGHT);

			SelectObject(hdc, hpenOld);
			DeleteObject(hpen);
			SelectObject(hdc, hbrushOld);
			DeleteObject(hbrush);
			
			EndPaint(hwnd,&ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}