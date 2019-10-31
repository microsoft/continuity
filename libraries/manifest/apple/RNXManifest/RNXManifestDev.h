#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface RNXManifestDev : NSObject

@property (readonly) NSString *bundleFileName;
@property (readonly) NSString *bundleFileExtension;

@property (readonly) NSString *packagerHost;
@property (readonly) NSString *packagerFileName;

- (RNXManifestDev *_Nullable)init;
- (RNXManifestDev *_Nullable)initWithData:(NSDictionary *)data;

@end

NS_ASSUME_NONNULL_END
