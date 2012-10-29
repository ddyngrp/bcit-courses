SOCKET AcceptSocket;
WSABUF DataBuf;

void main(void)
{
	WSAOVERLAPPED Overlapped;

	// Step 1: Start Winsock, and set up a listening socket

	// Step 2: Accept a new connection
	AcceptSocket = accept(ListenSocket, NULL, NULL);

	// Step 3: Now that we have an accepted socket, 
	// start processing I/O using overlapped I/O with a completion routine.  
	// To get the overlapped I/O processing started, 
	// first submit an overlapped WSARecv() request.

	Flags = 0;

	ZeroMemory(&Overlapped, sizeof(WSAOVERLAPPED));

	DataBuf.len = DATA_BUFSIZE;
	DataBuf.buf = Buffer;

	// Step 4: Post an asynchronous WSARecv() request
	// on the socket by specifying the WSAOVERLAPPED structure as a parameter, 
	// and supply the WorkerRoutine function below as the completion routine

	if (WSARecv(AcceptSocket, &DataBuf, 1, &RecvBytes, &Flags, &Overlapped, 
		WorkerRoutine) == SOCKET-ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("WSARecv() failed with error %d\n", WSAGetLastError()); 
			return;
		}
	}

	// Since the WSAWaitForMultipleEvents() API requires waiting on 
	// one or more event objects, we will have to create a dummy 
	// event object.  
	// As an alternative, we can use SleepEx() instead.

	EventArray[0] = WSACreateEvent(); 
	while(TRUE)
	{
		// Step 5: 
		Index = WSAWaitForMultipleEvents(l, EventArray, FALSE, WSA_INFINITE, TRUE);

		// Step 6:
		if (Index == WAIT_IO_COMPLETION)
		{
			// An overlapped request completion routine just completed.  
			// Continue servicing more completion routines.
			break;
		}
		else
		{
			// A bad error occurred--stop processing!  
			// If we were also processing an event object, 
			// this could be an index to the event array.
			return;
		}
	}
}


void CALLBACK WorkerRoutine(DWORD Error, DWORD BytesTransferred, LPWSAOVERLAPPED Overlapped, 
								DWORD InFlags)
{
	DWORD SendBytes, RecvBytes; 
	DWORD Flags;

	if (Error != 0 || BytesTransferred == 0)
	{
		// Either a bad error occurred on the socket or 
		// the socket was closed by a peer 
		closesocket(AcceptSocket); 
		return;
	}

	// At this point, an overlapped WSARecv() request completed successfully.  
	// Now we can retrieve the received data that is contained in the variable DataBuf.  
	// After processing the received data, we need to post another overlapped 
	// WSARecv() or WSASend() request.  
	// For simplicity, we will post another WSARecv() request.

	Flags = 0;
	
	ZeroMemory(&Overlapped, sizeof(WSAOVERLAPPED));

	DataBuf.len = DATA_BUFSIZE;
	DataBuf.buf = Buffer;

	if (WSARecv(AcceptSocket, &DataBuf, 1, &RecvBytes, &Flags, &Overlapped, 
		WorkerRoutine) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("WSARecvo failed with error %d\n", WSAGetLastError());
			return;
		}
	}
}
