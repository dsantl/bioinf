//
//  NJ.h
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Infinum Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Node.h"

/**
 Neighbor joining.
 */
@interface NJ : NSObject

/**
 Init method
 @param distanceArray Array of @c Node objects.
 @returns An instance of NJ.
 */
- (id)initWithDistanceArray:(NSMutableArray*)distanceArray r:(NSInteger)r;

/**
 Creating tree from graph of Node objects.
 @returns Array of @c Node objects that represents tree created with Neighbor joining method.
 */
- (NSMutableArray*)joinNeighbors;

@end
