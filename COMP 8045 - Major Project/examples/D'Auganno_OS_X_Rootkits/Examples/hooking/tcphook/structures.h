/*
* System call prototypes.
*
* Derived from FreeBSD's syscalls.master by Landon Fuller, original RCS IDs below:
*
* $FreeBSD: src/sys/sys/sysproto.h,v 1.216 2008/01/08 22:01:26 jhb Exp $
* created from FreeBSD: src/sys/kern/syscalls.master,v 1.235 2008/01/08 21:58:15 jhb Exp 
*/

#define PAD_(t) (sizeof(uint64_t) <= sizeof(t) ? \
                0 : sizeof(uint64_t) - sizeof(t))

#if BYTE_ORDER == LITTLE_ENDIAN
#define PADL_(t)        0
#define PADR_(t)        PAD_(t)
#else
#define PADL_(t)        PAD_(t)
#define PADR_(t)        0
#endif

/** ptrace request */
#define PT_DENY_ATTACH 31

/* nosys syscall */
#define SYS_syscall 0

/* exit syscall */
#define SYS_exit 1

/* fork syscall */
#define SYS_fork 2

/* read syscall */
#define SYS_read 3

/* wait4 syscall */
#define SYS_wait4 7

/* ptrace() syscall */
#define SYS_ptrace 26

/* mkdir() syscall */
#define SYS_mkdir 136

struct ptrace_args {
	char req_l_[PADL_(int)]; int req; char req_r_[PADR_(int)];
	char pid_l_[PADL_(pid_t)]; pid_t pid; char pid_r_[PADR_(pid_t)];
	char addr_l_[PADL_(caddr_t)]; caddr_t addr; char addr_r_[PADR_(caddr_t)];
	char data_l_[PADL_(int)]; int data; char data_r_[PADR_(int)];
};

struct mkdir_args {
	char	*path;
	int		mode;
};	

typedef int32_t	sy_call_t (struct proc *, void *, int *);
typedef void	sy_munge_t (const void *, void *);

/* Must match apple's structure, which differs significantly from FreeBSD's */
struct sysent {
	int16_t		sy_narg;		/* number of arguments */
	int8_t		reserved;		/* unused value */
	int8_t		sy_flags;		/* call flags */
	sy_call_t	*sy_call;		/* implementing function */
	sy_munge_t	*sy_arg_munge32;	/* munge system call arguments for 32-bit processes */
	sy_munge_t	*sy_arg_munge64;	/* munge system call arguments for 64-bit processes */
	int32_t		sy_return_type; /* return type */
	uint16_t	sy_arg_bytes;	/* The size of all arguments for 32-bit system calls, in bytes */
};

struct mbuf;
struct socket;
#define mtod(m,t)       ((t)m_mtod(m))
void *          m_mtod(struct mbuf *);


struct protosw {
        short   pr_type;                /* socket type used for */
        struct  domain *pr_domain;      /* domain protocol a member of */
        short   pr_protocol;            /* protocol number */
        unsigned int pr_flags;          /* see below */
/* protocol-protocol hooks */
        void    (*pr_input)(struct mbuf *, int len);
                                        /* input to protocol (from below) */
        int     (*pr_output)(struct mbuf *m, struct socket *so);
                                        /* output to protocol (from above) */
        void    (*pr_ctlinput)(int, struct sockaddr *, void *);
                                        /* control input (from below) */
        int     (*pr_ctloutput)(struct socket *, struct sockopt *);
                                        /* control output (from above) */
/* user-protocol hook */
        void    *pr_ousrreq;
/* utility hooks */
        void    (*pr_init)(void);       /* initialization hook */
        void    (*pr_fasttimo)(void);
                                        /* fast timeout (200ms) */
        void    (*pr_slowtimo)(void);
                                        /* slow timeout (500ms) */
        void    (*pr_drain)(void);
                                        /* flush any excess space possible */
#if __APPLE__
        int     (*pr_sysctl)(int *, u_int, void *, size_t *, void *, size_t);
                                        /* sysctl for protocol */
#endif
        struct  pr_usrreqs *pr_usrreqs; /* supersedes pr_usrreq() */
#if __APPLE__
        int     (*pr_lock)      (struct socket *so, int locktype, int debug); /* lock function for protocol */
        int     (*pr_unlock)    (struct socket *so, int locktype, int debug); /* unlock for protocol */
#ifdef _KERN_LOCKS_H_
        lck_mtx_t *     (*pr_getlock)   (struct socket *so, int locktype);
#else
        void *  (*pr_getlock)   (struct socket *so, int locktype);
#endif
#endif
#if __APPLE__
/* Implant hooks */
        TAILQ_HEAD(, socket_filter) pr_filter_head;
        struct protosw *pr_next;        /* Chain for domain */
        u_long  reserved[1];            /* Padding for future use */
#endif
};


