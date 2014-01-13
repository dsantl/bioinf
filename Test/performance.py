#!/usr/bin/env python

import sys
import numpy as np
import matplotlib.pyplot as plt

performance_files = sys.argv[1:]

time = dict()
memory = dict()
nodes = dict()

names = list()
graphs = list()

for i in performance_files:

	f = open(i, "r")

	time[i] = list()
	memory[i] = list()
	nodes[i] = list()

	per = f.readlines()

	for j in range(len(per)/2):
		nodes_cur = int(per[2*j].rstrip())
		split_per = per[2*j+1].rstrip().split()
		time_cur, memory_cur = float(split_per[0]), int(split_per[1])
		nodes[i].append(nodes_cur)
		time[i].append(time_cur)
		memory[i].append(memory_cur)

	gr, = plt.plot(nodes[i], time[i])
	graphs.append(gr)
	names.append(i.split("/")[1].split(".")[0])
	f.close()

plt.legend(graphs, names, "upper left")
plt.show()