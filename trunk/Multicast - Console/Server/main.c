#include <winsock2.h>
#include <errno.h>
#include <stdio.h>
#include <windows.h>

#define PORT	7000	/* Default port */
#define BUFSIZE	44100	/* 1.00 seconds of audio */

#define GROUP	"225.0.0.37"

int main(int argc, char* argv[]) {
	HANDLE	hFile;

	/* UDP connection related variables */
	SOCKET	sd;
	struct	sockaddr_in server;
	WSADATA	WSAData;
	WORD	wVersionRequested;
	char	buffer[BUFSIZE]; /* intermediate buffer for reading */
	DWORD totalRead = 0;


	char * fileName = "C:\\Ensemble.wav"; /* Hard-code filename */

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
			fprintf(stderr, "%s: unable to open file '%s'\n", argv[0], fileName);
			system("pause");
			ExitProcess(1);
	}

	// Initialize and set up the address structure
	memset((char *)&server, 0, sizeof(struct sockaddr_in)); 
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(GROUP); /* the multicast group */
	server.sin_port = htons(PORT); 

	printf("Server ready ");
	system("pause");

	while (TRUE) {
		DWORD readBytes;

		if(!ReadFile(hFile, buffer, sizeof(buffer), &readBytes, NULL)) {
			break;
		}

		totalRead += readBytes;

		printf("read = %d\n", totalRead);

		if(readBytes == 0) {
			sendto(sd, "EOF", sizeof("EOF"), 0, (struct sockaddr *)&server, sizeof(server));
			break;
		}

		if(readBytes < sizeof(buffer)) {
			printf("at end of buffer\n");
			memset(buffer + readBytes, 0, sizeof(buffer) - readBytes);
			printf("after memcpy\n");
		}

		if (sendto(sd, buffer, BUFSIZE, 0, (struct sockaddr *)&server, sizeof(server)) < 0) {
			printf("sendto() error\n");
			system("pause");
			exit(1);
		}

		Sleep(200);

		/* Wait for signal from client before sending next block */
		/* recvfrom(sd, 0, 0, 0, (struct sockaddr *)&client, &client_len); */
	}

	closesocket(sd);
	WSACleanup();

	system("pause");

	return 0;
}