//
//  TBLocalizableStrings.h
//  GPG Keychain Access
//
//  Created by Randall Wood on Fri May 23 2003.
//  Copyright (c) 2003 MacGPG Project. All rights reserved.
//

#import <Foundation/Foundation.h>

/*!
	@class TBLocalizableStrings
	@abstract	TBLocalizableStrings collects all internationalization in one place
	@discussion	TBLocalizableStrings defines every localizable string used in the
				GPG Keychain toolbar. It provides a static method that returns the
				localized string, allowing verbose comments in the .strings files
				and clean code in application. Each toolbar item has three
				localizable strings: the label used in the toolbar, the label used in
				the customization palette, and the tool tip. Every method defined in
				this class calls NSLocalizedStringFromTable(key, table, comment)
				where the key is the method call, the table is "Toolbar" and the
				comment is the string used in the development language. Tools for
				inspecting and updating localizations only need to be called against
				TBLocalizableStrings.m.
*/
@interface TBLocalizableStrings : NSObject
{
}

/*!
	@method TBBackupLabel
	@abstract	Returns the toolbar label for the Backup toolbar item.
	@discussion	Returns the toolbar label for the Backup toolbar item. See the
				method implementation for the actual string returned in the
				development language.
	@result		Returns the toolbar label for the Backup toolbar item.
*/
+ (NSString *)TBBackupLabel;
+ (NSString *)TBBackupPalette;
+ (NSString *)TBBackupToolTip;
+ (NSString *)TBDeleteLabel;
+ (NSString *)TBDeletePalette;
+ (NSString *)TBDeleteToolTip;
+ (NSString *)TBEditLabel;
+ (NSString *)TBEditPalette;
+ (NSString *)TBEditToolTip;
+ (NSString *)TBExportLabel;
+ (NSString *)TBExportPalette;
+ (NSString *)TBExportToolTip;
+ (NSString *)TBImportLabel;
+ (NSString *)TBImportPalette;
+ (NSString *)TBImportToolTip;
+ (NSString *)TBInfoLabel;
+ (NSString *)TBInfoPalette;
+ (NSString *)TBInfoToolTip;
+ (NSString *)TBGenerateLabel;
+ (NSString *)TBGeneratePalette;
+ (NSString *)TBGenerateToolTip;
+ (NSString *)TBSearchLabel;
+ (NSString *)TBSearchPalette;
+ (NSString *)TBSearchToolTip;
+ (NSString *)TBSignLabel;
+ (NSString *)TBSignPalette;
+ (NSString *)TBSignToolTip;
+ (NSString *)TBSearchLocal;
+ (NSString *)TBSearchRemote;
+ (NSString *)TBSearchLabelLocal;
+ (NSString *)TBSearchLabelRemote;

@end