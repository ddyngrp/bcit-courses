#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <bsm/audit_kevents.h>  /* Necessary to include AUE_NULL */

/*
 * This struct defines the arguments to our syscall function 'hello'.
 * The elements must be of type register_t, which is typically equivalent
 * to an into, or a pointer.
 */
struct hello_args {};

/*
 * Our hello system call that takes no arguments (as shown above).  Typically
 * the syscall_args is cast as the above struct (later examples will show more).
 */
static int hello(struct thread *td, void *syscall_args)
{
    uprintf("Hello, world, this is your friendly neighborhood syscall!\n");
    return(0);
}

/*
 * A sysent struct that defines the information about the system call (the
 * number of arguments and the associated function.
 * There is more to this struct, but we'll ignore the rest (auditing, etc).
 * From sys/sysent.h
 */
static struct sysent hello_sysent = {
    0,          /* hello takes no arguments */
    hello,      /* implement hello */
    AUE_NULL    /* No audit event */
};

/*
 * Declare our offset to be the next available system call.  Currently this is
 * really just '(-1)'
 * From sys/sysent.h
 */
static int offset = NO_SYSCALL;

/*
 * This is our load function.  The switch cases are of modeventtype_t from
 * sys/module.h.  We'll use MOD_LOAD and MOD_UNLOAD.  Note that not declaring a
 * MOD_UNLOAD case does nothing to prevent unloading (that's another example).
 * From sys/module.h
 */ 
static int load(struct module *module, int cmd, void *arg)
{
    int error = 0;
    switch (cmd)
    {
        case MOD_LOAD:
            uprintf("Hello, world! (I'm syscall %d)\n", offset);
            break;
        case MOD_UNLOAD:
            uprintf("Good-bye, cruel world! (I'm no longer syscall %d)\n", offset);
            break;
        default:
            error = EOPNOTSUPP;
            break;
    }
    return(error);
}

/*
 * The following cases are equivalent.  The SYSCALL_MODULE expands to the code
 * shown below.  It is generally advisable to use SYSCALL_MODULE as it expands
 * to the other case (and is more easy to maintain).
 */
#if 1
/*
 * From sys/sysent.h
 */
static struct syscall_module_data hello_syscall_mod = {
    load,               /* We use load to load the module */
    NULL,               /* No arguments to pass to load */
    &offset,            /* Our offset determined earlier */
    &hello_sysent,      /* Our new sysent */
    {0, NULL, AUE_NULL} /* Our old sysent */
};
/*
 * From sys/module.h
 */
static moduledata_t hello_mod = {
    hello,
    syscall_module_handler,
    &hello_syscall_mod
};
/*
 * From sys/module.h
 */
DECLARE_MODULE(hello, hello_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
#else
/*
 * A macro that simplifies the above process.
 * From sys/sysent.h
 */
SYSCALL_MODULE(hello, &offset, &hello_sysent, load, NULL);
#endif
