#include <winsock2.h>
#include <errno.h>
#include <stdio.h>
#include <windows.h>

#define PORT	7000	/* Default port */
#define BUFSIZE	8820	/* 0.20 seconds of audio */

int main(int argc, char* argv[]) {
	HANDLE	hFile;

	/* TCP connection related variables */
	int		client_len, port = PORT, n;
	SOCKET	sd, new_sd;
	struct	sockaddr_in server, client;
	WSADATA	WSAData;
	WORD	wVersionRequested;
	char	buffer[BUFSIZE]; /* intermediate buffer for reading */
	DWORD totalRead = 0;


	char * fileName = "Z:\\ironix\\Downloads\\Ensemble.wav"; /* Hard-code filename */

	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &WSAData);

	// Create a stream socket
	if ((sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
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

	client_len = sizeof(client); 

	/* Wait for client connection */
	printf("Waiting for client...\n");
	recvfrom(sd, 0, 0, 0, (struct sockaddr *)&client, &client_len);
	printf("Client IP Connected: %s\n", inet_ntoa(client.sin_addr));

	while (TRUE) {
		DWORD readBytes;

		if(!ReadFile(hFile, buffer, sizeof(buffer), &readBytes, NULL)) {
			break;
		}

		totalRead += readBytes;

		printf("read = %d\n", totalRead);

		if(readBytes == 0) {
			sendto(sd, "EOF", sizeof("EOF"), 0, (struct sockaddr *)&client, client_len);
			break;
		}

		if(readBytes < sizeof(buffer)) {
			printf("at end of buffer\n");
			memset(buffer + readBytes, 0, sizeof(buffer) - readBytes);
			printf("after memcpy\n");
		}

		sendto(sd, buffer, BUFSIZE, 0, (struct sockaddr *)&client, client_len);

		/* Wait for signal from client before sending next block */
		recvfrom(sd, 0, 0, 0, (struct sockaddr *)&client, &client_len);
	}

	closesocket(sd);
	WSACleanup();

	system("pause");

	return 0;
}