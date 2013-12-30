#!/usr/bin/env python

#Script read from stdin and generate dot file from bridge graph format

import sys

def generate_bridges(file, bridge_list, names):

	for i in bridge_list:
		node1 = i[0]
		node2 = i[1]
		weight = i[2]
		print >> file, "node{0} -- node{1} [label=\"{2}\"];".format(i[0], i[1], round(float(i[2]),4));

counter = 0
def get_next_int():
	global counter
	counter += 1
	return counter

def generate_head(file, names, no_nodes):
	print >> file, "graph graphname {"

	for i in range(no_nodes):
		if names.get(i):
			label = names[i]
		else:
			label = "node{0}".format(get_next_int())
		
		print >> file, "node{0} [label={1}]".format(i, label)

def generate_tail(file):
	print >> file, "}"

def generate_graph(filename, bridge_list, names, no_nodes):

	file_dot = open(filename, "w")

	generate_head(file_dot, names, no_nodes)
	generate_bridges(file_dot, bridge_list, names)
	generate_tail(file_dot)
	file_dot.close()



def main():

	bridge_list = list()
	no_nodes = 0
	set_nodes = set()
	
	for line in sys.stdin.readlines():
		sl = line.rstrip().split()
		bridge_list.append((sl[0], sl[1], sl[2]))
		set_nodes.add(sl[0])
		set_nodes.add(sl[1])

	no_nodes = len(set_nodes)
	names = dict()
	
	input_file = open("output.tmp", "r")
	for line in input_file:
		split_line = line.rstrip().split()
		names[int(split_line[0])] = split_line[1]
	input_file.close()

	generate_graph("graph.dot", bridge_list, names, no_nodes)

if __name__ == "__main__":
	main()