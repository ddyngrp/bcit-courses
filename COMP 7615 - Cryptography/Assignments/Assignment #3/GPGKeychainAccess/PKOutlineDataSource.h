/*
	PKOutlineDataSource.h
	GPG Keychain Access
 
	$Id: PKOutlineDataSource.h 1691 2005-06-18 12:43:15Z rhwood $
 
	Created by craigc@users.sourceforge.net on 2001-09-25.
 
	Copyright (C) 2001-2005 Mac GPG Project.
 
	This code is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free
	Software Foundation; either version 2 of the License, or any later version.
 
	This code is distributed in the hope that it will be useful, but WITHOUT ANY
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
	details.
 
	For a copy of the GNU General Public License, visit <http://www.gnu.org/> or
	write to the Free Software Foundation, Inc., 59 Temple Place--Suite 330,
	Boston, MA 02111-1307, USA.
 
	More info at <http://macgpg.sourceforge.net/>
 */

#import <Cocoa/Cocoa.h>
#import <MacGPGME/MacGPGME.h>
#import "PKController.h"
#import "PKLocalisableStrings.h"

@class PKController;

/*
typedef enum {
    GPG_RSAAlgorithm                =  1,
    GPG_RSAEncryptOnlyAlgorithm     =  2,
    GPG_RSASignOnlyAlgorithm        =  3,
    GPG_ElgamalEncryptOnlyAlgorithm = 16,
    GPG_DSAAlgorithm                = 17,
    GPG_EllipticCurveAlgorithm      = 18,
    GPG_ECDSAAlgorithm              = 19,
    GPG_ElgamalAlgorithm            = 20,
    GPG_DiffieHellmanAlgorithm      = 21
}GPGPublicKeyAlgorithm;
*/

@interface PKOutlineDataSource: NSObject
{
    NSMutableDictionary	*_keychain;	// all keys in the keychain
	NSMutableArray		*_secrets;	// the fingerprints of secret keys in the keychain
	NSArray				*_sortedKeys;	// array of keys in current sort order
	NSLock				*_refreshSemaphore;	// don't spam the UI with refresh calls

    IBOutlet NSOutlineView	*keyList;				// The OutlineView this data source is attached to
    IBOutlet NSSearchField	*ToolbarSearchField;	// Any string in this limits our diplay to the search value

    BOOL		keysAreSorted;
    BOOL		outlineViewHasBeenInitialized;
    SEL			sortingSelector;
    BOOL		ascendingOrder;
	BOOL		keysAreFiltered;
	NSString	*filter;

	NSTableColumn	*sortingTableColumn;
	IBOutlet NSMenu	*pkOutlineHeaderMenu;
    NSMutableArray	*allTableColumns;
    NSMutableArray	*selectedItems;
    BOOL			isUpdatingSelection;
	
}

- (int)countOfKeysInView;
- (int)countOfKeysInKeychain;
- (void)refresh:(id)sender;
- (void)filter:(id)sender;
- (void)setHasBeenInitialized:(BOOL)flag;
- (void)setSortingSelector:(SEL)selector ascending:(BOOL)ascending;
- (NSEnumerator *)keyListWithSearchPattern:(NSString *)searchPattern secretKeysOnly:(BOOL)secretKeysOnly;
- (BOOL)ascendingOrder;

- (void)setupTableColumns;

- (NSImage *)imageForKeyKind:(NSString *)kind withAlgorithm:(NSString *)algorithm isInvalid:(BOOL)isInvalid expirationDate:(NSDate *)expirationDate;

@end

@interface PKOutlineDataSource(Private)

- (NSArray *)sortedKeys;

@end

