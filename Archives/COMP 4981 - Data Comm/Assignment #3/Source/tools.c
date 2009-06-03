/*------------------------------------------------------------------------------
-- SOURCE FILE:	client.c - Checks the format of an IP address
-- 
-- PROGRAM:     chat
-- 
-- FUNCTIONS:   *get_in_addr(struct sockaddr *sa)
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- NOTES: This checks the format of IP addresses.
--
------------------------------------------------------------------------------*/

#include "tools.h"

/*------------------------------------------------------------------------------
-- FUNCTION:    *get_in_addr
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- INTERFACE:   *get_in_addr(struct sockaddr *sa)
--                   sa: the structure of the socket address
-- 
-- RETURNS: sockaddr_in: IPv4 address structure.
--          sockaddr_in6: IPv6 address structure
-- 
-- NOTES: This function checks whether an address is in IPv4 or IPv6 format
--        and returns the appropriate structure.
--		  
------------------------------------------------------------------------------*/
void *get_in_addr(struct sockaddr *sa) {
	/* Check if the address is IPv4 */
	if (sa->sa_family == AF_INET) {
		/* Return the IPv4 socket address */
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	/* Return the IPv6 socket address */
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

