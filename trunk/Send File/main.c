#include <winsock2.h>
#include <errno.h>
#include <stdio.h>
#include <windows.h>

#define SERVER_TCP_PORT	7000	// Default port
#define BUFSIZE			1024	//Buffer length

int main(int argc, char* argv[]) {
	HANDLE hFile;
	int	client_len, port = SERVER_TCP_PORT;
	SOCKET sd, new_sd;
	struct	sockaddr_in server, client;
	WSADATA WSAData;
	WORD wVersionRequested;
	char			buffer[BUFSIZE]; /* intermediate buffer for reading */

	char * fileName = "Z:\\ironix\\Downloads\\Ensemble.wav"; /* Hard-code filename */

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &WSAData);

	// Create a stream socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror ("Can't create a socket");
		exit(1);
	}

	/**
	 * try and open the file
	 */
	if((hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE) {
			fprintf(stderr, "%s: unable to open file '%s'\n", argv[0], argv[1]);
			system("pause");
			ExitProcess(1);
	}

	// Initialize and set up the address structure
	memset((char *)&server, 0, sizeof(struct sockaddr_in)); 
	server.sin_family = AF_INET;
	server.sin_port = htons(port); 
	server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

	// Bind an address to the socket
	if (bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		perror("Can't bind name to socket");
		exit(1);
	}

	// Listen for connections
	// queue up to 1 connect requests
	listen(sd, 1);

	client_len = sizeof(client); 

	if ((new_sd = accept (sd, (struct sockaddr *)&client, &client_len)) == -1) {
		fprintf(stderr, "Can't accept client\n"); 
		exit(1);
	}

	printf(" Remote Address:  %s\n", inet_ntoa(client.sin_addr));

	while (TRUE) {
		DWORD readBytes;

		if(!ReadFile(hFile, buffer, sizeof(buffer), &readBytes, NULL)) {
			closesocket(new_sd);
			break;
		}

		if(readBytes == 0) {
			closesocket(new_sd);
			break;
		}

		if(readBytes < sizeof(buffer)) {
			printf("at end of buffer\n");
			memset(buffer + readBytes, 0, sizeof(buffer) - readBytes);
			printf("after memcpy\n");
		}

		send(new_sd, buffer, BUFSIZE, 0);
	}

	closesocket(sd);
	WSACleanup();

	system("pause");

	return 0;
}