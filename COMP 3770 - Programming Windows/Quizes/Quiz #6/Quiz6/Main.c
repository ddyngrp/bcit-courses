#include <windows.h>		//needed for threading functions
#include <stdio.h>			//needed for printf
#include <conio.h>			//needed for _getch() function

int		getJellybeans();	//controlls access to jellybeans, returns 1 if able to get a jellybean, 0 otherwise
int		jellybeans;			//global store of jellybeans
int		sync=0;
DWORD id, id2;				//hold thread ids

HANDLE hMutex;
DWORD hEvent;

DWORD WINAPI Thread(PVOID pvoid);//my thread function

/*
Quiz6
Run the 3 programs provided in all possible orders and review results.
Programs 2 & 3 are simple counters displaying thier results approx. every
1s
Program 1 waits for EITHER program 2 OR program 3 to signal it before continuing.
Program 1 then spawns two threads which attempt to take Jellybeans from
a jar. There is only 1 jellybean.
If the user selects 'y' the threads are blocked when attempting to access
the jar if another thread is currently accessing the jar
Default is the threads can access the jar at the same time.
Note: Program 1 should be run from the Command Prompt!! (to allow users to enter 'y')
Function getJellybeans() is called by both threads.
Your program MUST cause a race condition (as seen in the example).
For synchronization you may NOT use Critical Sections or Single Variable
protection functions (must use Events and Mutexes).
Display must be the same as the examples except your full name MUST be displayed
as the first thing printed in each program/process.

Use GetCurrentThreadId() to get the ID of the current thread.

Marking Guide

Function					Mark
P1 Waiting to start				2
P2 & P3 Waiting to finish			2
Race condition occurs				2
Race condition prevented			2 (previous function must be present for any mark here)
Output correctly displayed			2

main() 
argc - number of arguments entered at the command prompt
argv[] - each argument passed in
returns 0 meaning success every time no matter what!!!
creates the critical section (lock) and launches the two threads
*/
int main(int argc, char* argv[])
{
	BOOL loop = TRUE;
	HANDLE hEvents[2];
	DWORD dwEvent;

	hEvents[0] = CreateEvent(NULL, FALSE, FALSE, TEXT("second"));
	hEvents[1] = CreateEvent(NULL, FALSE, FALSE, TEXT("third"));

	dwEvent = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);

	if (argc < 2) {
		sync = 0;
	}
	else {
		sync = (*argv[1] == 'y' ? 1 : 0);
	}

	while (loop) {
		switch (dwEvent) {
			case WAIT_OBJECT_0 + 0:
				printf("Second Program Signaled!\n");
				loop = FALSE;
				break;
			case WAIT_OBJECT_0 + 1:
				printf("Third Program Signaled!\n");
				loop = FALSE;
				break;
			case WAIT_ABANDONED:
				loop = FALSE;
				break;
		}
	}

	CreateThread(NULL,0,Thread,NULL,0,&id);//launch thread - will not actually be executed yet
	CreateThread(NULL,0,Thread,NULL,0,&id2);//launch 2nd thread - again not actually running yet*
	Sleep(2000);//causes the main thread to sleep for 2 seconds - allowing another thread to run
	_getch();//wait for a key press - necessary if you run on ".net" instead of VS 6.0

	//CloseHandle(hMutex);
	return 0;//what could go wrong?? :-)  Well lots actually, thread may not be created, ....
}

//function to access the global jellybean jar!!!
//returns 1 if successful at getting a jellybean, 0 otherwise
int getJellybeans() {
	int result=0;//assume will fail

	if (jellybeans >= 1) {
		printf("Found enough Jellybeans!\n");
		jellybeans = jellybeans - 1;//grab your jellybeans - WHAT NO BLUE JELLYBEANS! :-(
		result = 1;//we were successful at getting our meal of jellybeans
	}
	printf("number of beans left=%d\n",jellybeans);//tell everyone how many beans are left
	return result;//return if successful or not
}

//thread function - sole task is to get jellybeans then die (short but SWEET life :-)
//Both threads call the same thread function.
DWORD WINAPI Thread(PVOID pvoid) {
	jellybeans = GetCurrentThreadId();
	getJellybeans();
	return 0;
}