/* SearchKeyController */

#import <Cocoa/Cocoa.h>
#import <MacGPGME/MacGPGME.h>
#import "PKLocalisableStrings.h"
#import "TBLocalizableStrings.h"

@class PKLocalizableStrings;
@class TBLocalizableStrings;

@interface SearchKeyController : NSWindowController
{
    IBOutlet NSProgressIndicator	*busyIndicator;
    IBOutlet NSOutlineView			*keyList;
    IBOutlet NSSearchField			*searchField;
    IBOutlet NSTextField			*statusBar;
	IBOutlet NSView					*searchFieldView;
	NSMutableDictionary				*toolbarItems;
	NSArray							*searchResults;
	GPGContext						*context;
	BOOL							isSearching;	// is a search operation in progress?
	BOOL							isImporting;	// is an import operation in progress?
	
	/* Sorting */
    NSTableColumn	*sortingTableColumn;
	BOOL			keysAreSorted;
    SEL				sortingSelector;
    BOOL			ascendingOrder;
	
}

+ (id)sharedInstance;

- (IBAction)importKey:(id)sender;
- (IBAction)searchForKey:(id)sender;
- (void)searchForKeyResults:(NSNotification *)notification;
- (void)searchForKeyWithSearchString:(NSString *)searchString;

/* sorting */
- (void)setSortingSelector:(SEL)selector ascending:(BOOL)ascending;
- (BOOL)ascendingOrder;

// insert outlineView methods here

- (NSToolbarItem *)toolbar:(NSToolbar *)toolbar itemForItemIdentifier:(NSString *)itemIdentifier willBeInsertedIntoToolbar:(BOOL)flag;    
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;
- (BOOL)validateToolbarItem:(NSToolbarItem *)theItem;
- (void)addItemToToolbar:(NSString *)identifier
				   label:(NSString *)label
			paletteLabel:(NSString *)paletteLabel
				 toolTip:(NSString *)toolTip
				  target:(id)target
				  action:(SEL)action
		 settingSelector:(SEL)settingSelector
			 itemContent:(id)itemContent
					menu:(NSMenu *)menu;

@end
