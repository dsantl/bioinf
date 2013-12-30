#!/usr/bin/env python

import math
import sys
import subprocess

#Muscle align
def compute_align(filename):
	from Bio.Align.Applications import MuscleCommandline
	muscle_cline = MuscleCommandline(input=filename)
	stdout, stderr = muscle_cline()
	from StringIO import StringIO
	from Bio import AlignIO
	align = AlignIO.read(StringIO(stdout), "fasta")

	seq = []

	for i in align:
		seq.append((i.name, i.seq))	

	return seq

#Jukes-Cantor model
def compute_distance(A, B, k):

	lenght = len(A)
	D = 0
	total = 0
	for i in range(lenght):
		if A[i] != "-" and B[i] != "-":
			if A[i] != B[i]:
				D += 1
			total += 1

	if total == 0:
		total = 1
	
	D = float(D)/total
	
	distance = -k*math.log(1-D/k) 

	return distance


def main():
	input_file = sys.argv[1]

	seq = compute_align(input_file)

	output_file = open("output.tmp", "w")
	for i in range(len(seq)):
		print >> output_file, i, seq[i][0] 
	output_file.close()

	k = 0.75 #0.75 for DNK
	print("{0}".format(len(seq)))
	for i in range(len(seq)):
		for j in range(i+1, len(seq)):
			out = "{0} {1} {2}".format(i, j, compute_distance(seq[i][1], seq[j][1], k))
			print out
			print >> sys.stderr, out
if __name__ == "__main__":
	main()