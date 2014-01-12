//
//  main.m
//  neighbor_joining
//
//  Created by Filip Bec on 12/01/14.
//  Copyright (c) 2014 Filip Bec. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "NJ.h"
#import "Branch.h"

/**
 Main function.
 */
int main(int argc, const char * argv[])
{
    @autoreleasepool {
        
        int n = 0;
        int a, b;
        double value;

#ifdef DEBUG
        NSDate *programStart = [NSDate date];
#endif

        FILE *iFile = stdin;
        FILE *oFile = stdout;
        
        if (argc == 3) {
            iFile = fopen(argv[1], "r");
            oFile = fopen(argv[2], "w");
            
        } else if (argc == 2) {
            iFile = fopen(argv[1], "r");
        }
        
        if (iFile == NULL) {
            @throw [NSException exceptionWithName:@"FileError" reason:@"The input file can not be opened." userInfo:nil];
        }
        if (oFile == NULL) {
            @throw [NSException exceptionWithName:@"FileError" reason:@"The output file can not be opened." userInfo:nil];
        }
        
        
        NSMutableArray *array = [[NSMutableArray alloc] init];
    
        fscanf(iFile, "%d", &n);
        int N = n * (n - 1) / 2;
        
        for (int i = 0; i < N; ++i) {
            fscanf(iFile, "%d %d %lf", &a, &b, &value);
            Branch *node = [Branch branchWithDistance:value nodeIndexI:a nodeIndexJ:b];
            [array addObject:node];
        }
        
        NJ *nj = [[NJ alloc] initWithDistanceArray:array r:n];
        NSMutableArray *output = [nj joinNeighbors];
        
        for (Branch *node in output) {
            fprintf(oFile, "%ld %ld %f\n", node.i, node.j, node.distance);
        }
        
#ifdef DEBUG
        NSDate *programEnd = [NSDate date];
        NSTimeInterval executionTime = [programEnd timeIntervalSinceDate:programStart];
        NSLog(@"Execution Time = %f", executionTime);
#endif
        
    }
    return 0;
}

