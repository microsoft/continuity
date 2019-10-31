#import "Constants.h"
#import "DictionaryReader.h"
#import "RNXManifest.h"

@implementation RNXManifest

- (RNXManifest *_Nullable)initWithManifestData:(NSDictionary *)data
                                         error:(NSError **)error
{
    self = [super init];
    if (self)
    {
        DictionaryReader *reader = [[DictionaryReader alloc] initWithDictionary:data];

        NSDictionary *entriesData = [reader readKey:@"entry" asType:[NSDictionary class] error:error];
        if (!entriesData)
        {
            return nil;
        }
        DictionaryReader *entriesReader = [[DictionaryReader alloc] initWithDictionary:entriesData];

        NSMutableDictionary<NSString *, RNXManifestEntry *> *entries = [[NSMutableDictionary alloc] init];
        for (NSString *entryName in entriesData)
        {
            NSDictionary *entryData = [entriesReader readKey:entryName asType:[NSDictionary class] error:error];
            if (!entryData)
            {
                return nil;
            }

            if (!(entries[entryName] = [[RNXManifestEntry alloc] initWithName:entryName data:entryData error:error]))
            {
                return nil;
            }
        }
        _entries = entries;

        NSDictionary *devData = [reader readKey:@"dev" asType:[NSDictionary class]];
        _dev = devData ? [[RNXManifestDev alloc] initWithData:devData] : [[RNXManifestDev alloc] init];
    }

    return self;
}

- (RNXManifest *)initWithContentsOfFile:(NSString *)manifestPath
                                  error:(NSError **)error
{
    NSData *manifestFileContents = [NSData dataWithContentsOfFile:manifestPath options:0 error:error];
    if (!manifestFileContents)
    {
        return nil;
    }
    
    NSDictionary *manifestData = [NSJSONSerialization JSONObjectWithData:manifestFileContents options:kNilOptions error:error];
    if (!manifestData)
    {
        return nil;
    }

    return [self initWithManifestData:manifestData error:error];
}

@end
