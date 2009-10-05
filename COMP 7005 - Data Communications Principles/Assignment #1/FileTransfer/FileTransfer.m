#import <Foundation/Foundation.h>
#import <signal.h>
#import "ApplicationDelegate.h"

BOOL isRunning = YES;

void sigint_handler(int sig);
void run_server(void);
void run_client(NSString *serverIP);

int main (int argc, const char * argv[]) {
	signal(SIGINT, sigint_handler);
	
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	// Manage arguments
	NSUserDefaults *args = [NSUserDefaults standardUserDefaults];
	
	// Determine command-line arguments
	if ([args boolForKey:@"server"])
		run_server();
	else if ([args stringForKey:@"client"])
		run_client([args stringForKey:@"client"]);
	else {
		printf("Usage: %s [-server] [-client remote IP]\n", argv[0]);
	}

	
    [pool drain];
    return 0;
}

void run_server() {
	NSLog(@"Starting server...");
	ApplicationDelegate *appDelegate = [[ApplicationDelegate alloc] init];
	[appDelegate startServer];
	
	NSLog(@"Server running: Press CTRL+C to stop the server.");
	while (isRunning)
		sleep(1);
	
	NSLog(@"Shutting down server...");
	[appDelegate stopServer];
}

void run_client(NSString *serverIP) {
}

void sigint_handler(int sig) {
	printf("\n");
	isRunning = NO;
}