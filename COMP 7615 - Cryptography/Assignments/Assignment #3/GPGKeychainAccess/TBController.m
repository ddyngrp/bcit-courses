#import "TBController.h"

@implementation TBController

- (void)awakeFromNib
{
	[[TBSearchField cell] setSearchMenuTemplate:[[TBSearchField cell] searchMenuTemplate]];
	TBSearchMenuLocal = [[[TBSearchField cell] searchMenuTemplate] itemWithTag:1];
	TBSearchMenuRemote = [[[TBSearchField cell] searchMenuTemplate] itemWithTag:2];
	NSToolbar *toolbar = [[[NSToolbar alloc] initWithIdentifier:@"myToolbar"] autorelease];
	toolbarItems = [[NSMutableDictionary dictionary] retain];
	toolbarSearchItem = [[[NSToolbarItem alloc] init] retain];
	[self addItemToToolbar:@"New"
					label:[TBLocalizableStrings TBGenerateLabel]
					paletteLabel:[TBLocalizableStrings TBGeneratePalette]
					toolTip:[TBLocalizableStrings TBGenerateLabel]
					target:keyController
					action:@selector(keyGenerate:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Generate.tiff"]
					menu:NULL];
	[self addItemToToolbar:@"Delete"
					label:[TBLocalizableStrings TBDeleteLabel]
					paletteLabel:[TBLocalizableStrings TBDeletePalette]
					toolTip:[TBLocalizableStrings TBDeleteToolTip]
					target:keyController
					action:@selector(keyDelete:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Delete.tiff"]
					menu:NULL];
	[self addItemToToolbar:@"Import"
					label:[TBLocalizableStrings TBImportLabel]
					paletteLabel:[TBLocalizableStrings TBImportPalette]
					toolTip:[TBLocalizableStrings TBImportToolTip]
					target:keyController
					action:@selector(fileImport:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Import.tiff"]
					menu:NULL];
	[self addItemToToolbar:@"Export"
					label:[TBLocalizableStrings TBExportLabel]
					paletteLabel:[TBLocalizableStrings TBExportPalette]
					toolTip:[TBLocalizableStrings TBExportToolTip]
					target:keyController
					action:@selector(fileExport:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Export.tiff"]
					menu:NULL];
	[self addItemToToolbar:@"Search"
					label:[TBLocalizableStrings TBSearchLabel]
					paletteLabel:[TBLocalizableStrings TBSearchPalette]
					toolTip:[TBLocalizableStrings TBSearchToolTip]
					target:keyController
					action:NULL
					settingSelector:@selector(setView:)
					itemContent:TBSearchView
					menu:NULL];
	/* PKinspectorController - 0.7 version key info dialog */
	[self addItemToToolbar:@"Info"
					label:[TBLocalizableStrings TBInfoLabel]
					paletteLabel:[TBLocalizableStrings TBInfoPalette]
					toolTip:[TBLocalizableStrings TBInfoToolTip]
					target:inspectorController
					action:@selector(showWindow:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Info.tiff"]
					menu:NULL];
	 /* */
	/* keyInformation - new key info dialog currently strangely broken 
	[self addItemToToolbar:@"Info"
					 label:[TBLocalizableStrings TBInfoLabel]
			  paletteLabel:[TBLocalizableStrings TBInfoPalette]
				   toolTip:[TBLocalizableStrings TBInfoToolTip]
					target:keyController
					action:@selector(keyInformation:)
		   settingSelector:@selector(setImage:)
			   itemContent:[NSImage imageNamed:@"Info.tiff"]
					  menu:NULL];
	 /* */
	[self addItemToToolbar:@"Sign"
					label:[TBLocalizableStrings TBSignLabel]
					paletteLabel:[TBLocalizableStrings TBSignPalette]
					toolTip:[TBLocalizableStrings TBSignToolTip]
					target:keyController
					action:@selector(keySign:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Signature.tiff"]
					menu:NULL];
	[self addItemToToolbar:@"Edit"
					label:[TBLocalizableStrings TBEditLabel]
					paletteLabel:[TBLocalizableStrings TBEditPalette]
					toolTip:[TBLocalizableStrings TBEditToolTip]
					target:keyController
					action:@selector(keyEdit:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Edit.tiff"]
					menu:NULL];
	/*
	// Remove from UI until feature can be implemented
	[self addItemToToolbar:@"Backup"
					label:[TBLocalizableStrings TBBackupLabel]
					paletteLabel:[TBLocalizableStrings TBBackupPalette]
					toolTip:[TBLocalizableStrings TBBackupToolTip]
					target:keyController
					action:@selector(keyBackup:)
					settingSelector:@selector(setImage:)
					itemContent:[NSImage imageNamed:@"Backup.tiff"]
					menu:NULL];
	 */
    [toolbar setDelegate:self];
    [toolbar setAllowsUserCustomization:YES];
    [toolbar setAutosavesConfiguration: YES]; 
    [toolbar setDisplayMode: NSToolbarDisplayModeDefault];
    [pkWindow setToolbar:toolbar];
	[self setDoLocalSearch:YES];
}

- (void) dealloc
{
    [toolbarItems release];
	[toolbarSearchItem release];
    [super dealloc];
}

- (IBAction)search:(id)sender
{
	if (_doLocalSearch) {
		[keyController listFilter:sender];
	} else {
		[keyController keySearch:sender];
	}
}

- (IBAction)setSearchSourceToLocal:(id)sender
{
	[self setDoLocalSearch:YES];
}

- (IBAction)setSearchSourceToRemote:(id)sender
{
	[self setDoLocalSearch:NO];
}

- (BOOL)validateMenuItem:(NSMenuItem*)anItem
{
	return YES;
}

/*
 The stupid menus just don't work. The menu state is for some reason, unmutable. So Instead we change the Search label
 */
- (void)setDoLocalSearch:(BOOL)state
{
	_doLocalSearch = state;
	if (state) {
		[TBSearchMenuLocal setState:NSOnState];
		[TBSearchMenuRemote setState:NSOffState];
		[[TBSearchField cell] setPlaceholderString:[TBLocalizableStrings TBSearchLocal]];
		[[TBSearchField cell] setSendsWholeSearchString:NO];
		[toolbarSearchItem setLabel:[TBLocalizableStrings TBSearchLabelLocal]];
	} else {
		[TBSearchMenuLocal setState:NSOffState];
		[TBSearchMenuRemote setState:NSOnState];
		[[TBSearchField cell] setPlaceholderString:[TBLocalizableStrings TBSearchRemote]];
		[[TBSearchField cell] setSendsWholeSearchString:YES];
		[toolbarSearchItem setLabel:[TBLocalizableStrings TBSearchLabelRemote]];
	}
	[[[TBSearchField cell] searchMenuTemplate] update];
}

- (BOOL)doLocalSearch;
{
	return _doLocalSearch;
}

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag
{
    // We create and autorelease a new NSToolbarItem, and then go through the process of setting up its
    // attributes from the master toolbar item matching that identifier in our dictionary of items.
    NSToolbarItem *newItem = [[[NSToolbarItem alloc] initWithItemIdentifier:itemIdentifier] autorelease];
    NSToolbarItem *item = [toolbarItems objectForKey:itemIdentifier];
    
    [newItem setLabel:[item label]];
    [newItem setPaletteLabel:[item paletteLabel]];
    if ([item view] != NULL) {
		[newItem setView:[item view]];
    } else {
		[newItem setImage:[item image]];
    }
    [newItem setToolTip:[item toolTip]];
    [newItem setTarget:[item target]];
    [newItem setAction:[item action]];
    [newItem setMenuFormRepresentation:[item menuFormRepresentation]];
    // If we have a custom view, we *have* to set the min/max size - otherwise, it'll default to 0,0 and the custom
    // view won't show up at all!  This doesn't affect toolbar items with images, however.
    if ([newItem view] != NULL) {
		[newItem setMinSize:[[item view] bounds].size];
		[newItem setMaxSize:[[item view] bounds].size];
    }
	// Grab a reference to the search item so we can manipulate its label
	if ([itemIdentifier isEqualToString:@"Search"]) {
		[toolbarSearchItem release];
		toolbarSearchItem = newItem;
	}
    return newItem;
}

- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar
{
	return [NSArray arrayWithObjects:
			@"New",
			@"Import",
			@"Export",
			NSToolbarFlexibleSpaceItemIdentifier,
			@"Search",
			nil];
}

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar
{
    return [NSArray arrayWithObjects:
			@"New",
			@"Import", 
			@"Export",
			@"Backup",
			@"Delete",
			@"Sign",
			@"Edit",
			@"Info",
			@"Search",
			NSToolbarSeparatorItemIdentifier,
			NSToolbarSpaceItemIdentifier,
			NSToolbarFlexibleSpaceItemIdentifier,
			nil];
}

- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem
{
	return YES;
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

@end
