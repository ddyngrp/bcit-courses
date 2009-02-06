#include "master.h"
#include "client.h"

char * conn_status = "\033[31m(disconnected)";

void client_menu() {
	int c, cmenu = 1;

	while ((c = getchar()) && cmenu == 1) {
		switch (c) {
			case '1': // Set Server IP / Port
				break;

			case '2': // Connect to Server
				toggle_conn_status(1);
				break;

			case '3': // Send Test Data
				break;

			case '4': // Disconnect
				toggle_conn_status(0);
				break;

			case '5': // Exit
				toggle_conn_status(1);
				master_menu_print(0);
				cmenu = 0;
				break;

			default:
				client_menu_print();
				break;
		}
	}
}

void client_menu_print() {
	system("clear");
	printf("\033[1mRun as Client Menu: %s\r\n\033[0m", conn_status);
	printf(" 1. Set Server IP Address / Port\r\n");
	printf(" 2. Connect to Server\r\n");
	printf(" 3. Send Test Data\r\n");
	printf(" 4. Disconnect\r\n");
	printf(" 5. Exit\r\n");
	printf("> ");
}

void toggle_conn_status(int status) {
	if (status) {
		conn_status = "\033[31m(connected)";
	}
	else {
		conn_status = "\033[31m(disconnected)";
	}
}
