#!/usr/bin/python

import sys

fname = str(sys.argv[1])

with open(fname, 'r') as f:    
	matUdalj = []
	for line in f:
		line = line.split() 
        	if line:            
            		line = [float(i) for i in line]
            		matUdalj.append(line)


print("Pocetna matrica udaljenosti:")
print
for w in matUdalj:
	print("%s" % str(w))
print
print(".............................")


# algoritam NJ
# r je uvijek broj familija (taxa)
# velQ je dimenzija matrice Q koja se smanjuje svakom iteracijom za 1

r = len(matUdalj)
velQ = r

for g in range (0, r-3):
	q = []
	minimum = 100000

	# izrada Q matrice
	for i in range(0, velQ):
		redak = []
		for j in range (0, velQ):
			#print("%s %s : %s" %  (i, j, matUdalj[i][j]))
			sumI = 0
			sumJ = 0
			for k in range(0, velQ):
				sumI += matUdalj[i][k]
				sumJ += matUdalj[j][k]
			#print("suma i,j.. %s %s %s" % (sumI, sumJ, matUdalj[i][j]))
			if i == j :
				qval = 0.0
			else:
				qval = (velQ - 2)*matUdalj[i][j] - sumI - sumJ
			
				if (qval < minimum):
					minimum = qval
					minI = i
					minJ = j

			redak.append( qval ) 
		q.append(redak)

	# udaljenost izmedju clanova para i nove tocke
	sumI = 0
	sumJ = 0
	for k in range(0, velQ):
        	sumI += matUdalj[minI][k]
               	sumJ += matUdalj[minJ][k]

	distMinIAndNew = 0.5*matUdalj[minI][minJ] + (1/(2*(velQ-2))) * (sumI - sumJ)
	distMinJAndNew = matUdalj[minI][minJ] - distMinIAndNew

	# udaljenost od novog cvora do svih ostalih  tocaka	
	distNewAndAll = []
	for k in range(0, velQ):
		newDist = 0.5*(matUdalj[minI][k] + matUdalj[minJ][k] - matUdalj[minI][minJ])
		if k == minI:
			distNewAndAll.append(distMinIAndNew)
		elif k == minJ:
			distNewAndAll.append(distMinJAndNew)
		else:
			distNewAndAll.append(newDist)
	distNewAndAll.append(0.0)

	# konstrukcija nove matrice udaljenost s jednim novim cvorom
	# i bez odabranog para cvorova

	matUdalj.append(distNewAndAll)
	for it in range(0, len(matUdalj)-1):
		matUdalj[it].append(distNewAndAll[it])
	
	if minI < minJ:
		minJ -= 1

	del matUdalj[minI]
	del matUdalj[minJ]
        for k in range(0, velQ-1):
                del matUdalj[k][minJ]
		del matUdalj[k][minI]

	# ispis stanja u svakoj iteraciji
	print
	print("Iteracija: %s. Matrica Q:" % str(r-velQ+1))
	print
        print("minimum %s" % str(minimum))
	print
	for w in q:
        	print("%s" % str(w))
	print
	print(".............................")
	print
	print("Nova matrica udaljenosti:")
	print
	for w in matUdalj:
        	print("%s" % str(w))
	print
	print(".............................")

	velQ -= 1

