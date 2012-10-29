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
#include <sys/epoll.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define TRUE 1

static struct epoll_event *events;
static unsigned int mevent = 0; /* max number of events */
static int epfd = -1;

static void sig_exit(int);
static void usage(const char *);
static void err_sys(const char *);
static void err_quit(const char *, ...);
static void debug(const char *, ...);
static void * xmalloc(size_t);
static void * xcalloc(size_t, size_t);
static void * xrealloc(void *, size_t);
static int ep_add(int, int, int, void *);
static int ep_del(int, int);
static int ep_create(int, struct epoll_event **);
static int sock_set_nonblocking(int);
static int tcp_listen(unsigned short, int);

int main(int argc, char **argv)
{
	int i;
	int nfds;
	int listenfd, clifd;
	unsigned short port;
	size_t count;
	char b;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	
	if(argc != 3) 
	{
		usage(argv[0]);
		exit(1);
	}
	
	port = (unsigned short)atoi(argv[1]);
	mevent = (unsigned int)atoi(argv[2]);

	if((listenfd = tcp_listen(port, TRUE)) == -1)
		err_quit("tcp_listen failed..");

	if((epfd = ep_create(mevent, &events)) == -1) 
		err_quit("ep_create failed...");
		
	if(ep_add(epfd, EPOLLIN | EPOLLET, listenfd, NULL) == -1)
		err_quit("ep_add failed...");

	signal(SIGINT, sig_exit);
	signal(SIGTERM, sig_exit);
	
	for(;;) 
	{
		if((nfds = epoll_wait(epfd, events, mevent, -1)) < 0) {
			err_sys("epoll_wait");
		}
		
		for(i = 0; i < nfds; i++) 
		{
			if(events[i].data.fd == listenfd) 
			{
				if((clifd = accept(listenfd, (struct sockaddr *)&addr, &addrlen)) != -1) 
				{
					if(sock_set_nonblocking(clifd) != 0)
						err_quit("sock_set_nonblocking failed...");

					if(ep_add(epfd, EPOLLIN | EPOLLPRI | EPOLLET, clifd, NULL) == -1)
						err_quit("ep_add failed...");

					debug("accepted connection, fd = %d host = %s", clifd, inet_ntoa(addr.sin_addr));
					continue;
				}

				err_sys("accept");
			} 
			else 
			{
				debug("received %s event", (events[i].events & EPOLLPRI) ? "EPOLLPRI" : "non-EPOLLPRI");
				recv(events[i].data.fd, &b, sizeof(b), MSG_OOB); /* if it's not EPOLLPRI issue a different call !!!! */
				debug("data = %c", b);
			}
		}
	}

    exit(0);
}

int ep_del(int epfd, int fd)
{
	return epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
}

int ep_add(int epfd, int event, int fd, void *ptr)
{
	struct epoll_event ev;
	
	ev.data.fd = fd;
	ev.events = event;

	return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
}

int ep_create(int size, struct epoll_event **events)
{
    int epfd;

	(*events) = (struct epoll_event *)malloc(sizeof(struct epoll_event) * size);
	
	if(!(*events)) {
		return -1;
	}

	if((epfd = epoll_create(size)) == -1) {
		free(*events);
	}
	
	return epfd;
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

int tcp_listen(unsigned short port, int nonblocking)
{
	int fd;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int opt = 1, optlen = sizeof(opt);
	
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		return -1;
	}
	
	if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, optlen) == -1) 
	{
		return -1;
	}
	
	if(nonblocking) 
	{
		if(sock_set_nonblocking(fd) < 0) {
			return -1;
		}
	}
	
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(port);
	addr.sin_family = AF_INET;
	
	if(bind(fd, (struct sockaddr *)&addr, addrlen) < 0) 
	{
		return -1;
	}
	
	if(listen(fd, SOMAXCONN) < 0) 
	{
		return -1;
	}
		
	return fd;
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


void sig_exit(int signo)
{
	free(events);	
	exit(signo);	
}

static void usage(const char *argv)
{
	debug("usage: %s <port> <count>", argv);
	debug("       port: port number to listen on");
	debug("       count: epoll event count hint");
}

