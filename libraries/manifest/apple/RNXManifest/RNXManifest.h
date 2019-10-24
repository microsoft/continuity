#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface RNXManifest : NSObject

@property (readonly, nullable) NSDictionary *data;

@property (readonly, nullable) NSString *name;
@property (readonly, nullable) NSString *displayName;
@property (readonly, nullable) NSDictionary *initialProperties;
@property (readonly, nullable) UIColor *backgroundColor;

- (RNXManifest *_Nullable)init;
- (RNXManifest *_Nullable)initWithManifestPath:(NSString* _Nonnull)manifestPath;

@end
