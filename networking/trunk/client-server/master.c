/* Master control - Currently this only contains the main() function,
   but in the future it likely deal with more, such as the interface
   functions between networking and game logic.
*/

#include <ctype.h>
#include "client.h"
#include "server.h"

void help(void);

int main(int argc, char *argv[]) {
	static char optstring[] = "c:s";
	int c;

	if (argc == 1) {
		help();
		return 1;
	}

	while ((c = getopt(argc, argv, optstring)) != -1) {
		switch (c) {
			case 'c':
				if (argc != 4) {
					fprintf(stderr, "Invalid arguments\n");
					help();
				}
				else {
					fprintf(stderr, "Starting client...\n");
					start_client(argv[2], argv[3]);
				}
				break;
			case 's':
				fprintf(stderr, "Starting server...\n");
				start_server();
				break;
			case '?':
				if (optopt == 'c') {
					fprintf(stderr, "Option -%c requires arguments.\n", optopt);
					help();
				}
				else if (isprint(optopt)) {
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
					help();
				}
				else {
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
					help();
				}
				break;
			default:
				abort();
		}
	}

	return 1;
}

void help(void) {
	fprintf(stderr, "Usage: [-s] [-c <ip address> <port>]\n");
}
