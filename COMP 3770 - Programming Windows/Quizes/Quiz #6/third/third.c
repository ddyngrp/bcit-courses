#include <windows.h>
#include <stdio.h>
#include <conio.h>

int main()
{
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("third"));
	int i = 10;

	for (; i > 0; i--) {
		printf("Count=%d\n", i);
		Sleep(1000);
	}
	SetEvent(hEvent);

	return 0;
}