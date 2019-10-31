#import <Foundation/Foundation.h>
#import "RNXManifestDev.h"

@implementation RNXManifestDev

static const NSString *const kPropertyBundleFileName = @"bundleFileName";
static const NSString *const kPropertyBundleFileExtension = @"bundleFileExtension";
static const NSString *const kPropertyPackagerHost = @"packagerHost";
static const NSString *const kPropertyPackagerFileName = @"packagerFileName";

static const NSString *const kDefaultBundleFileName = @"main";
static const NSString *const kDefaultBundleFileExtension = @"jsbundle";
static const NSString *const kDefaultPackagerHost = @"localhost";
static const NSString *const kDefaultPackagerFileName = @"index";

- (RNXManifestDev *)init
{
    return [self initWithData:@{
        kPropertyBundleFileName: kDefaultBundleFileName,
        kPropertyBundleFileExtension: kDefaultBundleFileExtension,
        kPropertyPackagerHost: kDefaultPackagerHost,
        kPropertyPackagerFileName: kDefaultPackagerFileName
    }];
}

- (RNXManifestDev *)initWithData:(NSDictionary *)data
{
    self = [super init];
    if (self)
    {
        _bundleFileName = data[kPropertyBundleFileName] ?: kDefaultBundleFileName;
        _bundleFileExtension = data[kPropertyBundleFileExtension] ?: kDefaultBundleFileExtension;
        _packagerHost = data[kPropertyPackagerHost] ?: kDefaultPackagerHost;
        _packagerFileName = data[kPropertyPackagerFileName] ?: kDefaultPackagerFileName;
    }
    return self;
}

@end
