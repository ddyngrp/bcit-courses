
#define MSG_DATA			1		// application specific msg
#define MSG_ACK			2		// ACK
#define MSG_HEARTBEAT	3		// heartbeat message
#define SERVER_TCP_PORT 7000		// Default port
#define BUFLEN				256		//Buffer length
#define TRUE				1

typedef struct					/* message structure */
{
	u_int32_t type;				/* MSG_TYPE1, ... */
	char data[ BUFLEN ];
} msg_t;

#define T0				30		/* idle time before heartbeat */
#define T1				5		/* time to wait for response */


