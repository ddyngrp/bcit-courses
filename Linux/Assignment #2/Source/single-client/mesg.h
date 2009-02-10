#define MAXMESSAGEDATA	(4096-16) // Don't want sizeof(Mesg) > 4096
#define MESGHDRSIZE		(sizeof(Mesg) - MAXMESSAGEDATA) // Length of mesg_len and mesg_type

typedef struct {
	long mesg_type;	// message type
	int mesg_len;	// #bytes in mesg_data
	char mesg_data[MAXMESSAGEDATA];
} Mesg;
