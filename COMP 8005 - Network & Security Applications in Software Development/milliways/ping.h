#include        <stdio.h>
#include        <stdlib.h>
#include        <signal.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<sys/time.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<netinet/in_systm.h>
#include	<netinet/ip.h>
#include	<netinet/ip_icmp.h>
#include        <netdb.h>

#define	BUFSIZE		1500

			/* globals */
char	 recvbuf[BUFSIZE];
char	 sendbuf[BUFSIZE];

/*-------- Globals ----------------------*/
int datalen;			/* #bytes of data, following ICMP header */
char *host;
int  nsent;			/* add 1 for each sendto() */
pid_t pid;			/* our PID */
int sockfd;
int verbose;

/*---------- function prototypes ----------*/
int	 proc_v4(char *, ssize_t, struct timeval *);
int	 send_v4(void);
int	 readloop(void);
void	 sig_alrm(int);
void	 tv_sub(struct timeval *, struct timeval *);

struct proto 
{
  void	 (*fproc)(char *, ssize_t, struct timeval *);
  void	 (*fsend)(void);
  struct sockaddr  *sasend;	/* sockaddr{} for send, from getaddrinfo */
  struct sockaddr  *sarecv;	/* sockaddr{} for receiving */
  socklen_t	    salen;		/* length of sockaddr{}s */
  int	   	    icmpproto;	/* IPPROTO_xxx value for ICMP */
} *pr;


