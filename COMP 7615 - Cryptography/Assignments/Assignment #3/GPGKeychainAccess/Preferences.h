/* Preferences */

/*
This class has been basically copied from the Camino project's preferences controllers.
It is severe overkill for what we are doing, but seems a reasonable place to start.
If we want System Preferences style toolbar and grouped preferences, it is not overkill.
 */

#import <Cocoa/Cocoa.h>
#import <PreferencePanes/PreferencePanes.h>
#import "ToolbarAdditions.h"
#import "Preferences.h"
#import "PKPreferencesMultiIconView.h"
#import "PKPreferencesGroupedIconView.h"
#import "GPGKeys_PREFIX.h"

extern NSString *PKPreferencesWindowNotification;

@class PKPreferencesMultiIconView;
@class PKPreferencesGroupedIconView;

@interface PKPreferencesController : NSWindowController
{
    IBOutlet PKPreferencesGroupedIconView *groupView;
    IBOutlet NSImageView *loadingImageView;
    IBOutlet NSTextField *loadingTextField;
    IBOutlet NSView *loadingView;
    IBOutlet PKPreferencesMultiIconView *multiView;
	NSView *mainView;
	NSMutableArray *panes;
	NSMutableDictionary *loadedPanes;
	NSMutableDictionary *paneInfo;
	NSString *currentPaneIdentifier;
	NSString *pendingPane;
	BOOL closeWhenDoneWithSheet;
	BOOL closeWhenPaneIsReady;
}

- (void)showAll:(id)sender;
- (void)showPreferences:(id)sender;
- (void)selectPreferencePaneByIdentifier:(NSString *)identifier;
@end
