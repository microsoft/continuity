//
//  manifest.h
//  manifest
//
//  Created by afoxman on 10/22/19.
//  Copyright © 2019 Microsoft. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface manifest : NSObject

@property (readonly, nullable) NSDictionary *data;

@property (readonly, nullable) NSString *name;
@property (readonly, nullable) NSString *displayName;
@property (readonly, nullable) NSDictionary *initialProperties;
@property (readonly, nullable) UIColor *backgroundColor;

- (manifest* _Nullable)initWithManifestPath:(NSString* _Nonnull)manifestPath;

@end
