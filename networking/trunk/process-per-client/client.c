#include "master.h"
#include "client.h"

char * conn_status = "\033[31m(disconnected)";

void client_menu() {
	int c;

	while ((c = getchar())) {
		switch (c) {
			case '1':
				break;

			case '2':
				break;

			case '3':
				break;

			case '4':
				break;

			case '5':
				exit(0);
				break;

			default:
				print_client_menu();
				break;
		}
	}
}

void print_client_menu() {
	system("clear");
	printf("\033[1mRun as Client Menu: %s\r\n\033[0m", conn_status);
	printf(" 1. Set Server IP Address / Port\r\n");
	printf(" 2. Connect to Server\r\n");
	printf(" 3. Send Test Data\r\n");
	printf(" 4. Disconnect\r\n");
	printf(" 5. Exit\r\n");
	printf("> ");
}
