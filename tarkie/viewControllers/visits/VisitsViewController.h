#import "ViewController.h"
#import "DateBarCollectionView.h"

@interface VisitsViewController : ViewController<DateBarDelegate, UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet DateBarCollectionView *cvDateBar;
@property (weak, nonatomic) IBOutlet UILabel *lDate;
@property (weak, nonatomic) IBOutlet UIView *vBorder;
@property (weak, nonatomic) IBOutlet UITableView *tvVisits;

@end
