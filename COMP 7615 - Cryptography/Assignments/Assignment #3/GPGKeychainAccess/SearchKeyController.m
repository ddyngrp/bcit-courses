#import "SearchKeyController.h"

@interface SearchKeyController(Private)
- (NSArray *)sortedKeys;
@end

@implementation SearchKeyController

static SearchKeyController *_sharedInstance = nil;

+ (id) sharedInstance
{
	if (_sharedInstance == nil) {
		_sharedInstance = [[self alloc] initWithWindowNibName:@"SearchKeyPanel"];
    }
    return _sharedInstance;
}

- (id) initWithWindowNibName:(NSString *)windowNibName
{
    if (self = [super initWithWindowNibName:windowNibName]) {
		isSearching = NO;
		isImporting = NO;
		// initalize context
		context = [[[GPGContext alloc] init] retain];
		// initalize searchResults dictionary
		searchResults = [[[NSArray alloc] init] autorelease];
		// we want to know when async GPGME operations are completed
		[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(operationDidTerminate:) name:@"GPGAsynchronousOperationDidTerminateNotification" object:context];
		// set the sorting
		[self setSortingSelector:NSSelectorFromString(@"userID") ascending:YES];
	}
	return self;
}

- (void) windowDidLoad
{
	// workaround bug in searchfield menus
	[[searchField cell] setSearchMenuTemplate:[[searchField cell] searchMenuTemplate]];
	// setup the toolbar
	NSToolbar *toolbar = [[[NSToolbar alloc] initWithIdentifier:@"myToolbar"] autorelease];
	toolbarItems = [[NSMutableDictionary dictionary] retain];
	[self addItemToToolbar:@"Import"
					 label:[TBLocalizableStrings TBImportLabel]
			  paletteLabel:[TBLocalizableStrings TBImportPalette]
				   toolTip:[TBLocalizableStrings TBImportToolTip]
					target:self
					action:@selector(importKey:)
		   settingSelector:@selector(setImage:)
			   itemContent:[NSImage imageNamed:@"Import.tiff"]
					  menu:NULL];
	[self addItemToToolbar:@"Search"
					 label:[TBLocalizableStrings TBSearchLabel]
			  paletteLabel:[TBLocalizableStrings TBSearchPalette]
				   toolTip:[TBLocalizableStrings TBSearchToolTip]
					target:self
					action:NULL
		   settingSelector:@selector(setView:)
			   itemContent:searchFieldView
					  menu:NULL];
	[toolbar setDelegate:self];
	[toolbar setAllowsUserCustomization:NO];
	[toolbar setAutosavesConfiguration:NO]; 
	[toolbar setDisplayMode: NSToolbarDisplayModeDefault];
	[[self window] setToolbar:toolbar];
	[super windowDidLoad];
}

- (void) dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self name:@"GPGAsynchronousOperationDidTerminateNotification" object:context];
	[toolbarItems release];
	[searchResults release];
	[super dealloc];
}

- (IBAction)importKey:(id)sender
{
	NSMutableArray *keys;
	NSObject *key;
	unsigned index;

	keys = [NSMutableArray array];
	index = [[keyList selectedRowIndexes] firstIndex];
	while (index != NSNotFound) {
		key = [keyList itemAtRow:index];
		if ([key isKindOfClass:[GPGUserID class]]) {
			[keys addObject:[key key]];
		} else {
			[keys addObject:key];			
		}
		index = [[keyList selectedRowIndexes] indexGreaterThanIndex:index];
	}
	NSLog(@"%i", [keys count]);
	if ([keys count]) {
		isImporting = YES;
		[busyIndicator startAnimation:nil];
		[statusBar setStringValue:NSLocalizedStringFromTable(@"Downloading...",
															 @"ServerKeyPanel",
															 @"ongoing download")];
		[context asyncDownloadKeys:keys serverOptions:nil];
	} else {
		[statusBar setStringValue:NSLocalizedStringFromTable(@"Selection could not be downloaded",
															 @"ServerKeyPanel",
															 @"nothing to download")];
	}
}

- (void)importKeyResults:(NSNotification *)notification
{
	NSDictionary *results;
	
	GPGError anError = [[[notification userInfo] objectForKey:@"GPGErrorKey"] intValue];
	[self showWindow:nil];
	if (!isSearching) {
		[busyIndicator stopAnimation:nil];
	}
#if VERBOSE_LOGGING == 0
	if (_verboseLogging)
#endif
		NSLog(@"Download results: %@", [[notification object] operationResults]);
	if (anError != GPGErrorNoError) {
		NSBeginAlertSheet(NSLocalizedStringFromTable(@"ServerDownloadError", @"ServerKeyPanel", @"Error downloading keys from server"), nil, nil, nil, [self window], nil, NULL, NULL, NULL, GPGErrorDescription(anError));
	} else {
		results = [[notification object] operationResults];
		if ([[results objectForKey:@"keys"] count]) {
			[statusBar setStringValue:[NSString stringWithFormat:NSLocalizedStringFromTable(@"%i keys downloaded", @"ServerKeyPanel", @"status keys downloaded"), [results objectForKey:@"importedKeyCount"]]];
			// we should drop a sheet to announce results
		} else {
			searchResults = [[[NSArray alloc] init] retain];
			[statusBar setStringValue:NSLocalizedStringFromTable(@"No keys downloaded", @"ServerKeyPanel", @"status no keys downloaded")];
			// we should drop a sheet explaining lack of results
		}
	}
	isImporting = NO;
}

- (IBAction)searchForKey:(id)sender
{
	if (!isSearching) {
		isSearching = YES;
		[statusBar setStringValue:NSLocalizedStringFromTable(@"Searching...", @"ServerKeyPanel", @"ongoing search")];
		searchResults = [[[NSArray alloc] init] retain];
		[keyList reloadData];
		if ([[searchField stringValue] length]) {
			[busyIndicator startAnimation:nil];
			[context asyncSearchForKeysMatchingPatterns:[NSArray arrayWithObject:[searchField stringValue]] serverOptions:nil];
		} else {
			[statusBar setStringValue:NSLocalizedStringFromTable(@"", @"ServerKeyPanel", @"nothing to search for")];
		}
	} else {
		isSearching = NO;
		[busyIndicator stopAnimation:nil];
		[statusBar setStringValue:NSLocalizedStringFromTable(@"", @"ServerKeyPanel", @"search cancelled")];
	}
}

- (void)searchForKeyResults:(NSNotification *)notification
{
	NSDictionary *results;

	GPGError anError = [[[notification userInfo] objectForKey:@"GPGErrorKey"] intValue];
	[self showWindow:nil];
	[busyIndicator stopAnimation:nil];
#if VERBOSE_LOGGING == 0
	if (_verboseLogging)
#endif
		NSLog(@"Search results: %@", [[notification object] operationResults]);
	if (anError != GPGErrorNoError) {
		NSBeginAlertSheet(NSLocalizedStringFromTable(@"ServerSearchError",
													 @"ServerKeyPanel",
													 @"Error searching for keys from server"),
						  nil,
						  nil,
						  nil,
						  [self window],
						  nil,
						  NULL,
						  NULL,
						  NULL,
						  GPGErrorDescription(anError));
	} else {
		results = [[notification object] operationResults];
		if ([[results objectForKey:@"keys"] count]) {
			searchResults = [results objectForKey:@"keys"];
			[keyList reloadData];
			[statusBar setStringValue:[NSString stringWithFormat:NSLocalizedStringFromTable(@"%i keys found",
																							@"ServerKeyPanel",
																							@"status keys found"),
				[searchResults count]]];
		} else {
			searchResults = [[[NSArray alloc] init] retain];
			[statusBar setStringValue:NSLocalizedStringFromTable(@"No keys found",
																 @"ServerKeyPanel",
																 @"status no keys found")];
		}
	}
	isSearching = NO;
}

- (void)searchForKeyWithSearchString:(NSString *)searchString
{
	[self showWindow:nil];
	[searchField setStringValue:searchString];
	[self searchForKey:nil];
}

- (void) operationDidTerminate:(NSNotification *)notification
{
    if (isSearching) {
        [self searchForKeyResults:notification];
	} else if (isImporting) {
		[self importKeyResults:notification];
	}
}

- (int)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item
{
	return (!item) ? [[self sortedKeys] count] : ([item isKindOfClass:[GPGUserID class]]) ? 0 : [[item userIDs] count] - 1;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
    return ([self outlineView:outlineView numberOfChildrenOfItem:item] > 0) ? YES : NO;
}

- (id)outlineView:(NSOutlineView *)outlineView child:(int)index ofItem:(id)item
{
    if (!item) {
        NSAssert((index >= 0) && (index < [[self sortedKeys] count]), @"index out of range");
        return [[self sortedKeys] objectAtIndex:index];
    } else {
        NSAssert((index >= 0) && (index < [[item userIDs] count] - 1), @"index out of range");
        return [[item userIDs] objectAtIndex:(index + 1)];
    }
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item
{
	if ([item isKindOfClass:[GPGUserID class]]) {
		if ([[tableColumn identifier] isEqualToString:@"userID"]) {
			return [item userID];
		} else {
			return @"";
		}
	}
	if ([[tableColumn identifier] isEqualToString:@"expirationDate"]) {
		return [item expirationDate] ? [item expirationDate] : @"";
	} else if ([[tableColumn identifier] isEqualToString:@"keyID"]) {
		return [item keyID] ? [item keyID] : @"";
	} else if ([[tableColumn identifier] isEqualToString:@"isKeyRevoked"]) {
		return [PKLocalizableStrings yesOrNo:[item isKeyRevoked] ? YES : NO];
	} else {
		return [item performSelector:NSSelectorFromString([tableColumn identifier])];
	}
}

- (void)outlineViewSelectionDidChange:(NSNotification *)notification
{
	if ([[notification object] isEqual:keyList]) {		
	}
}

- (void)outlineView:(NSOutlineView *)outlineView
	willDisplayCell:(id)cell
	 forTableColumn:(NSTableColumn *)tableColumn
			   item:(id)item
{
	if (![cell isKindOfClass:[NSImageCell class]]) {
		if ([item isKeyRevoked] ? YES : NO) {
			[cell setTextColor:[NSColor redColor]];
		} else if ([item expirationDate] && NSOrderedAscending == [[item expirationDate] compare:[NSDate date]]) {
			[cell setTextColor:[NSColor grayColor]];
		} else {
			[cell setTextColor:[NSColor blackColor]];
		}
	}
}

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag
{
    // We create and autorelease a new NSToolbarItem, and then go through the process of setting up its
    // attributes from the master toolbar item matching that identifier in our dictionary of items.
    NSToolbarItem *newItem = [[[NSToolbarItem alloc] initWithItemIdentifier:itemIdentifier] autorelease];
    NSToolbarItem *item=[toolbarItems objectForKey:itemIdentifier];
    
    [newItem setLabel:[item label]];
    [newItem setPaletteLabel:[item paletteLabel]];
    if ([item view]!=NULL)
    {
		[newItem setView:[item view]];
    }
    else
    {
		[newItem setImage:[item image]];
    }
    [newItem setToolTip:[item toolTip]];
    [newItem setTarget:[item target]];
    [newItem setAction:[item action]];
    [newItem setMenuFormRepresentation:[item menuFormRepresentation]];
    // If we have a custom view, we *have* to set the min/max size - otherwise, it'll default to 0,0 and the custom
    // view won't show up at all!  This doesn't affect toolbar items with images, however.
    if ([newItem view]!=NULL)
    {
		[newItem setMinSize:[[item view] bounds].size];
		[newItem setMaxSize:[[item view] bounds].size];
    }
	
    return newItem;
}

- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar
{
	return [NSArray arrayWithObjects:
		@"Import",
		NSToolbarFlexibleSpaceItemIdentifier,
		@"Search",
		nil];
}

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:
		@"Import", 
		@"Search",
		NSToolbarFlexibleSpaceItemIdentifier,
		nil];
}

- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem
{
	return (!isImporting && !isSearching && [keyList numberOfSelectedRows]) ? YES : NO;
}

- (void)addItemToToolbar:(NSString *)identifier
				   label:(NSString *)label
			paletteLabel:(NSString *)paletteLabel
				 toolTip:(NSString *)toolTip
				  target:(id)target
				  action:(SEL)action
		 settingSelector:(SEL)settingSelector
			 itemContent:(id)itemContent
					menu:(NSMenu *)menu
{
    NSMenuItem *menuItem;
    NSToolbarItem *item = [[[NSToolbarItem alloc] initWithItemIdentifier:identifier] autorelease];
    [item setLabel:label];
    [item setPaletteLabel:paletteLabel];
    [item setToolTip:toolTip];
    [item setTarget:target];
    [item performSelector:settingSelector withObject:itemContent];
    [item setAction:action];
    if (menu != NULL) {
		menuItem=[[[NSMenuItem alloc] init] autorelease];
		[menuItem setSubmenu: menu];
		[menuItem setTitle: [menu title]];
		[item setMenuFormRepresentation:menuItem];
    }
    [toolbarItems setObject:item forKey:identifier];
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
    id					leftValue = [key performSelector:NSSelectorFromString(selector)];
    id					rightValue = [otherKey performSelector:NSSelectorFromString(selector)];
    NSComparisonResult	result;
	
    if([leftValue isKindOfClass:[NSString class]])
        result = [(NSString *)leftValue caseInsensitiveCompare:rightValue];
    else
        result = [(NSNumber *)leftValue compare:rightValue]; // Cast is not correct; we put it just to avoid a gcc warning
	
    if(!ascendingOrder)
        result = -result;
	
    return result;
}

- (NSArray *)sortedKeys
{
/*
	if(!keysAreSorted){
        NSArray	*sortedPublicKeys;
		
        sortedPublicKeys = [[searchResults sortedArrayUsingFunction:compareKeysWithSelector context:[NSDictionary dictionaryWithObjectsAndKeys:NSStringFromSelector(sortingSelector), @"selector", [NSNumber numberWithBool:ascendingOrder], @"ascending", nil]] retain];
		
        [searchResults release];
        searchResults = sortedPublicKeys;
        keysAreSorted = YES;
    }
 */
    return searchResults;
}

@end
