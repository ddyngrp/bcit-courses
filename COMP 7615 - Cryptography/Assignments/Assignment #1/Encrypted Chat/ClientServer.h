/*-----------------------------------------------------------------------------
 * SOURCE FILE:	ClientServer.h
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   October 4, 2009 - Steffen L. Norgren <ironix@trollop.org>
 *                                Combined SimpleCocoaClient.h with
 *                                SimpleCocoaServer.h and cleand it up.
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * NOTES: Header file for the ClientServerConnection class and Client/Server
 *        interfaces.
 *
 *---------------------------------------------------------------------------*/

#import <Cocoa/Cocoa.h>

// Common connection elements
@class ClientServerConnection;

// Return values of connect & listen messages
enum ClientServerInit {
    InitOK					= 1,
    InitError_Connected		= 1 << 1,
    InitError_Listening		= 1 << 2,
	InitError_Host			= 1 << 3,
	InitError_Port			= 1 << 4,
	InitError_Bind			= 1 << 5,
	InitError_Delegate		= 1 << 6,
	InitError_NoConnection	= 1 << 7,
	InitError_Timeout		= 1 << 8,
	InitError_NoSocket		= 1 << 9,
	InitError_Unknown		= 1 << 10
};
typedef enum ClientServerInit ClientServerInit;

enum ServerListenAddress {
	ListenOther		= 0,		// Same as ListenAll
	ListenAll		= 1,
	ListenLoopback	= 1 << 1,
	ListenLocal		= 1 << 2	// Same as ListenLoopback
};
typedef enum ServerListenAddress ServerListenAddress;

#define DEFAULT_CONNECTION_TIMEOUT 30

// Client Section
@interface Client : NSObject {
@private
	id						delegate;
	ClientServerConnection	*c;
	NSString				*remoteHost;
	int						remotePort;
	BOOL					isConnected;
	BOOL					hasBeenInitialized;
	int						connectionTimeout;
	NSStringEncoding		defaultStringEncoding;
}

+ (id)client;
+ (id)clientWithHost:(NSString *)initHost port:(int)initPort andDelegate:(id)initDl;
+ (id)clientConnectedTo:(NSString *)initHost onPort:(int)initPort withDelegate:(id)initDl;

- (id)init;
- (id)initWithHost:(NSString *)initHost port:(int)initPort delegate:(id)initDl;

- (ClientServerInit)connect;
- (void)disconnect;

- (BOOL)sendData:(NSData *)data;
- (BOOL)sendString:(NSString *)string;
- (BOOL)sendString:(NSString *)string withEncoding:(NSStringEncoding)encoding;

- (BOOL)setNewHost:(NSString *)newHost andPort:(int)newPort;
- (BOOL)isConnected;

- (id)delegate;
- (BOOL)setDelegate:(id)newDl;
- (NSString *)remoteHost;
- (NSString *)remoteHostName;
- (BOOL)setRemoteHost:(NSString *)newHost;
- (int)remotePort;
- (BOOL)setRemotePort:(int)newPort;
- (int)connectionTimeout;
- (void)setConnectionTimeout:(int)newTimeout;
- (NSStringEncoding)defaultStringEncoding;
- (void)setDefaultStringEncoding:(NSStringEncoding)encoding;

@end

// Server Section
@interface Server : NSObject {
@private
	int serverPort;
    id serverDelegate;			// Delegate that receives the messages
	BOOL isListening;			// Is server running?
    NSFileHandle *fileHandle;	// Server socket
    NSMutableArray *connections;// Contains all connections
	ServerListenAddress lAddr;	// All or localhost
	char lStrAddr[16];			// If listen address is ListenOther;
}

+ (id)server;
+ (id)serverWithPort:(int)initPort delegate:(id)initDelegate;

- (id)init;
- (id)initWithPort:(int)initPort delegate:(id)initDelegate;

- (ClientServerInit)startListening;
- (void)stopListening;
- (BOOL)isListening;

- (BOOL)setServerPort:(int)newPort;
- (int)serverPort;
- (ServerListenAddress)listenAddress;
- (NSString *)listenAddressAsString;
- (void)setListenAddress:(ServerListenAddress)newLAddr;
- (BOOL)setListenAddressByString:(NSString *)newStrAddr;

- (void)processMessage:(NSString *)message orData:(NSData *)data fromConnection:(ClientServerConnection *)con;
- (void)processNewConnection:(ClientServerConnection *)con;
- (void)processClosingConnection:(ClientServerConnection *)con;

- (NSArray *)connections;
- (void)closeConnection:(ClientServerConnection *)con;

- (BOOL)sendData:(NSData *)data toConnection:(ClientServerConnection *)con;
- (BOOL)sendString:(NSString *)string toConnection:(ClientServerConnection *)con;
- (void)sendDataToAll:(NSData *)data;
- (void)sendStringToAll:(NSString *)string;

@end

@interface ClientServerConnection : NSObject {
@private
	NSFileHandle *fileHandle;	// Connection Socket
    id connectionDelegate;		// Either client or server
    NSString *remoteAddress;	// Remote IP address
	int remotePort;				// Remote port
}

- (id)initWithFileHandle:(NSFileHandle *)fh delegate:(id)initDelegate;

- (NSFileHandle *)fileHandle;
- (NSString *)remoteAddress;
- (int)remotePort;

@end
