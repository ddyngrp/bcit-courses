#import "KeyInformation.h"

@implementation GKAKeyInformation

- (id)init
{
	return [self initWithKey:nil];
}

- (id)initWithKey:(GPGKey *)newKey
{
	if ((self = [super initWithWindowNibName:@"KeyInformation"])) {
		[self setKey:newKey];
	}
	return self;
}

- (void)awakeFromNib
{
	[[self window] setDelegate:self];
}

- (IBAction)showWindow:(id)sender
{
	[super showWindow:nil];
	[[self window] orderFront:self];
}

- (void)setKey:(GPGKey *)newKey
{
	[key release];
	[keyData release];
	key = newKey;
	keyData = [key dictionaryRepresentation];
	[window setTitle:[key name]];
	[name setStringValue:[key name]];
	[email setStringValue:[key email]];
	[comment setStringValue:[key comment]];
	[photoID setImage:[[[NSImage alloc] initWithData:[key photoData]] retain]];
	[created setObjectValue:[key creationDate]];
	[expires setObjectValue:[key expirationDate]];
	[fingerprint setStringValue:[key formattedFingerprint]];
	[keyID setStringValue:[key keyID]];
	[strength setObjectValue:[NSNumber numberWithInt:[key length]]];
	[type setStringValue:[key algorithmDescription]];
}

- (IBAction)addSignature:(id)sender
{
}

- (IBAction)addSubkey:(id)sender
{
}

- (IBAction)addUserID:(id)sender
{
}

- (IBAction)changePassphrase:(id)sender
{
}

- (IBAction)changeSubkeyExpiryDate:(id)sender
{
}

- (IBAction)disableKey:(id)sender
{
}

- (IBAction)makePrimaryID:(id)sender
{
}

- (IBAction)removeSignature:(id)sender
{
}

- (IBAction)removeSubkey:(id)sender
{
}

- (IBAction)removeUserID:(id)sender
{
}

- (IBAction)revokeSignature:(id)sender
{
}

- (IBAction)revokeSubkey:(id)sender
{
}

/*
 * Since KeyInformation is the target for these toolbar items,
 * KeyInformation must validate these items.
 */
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem
{
//	if ([pkOutline numberOfSelectedRows] != 1 &&
//		[theItem action] == @selector(showWindow:)) {
//		return NO;
//	}
	return YES;
}

@end
