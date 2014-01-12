//
//  NJ.m
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Infinum Ltd. All rights reserved.
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
        
        for (Node *n in distanceArray) {
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
    
    while (_r > 3) {
        int f = 0;
        int g = 0;
        CGFloat minVal = CGFLOAT_MAX;
        
        for (int numI = 0; numI < indexes.count; ++numI) {
            int i = [indexes[numI] intValue];
            
            for (int numJ = numI+1; numJ < indexes.count; ++numJ) {
                int j = [indexes[numJ] intValue];
                
                CGFloat q = (_r - 2.0) * dMatrix[i][j];
                for (NSNumber *numK in indexes) {
                    int k = [numK intValue];
                    
                    q -= dMatrix[i][k];
                    q -= dMatrix[j][k];
                }
                
                if (q < minVal) {
                    minVal = q;
                    f = i;
                    g = j;
                }
            }
        }
        
        float dfu = 0.0;
        float dgu = 0.0;
        
        for (NSNumber *numK in indexes) {
            int k = [numK intValue];
            dfu += dMatrix[f][k] - dMatrix[g][k];
        }
        dfu = 0.5 * dMatrix[f][g] + (0.5 / (_r - 2) * dfu);
        dgu = dMatrix[f][g] - dfu;
        
        _maxID++;
        
        Node *node1 = [Node nodeWithDistance:dfu I:f J:_maxID];
        Node *node2 = [Node nodeWithDistance:dgu I:g J:_maxID];
        
        [ret addObject:node1];
        [ret addObject:node2];
        
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
    
    _maxID++;
    
    int a = [indexes[0] intValue];
    int b = [indexes[1] intValue];
    int c = [indexes[2] intValue];

    float dau = (dMatrix[a][b] + dMatrix[a][c] - dMatrix[b][c]) / 2.0;
    float dbu = (dMatrix[b][a] + dMatrix[b][c] - dMatrix[a][c]) / 2.0;
    float dcu = (dMatrix[c][a] + dMatrix[c][b] - dMatrix[a][b]) / 2.0;
    
    Node *node1 = [Node nodeWithDistance:dau I:a J:_maxID];
    Node *node2 = [Node nodeWithDistance:dbu I:b J:_maxID];
    Node *node3 = [Node nodeWithDistance:dcu I:c J:_maxID];
    
    [ret addObjectsFromArray:@[node1, node2, node3]];
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
