//
//  NJ.m
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Filip Bec. All rights reserved.
//

#import "NJ.h"

@interface NJ () {
    float **dMatrix;
    NSInteger _r;
    NSInteger _maxID;
    NSInteger _N;
    
    NSMutableOrderedSet *indexes;
}

@end

@implementation NJ

- (id)initWithDistanceArray:(NSMutableArray *)distanceArray r:(NSInteger)r
{
    self = [super init];
    if (self) {
        indexes = [[NSMutableOrderedSet alloc] init];
        
        _r = r;
        _maxID = r - 1;
        
        _N = (int)(2*r);
        
        dMatrix = (float**)malloc(_N * sizeof(float*));
        for (int i = 0; i < _N; ++i) {
            dMatrix[i] = (float*)malloc(_N * sizeof(float));
            for (int j = 0; j < _N; ++j) {
                dMatrix[i][j] = 0;
            }
        }
        
        for (Branch *n in distanceArray) {
            dMatrix[n.i][n.j] = n.distance;
            dMatrix[n.j][n.i] = n.distance;
        }
        
        for (int i = 0; i < r; ++i) {
            [indexes addObject:@(i)];
        }
        
        
        
    }
    return self;
}


- (NSMutableArray *)joinNeighbors
{
    NSMutableArray *ret = [[NSMutableArray alloc] init];
    float *suma = (float*)malloc(_N * sizeof(float));
    
    while (_r > 3) {
        
        for (int numI = 0; numI < indexes.count; ++numI) {
            int i = [indexes[numI] intValue];
            
            suma[i] = 0.0;
            for (int numJ = 0; numJ < indexes.count; ++numJ) {
                int j = [indexes[numJ] intValue];
                
                suma[i] += dMatrix[i][j];
            }
        }
        
        int f = 0;
        int g = 0;
        CGFloat minVal = CGFLOAT_MAX;
        
        for (int numI = 0; numI < indexes.count; ++numI) {
            int i = [indexes[numI] intValue];
            
            for (int numJ = numI+1; numJ < indexes.count; ++numJ) {
                int j = [indexes[numJ] intValue];
                
                CGFloat q = (_r - 2.0) * dMatrix[i][j] - suma[i] - suma[j];
                
                if (q < minVal) {
                    minVal = q;
                    f = i;
                    g = j;
                }
            }
        }
        
        float dfu = 0.0;
        float dgu = 0.0;
        
        dfu = 0.5 * dMatrix[f][g] + (0.5 / (_r - 2) * (suma[f] - suma[g]));
        dgu = dMatrix[f][g] - dfu;
        
        _maxID++;
        
        Branch *branch1 = [Branch branchWithDistance:dfu nodeIndexI:f nodeIndexJ:_maxID];
        Branch *branch2 = [Branch branchWithDistance:dgu nodeIndexI:g nodeIndexJ:_maxID];
        
        [ret addObject:branch1];
        [ret addObject:branch2];
        
        for (NSNumber *numK in indexes) {
            int k = [numK intValue];
            
            float duk = 0.5 * (dMatrix[f][k] + dMatrix[g][k] - dMatrix[f][g]);
            
            dMatrix[_maxID][k] = duk;
            dMatrix[k][_maxID] = duk;
        }
        
        [indexes removeObject:@(f)];
        [indexes removeObject:@(g)];
        [indexes addObject:@(_maxID)];
        
        --_r;
    }
    free(suma);
    
    _maxID++;
    
    int a = [indexes[0] intValue];
    int b = [indexes[1] intValue];
    int c = [indexes[2] intValue];

    float dau = (dMatrix[a][b] + dMatrix[a][c] - dMatrix[b][c]) / 2.0;
    float dbu = (dMatrix[b][a] + dMatrix[b][c] - dMatrix[a][c]) / 2.0;
    float dcu = (dMatrix[c][a] + dMatrix[c][b] - dMatrix[a][b]) / 2.0;
    
    Branch *branch1 = [Branch branchWithDistance:dau nodeIndexI:a nodeIndexJ:_maxID];
    Branch *branch2 = [Branch branchWithDistance:dbu nodeIndexI:b nodeIndexJ:_maxID];
    Branch *branch3 = [Branch branchWithDistance:dcu nodeIndexI:c nodeIndexJ:_maxID];
    
    [ret addObjectsFromArray:@[branch1, branch2, branch3]];
    return ret;
}

- (void)dealloc
{
    for (int i = 0; i < _N; ++i) {
        free(dMatrix[i]);
    }
    free(dMatrix);
}

@end
