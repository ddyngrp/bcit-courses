#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/syscall.h>
#include <sys/sysproto.h>

/*
 * This hooks the read syscall.  We don't need to declare the args as they have
 * already been declared for the read syscall.
 */
static int read_hook(struct thread *td, void *syscall_args)
{
    struct read_args *args = (struct read_args *)syscall_args;

    int retval;
    int error;
    char rot13val;
    char base;

    retval = read(td, syscall_args);

    /*
     * If the caller requested one byte, read read one byte, and the file
     * descriptor used was 0, then we need to rot13 the ascii char.
     */
    if (args->nbyte == 1 && args->fd == 0)
    {
        /*
         * Pull the read byte into kernel memory
         */
        error = copyin(args->buf, &rot13val, 1);

        /*
         * Check that we didn't fail to copy
         */
        if (error != 0)
        {
            return(error);
        }

        /*
         * The ROT13 step
         */
        if (rot13val >= 'A' && rot13val <= 'Z')
        {
            base = 'A';
        }
        else if (rot13val >= 'a' && rot13val <= 'z')
        {
            base = 'a';
        }
        else
        {
            return retval;
        }
        rot13val -= base;
        rot13val += 13;
        rot13val %= 26;
        rot13val += base;

        /*
         * Put the byte from kernel memory back to the user memory
         */
        error = copyout(&rot13val, args->buf, 1);
        /*
         * Check that we didn't fail to copy
         */
        if (error != 0)
        {
            return(error);
        }
    }
    return retval;
}

/*
 * From sys/module.h
 */ 
static int load(struct module *module, int cmd, void *arg)
{
    int error = 0;

    switch (cmd) {
        case MOD_LOAD:
            sysent[SYS_read].sy_call = (sy_call_t *)read_hook;
            uprintf("Your text input is now ROT13'd.  znxr haybnq\n");
            break;
        case MOD_UNLOAD:
            sysent[SYS_read].sy_call = (sy_call_t *)read;
            uprintf("Back to normality\n");
            break;
        default:
            error = EOPNOTSUPP;
            break;
    }

    return(error);
}

static moduledata_t read_hook_mod = {
    "read_hook",        /* My name for it */
    load,               /* The event handler */
    NULL                /* No extra data */
};

DECLARE_MODULE(read_hook, read_hook_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
