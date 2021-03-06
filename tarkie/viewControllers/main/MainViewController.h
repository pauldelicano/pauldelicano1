#import "ViewController.h"
#import "DrawerViewController.h"
#import "MainPageBarCollectionView.h"
#import "LoadingDialogViewController.h"
#import "NoGPSDialogViewController.h"
#import "DropDownDialogViewController.h"
#import "ListDialogViewController.h"
#import "BreakViewController.h"
#import "CameraViewController.h"
#import "AttendanceSummaryViewController.h"

@interface MainViewController : ViewController<UIPageViewControllerDataSource, UIPageViewControllerDelegate, UIScrollViewDelegate, DrawerDelegate, MainPageBarDelegate, LoadingDelegate, NoGPSDelegate, DropDownDelegate, ListDelegate, BreakDelegate, CameraDelegate, AttendanceSummaryDelegate>

@property (weak, nonatomic) IBOutlet UIView *vStatusBar;
@property (weak, nonatomic) IBOutlet UIView *vNavBar;
@property (weak, nonatomic) IBOutlet MainPageBarCollectionView *cvMainPageBar;
@property (weak, nonatomic) IBOutlet UIView *vBottomBar;

@property (weak, nonatomic) IBOutlet UIView *vNavBarButtonsHome;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsHomeAnnouncements;
@property (weak, nonatomic) IBOutlet UILabel *lNavBarButtonsHomeAnnouncementsCount;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsHomeSync;
@property (weak, nonatomic) IBOutlet UILabel *lNavBarButtonsHomeSyncCount;

@property (weak, nonatomic) IBOutlet UIView *vNavBarButtonsVisits;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsVisitsDate;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsVisitsAddVisit;

@property (weak, nonatomic) IBOutlet UIView *vNavBarButtonsExpense;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsExpenseNewReport;

@property (weak, nonatomic) IBOutlet UIView *vNavBarButtonsInventory;

@property (weak, nonatomic) IBOutlet UIView *vNavBarButtonsForms;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsFormsSearch;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsFormsSelect;

@property (weak, nonatomic) IBOutlet UIView *vNavBarButtonsHistory;
@property (weak, nonatomic) IBOutlet UILabel *lNavBarButtonsHistoryDate;
@property (weak, nonatomic) IBOutlet UIButton *btnNavBarButtonsHistoryDate;

@property (strong, nonatomic) DrawerViewController *vcDrawer;
@property (strong, nonatomic) NSMutableArray<ViewController *> *viewControllers;
@property (nonatomic) BOOL isTimeIn;

- (BOOL)applicationDidBecomeActive;
- (BOOL)gpsRequest;
- (BOOL)cameraRequest;

- (void)updateUnSeenAnnouncementsCount;
- (void)updateSyncDataCount;

@end
