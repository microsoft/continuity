#import "manifest.h"
#import "UIColor+String.h"

@implementation manifest

- (manifest *_Nullable)init
{
    NSString *manifestPath = [[NSBundle mainBundle] pathForResource:@"app" ofType:@"json"];
    self = [self initWithManifestPath:manifestPath];
    return self;
}

- (manifest *_Nullable)initWithManifestPath:(NSString* _Nonnull)manifestPath
{
    self = [super init];
    if (self)
    {
        NSData *manifestData = [NSData dataWithContentsOfFile:manifestPath];
        _data = [NSJSONSerialization JSONObjectWithData:manifestData options:kNilOptions error:nil];
        
        _name = _data[@"name"];
        _displayName = _data[@"displayName"];
        _initialProperties = _data[@"initialProperties"];
        _backgroundColor = [UIColor colorFromString:_data[@"backgroundColor"]];
        if (!_backgroundColor)
            _backgroundColor = [UIColor colorWithRed:1.0f green:1.0f blue:1.0f alpha:1];
    }
    return self;
}

@end
