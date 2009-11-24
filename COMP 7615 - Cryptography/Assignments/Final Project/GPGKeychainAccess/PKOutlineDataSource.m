/*
	PKOutlineDataSource.m
	GPG Keychain Access

	$Id: PKOutlineDataSource.m 1671 2005-05-30 20:08:00Z rhwood $

	creationDate by craigc@users.sourceforge.net on 2001-09-25.

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

#import <AppKit/NSImage.h>
#import "PKOutlineDataSource.h"

@interface GPGKey(PKOutlineDataSource)
- (NSNumber *) lengthValue;
@end

@implementation GPGKey(PKOutlineDataSource)

- (NSNumber *) lengthValue
{
    return [NSNumber numberWithUnsignedInt:[self length]];
}

@end

@implementation PKOutlineDataSource

static NSComparisonResult compareKeysWithSelector(id key, id otherKey, void *context);

- (id)init
{
    if (self = [super init]) {
        _keychain = [[NSMutableDictionary alloc] init];
		_sortedKeys = [[NSArray alloc] init];
        _refreshSemaphore = [[NSLock alloc] init];
		filter = @"";
		keysAreFiltered = NO;
		
		[[NSDistributedNotificationCenter defaultCenter] addObserver:self selector:@selector(refresh:) name:@"GPGKeyringChangedNotification" object:nil];
    }
    return self;
}

- (void)dealloc
{
    [_keychain release];
	[_sortedKeys release];
    [_refreshSemaphore release];
	[filter release];
    [super dealloc];
}

- (int)countOfKeysInView
{
	return [[self sortedKeys] count];
}

- (int)countOfKeysInKeychain
{
	return [_keychain count];
}

- (oneway void)setSecrets:(NSMutableArray *)secrets
{
	[_secrets release];
	_secrets = [secrets retain];
}

- (oneway void)updateOutlineView:(NSDictionary *)dictionary
{
    // Executed in main thread
    [_keychain release];
    _keychain = [[NSMutableDictionary alloc] initWithDictionary:dictionary copyItems:YES];
    keysAreFiltered = NO;
	[keyList reloadData];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"GKA_PKCountOfKeysInViewChanged" object:[NSNumber numberWithInt:[self countOfKeysInView]]];
    [_refreshSemaphore unlock];
}

- (void)refresh:(id)sender
{
	NSDictionary *threadInfo;

	// if sender is a text field, use its value to limit the keys displayed
	if ([sender isKindOfClass:[NSSearchField class]]) {
		threadInfo = [NSDictionary dictionaryWithObjectsAndKeys:[sender stringValue], @"searchPattern", nil];
        [ToolbarSearchField setStringValue:[sender stringValue]];
	} else {
		threadInfo = [NSDictionary dictionaryWithObjectsAndKeys:@"", @"searchPattern", nil];
		[ToolbarSearchField setStringValue:@""];
	}

	// UI changes while refreshing
	[ToolbarSearchField setEnabled: NO];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"GKA_PKBeginRefresh" object:[keyList window]];
	keysAreSorted = NO;

	// refresh in seperate thread so as not to block UI
	[NSThread detachNewThreadSelector:@selector(doRefreshThread:) toTarget:self withObject:threadInfo];
}

- (void)filter:(id)sender
{
	keysAreFiltered = NO;
	filter = [sender stringValue];
	[keyList reloadData];
}

- (NSEnumerator *) keyListWithSearchPattern:(NSString *)searchPattern secretKeysOnly:(BOOL)secretKeysOnly
{
    // Executed in secondary thread
    NSEnumerator *key_list;
	GPGKeyListMode keyListMode;
    GPGContext *context = [[GPGContext alloc] init];

	keyListMode = [context keyListMode];
	NSLog(@"%u", keyListMode);
	keyListMode |= GPGKeyListModeSignatures;
	NSLog(@"%u", keyListMode);
	[context setKeyListMode:keyListMode];

    key_list = [context keyEnumeratorForSearchPattern:searchPattern secretKeysOnly:secretKeysOnly];

    [context release];
    return key_list;
}

/*
 Generate the keylisting
 
 This is an expensive operation, so we stick it in a seperate thread to stop the application from just totally siezing up
 during this operation.
 
 If we were running everything through GPGME or pipes and file buffers, maybe we could make a meaningful caching operation
 to speed things up, allowing us to dress things up (add signatures to the listing, indicate trust levels, etc)
 */
- (oneway void)doRefreshThread:(bycopy NSDictionary *)threadInfo
{
    // Executed in secondary thread
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc ] init];
    
    NSEnumerator *keyEnum;
    GPGKey *key;
    NSMutableArray *badKeys = [NSMutableArray array];
	NSMutableArray *secrets;
	NSArray *allKeys;
    NSMutableDictionary *keychain;
    int keyCount, keyIndex = 0;
	GPGKeyListMode keyListMode;

	GPGContext *context = [[GPGContext alloc] init];

	keyListMode = [context keyListMode];
	keyListMode |= GPGKeyListModeSignatures;
	[context setKeyListMode:keyListMode];

	// build list of secret keys
    keyEnum = [context keyEnumeratorForSearchPattern:[threadInfo objectForKey:@"searchPattern"] secretKeysOnly:YES];
	allKeys = [keyEnum allObjects];
    keyCount = [allKeys count];
	keyEnum = [allKeys objectEnumerator];
	secrets = [NSMutableArray arrayWithCapacity:keyCount];
	while (key = [keyEnum nextObject]) {
		[secrets addObject:[key keyID]];
	}
	
    // this next part is very ugly
	// to make it less ugly we work directly with objects instead of dictionary representations 
	keyEnum = [context keyEnumeratorForSearchPattern:[threadInfo objectForKey:@"searchPattern"] secretKeysOnly:NO];
	allKeys = [keyEnum allObjects];
    keyCount = [allKeys count];
	keyEnum = [allKeys objectEnumerator];
	[[NSNotificationCenter defaultCenter] postNotificationName:@"GKA_PKCountOfKeysInViewChanged" object:[NSNumber numberWithInt:keyCount]];
    //clear out old key list
    keychain = [NSMutableDictionary dictionaryWithCapacity:keyCount];
    // We want the view to refresh as fast as possible, but we don't want
    // to post too many invocations, so we use a semaphore: we try to lock,
    // and if it is successful, it means that view is ready to accept
    // refresh, else we forget the refresh. In any case, final refresh,
    // i.e. when all keys have been loaded, will be forced.
    if([_refreshSemaphore tryLock]) {
        // First, we clean the view: no keys
        [self performSelectorOnMainThread:@selector(updateOutlineView:) withObject:keychain waitUntilDone:NO];
	}
    while (key = [keyEnum nextObject]) {
        //error handling in place to catch incomplete keys
        //they will crash the program since it doesn't check for nil below
        NS_DURING
			if (!NSEqualRanges(NSMakeRange(NSNotFound, 0), [[key description] rangeOfString:@"TEST"])) {
				NSLog(@"%@", [key description]);
			}
            NSMutableDictionary *pub;
            NSMutableArray *children = [NSMutableArray array];
            NSEnumerator *childEnum;
            id aChild;
			// Subkeys
			childEnum = [[key subkeys] objectEnumerator];
            while ((aChild = [childEnum nextObject])) {
                [children addObject:[NSMutableDictionary dictionaryWithObjectsAndKeys:
                    @"sub", @"type",
					[self imageForKeyKind:@"sub" withAlgorithm:[aChild algorithmDescription] isInvalid:[aChild isKeyInvalid] expirationDate:[aChild expirationDate]], @"kind",
                    [key name], @"name",
                    [key email], @"email",
                    [aChild shortKeyID], @"shortkeyid",
                    [aChild creationDate], @"creationDate",
                    // [aChild length], @"len",
					0, @"len",
                    [aChild algorithmDescription], @"algo",
					[NSNumber numberWithBool:[aChild isKeyDisabled]], @"isItemDisabled",
                    [aChild expirationDate], @"expirationDate",
					[NSNumber numberWithBool:[aChild hasKeyExpired]], @"hasItemExpired",
                    [aChild fingerprint], @"fpr",
                    [NSNumber numberWithBool:[aChild isKeyInvalid]], @"isItemInvalid",
					[NSNumber numberWithBool:[aChild isKeyRevoked]], @"isItemRevoked",
                    [aChild isSecret], @"secret",
                    nil
                ]];
            }
			// User IDs
			// We would gather signatures here, but that's expensive, so we aren't doing that now
			childEnum = [[key userIDs] objectEnumerator];
            while ((aChild = [childEnum nextObject])) {
				NSEnumerator *signaturesEnumerator;
				id aSignature;
				NSMutableArray *signatures = [NSMutableArray array];
				signaturesEnumerator = [[aChild signatures] objectEnumerator];
				while (aSignature = [signaturesEnumerator nextObject]) {
					[signatures addObject:[NSDictionary dictionaryWithObjectsAndKeys:
						@"sig", @"type",
						[self imageForKeyKind:@"sig" withAlgorithm:nil isInvalid:[aSignature isSignatureInvalid] expirationDate:[aSignature expirationDate]], @"kind",
						[aSignature name], @"name",
						[aSignature email], @"email",
						[aSignature comment], @"comment",
						[aSignature signerKeyID], @"shortkeyid",
						[aSignature creationDate], @"creationDate",
						0, @"len",
						@"", @"algo",
						[NSNumber numberWithBool:NO], @"isItemDisabled",
						[aSignature expirationDate], @"expirationDate",
						[NSNumber numberWithBool:[aSignature hasSignatureExpired]], @"hasItemExpired",
						@"", @"fpr",
						[NSNumber numberWithBool:[aSignature isSignatureInvalid]], @"isItemInvalid",
						@"", @"isItemRevoked",
						[aSignature isExportable], @"secret",
						nil
					]];
				}
                [children addObject:[NSDictionary dictionaryWithObjectsAndKeys:
                    @"uid", @"type",
					signatures, @"children",
					[self imageForKeyKind:@"uid" withAlgorithm:nil isInvalid:[aChild isInvalid] expirationDate:[NSDate distantFuture]], @"kind",
                    [aChild name], @"name",
                    [aChild email], @"email",
                    @"", @"shortkeyid",
                    @"", @"creationDate",
                    @"", @"len",
                    @"", @"algo",
                    [NSNumber numberWithBool:NO], @"isItemDisabled",
                    [NSNumber numberWithBool:NO], @"hasItemExpired",
                    @"", @"fpr",
                    @"", @"secret",
                    [aChild comment], @"comment",
					[NSNumber numberWithBool:[aChild isInvalid]], @"isItemInvalid",	// for some reason this line can not be last, but also screws up all following lines
					[NSNumber numberWithBool:[aChild hasBeenRevoked]], @"isItemRevoked",
                    nil
                ]];
            }
			// Key
            pub = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                children, @"children",
				[secrets containsObject:[key keyID]] ? @"pair": @"pub", @"type",
				[self imageForKeyKind:([secrets containsObject:[key keyID]] ? @"pair": @"pub") withAlgorithm:[key algorithmDescription] isInvalid:[key isKeyInvalid] expirationDate:[key expirationDate]], @"kind",
                [key name], @"name",
                [key email], @"email",
                [key comment], @"comment",
                [key shortKeyID], @"shortkeyid",
                [key creationDate], @"creationDate",
                [key lengthValue], @"len",
                [key algorithmDescription], @"algo",
                [NSNumber numberWithBool:[key isKeyDisabled]], @"isItemDisabled",
                [NSNumber numberWithBool:[key hasKeyExpired]], @"hasItemExpired",
				(nil == [key expirationDate]) ? [NSDate distantFuture] : [key expirationDate], @"expirationDate",
				(nil == [key fingerprint]) ? @"" : [key fingerprint], @"fpr",
                [NSNumber numberWithBool:[key isKeyInvalid]], @"isItemInvalid",
                [NSNumber numberWithBool:[key isKeyRevoked]], @"isItemRevoked",
                nil
            ];
			// add key to list
			[keychain setObject:pub forKey:[key keyID]];
			if ([[key comment] isEqualToString:@"TEST"]) {
				NSLog(@"%@", [pub description]);
			}
        NS_HANDLER
            //there seems to be a memory leak here, just using NSLog instead
            // stephane: no, it is just because we are not in the main thread
            //NSBeginAlertSheet(NSLocalizedString(PKKeyListingWarningTitle, PKKeyListingWarningTitle), nil, nil, nil, [keyList window], nil, nil, nil, nil, NSLocalizedString(PKKeyListingKeyFailedString, PKKeyListingKeyFailedString), [key descriptionAsXMLString]);
            NSLog(@"%@", localException);
            //NSLog(@"Oops, you've got a bad key:\n%@", [key dictionaryRepresentation]);
			NSLog(@"Attempted to read a bad key.");
			NSLog(@"Please use GPG Key Enumerator to determine which key is bad.");
            [badKeys addObject:key];
        NS_ENDHANDLER
		
        if(++keyIndex != keyCount && [_refreshSemaphore tryLock]) {
            // Try to refresh, except after last key
            [self performSelectorOnMainThread:@selector(updateOutlineView:) withObject:keychain waitUntilDone:NO];
		}
    }
    // This time we do want refresh now, so we'll wait until we get the lock
    [_refreshSemaphore lock];
    [self performSelectorOnMainThread:@selector(updateOutlineView:) withObject:keychain waitUntilDone:NO];
    [self performSelectorOnMainThread:@selector(endRefresh:) withObject:badKeys waitUntilDone:NO];
	[context release];
	[pool release];
}

- (void) endRefresh:(NSArray *)badKeys
{
    // Executed in main thread
    [[NSNotificationCenter defaultCenter] postNotificationName:@"GKA_PKEndRefresh" object:[keyList window]];
    
    if([badKeys count] > 0){
        NSMutableArray	*messageLines = [NSMutableArray array];
        NSEnumerator	*anEnum = [badKeys objectEnumerator];
        GPGKey			*aKey;
        NSString		*aLocalizedStringFormat = NSLocalizedString(PKKeyListingKeyFailedString, PKKeyListingKeyFailedString);
        
        while(aKey = [anEnum nextObject])
            [messageLines addObject:[NSString stringWithFormat:aLocalizedStringFormat, [[aKey dictionaryRepresentation] description]]];

        (void)NSBeginAlertSheet(NSLocalizedString(PKKeyListingWarningTitle, PKKeyListingWarningTitle), nil, nil, nil, [keyList window], nil, NULL, NULL, NULL, @"%@", [messageLines componentsJoinedByString:@"\n"]);
    }
	
	[ToolbarSearchField setEnabled:YES];
}

- (NSImage *)imageForKeyKind:(NSString *)kind withAlgorithm:(NSString *)algorithm isInvalid:(BOOL)isInvalid expirationDate:(NSDate *)expirationDate
{
	NSString *path;
	NSMutableString *name;
	NSImage *image;
	name = [NSMutableString stringWithCapacity:3];
	[name appendString:((nil == algorithm) ? kind : [algorithm stringByAppendingString:kind])];
	if (isInvalid) {
		[name appendString:@"-inv"];
	} else if (NSOrderedAscending == [expirationDate compare:[NSDate date]]) {
		[name appendString:@"-exp"];
	}
	image = [NSImage imageNamed:name];
	if (nil == image) {
		NSLog(@"Missing key list icon: %@", name);
		path = [[NSBundle mainBundle] pathForImageResource:[name stringByAppendingString:@".tiff"]];
		image = [[[NSImage alloc] initWithContentsOfFile:path] retain];
		if (nil != image) {
			[image setName:name];
		}
	}
	return image;
}

- (void) setupTableColumns
{
    NSArray			*visibleTableColumnTags, *tableColumnWidths;
    NSEnumerator	*anEnum;
    int				i;
    int				tableColumnCount;
    NSMutableArray	*columnIdentifiers;
    NSTableColumn	*aColumn;
    NSNumber		*aNumber;
	
    [[NSUserDefaults standardUserDefaults] registerDefaults:[NSDictionary dictionaryWithObjectsAndKeys:@"2", @"SortingTableColumnTag", [NSArray arrayWithObjects:@"0", @"1", @"2", @"3", @"4", @"5", @"6", @"7", nil], @"VisibleTableColumnTags", @"YES", @"AscendingSorting", nil]];
    allTableColumns = [[NSArray alloc] initWithArray:[keyList tableColumns]];
    tableColumnCount = [allTableColumns count];
    columnIdentifiers = [NSMutableArray arrayWithCapacity:tableColumnCount];
	
    anEnum = [allTableColumns objectEnumerator];
    while(aColumn = [anEnum nextObject]) {
        [columnIdentifiers addObject:[aColumn identifier]];
	}
    sortingTableColumn = [[allTableColumns objectAtIndex:[[NSUserDefaults standardUserDefaults] integerForKey:@"SortingTableColumnTag"]] retain];
    ascendingOrder = [[NSUserDefaults standardUserDefaults] boolForKey:@"AscendingSorting"];
	
    // Let's restore column widths
    tableColumnWidths = [[NSUserDefaults standardUserDefaults] arrayForKey:@"TableColumnWidths"];
    anEnum = [tableColumnWidths objectEnumerator];
    i = 0;
    // Table column order is always the same
    while(aNumber = [anEnum nextObject]) {
		if (i < tableColumnCount) {
			[[allTableColumns objectAtIndex:i++] setWidth:[aNumber floatValue]];
		}
	}
    // Let's reorder visible columns
    visibleTableColumnTags = [[NSUserDefaults standardUserDefaults] arrayForKey:@"VisibleTableColumnTags"];
    anEnum = [visibleTableColumnTags objectEnumerator];
    i = 0;
    while(aNumber = [anEnum nextObject]){
        NSTableColumn	*aColumn = [allTableColumns objectAtIndex:[aNumber intValue]];
        int				currentColumn = [[keyList tableColumns] indexOfObject:aColumn];
		
        if(currentColumn != i)
            [keyList moveColumn:currentColumn toColumn:i];
        [[pkOutlineHeaderMenu itemAtIndex:[pkOutlineHeaderMenu indexOfItemWithTag:[aNumber intValue]]] setState:NSOnState];
        i++;
    }
    // And remove the invisible ones
    for(i = 1; i < tableColumnCount; i++){
        NSString	*aString = [NSString stringWithFormat:@"%d", i];
		
        if(![visibleTableColumnTags containsObject:aString]){
            aColumn = [allTableColumns objectAtIndex:i];
            [keyList removeTableColumn:aColumn];
        }
    }
	
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(outlineViewColumnDidResize:) name:NSOutlineViewColumnDidResizeNotification object:keyList];
    [self setHasBeenInitialized:YES];
    [self setSortingSelector:NSSelectorFromString([sortingTableColumn identifier]) ascending:ascendingOrder];
    selectedItems = [[NSMutableArray alloc] init];
}

- (void) updateSelection
{
    NSEnumerator	*anEnum = [selectedItems objectEnumerator];
    id				eachItem;
	
    isUpdatingSelection = YES;
    [keyList deselectAll:nil];
    while(eachItem = [anEnum nextObject])
        [keyList selectRow:[keyList rowForItem:eachItem] byExtendingSelection:YES];
    isUpdatingSelection = NO;
}

- (void) outlineViewColumnDidResize:(NSNotification *)aNotification
{
    NSEnumerator	*anEnum = [allTableColumns objectEnumerator];
    NSTableColumn	*aColumn;
    NSMutableArray	*widths = [NSMutableArray array];
	
    while(aColumn = [anEnum nextObject])
        [widths addObject:[NSNumber numberWithFloat:[aColumn width]]];
    [[NSUserDefaults standardUserDefaults] setObject:widths forKey:@"TableColumnWidths"];
}

- (BOOL) outlineView:(NSOutlineView *)outlineView shouldSelectTableColumn:(NSTableColumn *)tableColumn
{
    // Workaround to AppKit bug: tableView:didClickTableColumn: never invoked for outlineViews...
    // Reorder keys

    if (tableColumn != sortingTableColumn) {
#warning ERROR: sorting should be delayed, if no drag was performed...
        [outlineView setIndicatorImage:nil inTableColumn:sortingTableColumn];
        [sortingTableColumn release];
        sortingTableColumn = [tableColumn retain];
    }
    else {
        ascendingOrder = !ascendingOrder;
	}
    [outlineView setHighlightedTableColumn:tableColumn];
	
    [self setSortingSelector:NSSelectorFromString([sortingTableColumn identifier]) ascending:ascendingOrder];
    [outlineView reloadData];
    [self updateSelection];
	
    return NO;
}

- (void) outlineViewSelectionDidChange:(NSNotification *)notification
{
    if(!isUpdatingSelection){
        NSOutlineView	*outlineView = [notification object];
        NSEnumerator	*rowEnum = [outlineView selectedRowEnumerator];
        NSNumber		*eachRow;
		
        [selectedItems removeAllObjects];
        while(eachRow = [rowEnum nextObject])
            [selectedItems addObject:[outlineView itemAtRow:[eachRow intValue]]];
    }
}

- (int)outlineView:(NSOutlineView *)outlineView
       numberOfChildrenOfItem:(id)item
{
    return (item == nil) ? [[self sortedKeys] count] : [[item objectForKey:@"children"] count];
}

- (id)outlineView:(NSOutlineView *)outlineView
      child:(int)index
      ofItem:(id)item
{
    if (item == nil) {
        NSAssert((index >= 0) && (index < [[self sortedKeys] count]), @"index out of range");
        return [_sortedKeys objectAtIndex:index];
    } else {
        NSAssert((index >= 0) && (index < [[item objectForKey:@"children"] count]), @"index out of range");
        return [[item objectForKey:@"children"] objectAtIndex:index];
    }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView
        isItemExpandable:(id)item
{
    return ([self outlineView:outlineView numberOfChildrenOfItem:item] > 0) ? YES : NO;
}

- (id)outlineView:(NSOutlineView *)outlineView
      objectValueForTableColumn:(NSTableColumn *)tableColumn
      byItem:(id)item
{
	return [item objectForKey:[tableColumn identifier]];
}

- (void)outlineView:(NSOutlineView *)outlineView
		willDisplayCell:(id)cell
		forTableColumn:(NSTableColumn *)tableColumn
		item:(id)item
{
	if (![cell isKindOfClass:[NSImageCell class]]) {
		if ([[item objectForKey:@"isItemInvalid"] boolValue] || [[item objectForKey:@"isItemRevoked"] boolValue]) {
			[cell setTextColor:[NSColor redColor]];
		} else if ([[item objectForKey:@"isItemDisabled"] boolValue] || [[item objectForKey:@"hasItemExpired"] boolValue]) {
			[cell setTextColor:[NSColor grayColor]];
		} else {
			[cell setTextColor:[NSColor blackColor]];
		}
	}
}

// optional methods

- (BOOL)outlineView:(NSOutlineView*)outlineView
        acceptDrop:(id <NSDraggingInfo>)info
        item:(id)item
        childIndex:(int)index
{
    return NO;
}

- (NSDragOperation)outlineView:(NSOutlineView*)outlineView
                   validateDrop:(id <NSDraggingInfo>)info
                   proposedItem:(id)item
                   proposedChildIndex:(int)index
{
    return NSDragOperationNone;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView
        writeItems:(NSArray*)items
        toPasteboard:(NSPasteboard*)pboard
{
    return NO;
}

- (void) setSortingSelector:(SEL)selector ascending:(BOOL)ascending
{
    keysAreSorted = NO;
    sortingSelector = selector;
    ascendingOrder = ascending;
}

- (BOOL) ascendingOrder
{
    return ascendingOrder;
}

static NSComparisonResult compareKeysWithSelector(id key, id otherKey, void *context)
{
    BOOL				ascendingOrder = [[(NSDictionary *)context objectForKey:@"ascending"] boolValue];
    NSString			*selector = [(NSDictionary *)context objectForKey:@"selector"];
    id					leftValue = [key valueForKey:selector];
    id					rightValue = [otherKey valueForKey:selector];
    NSComparisonResult	result;

    if([leftValue isKindOfClass:[NSString class]])
        result = [(NSString *)leftValue caseInsensitiveCompare:rightValue];
    else
        result = [(NSNumber *)leftValue compare:rightValue]; // Cast is not correct; we put it just to avoid a gcc warning

    if(!ascendingOrder)
        result = -result;

    return result;
}

// possible candidate for removal. Test that ignoring the flag has no effect.
- (void) setHasBeenInitialized:(BOOL)flag
{
    outlineViewHasBeenInitialized = flag;
}

- (NSArray *) sortedKeys
{
	NSMutableArray *keys;
	NSEnumerator *enumerator;
	BOOL keysWereFiltered = !keysAreFiltered;
	id key;
	if (!keysAreFiltered) {
		if ([filter isEqualToString:@""]) {
			keys = [NSArray arrayWithArray:[_keychain allValues]];
		} else {
			keys = [NSMutableArray arrayWithCapacity:[_keychain count]];
			enumerator = [[_keychain allValues] objectEnumerator];
			while (key = [enumerator nextObject]) {
				if (!NSEqualRanges(NSMakeRange(NSNotFound, 0), [[key description] rangeOfString:filter])) {
					[keys addObject:key];
				}
			}
		}
		keysAreSorted = NO;
		keysAreFiltered = YES;
	} else {
		keys = [NSArray arrayWithArray:_sortedKeys];
	}
	if (!keysAreSorted) {
		[_sortedKeys release];
		_sortedKeys = [[keys sortedArrayUsingFunction:compareKeysWithSelector context:[NSDictionary dictionaryWithObjectsAndKeys:NSStringFromSelector(sortingSelector), @"selector", [NSNumber numberWithBool:ascendingOrder], @"ascending", nil]] retain];
		keysAreSorted = YES;
	}
	if (keysWereFiltered) {
		// posting this notification causes [self sortedKeys] to be called recursively
		[[NSNotificationCenter defaultCenter] postNotificationName:@"GKA_PKCountOfKeysInViewChanged" object:nil];
	}
	return _sortedKeys;
}

@end