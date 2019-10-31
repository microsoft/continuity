#import "Constants.h"
#import "DictionaryReader.h"
#import "RNXManifestEntry.h"
#import "UIColor+String.h"

@implementation RNXManifestEntry

- (RNXManifestEntry *)initWithName:(NSString *)name data:(NSDictionary *)data error:(NSError **)error
{
    self = [super init];
    if (self)
    {
        _name = name;
        
        DictionaryReader *reader = [[DictionaryReader alloc] initWithDictionary:data];
        if (!(_displayName = [reader readKey:@"displayName" asType:[NSString class] error:error]))
        {
            return nil;
        }

        _initialProperties = [reader readKey:@"initialProperties" asType:[NSDictionary class]];
        
        NSString *backgroundColor = [reader readKey:@"backgroundColor" asType:[NSString class]];
        _backgroundColor = [UIColor colorFromString:(backgroundColor ?: @"#ffffff")];
    }
    return self;
}

@end
