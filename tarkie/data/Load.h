#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

#import "Employees+CoreDataClass.h"
#import "Announcements+CoreDataClass.h"
#import "AnnouncementSeen+CoreDataClass.h"

#import "Stores+CoreDataClass.h"
#import "StoreContacts+CoreDataClass.h"

#import "ScheduleTimes+CoreDataClass.h"
#import "Schedules+CoreDataClass.h"
#import "TimeIn+CoreDataClass.h"
#import "TimeOut+CoreDataClass.h"

#import "Visits+CoreDataClass.h"
#import "VisitInventories+CoreDataClass.h"
#import "VisitForms+CoreDataClass.h"
#import "Photos+CoreDataClass.h"
#import "CheckIn+CoreDataClass.h"
#import "CheckOut+CoreDataClass.h"

#import "Inventories+CoreDataClass.h"

#import "Forms+CoreDataClass.h"

@interface Load : NSObject

//COMPANY
+ (NSArray<NSDictionary *> *)drawerMenus:(NSManagedObjectContext *)db;
+ (NSArray<NSDictionary *> *)modulePages:(NSManagedObjectContext *)db;
+ (NSArray<Employees *> *)employeeIDs:(NSManagedObjectContext *)db teamID:(long)teamID;
+ (NSArray<Announcements *> *)announcements:(NSManagedObjectContext *)db searchFilter:(NSString *)searchFilter isScheduled:(BOOL)isScheduled;
+ (NSArray<AnnouncementSeen *> *)syncAnnouncementSeen:(NSManagedObjectContext *)db;

//STORES
+ (NSArray<Stores *> *)stores:(NSManagedObjectContext *)db searchFilter:(NSString *)searchFilter;
+ (NSArray<Stores *> *)syncStores:(NSManagedObjectContext *)db;
+ (NSArray<Stores *> *)updateStores:(NSManagedObjectContext *)db;
+ (NSArray<StoreContacts *> *)storeContacts:(NSManagedObjectContext *)db storeID:(long)storeID;
+ (NSArray<StoreContacts *> *)syncStoreContacts:(NSManagedObjectContext *)db;
+ (NSArray<StoreContacts *> *)updateStoreContacts:(NSManagedObjectContext *)db;

//ATTENDANCE
+ (NSArray<ScheduleTimes *> *)scheduleTimes:(NSManagedObjectContext *)db;
+ (NSArray<Schedules *> *)syncSchedules:(NSManagedObjectContext *)db;
+ (NSArray<Schedules *> *)updateSchedules:(NSManagedObjectContext *)db;
+ (NSArray<TimeIn *> *)syncTimeIn:(NSManagedObjectContext *)db;
+ (NSArray<TimeIn *> *)uploadTimeInPhoto:(NSManagedObjectContext *)db;
+ (NSArray<TimeOut *> *)syncTimeOut:(NSManagedObjectContext *)db;
+ (NSArray<TimeOut *> *)uploadTimeOutPhoto:(NSManagedObjectContext *)db;
+ (NSArray<TimeOut *> *)uploadTimeOutSignature:(NSManagedObjectContext *)db;

//VISITS
+ (NSArray<Photos *> *)visitPhotos:(NSManagedObjectContext *)db visitID:(long)visitID;
+ (NSArray<Photos *> *)uploadVisitPhotos:(NSManagedObjectContext *)db;
+ (NSArray<Visits *> *)visits:(NSManagedObjectContext *)db date:(NSDate *)date isNoCheckOutOnly:(BOOL)isNoCheckOutOnly;
+ (NSArray<Visits *> *)syncVisits:(NSManagedObjectContext *)db;
+ (NSArray<Visits *> *)updateVisits:(NSManagedObjectContext *)db;
+ (NSArray<Visits *> *)deleteVisits:(NSManagedObjectContext *)db;
+ (NSArray<VisitInventories *> *)visitInventories:(NSManagedObjectContext *)db visitID:(long)visitID;
+ (NSArray<VisitForms *> *)visitForms:(NSManagedObjectContext *)db visitID:(long)visitID;
+ (NSArray<CheckIn *> *)syncCheckIn:(NSManagedObjectContext *)db;
+ (NSArray<CheckIn *> *)uploadCheckInPhoto:(NSManagedObjectContext *)db;
+ (NSArray<CheckOut *> *)syncCheckOut:(NSManagedObjectContext *)db;
+ (NSArray<CheckOut *> *)uploadCheckOutPhoto:(NSManagedObjectContext *)db;

//EXPENSE


//INVENTORY
+ (NSArray<Inventories *> *)inventories:(NSManagedObjectContext *)db date:(NSDate *)date;

//FORMS
+ (NSArray<Forms *> *)forms:(NSManagedObjectContext *)db date:(NSDate *)date;

@end