#!/usr/bin/python

import sys
import copy
import time
from collections import defaultdict

start_time = time.time()

spremiste = defaultdict(dict)

#fname = str(sys.argv[1])

#with open(fname, 'r') as f:
f = sys.stdin
matUdalj = []
for line in f:
	line = line.split()
	if line:
		if len(line) == 1:
			# prva linija, broj cvorova, inicijilaziraj matricu
			# nulama
			r = int(line[0]);
			
			matUdalj = [[0]*r for i in range(r)] 
		else:
			# linije s udaljenostima
			matUdalj[int(line[0])][int(line[1])] = float(line[2])
			matUdalj[int(line[1])][int(line[0])] = float(line[2])	
	
	


#print("Pocetna matrica udaljenosti:")
#print
#for w in matUdalj:
#	print("%s" % str(w))
#print
#print(".............................")


# algoritam NJ
# r je uvijek broj familija (taxa)
# velQ je dimenzija matrice Q koja se smanjuje svakom iteracijom za 1
indeksNoveTocke = r
indeksiKojiSuOstali = range(r)

r = len(matUdalj)
velQ = r

for g in range (0, r-3):
	q = []
	minimum = 100000
        sumInRow = [0]*velQ

        for k in range(0, velQ):
            for w in range(0, velQ):
                sumInRow[k] += matUdalj[k][w]


	# izrada Q matrice
	for i in range(0, velQ):
		redak = []
		for j in range (0, velQ):
			#print("%s %s : %s" %  (i, j, matUdalj[i][j]))
			#print("suma i,j.. %s %s %s" % (sumI, sumJ, matUdalj[i][j]))
			if i == j :
				qval = 0.0
			else:
                                qval = (velQ - 2)*matUdalj[i][j] - sumInRow[i] - sumInRow[j]
			
                                if (qval < minimum):
					minimum = qval
					minI = i
					minJ = j

			redak.append( qval ) 
		q.append(redak)

        # udaljenost izmedju clanova para i nove tocke

        distMinIAndNew = 0.5*matUdalj[minI][minJ] + (0.5/(velQ-2))*(sumInRow[minI] - sumInRow[minJ])
	distMinJAndNew = matUdalj[minI][minJ] - distMinIAndNew



	spremiste[2*r-velQ, indeksiKojiSuOstali[minI]] = distMinIAndNew
	spremiste[2*r-velQ, indeksiKojiSuOstali[minJ]] = distMinJAndNew

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

	del indeksiKojiSuOstali[minI]
	del indeksiKojiSuOstali[minJ]
	indeksiKojiSuOstali.append(r-1 + r-velQ+1);

	# ispis stanja u svakoj iteraciji
        #print
        #print("Iteracija: %s. Matrica Q:" % str(r-velQ+1))
        #print
        #print("minimum %s" % str(minimum))
        #print
        #for w in q:
        #	print("%s" % str(w))
        #print
        #print(".............................")
        #print
        #print("Nova matrica udaljenosti:")
        #print
        #for w in matUdalj:
        #	print("%s" % str(w))
        #print
        #print(".............................")

	velQ -= 1

# racunanje zadnjeg cvora
d1 = matUdalj[0][1]
d2 = matUdalj[0][2]
d3 = matUdalj[1][2]

w1 = (d1+d2-d3) / 2.0
w2 = (d1+d3-d2) / 2.0
w3 = (d3+d2-d1) / 2.0

spremiste[2*r-velQ, indeksiKojiSuOstali[0]] = w1
spremiste[2*r-velQ, indeksiKojiSuOstali[1]] = w2
spremiste[2*r-velQ, indeksiKojiSuOstali[2]] = w3


for keys,values in spremiste.items():
    for w in keys: 
	print w,
    print(values)

#print time.time() - start_time, "seconds"


