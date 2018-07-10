#import "CustomViewController.h"
#import "TextField.h"
#import "StoresViewController.h"

@protocol DropDownDelegate
@optional

- (void)onDropDownCancel:(int)type action:(int)action;
- (void)onDropDownSelect:(int)type action:(int)action item:(id)item;

@end

@interface DropDownDialogViewController : CustomViewController<UITableViewDataSource, UITableViewDelegate, StoresDelegate>

@property (weak, nonatomic) IBOutlet UILabel *lMessage;
@property (weak, nonatomic) IBOutlet TextField *tfDropDown;
@property (weak, nonatomic) IBOutlet UIButton *btnDropDown;
@property (weak, nonatomic) IBOutlet UITableView *tvItems;
@property (weak, nonatomic) IBOutlet TextView *tfNotes;
@property (weak, nonatomic) IBOutlet UIButton *btnNegative;
@property (weak, nonatomic) IBOutlet UIButton *btnPositive;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *tvItemsHeight;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *tfNotesHeight;

typedef enum {
    DROP_DOWN_TYPE_STORE,
    DROP_DOWN_TYPE_SCHEDULE,
    DROP_DOWN_TYPE_CHECK_OUT_STATUS
} DropDownType;

typedef enum {
    DROP_DOWN_ACTION_TIME_IN,
    DROP_DOWN_ACTION_TIME_OUT,
    DROP_DOWN_ACTION_CHECK_OUT
} DropDownAction;

@property (assign) id <DropDownDelegate> delegate;
@property (nonatomic) DropDownType type;
@property (nonatomic) DropDownAction action;
@property (strong, nonatomic) UIViewController *parent;
@property (strong, nonatomic) NSArray *items;

@end
