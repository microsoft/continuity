#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "Constants.h"
#import "RNXManifestEntry.h"

NS_ASSUME_NONNULL_BEGIN

@interface RNXManifestEntry : NSObject

@property (readonly) NSString *name;
@property (readonly) NSString *displayName;
@property (readonly, nullable) NSDictionary *initialProperties;
@property (readonly) UIColor *backgroundColor;

- (RNXManifestEntry *_Nullable)initWithName:(NSString *)name data:(NSDictionary *)data error:(NSError *_Nullable *)error;

@end

NS_ASSUME_NONNULL_END
