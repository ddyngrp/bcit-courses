/*
 * A number of items that could, and should, be updated when a different item is
 * changed are set only when they are made visible. This should not be. The controller
 * should maintain state in a manner similar to how it handles changing the key type;
 * by using an action that maintains all nib controls in a constant state.
 */
#import "GenerateKeyController.h"

@implementation GenerateKeyController

static GenerateKeyController *_sharedInstance = nil;

- (id)initWithWindowNibName:(NSString *)windowNibName
{
	if ((self = [super initWithWindowNibName:windowNibName])) {
		shouldAllowPerformClose = YES;
		dirty = NO;
		newKey = [[NSMutableDictionary alloc] initWithCapacity:8];
	}
	allowBlankPassPhrase = NO;
	return self;
}

- (void)dealloc
{
	[newKey dealloc];
	[super dealloc];
}

+ (id)sharedInstance
{
	if (_sharedInstance == nil) {
		_sharedInstance = [[self alloc] initWithWindowNibName:@"GenerateKeyAssistant"];
	}
	return _sharedInstance;
}

- (void)awakeFromNib
{
	[[self window] setDelegate:self];
	allowBlankPassPhrase = NO;
}

- (IBAction)introduceAssistant:(id)sender
{
	[backUpButton setEnabled:NO];
	[expertView removeFromSuperview];
	if (sender == backUpButton) {
		[keyTypeView removeFromSuperview];
	}
	[windowView addSubview:introductionView];
	if ([useAssistant state]) {
		[continueButton setAction:@selector(selectKeyType:)];
	} else {
		[continueButton setAction:@selector(expertSettings:)];
	}
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														  @"Introduction",
														  @"GenerateKeyAssistant",
														  @"Introduction")];
}

- (IBAction)selectKeyType:(id)sender
{
	if (sender == continueButton) {
		[introductionView removeFromSuperview];
	} else {
		[keySizeView removeFromSuperview];
	}
	[windowView addSubview:keyTypeView];
	[backUpButton setEnabled:YES];
	[backUpButton setAction:@selector(introduceAssistant:)];
	[continueButton setAction:@selector(selectKeySize:)];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														@"Select the Kind of Key",
														@"GenerateKeyAssistant",
														@"KeyType")];
}

- (IBAction)selectKeySize:(id)sender
{
	if (sender == continueButton) {
		[keyTypeView removeFromSuperview];
	} else {
		[expirationView removeFromSuperview];
	}
	[windowView addSubview:keySizeView];
	[backUpButton setAction:@selector(selectKeyType:)];
	[continueButton setAction:@selector(setKeyExpirationDate:)];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														@"Select the Key Size",
														@"GenerateKeyAssistant",
														@"KeySize")];
}

- (IBAction)setKeyExpirationDate:(id)sender
{
	if (sender == continueButton) {
		if ([self validateKeySize:(id)sender]) {
			[keySizeView removeFromSuperview];
		} else {
			return;
		}
	} else {
		[identityView removeFromSuperview];
	}
	[windowView addSubview:expirationView];
	[backUpButton setAction:@selector(selectKeySize:)];
	[continueButton setAction:@selector(setIdentity:)];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														@"Set the Expiration Date",
														@"GenerateKeyAssistant",
														@"ExpirationDate")];
}

- (IBAction)setIdentity:(id)sender
{
	if (sender == continueButton) {
		if ([self validateExpirationDate:(id)sender]) {
			[expirationView removeFromSuperview];
		} else {
			return;
		}
	} else {
		if ([showPassphrase state]) {
			[visiblePassphraseView removeFromSuperview];
		} else {
			[obscuredPassphraseView removeFromSuperview];
		}
	}
	[windowView addSubview:identityView];
	[backUpButton setAction:@selector(setKeyExpirationDate:)];
	[continueButton setAction:@selector(setPassphrase:)];
	//[continueButton setAction:@selector(confirmSettings:)];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														@"Set Your Identity",
														@"GenerateKeyAssistant",
														@"setIdentity")];
}

- (IBAction)setPassphrase:(id)sender
{
	if (sender == continueButton) {
		[identityView removeFromSuperview];
	} else {
		[confirmationView removeFromSuperview];
	}
	if (![showPassphrase state]) {
		[windowView addSubview:obscuredPassphraseView];
	} else {
		[windowView addSubview:visiblePassphraseView];
	}
	[backUpButton setAction:@selector(setIdentity:)];
	[continueButton setAction:@selector(confirmSettings:)];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														@"Set Your Passphrase",
														@"GenerateKeyAssistant",
														@"setPassphrase")];
}

- (IBAction)confirmSettings:(id)sender
{
	if (sender == continueButton) {
		if ([self validatePassphrase:(id)sender]) {
			if ([showPassphrase state]) {
				[visiblePassphraseView removeFromSuperview];
			} else {
				[obscuredPassphraseView removeFromSuperview];
			}
		} else {
			return;
		}
	}
	[windowView addSubview:confirmationView];
	[backUpButton setAction:@selector(setPassphrase:)];
	[continueButton setAction:@selector(generateKey:)];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														@"Confirm Your Selections",
														@"GenerateKeyAssistant",
														@"confirmSettings")];
	[confirmationKeySize setStringValue:[keySize stringValue]];
	if ([keyExpires state]) {
		[confirmationExpirationDate setStringValue:[expirationDate stringValue]];
	} else {
		[confirmationExpirationDate setStringValue:@""];
	}
	[confirmationFullName setStringValue:[fullName stringValue]];
	[confirmationEmailAddress setStringValue:[emailAddress stringValue]];
	[confirmationComment setStringValue:[comment stringValue]];
}

- (IBAction)generateKey:(id)sender
{
	if ([useAssistant state]) {
		[confirmationView removeFromSuperview];
		// see also setNewKeyType: and setNewKeySize:
  // this code should be replaced over time with setNewKey* methods
  // which respond to controll gerated actions
		[newKey setObject:[fullName stringValue] forKey:@"name"];
		[newKey setObject:[emailAddress stringValue] forKey:@"email"];
		if ([[comment stringValue] length]) {
			[newKey setObject:[comment stringValue] forKey:@"comment"];
		}
		if ([keyExpires state] && [[expirationDate stringValue] length]) {
			[newKey setObject:[[NSCalendarDate dateWithNaturalLanguageString:[expirationDate stringValue]] descriptionWithCalendarFormat:@"%Y-%m-%d"] forKey:@"expirationDate"];
		}
		if ([[obscuredPassphrase stringValue] length]) {
			[newKey setObject:[obscuredPassphrase stringValue] forKey:@"passphrase"];
		}
	} else {
		if ([self validateExpirationDate:nil] && [self validateKeySize:nil] && [self validateIdentity:nil]) {
			[expertView removeFromSuperview];
			// see also setNewKeyType: and setNewKeySize:
   // this code should be replaced over time with setNewKey* methods
   // which respond to controll generated actions
			[newKey setObject:[expertFullName stringValue] forKey:@"name"];
			[newKey setObject:[expertEmailAddress stringValue] forKey:@"email"];
			if ([[expertComment stringValue] length]) {
				[newKey setObject:[expertComment stringValue] forKey:@"comment"];
			}
			if ([[expertExpirationDate stringValue] length]) {
				[newKey setObject:[[NSCalendarDate dateWithNaturalLanguageString:[expertExpirationDate stringValue]] descriptionWithCalendarFormat:@"%Y-%m-%d"] forKey:@"expirationDate"];
			}
			if ([[expertPassPhrase stringValue] length]) {
				[newKey setObject:[expertPassPhrase stringValue] forKey:@"passphrase"];
			}
		} else {
			// return if any validation fails
			return;
		}
	}
	[windowView addSubview:generateView];
	[backUpButton setEnabled:NO];
	[continueButton setEnabled:NO];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														  @"Now making your key",
														  @"GenerateKeyAssistant",
														  @"generateKey")];
	shouldAllowPerformClose = NO;
	[generationProgress setIndeterminate:NO];
	[[self window] displayIfNeeded];

	[NSThread detachNewThreadSelector:@selector(generateKeyInThread:) toTarget:self withObject:newKey];
}

- (IBAction)expertSettings:(id)sender
{
	if (sender == continueButton) {
		[introductionView removeFromSuperview];
	} else {
		[confirmationView removeFromSuperview];
	}
	[windowView addSubview:expertView];
	[backUpButton setEnabled:YES];
	[backUpButton setAction:@selector(introduceAssistant:)];
	[continueButton setAction:@selector(generateKey:)];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														@"Make a new key",
														@"GenerateKeyAssistant",
														@"ExpertMode")];
}

- (IBAction)quitAssistant:(id)sender
{
	[[self window] performClose:self];
}

- (IBAction)useAddressBook:(id)sender
{
	if ([useAddressBook state]) {
		NSString *FullName;
		ABMultiValue *emailAddresses;
		ABPerson *aPerson;
		int counter;
		aPerson = [[ABAddressBook sharedAddressBook] me];
		FullName = [NSString stringWithFormat:@"%@ %@",
			[aPerson valueForProperty:kABFirstNameProperty],
			[aPerson valueForProperty:kABLastNameProperty]];
		emailAddresses = [aPerson valueForProperty:kABEmailProperty];
		[emailAddress removeAllItems];
		for (counter = 0; counter < [emailAddresses count]; counter++) {
			[emailAddress addItemWithObjectValue:[emailAddresses valueAtIndex:counter]];
		}
		[emailAddress setNumberOfVisibleItems:[emailAddress numberOfItems]];
		[emailAddress setStringValue:(NSString *)
			[emailAddresses valueAtIndex:
				[emailAddresses indexForIdentifier:
					[emailAddresses primaryIdentifier]]]];
		[emailAddress selectItemWithObjectValue:(NSString *)
			[emailAddresses valueAtIndex:
				[emailAddresses indexForIdentifier:
					[emailAddresses primaryIdentifier]]]];
		[fullName setStringValue:FullName];
		[expertEmailAddress setStringValue:(NSString *)
			[emailAddresses valueAtIndex:
				[emailAddresses indexForIdentifier:
					[emailAddresses primaryIdentifier]]]];
		[expertFullName setStringValue:FullName];
	}
}

- (IBAction)useAssistant:(id)sender
{
	if (sender == useAssistant) {
		if ([sender state]) {
			[continueButton setAction:@selector(selectKeyType:)];
		} else {
			[continueButton setAction:@selector(expertSettings:)];
		}
	}
}

- (IBAction)showPassphrase:(id)sender
{
	if (sender == showPassphrase) {
		if (![obscuredPassphrase isEqualTo:visiblePassphrase]) {
			[visiblePassphrase setStringValue:[obscuredPassphrase stringValue]];
			[confirmVisiblePassphrase setStringValue:[confirmObscuredPassphrase stringValue]];
		}
		[obscuredPassphraseView removeFromSuperview];
		[windowView addSubview:visiblePassphraseView];
		[showPassphrase setState:YES];
		[visibleShowPassphrase setState:YES];
	} else {
		if (![obscuredPassphrase isEqualTo:visiblePassphrase]) {
			[obscuredPassphrase setStringValue:[visiblePassphrase stringValue]];
			[confirmObscuredPassphrase setStringValue:[confirmVisiblePassphrase stringValue]];
		}
		[visiblePassphraseView removeFromSuperview];
		[windowView addSubview:obscuredPassphraseView];
		[showPassphrase setState:NO];
		[visibleShowPassphrase setState:NO];
	}
}

- (IBAction)keyExpires:(id)sender
{
	if (sender == expertKeyExpires) {
		[keyExpires setState:[expertKeyExpires state]];
	} else if (sender == keyExpires) {
		[expertKeyExpires setState:[keyExpires state]];
	}
	if ([keyExpires state]) {
		// assistant
		[expirationDate setSelectable:YES];
		[expirationDate setEditable:YES];
		[expirationDate setEnabled:YES];
		[expirationDateLabel setEnabled:YES];
		[integrateWithiCal setEnabled:YES];
		[expirationDate setObjectValue:[[NSCalendarDate calendarDate] dateByAddingYears:1 months:0 days:0 hours:0 minutes:0 seconds:0]];
		// expert
		[expertExpirationDate setSelectable:YES];
		[expertExpirationDate setEditable:YES];
		[expertExpirationDate setEnabled:YES];
		[expertExpirationDateLabel setEnabled:YES];
		[expertIntegrateWithiCal setEnabled:YES];
		[expertExpirationDate setObjectValue:[[NSCalendarDate calendarDate] dateByAddingYears:1 months:0 days:0 hours:0 minutes:0 seconds:0]];
	} else {
		// assistant
		[expirationDate setSelectable:NO];
		[expirationDate setEditable:NO];
		[expirationDate setEnabled:NO];
		[expirationDateLabel setEnabled:NO];
		[integrateWithiCal setEnabled:NO];
		[expirationDate setStringValue:@""];
		// expert
		[expertExpirationDate setSelectable:NO];
		[expertExpirationDate setEditable:NO];
		[expertExpirationDate setEnabled:NO];
		[expertExpirationDateLabel setEnabled:NO];
		[expertIntegrateWithiCal setEnabled:NO];
		[expertExpirationDate setStringValue:@""];
	}
}

/*!
 @method validateKeySize:
 @abstract Tests that the key size is valid
 @discussion The key size can be rejected for four reasons: it is not a number,
 it is too small, it is too large, or it is not a multiple of 32 (Elgamel) or
 64 (RSA/DSA).

 We bother the user only in the first case, as it could lead to failure later. We
 correct keys that are too small by setting the size to 1024 and of incorrect
 multiples by setting the key to the next whole multiple of 64 and notify the user
 that we corrected his key input. We ignore excessive key sizes.

 We could simply ignore every incorrectly sized key as GPG will correct an invalid
 keysize during key generation (as long as an integer is passed).

 This should be done using an NSNumberFormatter in the text field, but NSComboBox and
 NSNumberFormatter do not seem to be getting along.
 @param id The object sending us a message
 @result A boolean value indicating acceptance or failure. 
 */
- (BOOL)validateKeySize:(id)sender
{
	int keyLength;
	if (([useAssistant state] && ![keySize intValue]) || (![expertKeySize intValue])) {
		NSBeginAlertSheet(
					NSLocalizedStringFromTable(@"The selected key size is not a number.",
								@"GenerateKeyController",
								@"validateKeySize: non-numeric input error title"),
					nil,
					nil,
					nil,
					[self window],
					self,
					@selector(sheetKeySizeIsNotANumber:returnCode:contextInfo:),
					NULL,
					[self window],
					NSLocalizedStringFromTable(@"The key size must be a number.",
								@"GenerateKeyController",
								@"validateKeySize: non-numeric input error statement"),
					nil);
		return NO;
	}
	keyLength = ([useAssistant state]) ? [keySize intValue] : [expertKeySize intValue];
	// not every key has the same minimum valid size
	if (keyLength < 512) {
		keyLength = 1024;
	}
	// note that this rejects 1/2 of the values that are valid
	// should we care and test against key type and keysize?
	if (keyLength % 64) {
		keyLength = ((keyLength + 63) / 64) * 64;
	}
	if (([useAssistant state] && (keyLength != [keySize intValue])) || (keyLength != [expertKeySize intValue])) {
		[keySize setIntValue:keyLength];
		[expertKeySize setIntValue:keyLength];
		NSBeginAlertSheet(
					NSLocalizedStringFromTable(@"The selected key size was invalid.",
								@"GenerateKeyController",
								@"validateKeySize: invalid size error title"),
					nil,
					nil,
					nil,
					[self window],
					self,
					@selector(sheetKeySizeWasCorrected:returnCode:contextInfo:),
					NULL,
					[self window],
					NSLocalizedStringFromTable(@"The key size has been corrected to a valid size.",
								@"GenerateKeyController",
								@"validateKeySize: invalid size error statement"),
					nil);
		return NO;
	}
	return YES;
}

- (BOOL)validateExpirationDate:(id)sender
{
	if (![useAssistant state]) {
		[expirationDate setStringValue:[expertExpirationDate stringValue]];
		[keyExpires setState:[expertKeyExpires state]];
	}
	if ([keyExpires state]) {
		if (([(NSCalendarDate *)[NSCalendarDate dateWithNaturalLanguageString:[expirationDate stringValue]] compare:[NSDate date]]) != NSOrderedDescending) {
			NSBeginAlertSheet(
					 NSLocalizedStringFromTable(@"The expiration date is invalid.",
								 @"GenerateKeyController",
								 @"validateExpirationDate: date is valid"),
					 nil,
					 nil,
					 nil,
					 [self window],
					 self,
					 @selector(sheetInvalidExpirationDate:returnCode:contextInfo:),
					 NULL,
					 [self window],
					 NSLocalizedStringFromTable(@"The key can not be set to expire prior to its date of creation.",
								 @"GenerateKeyController",
								 @"validateExpirationDate: expiration date must be in the future"),
					 nil);
			return NO;
		}
	}
	return YES;
}

- (BOOL)validateIdentity:(id)sender
{
	return [self validatePassphrase:sender];
}

- (BOOL)validatePassphrase:(id)sender
{
	if (![useAssistant state]) {
		[obscuredPassphrase setStringValue:[expertPassPhrase stringValue]];
		[confirmObscuredPassphrase setStringValue:[expertConfirmPassPhrase stringValue]];
	} else if ([showPassphrase state]) {
		[obscuredPassphrase setStringValue:[visiblePassphrase stringValue]];
		[confirmObscuredPassphrase setStringValue:[confirmVisiblePassphrase stringValue]];
	}
	if (![[obscuredPassphrase stringValue] isEqual:[confirmObscuredPassphrase stringValue]]) {
		NSBeginAlertSheet(
					NSLocalizedStringFromTable(@"The passphrases are not the same.",
								@"GenerateKeyController",
								@"validateIdentity: passphrases do not matech error title"),
					nil,
					nil,
					nil,
					[self window],
					self,
					@selector(sheetMisMatchedPassPhrases:returnCode:contextInfo:),
					NULL,
					[self window],
					NSLocalizedStringFromTable(@"The passphrase and the confirmation must be the same.",
								@"GenerateKeyController",
								@"validateIdentity: passphrases do not matech error statement"),
					nil);
		return NO;
	}
	if (!allowBlankPassPhrase && ([[obscuredPassphrase stringValue] length] == 0)) {
		NSBeginAlertSheet(
					NSLocalizedStringFromTable(@"The passphrase is blank.",
								@"GenerateKeyController",
								@"validateIdentity: blank passphrase error title"),
					nil,
					NSLocalizedStringFromTable(@"More info",
								@"GenerateKeyController",
								@"validateIdentity: blank passphrase error button \"More info\""),
					NSLocalizedStringFromTable(@"Use blank passphrase",
								@"GenerateKeyController",
								@"validateIdentity: blank passphrase error button \"Continue\""),
					[self window],
					self,
					@selector(sheetBlankPassPhrase:returnCode:contextInfo:),
					NULL,
					[self window],
					NSLocalizedStringFromTable(@"A key with a blank passphrase may be used by anyone. Setting a blank passphrase is not recommended. Please provide a passphrase.",
								@"GenerateKeyController",
								@"validateIdentity: blank passphrase error statement"),
					nil);
		return NO;
	}
	if (([[obscuredPassphrase stringValue] length] <= 5) && ([[obscuredPassphrase stringValue] length] != 0)) {
		NSBeginAlertSheet(
					NSLocalizedStringFromTable(@"The passphrase is too short.",
					@"GenerateKeyController",
					@"validateIdentity: short passphrase error title"),
					nil,
					nil,
					nil,
					[self window],
					self,
					@selector(sheetShortPassPhrase:returnCode:contextInfo:),
					NULL,
					[self window],
					NSLocalizedStringFromTable(@"The passphrase must be six (6) or more characters in length.",
								@"GenerateKeyController",
								@"validateIdentity: short passphrase error statement"),
					nil);
		return NO;
	}
	return YES;
}

- (IBAction)setNewKeySize:(id)sender
{
//	if ([self validateKeySize:(id)sender]) {
		[newKey setObject:[NSNumber numberWithInt:[sender intValue]] forKey:@"length"];
		[newKey setObject:[NSNumber numberWithInt:[sender intValue]] forKey:@"subkeyLength"];
		[confirmationKeySize setStringValue:[sender stringValue]];
		if (sender == keySize) {
			[expertKeySize setStringValue:[sender stringValue]];
		} else {
			[keySize setStringValue:[keySize stringValue]];
		}
//	}
}

- (IBAction)setNewKeyType:(id)sender
{
	int selectedKeyType;
	selectedKeyType = [sender tag];
	[confirmationKeyType selectItemAtIndex:selectedKeyType];
	if (sender == keyType) {
		[expertKeyType selectItemAtIndex:selectedKeyType];
	} else {
		[keyType selectItemAtIndex:selectedKeyType];
	}
	switch (selectedKeyType) {
		case 0:	// DSA/ElGamel encryption
			[newKey setObject:@"DSA" forKey:@"type"];
			[newKey setObject:@"ELG-E" forKey:@"subkeyType"];
			break;
		case 1:	// DSA signature
			[newKey setObject:@"DSA" forKey:@"type"];
			[newKey removeObjectForKey:@"subkeyType"];
			break;
		case 2: // RSA signature
			[newKey setObject:@"RSA" forKey:@"type"];
			[newKey removeObjectForKey:@"subkeyType"];
			break;
		default:
			NSLog(@"error with selected key type; %i returned", selectedKeyType);
			break;
	}
}

- (BOOL)windowShouldClose:(id)sender
{
	if (shouldAllowPerformClose == NO) {
		dirty = NO;
	}
	if (sender == self) {
		return YES;
	}
	return shouldAllowPerformClose;
}

/*
 NSAlertDefaultReturn means the user pressed the default button.
 NSAlertAlternateReturn means the user pressed the alternate button.
 NSAlertOtherReturn means the user pressed the other button.
 NSAlertErrorReturn means an error occurred while running the alert panel.
 */
- (void)sheetKeySizeIsNotANumber:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
	[keySize selectItemAtIndex:[keySizesList indexOfItemWithTitle:@"1024"]];
	[keySize setObjectValue:
		[self comboBox:keySize objectValueForItemAtIndex:
			[keySize indexOfSelectedItem]]];
	[expertKeySize selectItemAtIndex:[keySize indexOfSelectedItem]];
	[expertKeySize setObjectValue:
		[self comboBox:expertKeySize objectValueForItemAtIndex:
			[expertKeySize indexOfSelectedItem]]];
}

- (void)sheetKeySizeWasCorrected:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
	// should we invalidate until the user accepts (clicks OK on) our notice?
}

- (void)sheetMisMatchedPassPhrases:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
	[obscuredPassphrase setStringValue:@""];
	[confirmObscuredPassphrase setStringValue:@""];
	[expertPassPhrase setStringValue:@""];
	[expertConfirmPassPhrase setStringValue:@""];
	[visiblePassphrase setStringValue:@""];
	[confirmVisiblePassphrase setStringValue:@""];
}

- (void)sheetShortPassPhrase:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
	[obscuredPassphrase setStringValue:@""];
	[confirmObscuredPassphrase setStringValue:@""];
	[expertPassPhrase setStringValue:@""];
	[expertConfirmPassPhrase setStringValue:@""];
	[visiblePassphrase setStringValue:@""];
	[confirmVisiblePassphrase setStringValue:@""];
}

- (void)sheetBlankPassPhrase:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
	if (returnCode == NSAlertAlternateReturn) {
		// open Help with a help page about blank passphrases.
		AHGotoPage(CFBundleGetValueForInfoDictionaryKey(CFBundleGetMainBundle(),
												  CFSTR("CFBundleHelpBookName")),
												  CFSTR("BlankPassPhrase.html"),
												  CFSTR("BlankPassPhrase"));
	} else if (returnCode == NSAlertOtherReturn) {
		if ([useAssistant state]) {
			if ([showPassphrase state]) {
				[visiblePassphraseView removeFromSuperview];
			} else {
				[obscuredPassphraseView removeFromSuperview];
			}
			[self confirmSettings:nil];
		} else {
			allowBlankPassPhrase = YES;
			[self generateKey:nil];
		}
	}
}

- (void)sheetInvalidExpirationDate:(NSWindow *)sheet returnCode:(int)returnCode contextInfo:(void *)contextInfo
{
	[expirationDate setStringValue:@""];
	[expertExpirationDate setStringValue:@""];
}

- (IBAction)showWindow:(id)sender
{
	[super showWindow:nil];
	if (!dirty) {
		dirty = YES;
		allowBlankPassPhrase = NO;
		// The use* buttons should get their initial state set from preferences
		[useAssistant setState:YES];
		[useAddressBook setState:YES];
		// we can't back past the first pane
		[backUpButton setEnabled:NO];
		// key types
		[keyType selectItemAtIndex:0];
		[self setNewKeyType:[keyType itemAtIndex:0]];
		// potential key sizes
		[keySize setNumberOfVisibleItems:[self numberOfItemsInComboBox:keySize]];
		[expertKeySize setNumberOfVisibleItems:[self numberOfItemsInComboBox:keySize]];
		[confirmationKeySize setNumberOfVisibleItems:
			[self numberOfItemsInComboBox:keySize]];
		[keySize selectItemAtIndex:[keySizesList indexOfItemWithTitle:@"1024"]];
		[self setNewKeySize:keySize];
		// use Address Book
		[self useAddressBook:nil];
		// use assistant or single pane
		if ([useAssistant state]) {
			[self introduceAssistant:nil];
		} else {
			[self expertSettings:nil];
		}
		// key expiration
		[self keyExpires:nil];
#if INTEGRATE_WITH_ICAL == 0
		[integrateWithiCal setTransparent:YES];
		[integrateWithiCal setToolTip:nil];
		[expertIntegrateWithiCal setTransparent:YES];
		[expertIntegrateWithiCal setToolTip:nil];
#endif
	}
}

- (void)generateKeyInThread:(id)keyData
{
	GPGContext *context;
	NSAutoreleasePool *pool;
				
	pool = [[NSAutoreleasePool alloc ] init];
	[[NSNotificationCenter defaultCenter]
    postNotificationName:@"GPGGenerateKeyDidBegin" object:self];
	NS_DURING
		context = [[[GPGContext alloc] init] retain];
		[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(generateKeyProgress:) name:@"GPGProgressNotification" object:nil];
		[context generateKeyFromDictionary:keyData secretKey:nil publicKey:nil];
	NS_HANDLER
		NSLog(@"%@: %@ (GPG Error:%@)", [localException name], [localException reason], [[localException userInfo] objectForKey:GPGErrorKey]);
	NS_ENDHANDLER
	[generationProgress stopAnimation:nil];
	[generationProgress setIndeterminate:NO];
	[generationProgress setDoubleValue:[generationProgress maxValue]];	
	shouldAllowPerformClose = YES;
	[generateView removeFromSuperview];
	[windowView addSubview:closingView];
	[windowTitle setStringValue:NSLocalizedStringFromTable(
														   @"Your key has been made",
														   @"GenerateKeyAssistant",
														   @"generateKey")];
	[continueButton setTitle:NSLocalizedStringFromTable(@"Finish", @"GenerateKeyAssistant", @"generateKey")];
	[continueButton setAction:@selector(quitAssistant:)];
	[continueButton setEnabled:YES];
	
	[[NSNotificationCenter defaultCenter] postNotificationName:@"GPGGenerateKeyDidEnd" object:self];
	[pool release];	
}

- (void)generateKeyProgress:(NSNotification *)notification
{
	if ([[[notification userInfo] objectForKey:@"total"] intValue]) {
		if ([generationProgress isIndeterminate]) {
			[generationProgress setIndeterminate:NO];
		}
		[generationProgress setDoubleValue:
			([[[notification userInfo] objectForKey:@"current"] floatValue] /
	[[[notification userInfo] objectForKey:@"total"] floatValue])];
	} else {
		if (![generationProgress usesThreadedAnimation]) {
			[generationProgress setUsesThreadedAnimation:YES];
		}
		if (![generationProgress isIndeterminate]) {
			[generationProgress setIndeterminate:YES];
		}
		[generationProgress startAnimation:nil];
		[generationProgress displayIfNeeded];
	}
	[[self window] displayIfNeeded];
}

- (void)controlTextDidChange:(NSNotification *)notification
{
	// really should check that the correct control is posting this notice
	[useAddressBook setState:NO];
}

- (id)comboBox:(NSComboBox *)aComboBox objectValueForItemAtIndex:(int)index
{
	return [NSNumber numberWithInt:[[[keySizesList itemAtIndex:index] title] intValue]];
}

- (int)numberOfItemsInComboBox:(NSComboBox *)aComboBox
{
	return [keySizesList numberOfItems];
}

@end
