//
//  manifest.m
//  manifest
//
//  Created by afoxman on 10/22/19.
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import "manifest.h"

@implementation manifest

- (id)init
{
    self = [super init];
    if (self)
    {
        _test = @"This is a test string from the manifest library.";
    }
    return self;
}

@end
