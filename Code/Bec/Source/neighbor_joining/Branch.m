//
//  Branch.m
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Filip Bec. All rights reserved.
//

#import "Branch.h"

@implementation Branch

+ (instancetype)branchWithDistance:(CGFloat)value nodeIndexI:(NSInteger)i nodeIndexJ:(NSInteger)j
{
    Branch *branch = [[Branch alloc] init];
    branch.distance = value;
    branch.i = i;
    branch.j = j;
    
    return branch;
}

- (BOOL)isEqual:(id)object
{
    if (![object isKindOfClass:[Branch class]]) {
        return NO;
    }
    
    Branch *branch = (Branch*)object;
    if ((branch.i == self.i && branch.j == self.j) || (branch.i == self.j && branch.j == self.i)) {
        return YES;
    }
    return NO;
}

- (NSString *)description
{
    return [NSString stringWithFormat:@"<Branch> %ld %ld: %f", self.i, self.j, self.distance];
}

@end
