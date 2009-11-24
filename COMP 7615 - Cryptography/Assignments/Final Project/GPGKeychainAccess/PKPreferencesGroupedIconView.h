/* PreferencesGroupedIconView */

#import <Cocoa/Cocoa.h>

@class PKPreferencesController;

@interface PKPreferencesGroupedIconView : NSView
{
    IBOutlet PKPreferencesController *preferencesController;
	NSBundle *selectedPane;
	NSArray *preferencePanes;
	NSArray *preferencePaneGroups;
	NSMutableArray *groupMultiIconViews;
}

- (void)setPreferencesController:(PKPreferencesController *)newPreferencesController;
- (void)setPreferencePanes:(NSArray *)newPreferencePanes;
- (NSArray *)preferencePanes;
- (void)setPreferencePaneGroups:(NSArray *)newPreferencePaneGroups;
- (NSArray *)preferencePaneGroups;
 
@end
