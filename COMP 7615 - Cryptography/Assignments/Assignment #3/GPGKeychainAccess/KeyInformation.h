/* KeyInformation */

#import <Cocoa/Cocoa.h>
#import <MacGPGME/MacGPGME.h>

@interface GKAKeyInformation : NSWindowController
{
	GPGKey *key;
	NSDictionary *keyData;
	
    IBOutlet NSButton *addSignature;
    IBOutlet NSButton *addSubkey;
    IBOutlet NSButton *addUserID;
    IBOutlet NSButton *changePassphrase;
    IBOutlet NSButton *changeSubkeyExpiryDate;
    IBOutlet NSTextField *comment;
    IBOutlet NSTextField *created;
    IBOutlet NSButton *disabled;
    IBOutlet NSTextField *email;
    IBOutlet NSTextField *expires;
    IBOutlet NSTextField *fingerprint;
    IBOutlet NSTextField *keyID;
    IBOutlet NSButton *makePrimaryID;
    IBOutlet NSTextField *name;
    IBOutlet NSImageView *photoID;
    IBOutlet NSButton *removeSignature;
    IBOutlet NSButton *removeSubkey;
    IBOutlet NSButton *removeUserID;
    IBOutlet NSButton *revokeSignature;
    IBOutlet NSButton *revokeSubkey;
    IBOutlet NSTableView *signatures;
    IBOutlet NSTextField *strength;
    IBOutlet NSTextField *subkeyCreated;
    IBOutlet NSTextField *subkeyExpires;
    IBOutlet NSTableView *subkeys;
    IBOutlet NSTextField *subkeyStatus;
    IBOutlet NSTextField *subkeyStrength;
    IBOutlet NSTextField *subkeyType;
    IBOutlet NSTabView *tabs;
    IBOutlet NSPopUpButton *trust;
    IBOutlet NSTextField *type;
    IBOutlet NSTableView *userIDs;
    IBOutlet NSWindow *window;
}

- (IBAction)showWindow:(id)sender;
- (IBAction)addSignature:(id)sender;
- (IBAction)addSubkey:(id)sender;
- (IBAction)addUserID:(id)sender;
- (IBAction)changePassphrase:(id)sender;
- (IBAction)changeSubkeyExpiryDate:(id)sender;
- (IBAction)disableKey:(id)sender;
- (IBAction)makePrimaryID:(id)sender;
- (IBAction)removeSignature:(id)sender;
- (IBAction)removeSubkey:(id)sender;
- (IBAction)removeUserID:(id)sender;
- (IBAction)revokeSignature:(id)sender;
- (IBAction)revokeSubkey:(id)sender;

- (id)initWithKey:(GPGKey *)newKey;
- (void)setKey:(GPGKey *)newKey;
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem;

@end
