#include	"ping.h"

int send_v4(void)
{
	int len;
	struct icmp *icmp;

	icmp = (struct icmp *) sendbuf;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_id = pid;
	icmp->icmp_seq = nsent++;
	if (gettimeofday((struct timeval *) icmp->icmp_data, NULL) == -1)
	{
	     printf ("gettimeofday error\n");
	     return (-1);
	}

	len = 8 + datalen;		/* checksum ICMP header and data */
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = in_cksum((u_short *) icmp, len);

	if (sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen) != len)
	{
	      printf ("sendto error\n");
	      return (-1);
	}
}
