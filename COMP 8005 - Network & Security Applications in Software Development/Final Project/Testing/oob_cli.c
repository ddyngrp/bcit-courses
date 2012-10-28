#define _BSD_SOURCE

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define TRUE 1
#define FALSE 0
#define MAX_HOST_LEN 256

static void usage(const char *);
static void err_sys(const char *);
static void err_quit(const char *, ...);
static void debug(const char *, ...);
static void * xmalloc(size_t);
static void * xcalloc(size_t, size_t);
static void * xrealloc(void *, size_t);
static int sock_set_nonblocking(int);
static int tcp_connect(const char *, unsigned short, int);

int main(int argc, char **argv)
{
	char host[MAX_HOST_LEN + 1];
	unsigned short port;
	int clifd;
	int nsend;

	if(argc != 3) 
	{
		usage(*argv);
		exit(1);
	}
	
	strncpy(host, argv[1], MAX_HOST_LEN);
	port = (unsigned short)atoi(argv[2]);
	
	if((clifd = tcp_connect(host, port, FALSE)) < 0) 
	{
		err_quit("tcp_connect failed");
	}
	
	debug("connected... descriptor: %d", clifd);
	debug("sleeping for 1 second");
	sleep(1);
	nsend = send(clifd, "qqqq", 4, MSG_OOB);
	debug("send %d bytes (OOB?)", nsend);
	exit(0);
}

int tcp_connect(const char *host, unsigned short port, int nonblocking)
{
	int fd;
	struct hostent *ent;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		return -1;
	}
	
	if(nonblocking) 
	{
		if(sock_set_nonblocking(fd) < 0) 
		{
			return -1;
		}
	}
	
	if(!(ent = gethostbyname(host))) 
	{
		return -1;
	}
	
	memcpy(&addr.sin_addr, ent->h_addr, ent->h_length);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	
	if(connect(fd, (struct sockaddr *)&addr, addrlen) < 0) 
	{
		if(errno != EINPROGRESS) 
		{
			return -1;
		}
	}

	return fd;
}


void *xmalloc(size_t size)
{
	void *p;
	
	if(!(p = malloc(size)))
		err_sys("malloc");
	
	return p;
}

void *xcalloc(size_t nmem, size_t size)
{
	void *p;
	
	if(!(p = calloc(nmem, size)))
		err_sys("calloc");
		
	return p;
}

void *xrealloc(void *vptr, size_t len)
{	
	void *p;

	if(!(p = realloc(vptr, len)))
		err_sys("realloc");
		
	return p;
}

void err_sys(const char *str)
{
	fprintf(stderr, "%s %d: %s\n", str, errno, strerror(errno));
	exit(errno);
}

void err_quit(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "... error %d: \"%s\"\n", errno, strerror(errno));
	va_end(ap);
	exit(1);
}

void debug(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}

int sock_set_nonblocking(int fd)
{
	int flags;
	
	if((flags = fcntl(fd, F_GETFL, 0)) < 0) {
 		return -1;
 	}
 	
 	if(fcntl(fd, F_SETFL, flags | O_NDELAY) < 0) {
 		return -1;
 	}
 	
 	return 0;
}

static void usage(const char *argv)
{
	debug("usage: %s <host> <port>", argv);
	debug("       host: host address");
	debug("       port: host port");
}

