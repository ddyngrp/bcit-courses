/* GenerateKeyController */

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>
#import <AddressBook/AddressBook.h>
#import <MacGPGME/MacGPGME.h>

@interface GenerateKeyController : NSWindowController
{
	// window
    IBOutlet NSButton *backUpButton;
    IBOutlet NSButton *continueButton;
    IBOutlet NSTextField *windowTitle;
	IBOutlet NSView *windowView;
	BOOL shouldAllowPerformClose;

	// identity
    IBOutlet NSTextField *comment;
    //IBOutlet NSSecureTextField *confirmPassPhrase;
    IBOutlet NSComboBox *emailAddress;
    IBOutlet NSTextField *fullName;
    IBOutlet NSView *identityView;
    //IBOutlet NSSecureTextField *passPhrase;
    IBOutlet NSButton *useAddressBook;

	// passphrases
    IBOutlet NSSecureTextField *confirmObscuredPassphrase;
    IBOutlet NSTextField *confirmVisiblePassphrase;
    IBOutlet NSSecureTextField *obscuredPassphrase;
    IBOutlet NSTextField *visiblePassphrase;
	IBOutlet NSButton *showPassphrase;
	IBOutlet NSButton *visibleShowPassphrase;
	IBOutlet NSView *obscuredPassphraseView;
	IBOutlet NSView *visiblePassphraseView;

	// confirmation
    IBOutlet NSTextField *confirmationComment;
    IBOutlet NSTextField *confirmationEmailAddress;
    IBOutlet NSTextField *confirmationExpirationDate;
    IBOutlet NSTextField *confirmationFullName;
    IBOutlet NSComboBox *confirmationKeySize;
    IBOutlet NSPopUpButton *confirmationKeyType;
	IBOutlet NSView *confirmationView;

	// expert
    IBOutlet NSTextField *expertComment;
    IBOutlet NSSecureTextField *expertConfirmPassPhrase;
    IBOutlet NSTextField *expertEmailAddress;
    IBOutlet NSTextField *expertExpirationDate;
	IBOutlet NSTextField *expertExpirationDateLabel;
    IBOutlet NSTextField *expertFullName;
	IBOutlet NSButton *expertKeyExpires;
    IBOutlet NSComboBox *expertKeySize;
    IBOutlet NSPopUpButton *expertKeyType;
    IBOutlet NSSecureTextField *expertPassPhrase;
	IBOutlet NSButton *expertIntegrateWithiCal;
    IBOutlet NSView *expertView;

	// expiration
	IBOutlet NSButton *keyExpires;
    IBOutlet NSTextField *expirationDate;
	IBOutlet NSTextField *expirationDateLabel;
    IBOutlet NSView *expirationView;
    IBOutlet NSButton *integrateWithiCal;

	// generateKey
    IBOutlet NSView *generateView;
    IBOutlet NSProgressIndicator *generationProgress;
	
	// closing
	IBOutlet NSView *closingView;

	// introduction
    IBOutlet NSView *introductionView;
    IBOutlet NSButton *useAssistant;

	// keySize
    IBOutlet NSComboBox *keySize;
    IBOutlet NSView *keySizeView;

	// keyType
    IBOutlet NSPopUpButton *keyType;
    IBOutlet NSView *keyTypeView;

	// menu holding list of potential keysizes
	IBOutlet NSMenu *keySizesList;

	// new key parameters
	NSMutableDictionary *newKey;

	// flag to prevent crazy looping while validating passphrases in "expert" mode
	BOOL allowBlankPassPhrase;
	
	// flag to track just what the hell is going on
	// if dirty == false then sharedInstance is capable of guiding the user through a key generation process
	// otherwise, such a process is ongoing and not to be interupted
	BOOL dirty;
	
}

// we never want multiple key generators running at once, so we use a shared instance
// this also helps memory management by preventing multiple instances of the key generator from being generated
+ (id)sharedInstance;

// Continue/BackUp button actions
- (IBAction)introduceAssistant:(id)sender;
- (IBAction)selectKeyType:(id)sender;
- (IBAction)selectKeySize:(id)sender;
- (IBAction)setKeyExpirationDate:(id)sender;
- (IBAction)setIdentity:(id)sender;
- (IBAction)setPassphrase:(id)sender;
- (IBAction)confirmSettings:(id)sender;
- (IBAction)expertSettings:(id)sender;
- (IBAction)generateKey:(id)sender;
- (IBAction)quitAssistant:(id)sender;

// Switches
- (IBAction)useAssistant:(id)sender;
- (IBAction)useAddressBook:(id)sender;
- (IBAction)showPassphrase:(id)sender;
- (IBAction)keyExpires:(id)sender;

// newKey dictionary actions
- (IBAction)setNewKeyType:(id)sender;
- (IBAction)setNewKeySize:(id)sender;

// keySize combo boxes
- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(int)index;
- (int)numberOfItemsInComboBox:(NSComboBox *)aComboBox;

// validate actions
- (BOOL)validateKeySize:(id)sender;
- (BOOL)validateExpirationDate:(id)sender;
- (BOOL)validateIdentity:(id)sender;
- (BOOL)validatePassphrase:(id)sender;
- (BOOL)windowShouldClose:(id)sender;

// threads
- (void)generateKeyInThread:(id)keyData;

// notification recievers
- (void)generateKeyProgress:(NSNotification *)notification;
- (void)controlTextDidChange:(NSNotification *)notification;

@end
