#include <unistd.h>
#include <errno.h>
#include <strings.h>
#include <stdlib.h>
#include "ping.h"

/*------- Function Prototypes -----------------------*/
void tv_sub (struct timeval *out, struct timeval *in);
void sig_alrm (int);
unsigned short in_cksum(unsigned short *, int);
int readloop(void);
char * Sock_ntop_host(const struct sockaddr *sa, socklen_t salen);

/*--------- Globals ----------------------------------*/
struct proto	proto_v4 = { proc_v4, send_v4, NULL, NULL, 0, IPPROTO_ICMP };
int	datalen = 56;		/* data that goes with ICMP echo request */

int main(int argc, char **argv)
{
	int c;
	struct addrinfo	hints, *ai;
	int n, socktype = 0;
	int family = 0;

	opterr = 0;		/* don't want getopt() writing to stderr */
	while ( (c = getopt(argc, argv, "v")) != -1)
	{
		switch (c)
		{
		        case 'v':
			  verbose++;
			break;

		        case '?':
			{
			  printf ("unrecognized option: %c", c);
			  return (-1);
			}
		}
	}

	if (optind != argc-1)
	{
		printf ("usage: ping [ -v ] <hostname>\n");
		return (-1);
	}
	host = argv[optind];

	pid = getpid();
	signal(SIGALRM, sig_alrm);

	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_flags = AI_CANONNAME;	/* always return canonical name */
	hints.ai_family = family;		/* 0, AF_INET, AF_INET6, etc. */
	hints.ai_socktype = socktype;	/* 0, SOCK_STREAM, SOCK_DGRAM, etc. */

	if ( (n = getaddrinfo(host, NULL, &hints, &ai)) != 0)
	  return(-1);

	printf("PING %s (%s): %d data bytes\n", ai->ai_canonname,
		   Sock_ntop_host(ai->ai_addr, ai->ai_addrlen), datalen);

	/* 4initialize according to protocol */
	if (ai->ai_family == AF_INET) 
	{
		pr = &proto_v4;
	} 
	else
	{
		printf ("unknown address family %d", ai->ai_family);
		return (-1);
	}

	pr->sasend = ai->ai_addr;
	if ((pr->sarecv = calloc(1, ai->ai_addrlen)) == NULL)
	{
	        printf ("calloc error\n");
		return (-1);
	}
	pr->salen = ai->ai_addrlen;

	readloop();

	exit(0);
}

/*------------------ Read from socket and process the packet ----------------*/
int readloop(void)
{
	int size;
	char recvbuf[BUFSIZE];
	socklen_t len;
	ssize_t n;
	struct timeval tval;

	sockfd = socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto);
	if (sockfd < 0)
	{
	     printf ("socket error\n");
	     return (-1);
	}
	setuid(getuid());		/* don't need special permissions any more */

	size = 60 * 1024;		/* OK if setsockopt fails */
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

	sig_alrm(SIGALRM);		/* send first packet */

	for ( ; ; ) 
	{
	        len = pr->salen;
		n = recvfrom(sockfd, recvbuf, sizeof(recvbuf), 0, pr->sarecv, &len);
		if (n < 0) 
		{
		  if (errno == EINTR)
		    continue;
		  else
		    perror("recvfrom error");
		}

		if (gettimeofday(&tval, NULL) == -1)
	        {
		    printf ("gettimeofday error\n");
		    return (-1);
		}
		(*pr->fproc)(recvbuf, n, &tval);
	}
}


/*--------------- Subtract two time intervals ---------------------*/
void tv_sub(struct timeval *out, struct timeval *in)
{
	if ( (out->tv_usec -= in->tv_usec) < 0) {	/* out -= in */
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

/*-------------- Signal Handler ----------------------------------*/

void sig_alrm(int signo)
{
	(*pr->fsend)();

	alarm(1);
	return;		/* probably interrupts recvfrom() */
}


/*-------- Checksum Algorithm (Public domain Ping) ----------------------*/
unsigned short in_cksum(unsigned short *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short	*w = addr;
	unsigned short	answer = 0;

	/*
	 * Our algorithm is simple, using a 32 bit accumulator (sum), we add
	 * sequential 16 bit words to it, and at the end, fold back all the
	 * carry bits from the top 16 bits into the lower 16 bits.
	 */
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}

		/* 4mop up an odd byte, if necessary */
	if (nleft == 1)
	{
		*(unsigned char *)(&answer) = *(unsigned char *)w ;
		sum += answer;
	}

       	/* 4add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return(answer);
}


char * Sock_ntop_host(const struct sockaddr *sa, socklen_t salen)
{
    static char str[128];		/* Unix domain is largest */

	switch (sa->sa_family) 
	{
	        case AF_INET:
		{
		  struct sockaddr_in	*sin = (struct sockaddr_in *) sa;

		  if (inet_ntop(AF_INET, &sin->sin_addr, str, sizeof(str)) == NULL)
			return(NULL);
		}
		return(str);
	}

    return (NULL);
}











