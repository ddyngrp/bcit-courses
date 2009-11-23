//
//  PKPreferencesLocalizableStrings.m
//  GPG Keychain Access
//
//  Created by Randall Wood on Sat Jun 21 2003.
//  Copyright (c) 2003 MacGPG Project. All rights reserved.
//

#import "PKPreferencesLocalizableStrings.h"


@implementation PKPreferencesLocalizableStrings

+ (NSString *)windowTitle {
	return NSLocalizedStringFromTable(@"PreferencesWindowTitle",
			@"Preferences",
			@"%@ Preferences");
}

+ (NSString *)loadingPreference {
	return NSLocalizedStringFromTable(@"LoadingPreferencePane",
			@"Preferences",
			@"Loading %@...");
}

+ (NSString *)alertPanelTitle {
	return NSLocalizedStringFromTable(@"AlertPanelTitle",
			@"Preferences",
			@"Preferences Error.");
}

+ (NSString *)alertPanelMessage {
	return NSLocalizedStringFromTable(@"AlertPanelMessageLoadingError",
			@"Preferences",
			@"Could not load %@");
}

@end
