#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>

/* This function is called at load/unload */
static int event_handler(struct module *module, int event, void *arg) {
	int e = 0; /* Error, 0 for normal return status */
	
	switch (event) {
		case MOD_LOAD:
			uprintf("The module has been loaded!\n");
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

/* The second argument of DECLARE_MODULE */
static moduledata_t testing_conf = {
	"testing",		/* module name */
	event_handler,	/* event handler */
	NULL			/* extra data */
};

DECLARE_MODULE(testing, testing_conf, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
