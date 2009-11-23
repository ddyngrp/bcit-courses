/* PreferencesMultiIconView */

#import <Cocoa/Cocoa.h>

@class PKPreferencesController;

extern const NSSize buttonSize;
extern const NSSize iconSize;
extern const unsigned int titleBaseLine;
extern const unsigned int iconBaseLine;
extern const unsigned int bottomBorder;

@interface PKPreferencesMultiIconView : NSView
{
	IBOutlet PKPreferencesController *preferencesController;
	unsigned int pressedIconIndex;
	unsigned int focusedIndex;
	int tag;
	NSBundle *selectedPane;
	NSArray *preferencePanes;
}

- (void)setPreferencesController:(PKPreferencesController *)newPreferencesController;
- (void)setPreferencePanes:(NSArray *)newPreferencePanes;
- (NSArray *)preferencePanes;
- (void)setSelectedPane:(NSBundle *)newSelectedClientRecord;
- (int)tag;
- (void)setTag:(int)newTag;

@end
