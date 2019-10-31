#ifndef Constants_h
#define Constants_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSErrorDomain const ManifestErrorDomain;

enum
{
    ManifestReadMissingRequiredKey      = 1,
    ManifestReadTypeMismatch            = 2,
};

NS_ASSUME_NONNULL_END

#endif // Constants_h
