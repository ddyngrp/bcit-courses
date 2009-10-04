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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * RETURNS: YES if data was sent, NO on an error.
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
 * DATE:        August 27, 2009
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
 * RETURNS: YES if string was sent, NO on an error.
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
 * DATE:        August 27, 2009
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
 * RETURNS: YES if string was sent, NO on an error.
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * RETURNS: YES on success, NO if currently connected.
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
 * DATE:        August 27, 2009
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
 * RETURNS: YES if connected
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * DATE:        August 27, 2009
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
 * FUNCTION:    server
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)server
 * 
 * RETURNS: Server object with standard setup.
 * 
 * NOTES: A Server object with no port and delegate set.
 *        Listens on all addresses.
 *
 *----------------------------------------------------------------------------*/
+ (id)server
{
	self = [[self alloc] init];
	return self;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    serverWithPort
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)serverWithPort:(int)initPort delegate:(id)initDelegate
 *                  initPort: port which the server is supposed to listen on.
 *                  delegate: delegate will be sent the processing messages.
 * 
 * RETURNS: Returns a Server object with a given port and delegate
 * 
 * NOTES: A Server object, fully initialized, listening on all addresses.
 *
 *----------------------------------------------------------------------------*/
+ (id)serverWithPort:(int)initPort delegate:(id)initDelegate
{
	self = [[self alloc] initWithPort:initPort delegate:initDelegate];
	return self;
}

#pragma mark Instance Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    init
 * 
 * DATE:        August 27, 2009
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
 * RETURNS: Returns a Server object with standard setup.
 * 
 * NOTES: Creates a Server object with no port and delegate set.
 *        Set to listen on all addresses.
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
 * FUNCTION:    initWithPort
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)initWithPort:(int)initPort delegate:(id)initDelegate
 *                  initPort: port which the server is supposed to listen on.
 *                  delegate: delegate will be sent the processing messages.
 * 
 * RETURNS: Returns a Server object with a given port and delegate.
 * 
 * NOTES: Creates a Server object with a port and delegate set.
 *        Set to listen on all addresses.
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
 * FUNCTION:    dealloc
 * 
 * DATE:        August 27, 2009
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
 * NOTES: Closes all current connections and performs garbage collection.
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
 * FUNCTION:    startListening
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (ClientServerInit)startListening
 * 
 * RETURNS: Returns an Init value, see constants for details.
 * 
 * NOTES: Starts the Server, if it was initialized correctly,
 *        and returns the status as a Init value.
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
 * FUNCTION:    stopListening
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)stopListening
 * 
 * RETURNS: void
 * 
 * NOTES: Closes all connections and stops listening for new connections.
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
 * FUNCTION:    isListening
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)isListening
 * 
 * RETURNS: Returns YES if the server is listening. Otherwise returns NO.
 * 
 * NOTES: Changes to the servers listening port, address as well as delegate
 *        may be only made when it is not listening.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)isListening
{
	return isListening;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setServerPort
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)setServerPort:(int)newPort
 *                    newPort: port which the server is supposed to listen on
 * 
 * RETURNS: Returns YES if the port could be changed, otherwise NO
 * 
 * NOTES: Sets the port of the server, and returns a BOOL value indicating
 *        success or failure.
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
 * FUNCTION:    serverPort
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (int)serverPort
 * 
 * RETURNS: Returns an int value representing the port number.
 * 
 * NOTES: Returns the port on which the server is set up to listen.
 *
 *----------------------------------------------------------------------------*/
- (int)serverPort
{
	return serverPort;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setServerDelegate
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)setServerDelegate:(id)newDelegate
 *                    newDelegate: the new delegate to listen for messages
 * 
 * RETURNS: YES if the delegate could be set, NO if the server is listening.
 * 
 * NOTES: Sets a new delegate to listen to incoming events.
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
 * FUNCTION:    listenAddress
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (ServerListenAddress)listenAddress
 * 
 * RETURNS: Returns the listen address represented by a ListenAddress value.
 * 
 * NOTES: Returns a ListenAddress value representing the general listen
 *        address. See constants for details.
 *
 *----------------------------------------------------------------------------*/
- (ServerListenAddress)listenAddress
{
	return lAddr;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    listenAddressAsString
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSString *)listenAddressAsString
 * 
 * RETURNS: Returns the listen address represented by a NSString object.
 * 
 * NOTES: Returns the IP Address the Server is listening on as a NSString object.
 *
 *----------------------------------------------------------------------------*/
- (NSString *)listenAddressAsString
{
	return [NSString stringWithUTF8String:lStrAddr];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setListenAddress
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)setListenAddress:(ServerListenAddress)newLAddr
 *                    newLAddr: new address to listen on
 * 
 * RETURNS: Returns YES if the address could be changed, otherwise NO
 * 
 * NOTES: Sets the address of the server with one of the preset ListenAddress
 *        values. Returns BOOL value indicating success or failure.
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
 * FUNCTION:    setListenAddressByString
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)setListenAddressByString:(NSString *)newStrAddr
 *                    newStrAddr: address to listen on
 * 
 * RETURNS: Returns YES if the address could be changed, otherwise NO
 * 
 * NOTES: Sets the listen address of the server to be the specified.
 *        Returns BOOL value indicating success or failure.
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
 * FUNCTION:    processMessage
 * 
 * DATE:        August 27, 2009
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
 *                    message: string that has been received
 *                    data: raw data as an NSData object
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Sent to the delegate after data has been received by one of the
 *        servers connections.
 *
 *----------------------------------------------------------------------------*/
- (void)processMessage:(NSString *)message orData:(NSData *)data fromConnection:(ClientServerConnection *)con
{
	if([serverDelegate respondsToSelector:@selector(processMessage:orData:fromConnection:)])
		[serverDelegate processMessage:message orData:data fromConnection:con];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    processNewConnection
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)processNewConnection:(ClientServerConnection *)con
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Will be sent the delegate after a new connection has been
 *        successfully established
 *
 *----------------------------------------------------------------------------*/
- (void)processNewConnection:(ClientServerConnection *)con
{
	if([serverDelegate respondsToSelector:@selector(processNewConnection:)])
		[serverDelegate processNewConnection:con];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    processClosingConnection
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)processClosingConnection:(ClientServerConnection *)con
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Will be sent the delegate just before the connection will be closed.
 *
 *----------------------------------------------------------------------------*/
- (void)processClosingConnection:(ClientServerConnection *)con
{
	if([serverDelegate respondsToSelector:@selector(processClosingConnection:)])
		[serverDelegate processClosingConnection:con];
}

#pragma mark Connections

/*-----------------------------------------------------------------------------
 * FUNCTION:    connections
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSArray *)connections
 * 
 * RETURNS: Returns an NSArray object containing all connections
 * 
 * NOTES: Returns an Array containing all connections.
 *
 *----------------------------------------------------------------------------*/
- (NSArray *)connections
{
	return connections;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    newConnection
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)newConnection:(NSNotification *)notification
 * 
 * RETURNS: void
 * 
 * NOTES: Called upon new incomming connections.
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
		ClientServerConnection *connection = [[ClientServerConnection alloc]
											  initWithFileHandle:remoteFileHandle delegate:self];

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
 * FUNCTION:    closeConnection
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)closeConnection:(ClientServerConnection *)con
 *                    con: connection the message was received from
 * 
 * RETURNS: void
 * 
 * NOTES: Closes the given connection.
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
 * FUNCTION:    sendData
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)sendData:(NSData *)data
 *                             toConnection:(ClientServerConnection *)con
 (                    data: data to be sent
 *                    con: connection the message was received from
 * 
 * RETURNS: Returns YES if the data was sent, otherwise NO
 * 
 * NOTES: Sends data in form of an NSData object to the given connection.
 *        Returns BOOL value indicating success or failure.
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
 * FUNCTION:    sendString
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (BOOL)sendString:(NSString *)string
 *                               toConnection:(ClientServerConnection *)con
 *                    string: the string to be sent.
 *                    con: connection the message was received from
 * 
 * RETURNS: Returns YES if the string could be sent, otherwise NO
 * 
 * NOTES: Sends a String of an NSData object to the given connection.
 *        Returns BOOL value indicating success or failure.
 *
 *----------------------------------------------------------------------------*/
- (BOOL)sendString:(NSString *)string toConnection:(ClientServerConnection *)con
{
	return [self sendData:[string dataUsingEncoding:NSASCIIStringEncoding] toConnection:con];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    sendDataToAll
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)sendDataToAll:(NSData *)data
 *                    data: data to be sent
 * 
 * RETURNS: void
 * 
 * NOTES: Sends the given data to all connected clients.
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
 * FUNCTION:    sendStringToAll
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)sendStringToAll:(NSString *)string
 *                    string: string to be sent
 * 
 * RETURNS: void
 * 
 * NOTES: Sends the given string to all connected clients.
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
 * FUNCTION:    initWithFileHandle
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (id)initWithFileHandle:(NSFileHandle *)fh delegate:(id)initDelegate
 *                  fh: file handle used by the connection
 *                  initDelegate: delegate that listens for events
 * 
 * RETURNS: ClientServerConnection object already connected.
 * 
 * NOTES: Returns a ClientServerConnection connected by the given file handle,
 *        waiting for data, sending it to the delegate.
 *
 *----------------------------------------------------------------------------*/
- (id)initWithFileHandle:(NSFileHandle *)fh delegate:(id)initDelegate
{
    if(self = [super init]) {
		fileHandle = [fh retain];
		connectionDelegate = [initDelegate retain];
		
		// Get IP address of remote client
		CFSocketRef socket = CFSocketCreateWithNative(kCFAllocatorDefault,
													  [fileHandle fileDescriptor],
													  kCFSocketNoCallBack, NULL, NULL);
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
 * FUNCTION:    dealloc
 * 
 * DATE:        August 27, 2009
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
 * NOTES: Closes all open file handles and connections.
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
 * FUNCTION:    description
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSString *)description
 * 
 * RETURNS: A string description of the remote connection
 * 
 * NOTES: Returns a formatted string containing the remote connection info.
 *
 *----------------------------------------------------------------------------*/
- (NSString *)description
{
	return [NSString stringWithFormat:@"%@:%d",[self remoteAddress],[self remotePort]];
}

#pragma mark Accessor Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    fileHandle
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSFileHandle *)fileHandle 
 * 
 * RETURNS: The socket's file handle
 * 
 * NOTES: Returns the file handle for the current socket
 *
 *----------------------------------------------------------------------------*/
- (NSFileHandle *)fileHandle 
{
	return fileHandle;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setRemoteAddress
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)setRemoteAddress:(NSString *)newAddress
 *                    newAddress: new remote address
 * 
 * RETURNS: void
 * 
 * NOTES: Sets a new remote address by first releasing the current address.
 *
 *----------------------------------------------------------------------------*/
- (void)setRemoteAddress:(NSString *)newAddress
{
	[remoteAddress release];
	remoteAddress = [newAddress copy];
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    remoteAddress
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (NSString *)remoteAddress
 * 
 * RETURNS: The current remote address
 * 
 * NOTES: Returns the remote address for the current connection.
 *
 *----------------------------------------------------------------------------*/
- (NSString *)remoteAddress
{
	return remoteAddress;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    setRemotePort
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)setRemotePort:(int)newPort
 *                    newPort: the new remote port
 * 
 * RETURNS: void
 * 
 * NOTES: Sets a new remote port for the current connection.
 *
 *----------------------------------------------------------------------------*/
- (void)setRemotePort:(int)newPort
{
	remotePort = newPort;
}

/*-----------------------------------------------------------------------------
 * FUNCTION:    remotePort
 * 
 * DATE:        August 27, 2009
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
 * RETURNS: The current port for the remote connection.
 * 
 * NOTES: Returns the current remote port used in the current connection.
 *
 *----------------------------------------------------------------------------*/
- (int)remotePort
{
	return remotePort;
}

#pragma mark Notification Methods

/*-----------------------------------------------------------------------------
 * FUNCTION:    dataReceivedNotification
 * 
 * DATE:        August 27, 2009
 * 
 * REVISIONS:   
 * 
 * DESIGNER:    David J. Koster <code@david-koster.de>
 * 
 * PROGRAMMER:  David J. Koster <code@david-koster.de>
 *              Steffen L. Norgren <ironix@trollop.org>
 * 
 * INTERFACE:   (void)dataReceivedNotification:(NSNotification *)notification
 * 
 * RETURNS: void
 * 
 * NOTES: Determines when data has been received and notifies the delegate.
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