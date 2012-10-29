#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
//#include <pcap.h>
#include <sys/prctl.h>

#define MASK "hello"
int main(int argc, char *argv[])
{
	/* mask the process name */
	memset(argv[0], 0, strlen(argv[0]));	
	strcpy(argv[0], MASK);
	prctl(PR_SET_NAME, MASK, 0, 0);

	/* change the UID/GID to 0 (raise privs) */
	setuid(0);
	setgid(0);
	/* setup packet capturing */
	/* ... */
	/* capture and pass packets to handler */
	/* ... */
	sleep(100);
}

