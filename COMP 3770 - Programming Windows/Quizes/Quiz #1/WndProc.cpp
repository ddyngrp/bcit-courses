

LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC		hdc;
	PAINTSTRUCT ps;
	RECT	rect;
	TCHAR string[50];
	va_list pArgList;
	int numW;//holds the number of windows stored in the "counter"

	switch (message){
		case WM_CREATE:
			PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			
			pArgList = (va_list)&numW;
			_vsntprintf(string,sizeof(string)/sizeof(TCHAR), TEXT("number of windows=%d"),pArgList);
			
			GetClientRect(hwnd, &rect);
			DrawText(hdc, string, -1, &rect,
					DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}


}