/*------------------------------------------------------------------------------
--	SOURCE FILE:	ifinfo.c -   Main program to list the network interface
--										 information on a system.
--
--	PROGRAM:			ifinfo.exe
--
--	FUNCTIONS:		Berkeley Socket API
--						Get_ifi_info
--                get_ifi_info
--						free_ifi_info
--
--	DATE:				March 9, 2001
--
--	REVISIONS:		(Date and Description)
--
--	DESIGNERS:     Based on the examples by Stevens (Ch. 16)
--						Modified and redesigned: Aman Abdulla
--
--	PROGRAMMERS:	Aman Abdulla
--
--	NOTES:
--	This program will call functions from getinfo.c to obtain detailed
--	information on all network interfaces installed on a system. The program
-- calls get_ifi_info once and steps through all the ifi_info strutures
-- returned.
------------------------------------------------------------------------------*/
#include <sys/socket.h>
#include	"ictl.h"

int main (int argc, char **argv)
{
	struct ifi_info	*ifi, *ifihead;
	struct sockaddr	*sa;
	u_char	*ptr;
	int i, family, doaliases;

	if (argc != 2)
	{
		printf ("usage: ictl  <doaliases>\n");
		exit(1);
	}
   printf("\n");
	family = AF_INET;
	doaliases = atoi(argv[1]);

	for (ifihead = ifi = Get_ifi_info(family, doaliases); ifi != NULL; ifi = ifi->ifi_next)
	{
		printf("%s: < ", ifi->ifi_name);

		if (ifi->ifi_flags & IFF_UP)
                          		printf("UP ");
		if (ifi->ifi_flags & IFF_BROADCAST)
			printf("BCAST ");
		if (ifi->ifi_flags & IFF_MULTICAST)
			printf("MCAST ");
		if (ifi->ifi_flags & IFF_LOOPBACK)
			printf("LOOP ");
		if (ifi->ifi_flags & IFF_POINTOPOINT)
			printf("P2P ");
		printf(">\n");

		ifi->ifi_hlen = 6;
		if ( (i = ifi->ifi_hlen) > 0)
		{
			printf("  MAC Address: ");
			ptr = (u_char *)ifi->ifi_hwaddr;
			//printf ("%x:%x:%x:%x:%x:%x\n", *(ptr +2), *(ptr +3), *(ptr +4),
         //	*(ptr +5), *(ptr + 6), *(ptr + 7));
			ptr++;
			do
			{
				printf("%s%x", (i == ifi->ifi_hlen) ? "  " : ":", *++ptr);
			}
			while (--i > 0);
				printf("\n");
		}
      if ( (sa = ifi->ifi_addr) != NULL)
			printf("  IP Address: %s\n", Sock_ntop_host(sa, sizeof(*sa)));
		if ( (sa = ifi->ifi_brdaddr) != NULL)
			printf("  Broadcast Address: %s\n", Sock_ntop_host(sa, sizeof(*sa)));
		if ( (sa = ifi->ifi_dstaddr) != NULL)
			printf("  Point-to-Point Address: %s\n", Sock_ntop_host(sa, sizeof(*sa)));
		printf("\n");
	}
	free_ifi_info(ifihead);
	exit(0);
}

char * Sock_ntop_host (const struct sockaddr *sa, socklen_t salen)
{
	static char str[128];
	struct sockaddr_in *sin = (struct sockaddr_in *) sa;

	if ((char *)(inet_ntop (AF_INET, &sin->sin_addr, str, sizeof(str))) == NULL)
		return (NULL);
	return (str);
}
