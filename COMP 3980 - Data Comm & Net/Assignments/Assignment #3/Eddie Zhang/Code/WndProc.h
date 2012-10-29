#include <windows.h>
#include <windowsx.h>


#include "resource.h"

HINSTANCE hInstance;

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;


     switch (message)
     {
     case WM_CREATE:

		  initializeToolBar(hwnd);
		 

          return 0 ;

     case WM_PAINT:
          hdc = BeginPaint (hwnd, &ps) ;

          printTag(hwnd,TEXT("Something to display"));
          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}

void initializeToolBar(HWND hwnd)
{
	HWND hTool;
	hTool = CreateWindowEx(0,TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0,0,0,0,
					hwnd,(HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);

	CreateWindow ("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
   						12, 50, 200, 180, hwnd, (HMENU)ID_LISTBOX,
                     hInstance, NULL);


	


}

void printTag(HWND hwnd, TCHAR* tag)
{
	//PAINTSTRUCT ps;
	TEXTMETRIC tm;
	int cxChar, cxCaps, cyChar;
	
	HDC hdc = GetDC(hwnd);
	GetTextMetrics(hdc, &tm);

	cxChar = tm.tmAveCharWidth;
	cxCaps = (tm.tmPitchAndFamily&1?3:2)*cxChar/2;
	cyChar = tm.tmHeight + tm.tmExternalLeading;
	SetTextAlign(hdc,TA_RIGHT|TA_TOP);



	TextOut(hdc,TYPESTART,50,TEXT("Type"),sizeof((BYTE*)TEXT("Type")));

	//TextOut(hdc,IDSTART,50,tag,20);
	//TextOut(hdc,DATASTART,50,tag,20);

	
	ReleaseDC(hwnd,hdc);


}

