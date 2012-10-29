
/*******************************************************
* Basic program that uses inotify to watch for events 
* on a specified directory. Makes use of select and read
* calls.
********************************************************/


#include <stdio.h>
#include <sys/inotify.h>
#include <sys/select.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#pragma pack(1)

#define TRUE 1
#define FALSE 0
#define EVENT_SIZE (sizeof (struct inotify_event))
#define BUF_LEN	(1024 * (EVENT_SIZE + 16))
#define ALL_MASK 0xffffffff

// Globals - volatile qualifier tells compiler that variable can be modified asynchronously during program execution
static volatile sig_atomic_t doneflag = FALSE;


//----------- Function Prototypes --------------------
static void set_done_flag (int);
void print_mask(int);

int main (void)
{
	int len, i, ret, fd, wd;
	struct timeval time;
	static struct inotify_event *event;
	fd_set rfds;
	char buf[BUF_LEN];
	struct sigaction act;

	// time out after 10 seconds	
	time.tv_sec = 10;
	time.tv_usec = 0;

	fd = inotify_init();
	if (fd < 0)
		perror ("inotify_init");
	
	//wd = inotify_add_watch (fd, "/data/temp", (uint32_t)ALL_MASK);
	wd = inotify_add_watch (fd, "/data/temp", (uint32_t)IN_MODIFY|IN_CREATE|IN_DELETE);
	
	if (wd < 0)
		perror ("inotify_add_watch");

	FD_ZERO (&rfds);
	FD_SET (fd, &rfds);

	// set up the signal handler 
	act.sa_handler = set_done_flag;
	act.sa_flags = 0;
	if ((sigemptyset (&act.sa_mask) == -1 || sigaction (SIGINT, &act, NULL) == -1))
	{
		perror ("Failed to set SIGINT handler");
		exit (EXIT_FAILURE);
	}

	while (!doneflag)
	{
		ret = select (fd + 1, &rfds, NULL, NULL, NULL);
		len = read (fd, buf, BUF_LEN);
	
		i = 0;
		if (len < 0) 
		{
        		if (errno == EINTR) /* need to reissue system call */
				perror ("read");
        		else
                		perror ("read");
		} 
		else if (!len) /* BUF_LEN too small? */
		{
			printf ("buffer too small!\n");
			exit (1);
		}

		while (i < len) 
		{
        		//struct inotify_event *event;
        		event = (struct inotify_event *) &buf[i];

        		printf ("\nwd=%d mask=%u cookie=%u len=%u\n", event->wd, event->mask, event->cookie, event->len);
        		if (event->len)
                		printf ("name=%s\n", event->name);
        		i += EVENT_SIZE + event->len;
		}
	
		if (ret < 0)
			perror ("select");
		else if (!ret)
			printf ("timed out\n");
		else if (FD_ISSET (fd, &rfds))
		{
			print_mask (event->mask);
		}
	}
	
	printf ("Cleaning up and Terminating....................\n");
	fflush (stdout);
	ret = inotify_rm_watch (fd, wd);
	if (ret)
		perror ("inotify_rm_watch");
	if (close(fd))
		perror ("close");
	return 0;
}

void print_mask(int mask)
{
        if (mask & IN_ACCESS)
                printf("ACCESS ");
        if (mask & IN_MODIFY)
                printf("MODIFY ");
        if (mask & IN_ATTRIB)
                printf("ATTRIB ");
        if (mask & IN_CLOSE)
                printf("CLOSE ");
        if (mask & IN_OPEN)
                printf("OPEN ");
        if (mask & IN_MOVED_FROM)
                printf("MOVE_FROM ");
        if (mask & IN_MOVED_TO)
                printf("MOVE_TO ");
        if (mask & IN_DELETE)
                printf("DELETE ");
        if (mask & IN_CREATE)
                printf("CREATE ");
        if (mask & IN_DELETE_SELF)
                printf("DELETE_SELF ");
        if (mask & IN_UNMOUNT)
                printf("UNMOUNT ");
        if (mask & IN_Q_OVERFLOW)
                printf("Q_OVERFLOW ");
        if (mask & IN_IGNORED)
                printf("IGNORED " );

        if (mask & IN_ISDIR)
                printf("(dir) ");
        else
                printf("(file) ");

        printf("0x%08x\n", mask);
}

static void set_done_flag (int signo)
{
	doneflag = TRUE;
}
