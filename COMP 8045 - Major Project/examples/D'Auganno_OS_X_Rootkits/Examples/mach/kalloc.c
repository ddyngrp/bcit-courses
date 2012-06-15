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
#include <mach/mach.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define KSIZE 512


int main(int argc, char **argv) {
        mach_port_t     kernel_task;
        kern_return_t   err;
        long            value = 0x41;
	vm_address_t	myaddr;
	int i;

        if(getuid() && geteuid()) {
                printf("Root priviledges required!\n");
        	exit(1);
	}

	err = task_for_pid(mach_task_self(), 0, &kernel_task);
	if((err != KERN_SUCCESS) || !MACH_PORT_VALID(kernel_task)) {
                printf("getting kernel task.");
        	exit(1);
        }

	if(vm_allocate(kernel_task, &myaddr, 512, 1)) {
		printf("Error allocating kmem.\n");
        	exit(1);
	}
	printf("New memory allocated at %p\n", (vm_address_t) myaddr);

	for(i=0;i<KSIZE;i++) {
		if(vm_write(kernel_task, (vm_address_t) myaddr+i, (vm_address_t) &value, 1)) {
			printf("Error writing to kmem at %p\n", (vm_address_t) myaddr+i);
			exit(1);
		}
		else {
			printf("Wrote 0x41 to %p\n", myaddr+i);
		}
	}
	printf("Done!\nNew Region located at %p\n", (vm_address_t) myaddr);
	exit(0);
}
