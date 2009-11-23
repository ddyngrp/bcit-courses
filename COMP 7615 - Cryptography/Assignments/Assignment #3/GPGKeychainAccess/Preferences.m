#import "Preferences.h"

NSString *PKToolbarShowAllItemIdentifier = @"PKToolbarShowAllItem";
NSString *PKPreferencesWindowNotification = @"PKPreferencesWindowNotification";

@interface NSToolbar (NSToolbarPrivate)
- (NSView *)_toolbarView;
@end

@interface PKPreferencesController (PKPreferencesControllerPrivate)
- (void)_doUnselect:(NSNotification *)notification;
- (IBAction)_selectPreferencePane:(id)sender;
- (void)_resizeWindowForContentView:(NSView *)view;
- (NSImage *)_imageForPaneBundle:(NSBundle *)bundle;
- (NSString *)_paletteLabelForPaneBundle:(NSBundle *)bundle;
- (NSString *)_labelForPaneBundle:(NSBundle *)bundle;
@end

@implementation PKPreferencesController

- (id)init
{
	if ((self = [super init])) {
		unsigned i = 0;
		NSBundle *bundle = nil;
		NSString *bundlePath = [NSString stringWithFormat:@"%@/Contents/Resources/PreferencePanes", [[NSBundle mainBundle] bundlePath]];
		panes = [[[NSFileManager defaultManager] directoryContentsAtPath:bundlePath] mutableCopy];
		for (i = 0; i < [panes count]; i++) {
			bundle = [NSBundle bundleWithPath:[NSString stringWithFormat:@"%@/%@", bundlePath, [panes objectAtIndex:i]]];
			[bundle load];
			if (bundle) {
				[panes replaceObjectAtIndex:i withObject:bundle];
			} else {
				[panes removeObjectAtIndex:i];
				i--;
			}
		}
		loadedPanes = [[NSMutableDictionary dictionary] retain];
		paneInfo = [[NSMutableDictionary dictionary] retain];
		[NSBundle loadNibNamed:@"Preferences" owner:self];
		[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector( _doUnselect: ) name:@"NSPreferencePaneDoUnselectNotification" object:nil];
	}
	return self;
}

- (void)dealloc
{
	[loadedPanes autorelease];
	[panes autorelease];
	[paneInfo autorelease];
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	loadedPanes = nil;
	panes = nil;
	paneInfo = nil;
	[super dealloc];
}

- (void)awakeFromNib
{
#if USE_MULTIPLE_PREFERENCES == 1
	NSToolbar *toolbar = [[[NSToolbar alloc] initWithIdentifier:@"preferences.toolbar"] autorelease];
	NSArray *groups = [NSArray arrayWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"PKPreferencePaneGroups" ofType:@"plist"]];
	if (groups) {
		[groupView setPreferencePanes:panes];
		[groupView setPreferencePaneGroups:groups];
		mainView = groupView;
	} else {
		[multiView setPreferencePanes:panes];
		mainView = multiView;
	}
	[self showAll:nil];
	[[self window] setDelegate:self];
	[toolbar setAllowsUserCustomization:YES];
	[toolbar setAutosavesConfiguration:YES];
	[toolbar setDelegate:self];
	[toolbar setAlwaysCustomizableByDrag:YES];
	[toolbar setShowsContextMenu:NO];
	[[self window] setToolbar:toolbar];
	[toolbar setDisplayMode:NSToolbarDisplayModeIconAndLabel];
	[toolbar setIndexOfFirstMovableItem:2];
#else
	[self showAll:nil];
	[[self window] setDelegate:self];
	[self selectPreferencePaneByIdentifier:@"net.sourceforge.macgpg.gpgpreferences"];
#endif
}

- (IBAction)showAll:(id)sender
{
	if ([[[self window] contentView] isEqual:mainView]) {
		return;
	}
	if (currentPaneIdentifier && [[loadedPanes objectForKey:currentPaneIdentifier] shouldUnselect] != NSUnselectNow) {
		return;
	}
	[[self window] setContentView:[[[NSView alloc] initWithFrame:[mainView frame]] autorelease]];
	[[self window] setTitle:[NSString stringWithFormat:NSLocalizedString(@"%@ Preferences", nil), [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleName"]]];
	[self _resizeWindowForContentView:mainView];
	[[loadedPanes objectForKey:currentPaneIdentifier] willUnselect];
	[[self window] setContentView:mainView];
	[[loadedPanes objectForKey:currentPaneIdentifier] didUnselect];
	[currentPaneIdentifier autorelease];
	currentPaneIdentifier = nil;
	[[self window] setInitialFirstResponder:mainView];
	[[self window] makeFirstResponder:mainView];
}

- (IBAction)showPreferences:(id)sender
{
#if USE_MULTIPLE_PREFERENCES == 1
	[self showAll:nil];
#else
	[self selectPreferencePaneByIdentifier:@"net.sourceforge.macgpg.gpgpreferences"];
#endif
	[[self window] makeKeyAndOrderFront:nil];
}

- (void) selectPreferencePaneByIdentifier:(NSString *)identifier
{
	NSBundle *bundle = [NSBundle bundleWithIdentifier:identifier];
	if (bundle && ![currentPaneIdentifier isEqualToString:identifier]) {
		NSPreferencePane *pane = nil;
		NSView *prefView = nil;
		if (currentPaneIdentifier &&
			[[loadedPanes objectForKey:currentPaneIdentifier] shouldUnselect] != NSUnselectNow) {
			closeWhenPaneIsReady = NO;
			[pendingPane autorelease];
			pendingPane = [identifier retain];
			return;
		}
		[pendingPane autorelease];
		pendingPane = nil;
		[loadingImageView setImage:[self _imageForPaneBundle:bundle]];
		[loadingTextField setStringValue:[NSString stringWithFormat:NSLocalizedString(@"Loading %@...", nil), [self _labelForPaneBundle:bundle]]];
		[[self window] setTitle:[self _labelForPaneBundle:bundle]];
		[[self window] setContentView:loadingView];
		[[self window] display];
		if (!(pane = [loadedPanes objectForKey:identifier])) {
			pane = [[[[bundle principalClass] alloc] initWithBundle:bundle] autorelease];
			if (pane) {
				[loadedPanes setObject:pane forKey:identifier];
			}
		}
		if ([pane loadMainView]) {
			[pane willSelect];
			prefView = [pane mainView];
			[self _resizeWindowForContentView:prefView];
			[[loadedPanes objectForKey:currentPaneIdentifier] willUnselect];
			[[self window] setContentView:prefView];
			[[loadedPanes objectForKey:currentPaneIdentifier] didUnselect];
			[pane didSelect];
			[[NSNotificationCenter defaultCenter]
			postNotificationName: PKPreferencesWindowNotification
			object: self
			userInfo: [NSDictionary dictionaryWithObjectsAndKeys:[self window], @"window", nil]];
			[currentPaneIdentifier autorelease];
			currentPaneIdentifier = [identifier copy];
			[[self window] setInitialFirstResponder:[pane initialKeyView]];
			[[self window] makeFirstResponder:[pane initialKeyView]];
		} else {
			NSRunCriticalAlertPanel(NSLocalizedString(@"Preferences Error", nil),
			[NSString stringWithFormat:NSLocalizedString(@"Could not load %@", nil), [self _labelForPaneBundle:bundle]], nil, nil, nil);
		}
	}
}

- (BOOL)windowShouldClose:(id)sender
{
	if (currentPaneIdentifier && [[loadedPanes objectForKey:currentPaneIdentifier] shouldUnselect] != NSUnselectNow) {
		closeWhenPaneIsReady = YES;
		return NO;
	}
	return YES;
}

- (void)windowWillClose:(NSNotification *)notification
{
	[[loadedPanes objectForKey:currentPaneIdentifier] willUnselect];
	[[loadedPanes objectForKey:currentPaneIdentifier] didUnselect];
	[currentPaneIdentifier autorelease];
	currentPaneIdentifier = nil;
	[[NSUserDefaults standardUserDefaults] synchronize];
}

- (NSToolbarItem *) toolbar:(NSToolbar *) toolbar
	itemForItemIdentifier:(NSString *) itemIdentifier
	willBeInsertedIntoToolbar:(BOOL) flag
{
	NSToolbarItem *toolbarItem = [[[NSToolbarItem alloc] initWithItemIdentifier:itemIdentifier] autorelease];
	if ( [itemIdentifier isEqualToString:PKToolbarShowAllItemIdentifier] ) {
		[toolbarItem setLabel:NSLocalizedString( @"Show All", nil )];
		[toolbarItem setImage:[NSImage imageNamed:@"NSApplicationIcon"]];
		[toolbarItem setTarget:self];
		[toolbarItem setAction:@selector( showAll: )];
	} else {
		NSBundle *bundle = [NSBundle bundleWithIdentifier:itemIdentifier];
		if( bundle ) {
			[toolbarItem setLabel:[self _labelForPaneBundle:bundle]];
			[toolbarItem setPaletteLabel:[self _paletteLabelForPaneBundle:bundle]];
			[toolbarItem setImage:[self _imageForPaneBundle:bundle]];
			[toolbarItem setTarget:self];
			[toolbarItem setAction:@selector(_selectPreferencePane:)];
		} else toolbarItem = nil;
	}
	return toolbarItem;
}

- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar *)toolbar
{
	NSMutableArray *fixed = [NSMutableArray arrayWithObjects:PKToolbarShowAllItemIdentifier, NSToolbarSeparatorItemIdentifier, nil];
	NSArray *defaults = [NSArray arrayWithContentsOfFile:[[NSBundle mainBundle] pathForResource:@"PKPreferencePaneDefaults" ofType:@"plist"]];
	[fixed addObjectsFromArray:defaults];
	return fixed;
}

- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar *)toolbar
{
	NSMutableArray *items = [NSMutableArray array];
	NSEnumerator *enumerator = [panes objectEnumerator];
	id item = nil;
	while ((item = [enumerator nextObject])) {
		[items addObject:[item bundleIdentifier]];
	}
	[items addObject:NSToolbarSeparatorItemIdentifier];
	return items;
}

@end

@implementation PKPreferencesController (PKPreferencesControllerPrivate)

- (IBAction)_selectPreferencePane:(id)sender
{
	[self selectPreferencePaneByIdentifier:[sender itemIdentifier]];
}

- (void)_doUnselect:(NSNotification *)notification
{
	if( closeWhenPaneIsReady ) {
		[[self window] close];
	}
	[self selectPreferencePaneByIdentifier:pendingPane];
}

- (void)_resizeWindowForContentView:(NSView *)view
{
	NSRect windowFrame, newWindowFrame;
	unsigned int newWindowHeight;
	windowFrame = [NSWindow contentRectForFrameRect:[[self window] frame] styleMask:[[self window] styleMask]];
	newWindowHeight = NSHeight([view frame]);
	if ([[[self window] toolbar] isVisible]) {
		newWindowHeight += NSHeight([[[[self window] toolbar] _toolbarView] frame]);
	}
	newWindowFrame = [NSWindow frameRectForContentRect:NSMakeRect(NSMinX(windowFrame), NSMaxY(windowFrame) - newWindowHeight, NSWidth(windowFrame), newWindowHeight) styleMask:[[self window] styleMask]];
	[[self window] setFrame:newWindowFrame display:YES animate:[[self window] isVisible]];
}

- (NSImage *)_imageForPaneBundle:(NSBundle *)bundle
{
	NSImage *image = nil;
	NSMutableDictionary *cache = [paneInfo objectForKey:[bundle bundleIdentifier]];
	image = [[[cache objectForKey:@"PKPreferencePaneImage"] retain] autorelease];
	if (!image) {
		NSDictionary *info = [bundle infoDictionary];
		image = [[[NSImage alloc] initWithContentsOfFile:[bundle pathForImageResource:[info objectForKey:@"NSPrefPaneIconFile"]]] autorelease];
		if (!image) {
			image = [[[NSImage alloc] initWithContentsOfFile:[bundle pathForImageResource:[info objectForKey:@"CFBundleIconFile"]]] autorelease];
		}
		if (!cache) {
			[paneInfo setObject:[NSMutableDictionary dictionary] forKey:[bundle bundleIdentifier]];
		}
		cache = [paneInfo objectForKey:[bundle bundleIdentifier]];
		if (image) {
			[cache setObject:image forKey:@"PKPreferencePaneImage"];
		}
	}
	return image;
}

- (NSString *)_paletteLabelForPaneBundle:(NSBundle *)bundle
{
	NSString *label = nil;
	NSMutableDictionary *cache = [paneInfo objectForKey:[bundle bundleIdentifier]];
	label = [[[cache objectForKey:@"PKPreferencePanePaletteLabel"] retain] autorelease];
	if (!label) {
		NSDictionary *info = [bundle infoDictionary];
		label = NSLocalizedStringFromTableInBundle( @"NSPrefPaneIconLabel", @"InfoPlist", bundle, nil );
		if ([label isEqualToString:@"NSPrefPaneIconLabel"]) {
			label = [info objectForKey:@"NSPrefPaneIconLabel"];
		}
		if (!label) {
			label = NSLocalizedStringFromTableInBundle( @"CFBundleName", @"InfoPlist", bundle, nil );
		}
		if ([label isEqualToString:@"CFBundleName"]) {
			label = [info objectForKey:@"CFBundleName"];
		}
		if (!label) {
			label = [bundle bundleIdentifier];
		}
		if (!cache) {
			[paneInfo setObject:[NSMutableDictionary dictionary] forKey:[bundle bundleIdentifier]];
		}
		cache = [paneInfo objectForKey:[bundle bundleIdentifier]];
		if (label) {
			[cache setObject:label forKey:@"PKPreferencePanePaletteLabel"];
		}
	}
	return label;
}

- (NSString *)_labelForPaneBundle:(NSBundle *)bundle
{
	NSString *label = nil;
	NSMutableDictionary *cache = [paneInfo objectForKey:[bundle bundleIdentifier]];
	label = [[[cache objectForKey:@"PKPreferencePaneLabel"] retain] autorelease];
	if (!label) {
		NSDictionary *info = [bundle infoDictionary];
		label = NSLocalizedStringFromTableInBundle( @"CFBundleName", @"InfoPlist", bundle, nil );
		if ([label isEqualToString:@"CFBundleName"]) {
			label = [info objectForKey:@"CFBundleName"];
		}
		if (!label) {
			label = [bundle bundleIdentifier];
		}
		if (!cache) {
			[paneInfo setObject:[NSMutableDictionary dictionary] forKey:[bundle bundleIdentifier]];
		}
		cache = [paneInfo objectForKey:[bundle bundleIdentifier]];
		if (label) {
			[cache setObject:label forKey:@"PKPreferencePaneLabel"];
		}
	}
	return label;
}

@end