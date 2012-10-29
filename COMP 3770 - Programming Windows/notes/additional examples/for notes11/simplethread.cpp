#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>

DWORD WINAPI Thread(PVOID pVoid);
DWORD id, id2;
HANDLE h1,h2;
LPCSTR name1 = "One";
LPCSTR name2 = "Two";


int _tmain(int argc, _TCHAR* argv[])
{
	CreateThread(NULL,0,Thread,NULL,0,&id);
	printf("Thread1 is called %d\n", id);
	CreateThread(NULL,0,Thread,NULL,0,&id);
	printf("Thread2 is called %d\n", id);
	Sleep(0);
	_getch();
	return 0;
}

DWORD WINAPI Thread(PVOID pVoid){
	for(int i=0;i<9; i++){
		for(int j=0;j<9999;j++){
		}
		printf("Hi my name is %d and my i=%d\n", GetCurrentThreadId(), i);

	}
	return 0;
}