#!/usr/bin/python

import sys
import random
import os

if not os.path.exists('testovi'):
    os.makedirs('testovi')

for i in [3, 5, 10, 50, 100, 150, 300, 500, 1000]:
    f = open('./testovi/%d.in' % i, 'w')
    f.write('%d\n' % i)
    for x in range(0, i + 1) :
        for y in range(x + 1, i):
            f.write('%d %d %f\n' % (x, y, random.uniform(1,50)))
