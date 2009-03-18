#include "tools.h"

/* Get sockaddr for IPv4 or IPv6 */
void *get_in_addr(struct sockaddr *sa) {
	/* Check if the address is IPv4 */
	if (sa->sa_family == AF_INET) {
		/* Return the IPv4 socket address */
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	/* Return the IPv6 socket address */
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

