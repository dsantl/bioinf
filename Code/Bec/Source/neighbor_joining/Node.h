//
//  Node.h
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Infinum Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Node : NSObject

@property (nonatomic, assign) CGFloat distance;

@property (nonatomic, assign) NSInteger i;
@property (nonatomic, assign) NSInteger j;

+ (instancetype)nodeWithDistance:(CGFloat)value I:(NSInteger)i J:(NSInteger)j;

@end
