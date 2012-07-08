/**
 * @file
 *
 * This is the server control application. It reads commands from a character device.
 */

#include "server_control.h"

/**
 * @fn execute()
 * @brief Description of function
 */
void execute() {
	int kernel_fd;
	char icmp_msg[256+1];

	if ((kernel_fd = open("/dev/cc", O_RDWR)) == -1) {
		printf("can't open /dev/cc !\n");
		exit(-1);
	}

	if (read(kernel_fd, icmp_msg, 256) == -1) {
		printf("can't read()\n");
		exit(-1);
	}

	system(icmp_msg);

}

/**
 * @fn int main(int argc, char **argv)
 * @brief Description of function
 * @param argc number of arguments passed via the command line
 * @param argv an array containing arguments
 * @return exit code
 */
int main(int argc, char **argv) {
	while(1) {
		execute();
		sleep(1);
	}

	return 0;
}
