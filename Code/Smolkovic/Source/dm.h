#ifndef DISTANCE_MATRIX
#define DISTANCE_MATRIX 

#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;


/*
	Distance Matrix
		- get, insert distance value
		- get row, get sum of row
		- remove row, column
		- print distance matrix
*/

class DistanceMat {
private:
	vector< vector< double > > d;
	map< int, double > sumRowMap;

public:
	DistanceMat(int);
	~DistanceMat() { }

	void insert(int, int, double);
	double get(int, int);
	int getSize();
	vector<double>& getRow(int);
	double sumRow(int);
	
	void removeRow(int);
	void removeCol(int);

	void print();
};


#endif