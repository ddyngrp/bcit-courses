/*
 *  structures.h
 *  keyLogger
 *
 *  Created by x30n on 4/8/08.
 *  Copyright 2008 Digital Revelation. All rights reserved.
 *
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
