/* TBController */

#import <Cocoa/Cocoa.h>
#import "TBLocalizableStrings.h"

@class PKController;
@class PKInspectorController;
@class TBLocalizableStrings;

@interface TBController : NSObject
{
	IBOutlet NSWindow *pkWindow;
	IBOutlet PKController *keyController;
    IBOutlet PKInspectorController *inspectorController;
    IBOutlet NSOutlineView *keyOutline;

	IBOutlet NSSearchField *TBSearchField;
	IBOutlet NSView *TBSearchView;
	IBOutlet NSMenuItem *TBSearchMenuLocal;
	IBOutlet NSMenuItem *TBSearchMenuRemote;
	
	NSMutableDictionary *toolbarItems;
	NSToolbarItem *toolbarSearchItem;
	BOOL _doLocalSearch;
}

- (IBAction)search:(id)sender;
- (IBAction)setSearchSourceToLocal:(id)sender;
- (IBAction)setSearchSourceToRemote:(id)sender;

- (BOOL)validateMenuItem:(NSMenuItem*)anItem;
- (void)setDoLocalSearch:(BOOL)state;
- (BOOL)doLocalSearch;

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