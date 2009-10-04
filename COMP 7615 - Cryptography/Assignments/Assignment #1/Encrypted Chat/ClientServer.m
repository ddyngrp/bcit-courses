/*-----------------------------------------------------------------------------
 * SOURCE FILE:	ClientServer.m
 * 
 * PROGRAM:     Encrypted Chat
 * 
 * FUNCTIONS:   Client Interface Methods
 *              + (id)client
 *              + (id)clientWithHost:(NSString *)initHost port:(int)initPort
 *                       andDelegate:(id)initDl
 *              + (id)clientConnectedTo:(NSString *)initHost
 *                               onPort:(int)initPort withDelegate:(id)initDl
 *              - (id)init
 *              - (id)initWithHost:(NSString *)initHost port:(int)initPort
 *                        delegate:(id)initDl
 *              - (void)dealloc
 *              - (ClientServerInit)connect
 *              - (void)disconnect
 *              - (void)closeConnection:(ClientServerConnection *)con
 *              - (BOOL)sendData:(NSData *)data
 *              - (BOOL)sendString:(NSString *)string
 *              - (BOOL)sendString:(NSString *)string 
 *                    withEncoding:(NSStringEncoding)encoding
 *              - (void)processMessage:(NSString *)message orData:(NSData *)data
 *                      fromConnection:(ClientServerConnection *)con
 *              - (id)delegate
 *              - (BOOL)setDelegate:(id)newDl
 *              - (ClientServerConnection *)c
 *              - (void)setC:(ClientServerConnection *)con
 *              - (BOOL)setNewHost:(NSString *)newHost andPort:(int)newPort
 *              - (NSString *)remoteHost
 *              - (NSString *)remoteHostName
 *              - (BOOL)setRemoteHost:(NSString *)newHost
 *              - (int)remotePort
 *              - (BOOL)setRemotePort:(int)newPort
 *              - (BOOL)isConnected
 *              - (void)setIsConnected:(BOOL)flag
 *              - (int)connectionTimeout
 *              - (void)setConnectionTimeout:(int)newTimeout
 *              - (NSStringEncoding)defaultStringEncoding
 *              - (void)setDefaultStringEncoding:(NSStringEncoding)encoding
 *              
 *              Server Interface Methods
 *              + (id)server
 *              + (id)serverWithPort:(int)initPort delegate:(id)initDelegate
 *              - (id)init
 *              - (id)initWithPort:(int)initPort delegate:(id)initDelegate
 *              - (void)dealloc
 *              - (ClientServerInit)startListening
 *              - (void)stopListening
 *              - (BOOL)isListening
 *              - (BOOL)setServerPort:(int)newPort
 *              - (int)serverPort
 *              - (BOOL)setServerDelegate:(id)newDelegate
 *              - (ServerListenAddress)listenAddress
 *              - (NSString *)listenAddressAsString
 *              - (void)setListenAddress:(ServerListenAddress)newLAddr
 *              - (BOOL)setListenAddressByString:(NSString *)newStrAddr
 *              - (void)processMessage:(NSString *)message orData:(NSData *)data
 *                      fromConnection:(ClientServerConnection *)con;
 *              - (void)processNewConnection:(ClientServerConnection *)con
 *              - (void)processClosingConnection:(ClientServerConnection *)con
 *              - (NSArray *)connections
 *              - (void)newConnection:(NSNotification *)notification
 *              - (void)closeConnection:(ClientServerConnection *)con
 *              - (BOOL)sendData:(NSData *)data
 *                  toConnection:(ClientServerConnection *)con
 *              - (BOOL)sendString:(NSString *)string
 *                    toConnection:(ClientServerConnection *)con
 *              - (void)sendDataToAll:(NSData *)data
 *              - (void)sendStringToAll:(NSString *)string
 *              
 *              ClientServerConnection Interface Methods
 *              - (id)initWithFileHandle:(NSFileHandle *)fh
 *                              delegate:(id)initDelegate
 *              - (void)dealloc
 *              - (NSString *)description
 *              - (NSFileHandle *)fileHandle 
 *              - (void)setRemoteAddress:(NSString *)newAddress
 *              - (NSString *)remoteAddress
 *              - (void)setRemotePort:(int)newPort
 *              - (int)remotePort
 *              - (void)dataReceivedNotification:(NSNotification *)notification
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   October 4, 2009 - Steffen L. Norgren <ironix@trollop.org>
 *                                Combined SimpleCocoaClient.m with
 *                                SimpleCocoaServer.m and cleand it up.
 *                                Removed duplicate functions, corrected
 *                                all warnings and deprecated calls.
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * NOTES: Handles all client and server related functions and callbacks.
 *
 *---------------------------------------------------------------------------*/

#import "ClientServer.h"
#import <sys/socket.h>
#import <netinet/in.h>
#import <netdb.h>
#import <arpa/inet.h>

#pragma mark Client

@interface Client (PrivateMethods)

- (void)setIsConnected:(BOOL)val;
- (void)setC:(ClientServerConnection *)con;
- (ClientServerConnection *)c;
- (void)closeConnection:(ClientServerConnection *)con;

@end


@implementation Client

#pragma mark Class Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    client
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)client
 * 
 * RETURNS: A Client object with no port and delegate set.
 * 
 * NOTES: Returns a Client object with standard setup.
 *
 *----------------------------------------------------------------------------*/
+ (id)client
{
	Client *c = [[Client alloc] init];
	return c;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    clientWithHost
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)clientWithHost:(NSString *)initHost port:(int)initPort
 *                                 andDelegate:(id)initDl
 *                  initHost: the host to connect to
 *                  port: the remote port
 * 
 * RETURNS: A Client object with a host and port set.
 * 
 * NOTES: Returns a Client object with a specified host and port.
 *
 *----------------------------------------------------------------------------*/
+ (id)clientWithHost:(NSString *)initHost port:(int)initPort andDelegate:(id)initDl
{
	Client *c = [[Client alloc] initWithHost:initHost port:initPort delegate:initDl];
	return c;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    clientConnectedTo
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)clientConnectedTo:(NSString *)initHost onPort:(int)initPort
 *                                    withDelegate:(id)initDl
 *                  initHost: the host the client is connecting to
 *                  onPort: the remote port
 *                  withDelegate: the calling delegate
 * 
 * RETURNS: A Client object with a host and port set if a connection exists.
 * 
 * NOTES: Returns a Client object with a host and port set if the connection
 *        can be established.
 *
 *----------------------------------------------------------------------------*/
+ (id)clientConnectedTo:(NSString *)initHost onPort:(int)initPort withDelegate:(id)initDl
{
	Client *c = [[Client alloc] initWithHost:initHost port:initPort delegate:initDl];
	
	if(c) {
		if([c connect] == InitOK) {
			return c;
		}
	}
	return nil;
}


#pragma mark Instance Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    init
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)init
 * 
 * RETURNS: Returns a Client object with standard setup.
 * 
 * NOTES: Initializes a Client object's default values.
 *
 *----------------------------------------------------------------------------*/
- (id)init
{
	if(hasBeenInitialized)
		return nil;
	self = [super init];
	isConnected = NO;
	defaultStringEncoding = NSUTF8StringEncoding;
	hasBeenInitialized = YES;
	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    initWithHost
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)initWithHost:(NSString *)initHost port:(int)initPort
 *                               delegate:(id)initDl
 *                  initHost: the host the client is connecting to
 *                  onPort: the remote port
 *                  withDelegate: the calling delegate
 * 
 * RETURNS: Returns a Client object with a given host, port and delegate.
 * 
 * NOTES: Initilizes a Client object with a given host, port and delegate.
 *
 *----------------------------------------------------------------------------*/
- (id)initWithHost:(NSString *)initHost port:(int)initPort delegate:(id)initDl
{
	if(self = [self init]) {
		if(![self setRemoteHost:initHost])
			return nil;
		if(![self setRemotePort:initPort])
			return nil;
		if(![self setDelegate:initDl])
			return nil;
	} else {
		return nil;
	}
	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    dealloc
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)dealloc
 * 
 * RETURNS: void
 * 
 * NOTES: Performs garbage collection.
 *
 *----------------------------------------------------------------------------*/
- (void)dealloc
{
	if(isConnected) {
		[self disconnect];
	}
	[remoteHost release];
	[delegate release];
	[super dealloc];
}


#pragma mark Connecting

/*-----------------------------------------------------------------------------
 * FUNCTION:    connect
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (ClientServerInit)connect
 * 
 * RETURNS: InitOK if connect succeeded, otherwise an error code.
 * 
 * NOTES: Attempts to connect to a specified host and port.
 *
 *----------------------------------------------------------------------------*/
- (ClientServerInit)connect
{
	if(isConnected)
		return InitError_Connected;
	if(!remoteHost)
		return InitError_Host;
	if(remotePort < 1)
		return InitError_Port;
	if(!delegate)
		return InitError_Delegate;
	
	int filedescriptor = -1;
	CFSocketRef socket = CFSocketCreate(kCFAllocatorDefault, PF_INET, SOCK_STREAM, IPPROTO_TCP, 1, NULL, NULL);
	
	if(socket) {
		
		filedescriptor = CFSocketGetNative(socket);
		
		// This prevents the socket from existing after the server has crashed or been forced to close
		int yes = 1;
		setsockopt(filedescriptor, SOL_SOCKET, SO_REUSEADDR, (void *)&yes, sizeof(yes));
		
		struct sockaddr_in addr4;
		memset(&addr4, 0, sizeof(addr4));
		addr4.sin_len = sizeof(addr4);
		addr4.sin_family = AF_INET;
		addr4.sin_port = htons(remotePort);
		inet_pton(AF_INET, [remoteHost UTF8String], &addr4.sin_addr);
		
		NSData *address4 = [NSData dataWithBytes:&addr4 length:sizeof(addr4)];
		
		int retVal = CFSocketConnectToAddress(socket, (CFDataRef)address4, [self connectionTimeout]);
		
		if(retVal == kCFSocketError)
			return InitError_NoConnection;
		if(retVal == kCFSocketTimeout)
			return InitError_Timeout;
		if(retVal != kCFSocketSuccess)
			return InitError_Unknown;
		
	} else {
		return InitError_NoSocket;
	}
	
	NSFileHandle *fileHandle = [[NSFileHandle alloc] initWithFileDescriptor:filedescriptor closeOnDealloc:YES];
	if(fileHandle) {
		ClientServerConnection *connection = [[ClientServerConnection alloc] initWithFileHandle:fileHandle delegate:self];
		if(connection) {
			[self setC:connection];
			[self setIsConnected:YES];
		}
		[connection release];
	}
	return InitOK;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    disconnect
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)disconnect
 * 
 * RETURNS: void
 * 
 * NOTES: Disconnects all currently open Client connections.
 *
 *----------------------------------------------------------------------------*/
- (void)disconnect
{
	if([delegate respondsToSelector:@selector(connectionWillClose:)])
		[delegate performSelector:@selector(connectionWillClose:) withObject:self];
	[self setC:nil];
	[self setIsConnected:NO];
	if([delegate respondsToSelector:@selector(connectionDidClose:)])
		[delegate performSelector:@selector(connectionDidClose:) withObject:self];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    closeConnection
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)closeConnection:(ClientServerConnection *)con
 * 
 * RETURNS: void
 * 
 * NOTES: Closes a specified Client connection.
 *
 *----------------------------------------------------------------------------*/
- (void)closeConnection:(ClientServerConnection *)con
{
	[self disconnect];
}


#pragma mark Sending and Receiving

/*-----------------------------------------------------------------------------
 * FUNCTION:    sendData
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)sendData:(NSData *)data
 *                    data: the data to be sent
 * 
 * RETURNS: True if data was sent, false on an error.
 * 
 * NOTES: Attempts to send data through the current connection.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)sendData:(NSData *)data
{
	@try {
		[[c fileHandle] writeData:data];
    }
    @catch (NSException *exception) {
		return NO;
    }
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    sendString
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)sendString:(NSString *)string
 *                    string: the string to be sent
 * 
 * RETURNS: True if string was sent, false on an error.
 * 
 * NOTES: Attempts to send a string through the current connection.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)sendString:(NSString *)string
{
	return [self sendData:[string dataUsingEncoding:[self defaultStringEncoding]]];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    sendString
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)sendString:(NSString *)string
 *                               withEncoding:(NSStringEncoding)encoding
 *                    string: the string to be sent
 *                    encoding: the type of text encoding used
 * 
 * RETURNS: True if string was sent, false on an error.
 * 
 * NOTES: Attempts to send a string with a specific encoding through the
 *        current connection.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)sendString:(NSString *)string withEncoding:(NSStringEncoding)encoding
{
	return [self sendData:[string dataUsingEncoding:encoding]];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    processMessage
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)processMessage:(NSString *)message orData:(NSData *)data
 *                                fromConnection:(ClientServerConnection *)con
 *                    message: message received
 *                    orData: or the data received
 *                    fromConnection: the open connection
 * 
 * RETURNS: void
 * 
 * NOTES: Processes a message (string) or data object sent from the server.
 *
 *----------------------------------------------------------------------------*/
- (void)processMessage:(NSString *)message orData:(NSData *)data fromConnection:(ClientServerConnection *)con
{
	if([delegate respondsToSelector:@selector(processMessage:orData:fromConnection:)])
		[delegate processMessage:message orData:data fromConnection:con];
}


#pragma mark Accessor Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    delegate
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)delegate
 * 
 * RETURNS: The instance id of the object's delegate
 * 
 * NOTES: Returns the current delegate.
 *
 *----------------------------------------------------------------------------*/
- (id)delegate
{
	return delegate;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setDelegate
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)setDelegate:(id)newDl
 * 
 * RETURNS: True if the Client object being delegated isn't connected.
 * 
 * NOTES: Connects a Client object to a new delegate.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)setDelegate:(id)newDl
{
	if(isConnected)
		return NO;
	[self willChangeValueForKey:@"delegate"];
	newDl = [newDl retain];
	[delegate release];
	delegate = newDl;
	[self didChangeValueForKey:@"delegate"];
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    c
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (ClientServerConnection *)c
 * 
 * RETURNS: The ClientServerConnection object for the Client
 * 
 * NOTES: Returns the ClientServerConnection for the Client object.
 *
 *----------------------------------------------------------------------------*/
- (ClientServerConnection *)c
{
	return c;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setC
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)setC:(ClientServerConnection *)con
 *                    con: the connection object
 * 
 * RETURNS: void
 * 
 * NOTES: Assigns a ClientServerConnection object to a new connection.
 *
 *----------------------------------------------------------------------------*/
- (void)setC:(ClientServerConnection *)con
{
	[self willChangeValueForKey:@"c"];
	con = [con retain];
	[c release];
	c = con;
	[self didChangeValueForKey:@"c"];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setNewHost
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)setNewHost:(NSString *)newHost andPort:(int)newPort
 *                    newHost: the remote host
 *                    andPort: the remote port
 * 
 * RETURNS: True setting the new host succeeds.
 * 
 * NOTES: Sets a new host for the connection.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)setNewHost:(NSString *)newHost andPort:(int)newPort
{
	if(isConnected)
		return NO;
	if(![self setRemoteHost:newHost])
		return NO;
	if(![self setRemotePort:newPort])
		return NO;
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    remoteHost
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSString *)remoteHost
 * 
 * RETURNS: The remote host IP
 * 
 * NOTES: The remote host IP for the current connection.
 *
 *----------------------------------------------------------------------------*/
- (NSString *)remoteHost
{
	return remoteHost;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    remoteHostName
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSString *)remoteHostName
 * 
 * RETURNS: The remote host name
 * 
 * NOTES: The remote host name for the current connection.
 *
 *----------------------------------------------------------------------------*/
- (NSString *)remoteHostName
{
	struct in_addr IPaddr;
	struct hostent *host;
	inet_pton(AF_INET, [remoteHost UTF8String], &IPaddr);
	host = gethostbyaddr((char *) &IPaddr, sizeof(IPaddr),AF_INET);
	return [NSString stringWithUTF8String:(host->h_name)];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setRemoteHost
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)setRemoteHost:(NSString *)newHost
 *                    newHost: the new host name
 * 
 * RETURNS: True if setting the new host succeeds.
 * 
 * NOTES: Only sets a new remote host if the connection isn't open.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)setRemoteHost:(NSString *)newHost
{
	if(isConnected)
		return NO;
	newHost = [newHost retain];
	if(!newHost)
		return NO;
	
	struct in_addr IPaddr;
	struct hostent *host;
	int IPok = inet_pton(AF_INET, [newHost UTF8String], &IPaddr);
	[self willChangeValueForKey:@"remoteHost"];
	if(!IPok) {
		host = gethostbyname([newHost UTF8String]);
		if(host) {
			[newHost release];
			char ipchar[16];
			inet_ntop(AF_INET,host->h_addr_list[0], ipchar, sizeof(ipchar));
			newHost = [NSString stringWithUTF8String:ipchar];
		} else {
			[self didChangeValueForKey:@"remoteHost"];
			return NO;
		}
	}
	[remoteHost release];
	remoteHost = newHost;
	[self didChangeValueForKey:@"remoteHost"];
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    remotePort
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (int)remotePort
 * 
 * RETURNS: The remote port
 * 
 * NOTES: The remote port for the current connection.
 *
 *----------------------------------------------------------------------------*/
- (int)remotePort
{
	return remotePort;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setRemotePort
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)setRemotePort:(int)newPort
 *                    newPort: the new remote port
 * 
 * RETURNS: True on success, false if currently connected.
 * 
 * NOTES: Sets a new remote port only if not currently connected.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)setRemotePort:(int)newPort
{
	if(isConnected)
		return NO;
	[self willChangeValueForKey:@"remotePort"];
	remotePort = newPort;
	[self didChangeValueForKey:@"remotePort"];
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    isConnected
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)isConnected
 * 
 * RETURNS: True if connected
 * 
 * NOTES: Returns the current state of the connection.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)isConnected
{
	return isConnected;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setIsConnected
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)setIsConnected:(BOOL)flag
 * 
 * RETURNS: void
 * 
 * NOTES: Sets the current connection state.
 *
 *----------------------------------------------------------------------------*/
- (void)setIsConnected:(BOOL)flag
{
	[self willChangeValueForKey:@"isConnected"];
	isConnected = flag;
	[self didChangeValueForKey:@"isConnected"];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    connectionTimeout
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (int)connectionTimeout
 * 
 * RETURNS: The value of the connection timeout.
 * 
 * NOTES: Returns the value of the current connection timeout.
 *
 *----------------------------------------------------------------------------*/
- (int)connectionTimeout
{
	if(connectionTimeout < 1)
		return DEFAULT_CONNECTION_TIMEOUT;
	return connectionTimeout;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setConnectionTimeout
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)setConnectionTimeout:(int)newTimeout
 *                    newTimeout: the connection timeout in seconds
 * 
 * RETURNS: void
 * 
 * NOTES: Sets the connection timeout.
 *
 *----------------------------------------------------------------------------*/
- (void)setConnectionTimeout:(int)newTimeout
{
	[self willChangeValueForKey:@"connectionTimeout"];
	connectionTimeout = newTimeout;
	[self didChangeValueForKey:@"connectionTimeout"];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    defaultStringEncoding
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSStringEncoding)defaultStringEncoding
 * 
 * RETURNS: The default string encoding method
 * 
 * NOTES: Returns the current string encoding method.
 *
 *----------------------------------------------------------------------------*/
- (NSStringEncoding)defaultStringEncoding
{
	return defaultStringEncoding;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setDefaultStringEncoding
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)setDefaultStringEncoding:(NSStringEncoding)encoding
 *                    encoding: the string encoding method to be used
 * 
 * RETURNS: void
 * 
 * NOTES: Sets the default string encoding.
 *
 *----------------------------------------------------------------------------*/
- (void)setDefaultStringEncoding:(NSStringEncoding)encoding
{
	[self willChangeValueForKey:@"defaultStringEncoding"];
	defaultStringEncoding = encoding;
	[self didChangeValueForKey:@"defaultStringEncoding"];
}

@end

#pragma mark Server

@implementation Server

#pragma mark Class Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
+ (id)server
{
	self = [[self alloc] init];
	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
+ (id)serverWithPort:(int)initPort delegate:(id)initDelegate
{
	self = [[self alloc] initWithPort:initPort delegate:initDelegate];
	return self;
}

#pragma mark Instance Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (id)init
{
	if(self = [super init]) {
		serverPort = 0;
		serverDelegate = nil;
		connections = [[NSMutableArray alloc] init];
		lAddr = ListenAll;
		isListening = NO;
	}
	
	return self;	
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (id)initWithPort:(int)initPort delegate:(id)initDelegate
{
	if(self = [super init]) {
		serverPort = initPort;
		serverDelegate = [initDelegate retain];
		connections = [[NSMutableArray alloc] init];
		lAddr = ListenAll;
		isListening = NO;
	}
	
	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)dealloc
{
	if(isListening) {
		[[NSNotificationCenter defaultCenter] removeObserver:self];
		[fileHandle release];
	}
	[connections release];
	[serverDelegate release];
	[super dealloc];
}

#pragma mark Listening Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (ClientServerInit)startListening
{
	if(isListening)
		return InitError_Listening;
	if(serverPort < 1)
		return InitError_Port;
	if(!serverDelegate)
		return InitError_Delegate;
	
	int filedescriptor = -1;
	CFSocketRef socket = CFSocketCreate(kCFAllocatorDefault, PF_INET, SOCK_STREAM, IPPROTO_TCP, 1, NULL, NULL);
	
	if(socket) {
		
		filedescriptor = CFSocketGetNative(socket);
		
		//this code prevents the socket from existing after the server has crashed or been forced to close
		
		int yes = 1;
		setsockopt(filedescriptor, SOL_SOCKET, SO_REUSEADDR, (void *)&yes, sizeof(yes));
		
		struct sockaddr_in addr4;
		memset(&addr4, 0, sizeof(addr4));
		addr4.sin_len = sizeof(addr4);
		addr4.sin_family = AF_INET;
		addr4.sin_port = htons(serverPort);
		if(lAddr == ListenLoopback)
			addr4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		else if(lAddr == ListenLocal)
			addr4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		else if((lAddr == ListenOther) && (lStrAddr))
			inet_pton(AF_INET, lStrAddr, &addr4.sin_addr);
		else
			addr4.sin_addr.s_addr = htonl(INADDR_ANY); //any network address, e.g. 127.0.0.1, 168.192.2.101 etc;
		// inet_pton(AF_INET, "127.0.0.1", &addr4.sin_addr); would set the listening IP to only 127.0.0.1
		NSData *address4 = [NSData dataWithBytes:&addr4 length:sizeof(addr4)];
		
		if (kCFSocketSuccess != CFSocketSetAddress(socket, (CFDataRef)address4))
			return InitError_Bind;
		
	} else {
		return InitError_NoSocket;
	}
	
	fileHandle = [[NSFileHandle alloc] initWithFileDescriptor:filedescriptor
											   closeOnDealloc:YES];
	NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
	[nc addObserver:self
		   selector:@selector(newConnection:)
			   name:NSFileHandleConnectionAcceptedNotification
			 object:nil];
	[fileHandle acceptConnectionInBackgroundAndNotify];
	
	isListening = YES;
	return InitOK;
	
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)stopListening
{
	if(!isListening)
		return; //Server is not listening
	
	//close every connection:
	while ([connections count] != 0) {
		[self closeConnection:[connections objectAtIndex:0]];
	}
	
	[[NSNotificationCenter defaultCenter] removeObserver:self]; //don't handle new requests;
	CFSocketRef socket = CFSocketCreateWithNative(kCFAllocatorDefault,[fileHandle fileDescriptor],1,NULL,NULL);
	CFSocketInvalidate(socket);
	CFRelease(socket);
	[fileHandle release];
	
	//server is not running anymore
	isListening = NO;
}

#pragma mark Accessor Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (BOOL)isListening
{
	return isListening;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (BOOL)setServerPort:(int)newPort
{
	if(!isListening)
		serverPort = newPort;
	else
		return NO;
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (int)serverPort
{
	return serverPort;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (BOOL)setServerDelegate:(id)newDelegate
{
	if(!isListening) {
		[serverDelegate release];
		serverDelegate = newDelegate;
	} else {
		return NO;
	}
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (ServerListenAddress)listenAddress
{
	return lAddr;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (NSString *)listenAddressAsString
{
	return [NSString stringWithUTF8String:lStrAddr];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)setListenAddress:(ServerListenAddress)newLAddr
{
	lAddr = newLAddr;
	NSString *tmpListenAddr;
	if(lAddr == ListenLoopback)
		tmpListenAddr = @"127.0.0.1";
	else if(lAddr == ListenLocal) 
		tmpListenAddr = @"127.0.0.1";
	else
		tmpListenAddr = @"0.0.0.0";
	
	strncpy(lStrAddr,[tmpListenAddr UTF8String],15);
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (BOOL)setListenAddressByString:(NSString *)newStrAddr
{
	if(!isListening) {
		[self setListenAddress:ListenOther]; //needs to be called
		strncpy(lStrAddr, [newStrAddr UTF8String], 15); //before address is copied here
	} else {
		return NO;
	}
	return YES;
}

#pragma mark Delegate Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)processMessage:(NSString *)message orData:(NSData *)data fromConnection:(ClientServerConnection *)con;
{
	if([serverDelegate respondsToSelector:@selector(processMessage:orData:fromConnection:)])
		[serverDelegate processMessage:message orData:data fromConnection:con];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)processNewConnection:(ClientServerConnection *)con
{
	if([serverDelegate respondsToSelector:@selector(processNewConnection:)])
		[serverDelegate processNewConnection:con];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)processClosingConnection:(ClientServerConnection *)con
{
	if([serverDelegate respondsToSelector:@selector(processClosingConnection:)])
		[serverDelegate processClosingConnection:con];
}

#pragma mark Connections

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (NSArray *)connections
{
	return connections;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)newConnection:(NSNotification *)notification
{
	NSDictionary *userInfo = [notification userInfo];
	NSFileHandle *remoteFileHandle = [userInfo objectForKey:
									  NSFileHandleNotificationFileHandleItem];
	NSNumber *errorNo = [userInfo objectForKey:@"NSFileHandleError"];
	if(errorNo) {
		return;
	}
	
	[fileHandle acceptConnectionInBackgroundAndNotify];
	
	if(remoteFileHandle) {
		ClientServerConnection *connection = [[ClientServerConnection alloc] initWithFileHandle:remoteFileHandle delegate:self];
		if(connection) {
			NSIndexSet *insertedIndexes = [NSIndexSet indexSetWithIndex:[connections count]];
            [self willChange:NSKeyValueChangeInsertion
             valuesAtIndexes:insertedIndexes forKey:@"connections"];
            [connections addObject:connection];
            [self didChange:NSKeyValueChangeInsertion
			valuesAtIndexes:insertedIndexes forKey:@"connections"];
            [connection release];
			[self processNewConnection:connection];
		}
	}
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)closeConnection:(ClientServerConnection *)con
{
	[self processClosingConnection:con];
	int connectionIndex = [connections indexOfObjectIdenticalTo:con];
    if(connectionIndex == (int)NSNotFound)
		return;
	NSIndexSet *connectionIndexSet = [NSIndexSet indexSetWithIndex:connectionIndex];
    [self willChange:NSKeyValueChangeRemoval valuesAtIndexes:connectionIndexSet
              forKey:@"connections"];
    [connections removeObjectsAtIndexes:connectionIndexSet];
	
	// The connection was released when added to the array
    [self didChange:NSKeyValueChangeRemoval valuesAtIndexes:connectionIndexSet
             forKey:@"connections"];
}

#pragma mark Sending Data

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (BOOL)sendData:(NSData *)data toConnection:(ClientServerConnection *)con
{
	NSFileHandle *remoteFileHandle = [con fileHandle];
	@try {
        [remoteFileHandle writeData:data];
    }
    @catch (NSException *exception) {
		return NO;
    }
	return YES;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (BOOL)sendString:(NSString *)string toConnection:(ClientServerConnection *)con
{
	return [self sendData:[string dataUsingEncoding:NSASCIIStringEncoding] toConnection:con];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)sendDataToAll:(NSData *)data
{
	NSEnumerator *en = [connections objectEnumerator];
	ClientServerConnection *con;
	
	while(con = [en nextObject])
		[self sendData:data toConnection:con];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)sendStringToAll:(NSString *)string
{
	[self sendDataToAll:[string dataUsingEncoding:NSASCIIStringEncoding]];
}

@end

#pragma mark Common Methods

@interface ClientServerConnection (PrivateMethods)

- (void)setRemoteAddress:(NSString *)newAddress;
- (void)setRemotePort:(int)newPort;

@end

@implementation ClientServerConnection

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (id)initWithFileHandle:(NSFileHandle *)fh delegate:(id)initDelegate
{
    if(self = [super init]) {
		fileHandle = [fh retain];
		connectionDelegate = [initDelegate retain];
		
		// Get IP address of remote client
		CFSocketRef socket = CFSocketCreateWithNative(kCFAllocatorDefault, [fileHandle fileDescriptor], kCFSocketNoCallBack, NULL, NULL);
		CFDataRef addrData = CFSocketCopyPeerAddress(socket);
		CFRelease(socket);
		
		if(addrData) {
			struct sockaddr_in *sock = (struct sockaddr_in *)CFDataGetBytePtr(addrData);
			[self setRemotePort:(sock->sin_port)];
			char *naddr = inet_ntoa(sock->sin_addr);
			[self setRemoteAddress:[NSString stringWithCString:naddr encoding:NSUTF8StringEncoding]];
			CFRelease(addrData);
		} else {
			[self setRemoteAddress:@"NULL"];
		}
		
		// Register for notification when data arrives
		NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
		[nc addObserver:self
			   selector:@selector(dataReceivedNotification:)
				   name:NSFileHandleReadCompletionNotification
				 object:fileHandle];
		[fileHandle readInBackgroundAndNotify];
	}
	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	[connectionDelegate release];
	[fileHandle closeFile];
	[fileHandle release];
	[remoteAddress release];
	[super dealloc];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (NSString *)description
{
	return [NSString stringWithFormat:@"%@:%d",[self remoteAddress],[self remotePort]];
}

#pragma mark Accessor Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (NSFileHandle *)fileHandle 
{
	return fileHandle;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)setRemoteAddress:(NSString *)newAddress
{
	[remoteAddress release];
	remoteAddress = [newAddress copy];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (NSString *)remoteAddress
{
	return remoteAddress;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)setRemotePort:(int)newPort
{
	remotePort = newPort;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (int)remotePort
{
	return remotePort;
}

#pragma mark Notification Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    
 * 
 * DATE:        October 4, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   
 * 
 * RETURNS: 
 * 
 * NOTES: 
 *
 *----------------------------------------------------------------------------*/
- (void)dataReceivedNotification:(NSNotification *)notification
{
	NSData *data = [[notification userInfo] objectForKey:NSFileHandleNotificationDataItem];
	
	if ([data length] == 0) {
		// NSFileHandle's way of telling us that the client closed the connection
		[connectionDelegate closeConnection:self];
		return;
	} else {
		[fileHandle readInBackgroundAndNotify];
		NSString *received = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		if([received characterAtIndex:0] == 0x04) { // End-Of-Transmission sent by client
			return;
		}
		[connectionDelegate processMessage:received orData:data fromConnection:self];
	}
}

@end