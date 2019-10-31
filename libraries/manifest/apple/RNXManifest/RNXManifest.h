#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "RNXManifestDev.h"
#import "RNXManifestEntry.h"

NS_ASSUME_NONNULL_BEGIN

@interface RNXManifest : NSObject

@property (readonly) NSDictionary<NSString *, RNXManifestEntry *> *entries;
@property (readonly) RNXManifestDev *dev;

- (RNXManifest *_Nullable)initWithManifestData:(NSDictionary *)data
                                         error:(NSError *_Nullable *)error;

- (RNXManifest *_Nullable)initWithContentsOfFile:(NSString *)manifestPath
                                           error:(NSError *_Nullable *)error;

@end

NS_ASSUME_NONNULL_END
