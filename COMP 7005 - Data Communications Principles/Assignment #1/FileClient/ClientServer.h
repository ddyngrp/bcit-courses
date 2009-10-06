/*-----------------------------------------------------------------------------
 * SOURCE FILE:	ClientServer.h
 * 
 * PROGRAM:     Encrypted Chat <Client>
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   October 4, 2009 - Steffen L. Norgren <ironix@trollop.org>
 *                                Combined SimpleCocoaClient.h with
 *                                SimpleCocoaServer.h and cleand it up.
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 *                              http://www.1-more-thing.de/code/simpleserver
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *                              http://www.1-more-thing.de/code/simpleserver
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
    InitError_Connected		= 2,
    InitError_Listening		= 4,
	InitError_Host			= 8,
	InitError_Port			= 16,
	InitError_Bind			= 32,
	InitError_Delegate		= 64,
	InitError_NoConnection	= 128,
	InitError_Timeout		= 256,
	InitError_NoSocket		= 512,
	InitError_Unknown		= 1024
};
typedef enum ClientServerInit ClientServerInit;

enum ServerListenAddress {
	ListenOther		= 0,		// Same as ListenAll
	ListenAll		= 1,
	ListenLoopback	= 2,
	ListenLocal		= 4	// Same as ListenLoopback
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
