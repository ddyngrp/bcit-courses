/*
	MODULE: main.cpp

	PURPOSE: Manages window creation and message processing

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
 */

#include "s_main.h"
#include "s_resource.h"
#include "s_winMaker.h"
#include "s_winEx.h"
#include <new.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, char * cmdParam, int cmdShow) {
    _set_new_handler (&NewHandler);

    try {
        // Create top window class
        TopWinClass topWinClass(ID_MAIN, hInst, MainWndProc);

        // Is there a running instance of this program?
        HWND hWndOther = topWinClass.GetRunningWindow();
        if (hWndOther != 0) {
            ::SetForegroundWindow(hWndOther);
			if (::IsIconic(hWndOther)) {
                ::ShowWindow(hWndOther, SW_RESTORE);
			}
            return 0;
        }
        topWinClass.Register();

        // Create top window
        ResString caption(hInst, ID_CAPTION);
        TopWinMaker topWin(topWinClass, caption);
        topWin.Create();
        topWin.Show(cmdShow);

        // The main message loop
        MSG  msg;
        int status;
        while ((status = ::GetMessage(&msg, 0, 0, 0)) != 0) {
			if (status == -1) {
                return -1;
			}
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }

        return (int)msg.wParam;
    }
    catch (WinException e) {
        char buf[50];
        wsprintf(buf, "%s, Error %d", e.GetMessage(), e.GetError());
        ::MessageBox(0, buf, "Exception", MB_ICONEXCLAMATION | MB_OK);
    }
    catch (...) {
        ::MessageBox(0, "Unknown", "Exception", MB_ICONEXCLAMATION | MB_OK);
    }

    return 0;
}            

int NewHandler(size_t size) {
    throw WinException("Out of memory");
    return 0;
}

