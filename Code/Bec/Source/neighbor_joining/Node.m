//
//  Node.m
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Infinum Ltd. All rights reserved.
//

#import "Node.h"

@implementation Node

+ (instancetype)nodeWithDistance:(CGFloat)value I:(NSInteger)i J:(NSInteger)j
{
    Node *node = [[Node alloc] init];
    node.distance = value;
    node.i = i;
    node.j = j;
    
    return node;
}

- (BOOL)isEqual:(id)object
{
    if (![object isKindOfClass:[Node class]]) {
        return NO;
    }
    
    Node *node = (Node*)object;
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
