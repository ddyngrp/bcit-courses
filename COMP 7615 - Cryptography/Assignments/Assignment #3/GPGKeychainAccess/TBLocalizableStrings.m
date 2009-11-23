//
//  TBLocalizableStrings.m
//  GPG Keychain Access
//
//  Created by Randall Wood on Fri May 23 2003.
//  Copyright (c) 2003 MacGPG Project. All rights reserved.
//

#import "TBLocalizableStrings.h"

@implementation TBLocalizableStrings

+ (NSString *)TBBackupLabel {
	return NSLocalizedStringFromTable(@"TBBackupLabel",
			@"Toolbar",
			@"Backup");
}

+ (NSString *)TBBackupPalette {
	return NSLocalizedStringFromTable(@"TBBackupPalette",
			@"Toolbar",
			@"Backup My Keys");
}

+ (NSString *)TBBackupToolTip {
	return NSLocalizedStringFromTable(@"TBBackupToolTip",
			@"Toolbar",
			@"Backup my keys to removable media.");
}

+ (NSString *)TBDeleteLabel {
	return NSLocalizedStringFromTable(@"TBDeleteLabel",
			@"Toolbar",
			@"Delete");
}

+ (NSString *)TBDeletePalette {
	return NSLocalizedStringFromTable(@"TBDeletePalette",
			@"Toolbar",
			@"Delete Key");
}

+ (NSString *)TBDeleteToolTip {
	return NSLocalizedStringFromTable(@"TBDeleteToolTip",
			@"Toolbar",
			@"Delete the selected key.");
}

+ (NSString *)TBEditLabel {
	return NSLocalizedStringFromTable(@"TBEditLabel",
			@"Toolbar",
			@"Edit");
}

+ (NSString *)TBEditPalette {
	return NSLocalizedStringFromTable(@"TBEditPalette",
			@"Toolbar",
			@"Edit Key");
}

+ (NSString *)TBEditToolTip {
	return NSLocalizedStringFromTable(@"TBEditToolTip",
			@"Toolbar",
			@"Edit the selected key.");
}

+ (NSString *)TBExportLabel {
	return NSLocalizedStringFromTable(@"TBExportLabel",
			@"Toolbar",
			@"Export");
}

+ (NSString *)TBExportPalette {
	return NSLocalizedStringFromTable(@"TBExportPalette",
			@"Toolbar",
			@"Export Key");
}

+ (NSString *)TBExportToolTip {
	return NSLocalizedStringFromTable(@"TBExportToolTip",
			@"Toolbar",
			@"Export the selected key.");
}

+ (NSString *)TBImportLabel {
	return NSLocalizedStringFromTable(@"TBImportLabel",
			@"Toolbar",
			@"Import");
}

+ (NSString *)TBImportPalette {
	return NSLocalizedStringFromTable(@"TBImportPalette",
			@"Toolbar",
			@"Import Keys");
}

+ (NSString *)TBImportToolTip {
	return NSLocalizedStringFromTable(@"TBImportToolTip",
			@"Toolbar",
			@"Import keys from a file.");
}

+ (NSString *)TBInfoLabel {
	return NSLocalizedStringFromTable(@"TBInfoLabel",
			@"Toolbar",
			@"Info");
}

+ (NSString *)TBInfoPalette {
	return NSLocalizedStringFromTable(@"TBInfoPalette",
			@"Toolbar",
			@"Get Info");
}

+ (NSString *)TBInfoToolTip {
	return NSLocalizedStringFromTable(@"TBInfoToolTip",
			@"Toolbar",
			@"Get info about the selected key.");
}

+ (NSString *)TBGenerateLabel {
	return NSLocalizedStringFromTable(@"TBGenerateLabel",
			@"Toolbar",
			@"New");
}

+ (NSString *)TBGeneratePalette {
	return NSLocalizedStringFromTable(@"TBGeneratePalette",
			@"Toolbar",
			@"New Key");
}

+ (NSString *)TBGenerateToolTip {
	return NSLocalizedStringFromTable(@"TBGenerateToolTip",
			@"Toolbar",
			@"Generate a new key pair.");
}

+ (NSString *)TBSearchLabel {
	return NSLocalizedStringFromTable(@"TBSearchLabel",
			@"Toolbar",
			@"Search");
}

+ (NSString *)TBSearchPalette {
	return NSLocalizedStringFromTable(@"TBSearchPalette",
			@"Toolbar",
			@"Search keys");
}

+ (NSString *)TBSearchToolTip {
	return NSLocalizedStringFromTable(@"TBSearchToolTip",
			@"Toolbar",
			@"Search for a local public key.");
}

+ (NSString *)TBSignLabel {
	return NSLocalizedStringFromTable(@"TBSignLabel",
			@"Toolbar",
			@"Sign");
}

+ (NSString *)TBSignPalette {
	return NSLocalizedStringFromTable(@"TBSignPalette",
			@"Toolbar",
			@"Sign Key");
}

+ (NSString *)TBSignToolTip {
	return NSLocalizedStringFromTable(@"TBSignToolTip",
									  @"Toolbar",
									  @"Sign a public key.");
}

+ (NSString *)TBSearchLocal {
	return NSLocalizedStringFromTable(@"Keychain",
									  @"Toolbar",
									  @"Search the local keychain for a given key. (Search Field)");
}

+ (NSString *)TBSearchRemote {
	return NSLocalizedStringFromTable(@"Server",
									  @"Toolbar",
									  @"Search the key server(s) for a given key. (Search Field)");
}

+ (NSString *)TBSearchLabelLocal {
	return NSLocalizedStringFromTable(@"Keychain Search",
									  @"Toolbar",
									  @"Search the local keychain for a given key. (Label)");
}

+ (NSString *)TBSearchLabelRemote {
	return NSLocalizedStringFromTable(@"Server Search",
									  @"Toolbar",
									  @"Search the key server(s) for a given key. (Label)");
}

@end
