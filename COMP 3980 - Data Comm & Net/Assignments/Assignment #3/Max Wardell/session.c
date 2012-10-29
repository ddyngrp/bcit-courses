// Program WinMenu.cpp
#include "cases.h"
#include "functions.h"

char str[80] = "";

#pragma warning(disable: 4096)

/*int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow)
*Purpose: The start of execution; the entry point to the program.
*Arg 1 - Handle to the process (running program).
*Arg 2 - Handle to the previous process (Always NULL in Win32).
*Arg 3 - The command line arguments as a single string (not including the program name).
*Arg 4 - Decides whether the window will be normal, maximized or minimized.
*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
 						  LPSTR lspszCmdParam, int nCmdShow) {
	RegisterInstance(hInst);
	MakeWindow(nCmdShow, hInst);
	WinMessageLoop();
}
