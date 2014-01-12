//
//  NJ.h
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Filip Bec. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Branch.h"

/**
 Neighbor joining.
 */
@interface NJ : NSObject

/**
 Init method
 @param distanceArray Array of @c Branch objects.
 @returns An instance of NJ.
 */
- (id)initWithDistanceArray:(NSMutableArray*)distanceArray r:(NSInteger)r;

/**
 Creating tree from graph of Branch objects.
 @returns Array of @c Branch objects that represents tree created with Neighbor joining method.
 */
- (NSMutableArray*)joinNeighbors;

@end
