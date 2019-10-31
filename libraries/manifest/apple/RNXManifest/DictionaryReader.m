#import "Constants.h"
#import "DictionaryReader.h"

@implementation DictionaryReader

- (DictionaryReader *)initWithDictionary:(NSDictionary *)dictionary
{
    self = [super init];
    if (self)
    {
        _dictionary = dictionary;
    }
    return self;
}

- (id)readKey:(NSString *)key asType:(Class)valueType error:(NSError **)error
{
    id o = [_dictionary objectForKey:key];
    if (!o)
    {
        if (error)
        {
            *error = [NSError errorWithDomain:ManifestErrorDomain
                                         code:ManifestReadMissingRequiredKey
                                     userInfo:@{
                @"missingRequiredKey": key
            }];
        }
        return nil;
    }

    if (![o isKindOfClass:valueType])
    {
        if (error)
        {
            *error = [NSError errorWithDomain:ManifestErrorDomain
                                         code:ManifestReadTypeMismatch
                                     userInfo:@{
                @"keyWithIncorrectType": key,
                @"value": o,
                @"expectedType": NSStringFromClass(valueType),
                @"actualType": NSStringFromClass([o class])
            }];
        }
        return nil;
    }

    return o;
}

- (id)readKey:(NSString *)key asType:(Class)valueType
{
    return [self readKey:key asType:valueType error:nil];
}

@end
