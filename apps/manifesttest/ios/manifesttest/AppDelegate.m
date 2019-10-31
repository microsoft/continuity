/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "AppDelegate.h"

#import <React/RCTBridge.h>
#import <React/RCTBundleURLProvider.h>
#import <React/RCTRootView.h>

@implementation AppDelegate


- (BOOL)loadAppManifest:(NSString *)manifestPath
{
  NSError *error;

  _manifest = [[RNXManifest alloc] initWithContentsOfFile:manifestPath error:&error];
  if (!_manifest)
  {
    [self showManifestError:error withManifestPath:manifestPath usingViewController:_window.rootViewController];
    return NO;
  }
  
  return YES;
}

- (RCTRootView *)createReactNativeExperience:(RCTBridge *)bridge fromEntry:(RNXManifestEntry *)entry
{
  RCTRootView *rootView = [[RCTRootView alloc] initWithBridge:bridge moduleName:entry.name initialProperties:entry.initialProperties];
  rootView.backgroundColor = entry.backgroundColor;

  return rootView;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  //  Create the test app view controller which renders the RNX and any error messages.
  //  Brownfield apps will provide this, rather than creating it.
  //
  _window = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
  _window.rootViewController = [[UIViewController alloc] init];

  //  Load the react-native manifest for this brownfield app.
  //
  if (![self loadAppManifest:[[NSBundle mainBundle] pathForResource:@"app" ofType:@"json"]])
  {
    return NO;
  }

  //  Create a bridge to be shared among all RNXs (singleton).
  //
  RCTBridge *bridge = [[RCTBridge alloc] initWithDelegate:self launchOptions:launchOptions];

  //  Create the test app RNX.
  //
  RCTRootView *rootView = [self createReactNativeExperience:bridge fromEntry:_manifest.entries[@"manifesttest"]];

  //  Render the RNX.
  //
  _window.rootViewController.view = rootView;
  [self.window makeKeyAndVisible];

  return YES;
}

- (NSURL *)sourceURLForBridge:(RCTBridge *)bridge
{
  RCTBundleURLProvider *provider = [RCTBundleURLProvider sharedSettings];

#if DEBUG
  NSString *packagerHost = [provider jsLocation];
#if RCT_DEV
  if (!packagerHost && [provider isPackagerRunning:_manifest.dev.packagerHost])
  {
    packagerHost = _manifest.dev.packagerHost;
  }
#endif // RCT_DEV

  if (packagerHost)
  {
    return [RCTBundleURLProvider jsBundleURLForBundleRoot:_manifest.dev.packagerFileName
                                             packagerHost:packagerHost
                                                enableDev:[provider enableDev]
                                       enableMinification:[provider enableMinification]];
  }
#endif // DEBUG

  return [provider jsBundleURLForFallbackResource:_manifest.dev.bundleFileName
                                fallbackExtension:_manifest.dev.bundleFileExtension];
}

- (void)showManifestError:(NSError *)error withManifestPath:(NSString *)manifestPath usingViewController:(UIViewController *)controller
{
  NSMutableString *message = [NSMutableString stringWithCapacity:500];
  [message appendFormat:@"Failed to load the react-native manifest: error %i (%@)\n\n", (int)error.code, error.domain];
  [message appendFormat:@"Path = %@", manifestPath];
  if (error.userInfo && error.userInfo.count > 0)
  {
    for (id key in error.userInfo)
    {
      [message appendFormat:@"\n\n%@ = %@", key, [error.userInfo objectForKey:key]];
    }
  }

  NSMutableParagraphStyle *style = [[NSMutableParagraphStyle alloc] init];
  style.alignment = NSTextAlignmentLeft;

  NSMutableAttributedString *stylizedMessage = [[NSMutableAttributedString alloc] initWithString:message attributes:@{NSParagraphStyleAttributeName:style, NSFontAttributeName:[UIFont systemFontOfSize:14.0]}];

  UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Manifest Error" message:@"" preferredStyle:UIAlertControllerStyleAlert];
  [alert setValue:stylizedMessage forKey:@"attributedMessage"];

  UIAlertAction *action = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction *a) {
    [controller dismissViewControllerAnimated:YES completion:nil];
  }];
  [alert addAction:action];

  [self.window makeKeyAndVisible];
  [controller presentViewController:alert animated:YES completion:nil];
}

@end
