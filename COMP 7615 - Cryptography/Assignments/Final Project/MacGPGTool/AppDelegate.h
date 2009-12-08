#include <Cocoa/Cocoa.h>
#include <MacGPGME/MacGPGME.h>

@interface AppDelegate : NSObject
{
    NSArray	*keys;
    NSArray	*selectedKeyUserIDsWithSignatures;
    
	// Key Search
    IBOutlet NSTableView	*keyTableView;
    IBOutlet NSTextField	*searchPatternTextField;
    IBOutlet NSTextView		*xmlTextView;
    IBOutlet NSBox			*mainKeyBox;
    IBOutlet NSButton		*secretKeySwitch;
	
	// Algorithm & Length
    IBOutlet NSTextField	*algorithmTextField;
    IBOutlet NSTextField	*lengthTextField;
	
	// Key Abilities
    IBOutlet NSButtonCell	*hasSecretSwitch;
    IBOutlet NSButtonCell	*canExcryptSwitch;
    IBOutlet NSButtonCell	*canSignSwitch;
    IBOutlet NSButtonCell	*canCertifySwitch;
	
	// Key Info
    IBOutlet NSButtonCell	*isRevokedSwitch;
    IBOutlet NSButtonCell	*isInvalidSwitch;
    IBOutlet NSButtonCell	*hasExpiredSwitch;
    IBOutlet NSButtonCell	*isDisabledSwitch;
	
	// Passphrase
    IBOutlet NSTextField	*passphraseDescriptionTextField;
    IBOutlet NSTextField	*passphraseTextField;
    IBOutlet NSPanel		*passphrasePanel;
	
	// Encryption
    IBOutlet NSTextField	*encryptionInputFilenameTextField;
    IBOutlet NSButtonCell	*encryptionArmoredSwitch;
    IBOutlet NSTextField	*encryptionOutputFilenameTextField;
    IBOutlet NSPanel		*encryptionPanel;
    IBOutlet NSButtonCell	*trustSwitch;
	
	// Signing
    IBOutlet NSTextField	*signingInputFilenameTextField;
    IBOutlet NSButtonCell	*signingArmoredSwitch;
    IBOutlet NSButtonCell	*signingDetachedSwitch;
    IBOutlet NSTextField	*signingOutputFilenameTextField;
    IBOutlet NSPanel		*signingPanel;
}

- (IBAction) searchKeys:(id)sender;

- (IBAction) encrypt:(id)sender;
- (IBAction) decrypt:(id)sender;
- (IBAction) askInputFileForEncryption:(id)sender;
- (IBAction) askOutputFileForEncryption:(id)sender;

- (IBAction) sign:(id)sender;
- (IBAction) askInputFileForSigning:(id)sender;
- (IBAction) askOutputFileForSigning:(id)sender;

- (IBAction) verify:(id)sender;
- (IBAction) verifyDetachedSignature:(id)sender;

- (IBAction) ok:(id)sender;
- (IBAction) cancel:(id)sender;

@end