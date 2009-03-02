/* Master control - Currently this only contains the main() function,
   but in the future it likely deal with more, such as the interface
   functions between networking and game logic.
*/

#include <ctype.h>
#include "client.h"
#include "server.h"

void usage(void);

int main(int argc, char *argv[]) {
	char optstring[] = "c:s";
	int c;

	if (argc == 1 || argc > 4) 
		usage();

	while ((c = getopt(argc, argv, optstring)) != -1) {
		switch (c) {
			case 'c':
				if (argc != 4) {
					fprintf(stderr, "Invalid number of arguments\n");
					usage();
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
					usage();
				}
				else if (isprint(optopt)) {
					fprintf(stderr, "Unknown option `-%c'.\n", optopt);
					usage();
				}
				else {
					fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
					usage();
				}
				break;
			default:
				abort();
		}
	}
	return EXIT_SUCCESS;
}

void usage(void) {
	fprintf(stderr, "Usage: [-s] [-c <ip address> <port>]\n");
	exit(EXIT_FAILURE);
}
