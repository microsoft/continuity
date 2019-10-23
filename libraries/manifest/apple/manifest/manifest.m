//
//  manifest.m
//  manifest
//
//  Created by afoxman on 10/22/19.
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "manifest.h"

@implementation manifest

- (manifest* _Nullable)initWithManifestPath:(NSString* _Nonnull)manifestPath
{
    self = [super init];
    if (self)
    {
        NSData *manifestData = [NSData dataWithContentsOfFile:manifestPath];
        _data = [NSJSONSerialization JSONObjectWithData:manifestData options:kNilOptions error:nil];
        
        _name = _data[@"name"];
        _displayName = _data[@"displayName"];
        _initialProperties = _data[@"initialProperties"];
        
        NSString *backgroundColor = _data[@"backgroundColor"];
        if (backgroundColor && backgroundColor.length > 0)
        {
            // TODO: LEFT OFF HERE: use react-native libraries to parse the color string to a UIColor object
            _backgroundColor = [UIColor colorWithRed:1.0f green:1.0f blue:1.0f alpha:1];
        }
        else
        {
            _backgroundColor = [UIColor colorWithRed:1.0f green:1.0f blue:1.0f alpha:1];
        }
    }
    return self;
}

@end
