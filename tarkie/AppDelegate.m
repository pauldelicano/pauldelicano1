#import "AppDelegate.h"
#import "App.h"
#import "Get.h"
#import "Update.h"
#import "File.h"
#import "Time.h"
#import "MainViewController.h"

@interface AppDelegate()

@property (strong, nonatomic) NSPersistentStoreCoordinator *psc;
@property (strong, nonatomic) NSTimer *timer;
@property (nonatomic) long interval;
@property (nonatomic) BOOL applicationDidEnterBackground, isUpdatingLocation;

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [UIDevice.currentDevice setBatteryMonitoringEnabled:YES];
    self.psc = [self persistentStoreCoordinatorInit:@"tarkie.db"];
    self.db = [self managedObjectContextInit:self.psc councurrencyType:NSPrivateQueueConcurrencyType];
    self.dbTracking = [self managedObjectContextInit:self.psc councurrencyType:NSPrivateQueueConcurrencyType];
    self.dbAlerts = [self managedObjectContextInit:self.psc councurrencyType:NSPrivateQueueConcurrencyType];
    self.locationManager = [self locationManagerInit:self];
    self.userNotificationCenter = [self userNotificationCenterInit:self];
    NSSetUncaughtExceptionHandler(&uncaughtExceptionHandler);
    return YES;
}

void uncaughtExceptionHandler(NSException *exception) {
    [File saveExceptionToBackup:exception];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    if(self.applicationDidEnterBackground) {
        UIViewController *rootViewController = self.window.rootViewController;
        if([rootViewController isKindOfClass:UINavigationController.class]) {
            rootViewController = [(UINavigationController *)rootViewController topViewController];
        }
        [rootViewController viewDidAppear:NO];
    }
    self.applicationDidEnterBackground = NO;
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    self.applicationDidEnterBackground = YES;
    if(self.isUpdatingLocation && self.authorizationStatus != kCLAuthorizationStatusAuthorizedAlways) {
        [self.locationManager stopUpdatingLocation];
    }
}

- (NSPersistentStoreCoordinator *)persistentStoreCoordinatorInit:(NSString *)dbName {
    NSPersistentStoreCoordinator *persistentStoreCoordinator = [NSPersistentStoreCoordinator.alloc initWithManagedObjectModel:[NSManagedObjectModel.alloc initWithContentsOfURL:[NSBundle.mainBundle URLForResource:@"DataModel" withExtension:@"momd"]]];
    NSError *error = nil;
    NSMutableDictionary *options = NSMutableDictionary.alloc.init;
    options[NSMigratePersistentStoresAutomaticallyOption] = @YES;
    options[NSInferMappingModelAutomaticallyOption] = @YES;
    options[NSSQLitePragmasOption] = @{@"journal_mode":@"DELETE"};
    [persistentStoreCoordinator addPersistentStoreWithType:NSSQLiteStoreType configuration:nil URL:[[NSFileManager.defaultManager URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask].lastObject URLByAppendingPathComponent:dbName] options:options error:&error];
    if(error != nil) {
        NSLog(@"error: appDelegate persistentStoreCoordinatorInit - %@", error.localizedDescription);
    }
    return persistentStoreCoordinator;
}

- (NSManagedObjectContext *)managedObjectContextInit:(NSPersistentStoreCoordinator *)persistentStoreCoordinator councurrencyType:(NSManagedObjectContextConcurrencyType)concurrencyType {
    NSManagedObjectContext *managedObjectContext = [NSManagedObjectContext.alloc initWithConcurrencyType:concurrencyType];
    managedObjectContext.persistentStoreCoordinator = persistentStoreCoordinator;
    return managedObjectContext;
}

- (CLLocationManager *)locationManagerInit:(id)delegate {
    CLLocationManager *locationManager = CLLocationManager.alloc.init;
    locationManager.delegate = delegate;
    locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    locationManager.distanceFilter = kCLDistanceFilterNone;
    locationManager.pausesLocationUpdatesAutomatically = NO;
    locationManager.allowsBackgroundLocationUpdates = YES;
    return locationManager;
}

- (UNUserNotificationCenter *)userNotificationCenterInit:(id)delegate {
    UNUserNotificationCenter *userNotificationCenter = UNUserNotificationCenter.currentNotificationCenter;
    userNotificationCenter.delegate = delegate;
    [userNotificationCenter requestAuthorizationWithOptions:(UNAuthorizationOptionSound | UNAuthorizationOptionAlert) completionHandler:^(BOOL granted, NSError * _Nullable error){
        if(error != nil) {
            NSLog(@"error: appDelegate userNotificationCenterInit - %@", error.localizedDescription);
            return;
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            [UIApplication.sharedApplication registerForRemoteNotifications];
        });
    }];
    return userNotificationCenter;
}

- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status {
    if(self.isUpdatingLocation) {
        if(self.authorizationStatus != 0 && self.authorizationStatus != status) {
            if(status == kCLAuthorizationStatusAuthorizedAlways) {
                NSLog(@"alert: ALERT_TYPE_TURNED_ON_GPS");
                [Update alertSave:self.dbAlerts alertTypeID:ALERT_TYPE_TURNED_ON_GPS gpsID:[Update gpsSave:self.dbTracking dbAlerts:self.dbAlerts location:self.location] value:nil];
            }
            else {
                NSLog(@"alert: ALERT_TYPE_TURNED_OFF_GPS");
                [Update alertSave:self.dbAlerts alertTypeID:ALERT_TYPE_TURNED_OFF_GPS gpsID:[Update gpsSave:self.dbTracking dbAlerts:self.dbAlerts location:self.location] value:nil];
            }
        }
        [self.locationManager startUpdatingLocation];
    }
    if(self.applicationDidEnterBackground && self.isUpdatingLocation && status != kCLAuthorizationStatusAuthorizedAlways) {
        [self.locationManager stopUpdatingLocation];
    }
    self.authorizationStatus = status;
}

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations {
    self.location = locations.lastObject;
    if(self.isUpdatingLocation && self.settingLocationGPSTracking && self.settingLocationGPSTrackingInterval != 0) {
        if(self.timer != nil && self.interval != 0 && self.interval != self.settingLocationGPSTrackingInterval) {
            [self.timer invalidate];
            self.timer = nil;
        }
        if(self.timer == nil) {
            if([Get isTimeIn:self.dbTracking]) {
                self.interval = self.settingLocationGPSTrackingInterval;
                if([self saveTracking]) {
                    [NSNotificationCenter.defaultCenter postNotificationName:@"UserNotificationCenterDidUpdateLocations" object:nil userInfo:nil];
                }
                self.timer = [NSTimer scheduledTimerWithTimeInterval:self.interval * 60 target:^{
                    if([self saveTracking]) {
                        [NSNotificationCenter.defaultCenter postNotificationName:@"UserNotificationCenterDidUpdateLocations" object:nil userInfo:nil];
                    }
                } selector:@selector(invoke) userInfo:nil repeats:YES];
            }
        }
    }
}

- (BOOL)application:(UIApplication *)application shouldSaveApplicationState:(NSCoder *)coder {
    return YES;
}

- (BOOL)application:(UIApplication *)application shouldRestoreApplicationState:(NSCoder *)coder {
    return YES;
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler {
    completionHandler(UNAuthorizationOptionSound | UNAuthorizationOptionAlert);
    [NSNotificationCenter.defaultCenter postNotificationName:@"UserNotificationCenterWillPresentNotification" object:nil userInfo:notification.request.content.userInfo];
}

- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)(void))completionHandler {
    completionHandler();
    [NSNotificationCenter.defaultCenter postNotificationName:@"UserNotificationCenterDidReceiveNotificationResponse" object:nil userInfo:response.notification.request.content.userInfo];
}

- (void)startUpdatingLocation {
    [self.locationManager startUpdatingLocation];
    self.isUpdatingLocation = YES;
}

- (void)stopUpdatingLocation {
    [self.locationManager stopUpdatingLocation];
    self.isUpdatingLocation = NO;
    if(self.timer != nil) {
        [self.timer invalidate];
        self.timer = nil;
    }
}

- (BOOL)saveTracking {
    int64_t gpsID = [Update gpsSave:self.dbTracking dbAlerts:self.dbAlerts location:self.location];
    if(gpsID == 0) {
        return NO;
    }
    Tracking *tracking = [NSEntityDescription insertNewObjectForEntityForName:@"Tracking" inManagedObjectContext:self.dbTracking];
    tracking.trackingID = [Get sequenceID:self.dbTracking entity:@"Tracking" attribute:@"trackingID"] + 1;
    tracking.syncBatchID = self.syncBatchID;
    tracking.employeeID = self.employee.employeeID;
    NSDate *currentDate = NSDate.date;
    tracking.date = [Time getFormattedDate:DATE_FORMAT date:currentDate];
    tracking.time = [Time getFormattedDate:TIME_FORMAT date:currentDate];
    tracking.isSync = NO;
    tracking.timeInID = [Get timeIn:self.dbTracking].timeInID;
    tracking.gpsID = gpsID;
    return [Update save:self.dbTracking];
}

@end
