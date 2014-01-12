//
//  Node.m
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Infinum Ltd. All rights reserved.
//

#import "Branch.h"

@implementation Branch

+ (instancetype)branchWithDistance:(CGFloat)value nodeIndexI:(NSInteger)i nodeIndexJ:(NSInteger)j
{
    Branch *node = [[Branch alloc] init];
    node.distance = value;
    node.i = i;
    node.j = j;
    
    return node;
}

- (BOOL)isEqual:(id)object
{
    if (![object isKindOfClass:[Branch class]]) {
        return NO;
    }
    
    Branch *node = (Branch*)object;
    if ((node.i == self.i && node.j == self.j) || (node.i == self.j && node.j == self.i)) {
        return YES;
    }
    return NO;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<Node> %ld %ld: %f", self.i, self.j, self.distance];
}

@end
