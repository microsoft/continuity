#ifndef DictionaryReader_h
#define DictionaryReader_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface DictionaryReader : NSObject
{
    NSDictionary *_dictionary;
};

- (DictionaryReader *)initWithDictionary:(NSDictionary *)dictionary;

- (id)readKey:(NSString *)key asType:(Class)valueType error:(NSError **)error;
- (id)readKey:(NSString *)key asType:(Class)valueType;

@end

NS_ASSUME_NONNULL_END

#endif /* DictionaryReader_h */
