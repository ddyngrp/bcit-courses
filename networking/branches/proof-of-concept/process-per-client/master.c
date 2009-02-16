#include "master.h"
#include "client.h"
#include "server.h"

char * srv_status = "\033[31m(stopped)";

int main(void) {
	master_menu_print(0);
	master_menu();

	return 0;
}

void master_menu() {
	int c;
	int smenu = 0;

	while ((c = getchar())) {
		switch (c) {
			case '1': // Run as Server
				smenu = 1;

				while ((c = getchar()) && smenu) {
					switch (c) {
						case '1': // Set Server Port
							break;
						
						case '2': // Start Server
							toggle_srv_status(1);
							break;

						case '3': // Stop Server
							toggle_srv_status(0);
							break;

						case '4': // Exit
							// Stop the server and disconnect clients
							toggle_srv_status(0);
							smenu = 0;
							master_menu_print(0);
							break;

						default:
							master_menu_print(1);
							break;
					}
				}
				break;

			case '2': // Start Client
				// Run client function (not a new process)
				client_menu();
				break;

			case '3': // Exit
				// Stop the server and disconnect clients
				exit(0);
				break;

			default:
				master_menu_print(0);
				break;
		}
	}
}

void master_menu_print(int submenu) {
	if (submenu) {
		system("clear");
		printf("\033[1mRun as Server Menu: %s\r\n\033[0m", srv_status);
		printf(" 1. Set Server Port\r\n");
		printf(" 2. Start Server\r\n");
		printf(" 3. Stop Server\r\n");
		printf(" 4. Exit\r\n");
		printf("> ");
	}
	else {
		system("clear");
		printf("\033[1mMaster Menu:\033[0m\r\n");
		printf(" 1. Run as Server\r\n");
		printf(" 2. Start Client\r\n");
		printf(" 3. Exit\r\n");
		printf("> ");
	}
}

void toggle_srv_status(int status) {
	if (status) {
		srv_status = "\033[31m(running)";
	}
	else {
		srv_status = "\033[31m(stopped)";
	}
}
