//
//  PKLocalisableStrings.m
//  GPG Keychain Access
//
//  Created by Simon Stapleton on Sat Feb 09 2002.
//  Copyright (C) 2001 Mac GPG Project.
//
//  This code is free software; you can redistribute it and/or modify it under
//  the terms of the GNU General Public License as published by the Free
//  Software Foundation; either version 2 of the License, or any later version.
//
//  This code is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
//  FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
//  details.
//
//  For a copy of the GNU General Public License, visit <http://www.gnu.org/> or
//  write to the Free Software Foundation, Inc., 59 Temple Place--Suite 330,
//  Boston, MA 02111-1307, USA.
//
//  More info at <http://macgpg.sourceforge.net/> or <macgpg@rbisland.cx>
//

#import "PKLocalisableStrings.h"

NSString * PKDoesNotExpire = @"PKDoesNotExpire";

NSString * PKImportSheetTitle = @"PKImportSheetTitle";
NSString * PKImportSuccessString = @"PKImportSuccessString";
NSString * PKErrorSheetTitle = @"PKErrorSheetTitle";
NSString * PKKeyListingWarningTitle = @"PKKeyListingWarningTitle";
NSString * PKKeyListingKeyFailedString = @"PKKeyListingKeyFailedString";

NSString * PKWarningSecretKeyExportString = @"PKWarningSecretKeyExportString";
NSString * PKWarningSecretKeyDeleteString = @"PKWarningSecretKeyDeleteString";
NSString * PKWarningKeyDeleteString = @"PKWarningKeyDeleteString";
NSString * PKErrorGPHandbook = @"PKErrorGPHandbook";
NSString * PKSystemPreferencesError = @"PKSystemPreferencesError";
NSString * PKSystemPreferencesSolution = @"PKSystemPreferencesSolution";

@implementation PKLocalizableStrings

+ (NSString *)yes {
	return NSLocalizedStringFromTable(@"Yes", @"Localizable", @"Yes");
}

+ (NSString *)no {
	return NSLocalizedStringFromTable(@"No", @"Localizable", @"No");
}

+ (NSString *)yesOrNo:(BOOL)yesOrNo {
	return (yesOrNo) ?
	[PKLocalizableStrings yes] :
	[PKLocalizableStrings no];
}

+ (NSString *)warning {
	return NSLocalizedStringFromTable(@"Warning",
								   @"Localizable",
								   @"Sheet title: warning");
}

@end