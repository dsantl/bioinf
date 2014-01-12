//
//  Node.h
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Infinum Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Input and ouput objects for @c NJ class. Represents branch between two nodes in graph.
 */
@interface Branch : NSObject

@property (nonatomic, assign) CGFloat distance;

@property (nonatomic, assign) NSInteger i;
@property (nonatomic, assign) NSInteger j;


/**
 Creates new instance of @c Branch object.
 @param value Distance between node @c i and node @c j.
 @param i First node index.
 @param i Second node index.
 @returns An instance of @c Branch object.
 */
+ (instancetype)branchWithDistance:(CGFloat)value nodeIndexI:(NSInteger)i nodeIndexJ:(NSInteger)j;

@end
