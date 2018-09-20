#import "TableViewCell.h"

@interface AnnouncementItemTableViewCell : TableViewCell

@property (weak, nonatomic) IBOutlet UIImageView *ivPhoto;
@property (weak, nonatomic) IBOutlet UILabel *lName;
@property (weak, nonatomic) IBOutlet UILabel *lDetails;
@property (weak, nonatomic) IBOutlet UILabel *lArrow;

@end
