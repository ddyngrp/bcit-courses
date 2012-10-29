/*
 * Numbers.c  - Modified for priority level demo.
 *
 *
 * Starts five threads and gives visible feedback
 * of these threads running by printing a number
 * passed in from the primary thread.
 *
 * Note: There is no synchronization so the output is not
 *  		predictable.
 *
 * Thread 2 is first created using the CREATE_SUSPENDED flag.
 * Then Thread 2 is given the THREAD_PRIORITY_LOWEST level.
 * Note that the output directed to a file will look quite different
 * from the output produced on the screen (most of the time!).
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
    HANDLE hThrd;
    DWORD threadId;
    int i;
    
    for (i=0; i<5; i++)
    {
        if (i != 2)
        	hThrd = CreateThread(NULL, 0, ThreadFunc, (LPVOID)i, 0, &threadId );
        else
        {
         	hThrd = CreateThread(NULL, 0, ThreadFunc, (LPVOID)i,
            	CREATE_SUSPENDED, &threadId );
        		SetThreadPriority (hThrd, THREAD_PRIORITY_LOWEST);
            ResumeThread (hThrd);
        }
        if (hThrd)
        {
            printf("Thread launched %d\n", i);
            CloseHandle(hThrd);
        }
    }
    // Wait for the threads to complete.
    // We'll see a better way of doing this later.
    Sleep(2000);

    return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
    int i;
    for (i=0;i<10;i++)
	    printf("%d%d%d%d%d%d%d%d\n",n,n,n,n,n,n,n,n);
    return 0;
}
