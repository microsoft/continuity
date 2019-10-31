#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIColor (String)

/// Create a UIColor object from a string.
///
/// Supported formats:
///    #rgb
///    #rrggbb

+ (UIColor *)colorFromString:(NSString*)colorString;

@end

NS_ASSUME_NONNULL_END
