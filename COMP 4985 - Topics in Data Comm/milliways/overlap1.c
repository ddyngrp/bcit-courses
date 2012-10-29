void main(void)
{
	WSABUF DataBuf;
	DWORD EventTotal 0;
	WSAEVENT EventArray[WSA_MAXIMUM_WAIT_EVENTS];
	WSAOVERLAPPED AcceptOverlapped;
	SOCKET ListenSocket, AcceptSocket;

	// Step 1: Start Winsock and set up a listening socket


	//Step 2: Accept an inbound connection
	AcceptSocket = accept(ListenSocket, NULL, NULL);

	//Step 3: Set up an overlapped structure
	EventArray[EventTotal] = WSACreateEvent();
	
	ZeroMemory(&AcceptOverlapped, sizeof(WSAOVERLAPPED));
	AcceptOverlapped.hEvent = EventArray[EventTotal];

	DataBuf.len = DATA_BUFSIZE:
	DataBuf.buf = buffer;

	EventTotal++;

	//Step 4: Post a WSARecv request to begin receiving data on the socket
	WSARecv(
		AcceptSocket, 
		&DataBuf, 
		1, 
		&RecvBytes,
		&Flags, 
		&AcceptOverlapped, 
		NULL
	);

	//Process overlapped receives on the socket.
	while(TRUE)
	{
		//Step 5: Wait for the overlapped I/O call to complete 
		Index = WSAWaitForMultipleEvents(
			EventTotal,
			EventArray, 
			FALSE, 
			WSA-INFINITE, 
			FALSE
		);

		// Index should be 0 because we have only one event handle in EventArray

		// Step 6: Reset the signaled event 
		WSAResetEvent(EventArray[Index - WSA_WAIT_EVENT_0]);

		// Step 7: Determine the status of the overlapped request
		WSAGetOverlappedResult(
			AcceptSocket,
			&AcceptOverlapped, 
			&BytesTransferred,
			FALSE, 
			&Flags
		);

		// First check to see whether the peer has closed the connection, 
		// and if so, close the socket

		if (BytesTransferred == 0)
		{
			printf("Closing socket %d\n", AcceptSocket);
			closesocket(AcceptSocket);
			WSACloseEvent(EventArray[Index WSA_WAIT_EVENT_0]); 
			return;
		}

		// Do something with the received data.
		// DataBuf contains the received data.


		// Step 8: Post another WSARecv() request on the socket

		Flags = 0;
		ZeroMemory(&AcceptOverlapped, sizeof(WSAOVERLAPPED));
		AcceptOverlapped.hEvent = EventArray[Index - WSA_WAIT_EVENT_0];

		DataBuf.len = DATA-BUFSIZE;
		DataBuf.buf = Buffer;

		WSARecv(AcceptSocket, 
			&DataBuf, 
			1,
			&RecvBytes, 
			&Flags, 
			&AcceptOverlapped,
			NULL
		);
	}
}