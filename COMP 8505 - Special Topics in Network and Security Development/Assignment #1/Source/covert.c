/*-----------------------------------------------------------------------------
 * covert.c - Covert communication over TCP/IP
 * Copyright (C) 2010 Steffen L. Norgren <ironix@trollop.org>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *----------------------------------------------------------------------------*/

#include "covert.h"

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS:     
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
int main (int argc, const char *argv[])
{

	/* make sure user is root */
	if (geteuid() != USER_ROOT) {
		fprintf(stderr, "You must be root to run this program.\n");
		exit(ERROR_NOTROOT);
	}

	/* parse CLI options */
	if (argc == 1)
		print_settings();
	else
		if (parse_options(argc, argv) == ERROR_OPTIONS) {
			err(1, "Invalid options");
			exit(ERROR_OPTIONS);
		}

	file_io("INSTALL", NULL);

    return ERROR_NONE;
}

void print_settings()
{
}

void print_usage()
{
}

int parse_options(int argc, const char *argv[])
{
	return ERROR_NONE;
}

int file_io(char *file_name, char *recv_buffer)
{
	FILE *file;
	char buffer[BUFFER_SIZE + 1];
	int file_size;
	int	read_bytes;
	int file_position = 0;

	/* determine if we are reading or writing */
	if (recv_buffer == NULL) { /* server sends file */
		if ((file = fopen(file_name, "rb")) == NULL)
			return ERROR_FILE;
		else {
			fseek(file, 0, SEEK_END);
			file_size = ftell(file);
			rewind(file);

			/* accumulate 32 bits of data, which is the length
			 * of the source addresss */
			while (file_position < file_size) {
				read_bytes = fread(buffer, sizeof(char), BUFFER_SIZE, file);

				file_position += read_bytes;

				packet_forge(atoi(buffer)); /* send the packet */
				usleep(DELAY_USEC); /* give the packet time to get there */

				printf("%s", buffer);

				memset(&buffer, '\0', sizeof(buffer)); /* clear the buffer */
			}
		}

		fclose(file);
	}
	else if (recv_buffer != NULL) { /* client receives file */
	}

	return ERROR_NONE;
}

void packet_forge(unsigned int source_addr)
{
	struct ip iph;
	/* struct tcphdr tcph; */

	/* seed random number generator */
	srand(time(NULL));

	/* Create a forged IP header */
	iph.ip_hl	= 0x5;
	iph.ip_v	= 0x4;
	iph.ip_tos	= 0x0;
	iph.ip_len	= htons(40);
	iph.ip_id	= htonl((int)(255.0 * rand() / (RAND_MAX + 1.0))); /* random IP ident */
	iph.ip_off	= IP_DF; /* don't fragment */
	iph.ip_ttl	= 0x64;
	iph.ip_sum	= 0;
	iph.ip_p	= IPPROTO_TCP;
	iph.ip_src.s_addr = source_addr;
	iph.ip_dst.s_addr = conn_info.dest_ip;
}

void packet_decode()
{
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    in_cksum
 * 
 * DATE:        May 17, 2010
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    W. Richard Stevens (From UNIX Network Programming)
 * 
 * PROGRAMMER:  W. Richard Stevens (From UNIX Network Programming)
 * 
 * INTERFACE:   
 * 
 * RETURNS:     
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
uint16_t in_cksum(uint16_t *addr, int len)
{
	int nleft = len;
	uint32_t sum = 0;
	uint16_t *w = addr;
	uint16_t answer = 0;

	/* Our algorithm is simple, using a 32-bit accumulator (sum), we add
	 * sequential 16-bit words to it, and at the end, fold back all the
	 * carry bits from the top 16 bits into the lower 16 bits.
	 */
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nleft ==1) {
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}

	/* add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff); /* add high 16 to low 16 */
	sum += (sum >> 16);					/* add carry */
	answer = ~sum;						/* truncate to 16 bits */

	return (answer);
}
