/* Borland C++, Version 5.01 */

/* This example of a multithreaded server process has a main thread that
 * loops continuously, creating a pipe instance and waiting for a client
 * process to connect. When a client process connects, the server process
 *creates a thread to service that client and the loop starts over.
*/


#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <windows.h> 
 
VOID InstanceThread(LPVOID); 
VOID GetAnswerToRequest(LPTSTR, LPTSTR, LPDWORD); 
 
int xx = 0; 
 
DWORD main(VOID) { 
  BOOL fConnected; 
  DWORD dwThreadId; 
  HANDLE hPipe, hThread; 
  LPTSTR lpszPipename = "\\\\.\\pipe\\mynamedpipe"; 
 
  /* 
   * The main loop creates an instance of the named pipe and 
   * then waits for a client to connect to it. When the client 

   * connects, a thread is created to handle communications 
   * with that client, and the loop is repeated. 
   */ 
 
  for (;;) { 
      hPipe = CreateNamedPipe( 
          lpszPipename,             /* pipe name          */ 
          PIPE_ACCESS_DUPLEX,       /* read/write access  */ 
          PIPE_TYPE_MESSAGE |       /* message type pipe  */ 
          PIPE_READMODE_MESSAGE |   /* message-read mode  */ 
          PIPE_WAIT,                /* blocking mode      */ 

          PIPE_UNLIMITED_INSTANCES, /* max. instances     */ 
          BUFSIZE,                  /* output buffer size */ 
          BUFSIZE,                  /* input buffer size  */ 
          PIPE_TIMEOUT,             /* client time-out    */ 
          NULL);                    /* no security attr.  */ 
      if (hPipe == INVALID_HANDLE_VALUE) 
          MyErrExit("CreatePipe"); 
 
      /* 
       * Wait for the client to connect; if it succeeds, 
       * the function returns TRUE. If the function returns FALSE, 

       * GetLastError returns ERROR_PIPE_CONNECTED. 
       */ 
 
      fConnected = ConnectNamedPipe(hPipe, NULL) ? 
                   TRUE : 
                   (GetLastError() == ERROR_PIPE_CONNECTED); 
 
      if (fConnected) { 
 
          /* Create a thread for this client. */ 
 
          hThread = CreateThread( 
              NULL,           /* no security attr.    */ 
              0,              /* default stack size   */ 
              (LPTHREAD_START_ROUTINE) InstanceThread, 

              (LPVOID) hPipe, /* thread parameter     */ 
              0,              /* not suspended        */ 
              &dwThreadId);   /* returns thread ID    */ 
          if (hThread == INVALID_HANDLE_VALUE) 
              MyErrExit("CreateThread"); 
 
      } else 
 
         /* The client could not connect, so close the pipe. */ 
 
         CloseHandle(hPipe); 
 
  } 
 
  return 1; 
} 
 
VOID InstanceThread(LPVOID lpvParam) { 
  CHAR chRequest[BUFSIZE]; 

  CHAR chReply[BUFSIZE]; 
  DWORD cbBytesRead, cbReplyBytes, cbWritten; 
  BOOL fSuccess; 
  HANDLE hPipe; 
 
 
  /* The thread's parameter is a handle to a pipe instance. */ 
 
  hPipe = (HANDLE) lpvParam; 
 
  while (1) { 
 
      /* Read client requests from the pipe. */ 
 
      fSuccess = ReadFile( 
          hPipe,        /* handle to pipe         */ 
          chRequest,    /* buffer to receive data */ 
          BUFSIZE,      /* size of buffer         */ 

          &cbBytesRead, /* number of bytes read   */ 
          NULL);        /* not overlapped I/O     */ 
      if (! fSuccess || cbBytesRead == 0) 
          break; 
      GetAnswerToRequest(chRequest, chReply, &cbReplyBytes); 
 
      /* Write the reply to the pipe. */ 
 
      fSuccess = WriteFile( 
         hPipe,        /* handle to pipe           */ 
         chReply,      /* buffer to write from     */ 
         cbReplyBytes, /* number of bytes to write */ 

         &cbWritten,   /* number of bytes written  */ 
         NULL);        /* not overlapped I/O       */ 
      if (! fSuccess || cbReplyBytes != cbWritten) break; 
  } 
 
  /* 
   * Flush the pipe to allow the client to read the pipe's contents 
   * before disconnecting. Then disconnect the pipe, and close the 
   * handle to this pipe instance. 
   */ 
 
  FlushFileBuffers(hPipe); 
  DisconnectNamedPipe(hPipe); 
  CloseHandle(hPipe); 
} 
