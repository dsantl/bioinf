#include "structure.h"

//Integer generator
unsigned int GLOBAL_INT;

/* Generate new int
	*return new integer from GLOBAL_INT
*/
unsigned int generate_new_int()
{	
	GLOBAL_INT += 1;
	return GLOBAL_INT-1;
}

/* Init generator
	*param i - first number
*/
void init_int_generator(unsigned int i)
{
	GLOBAL_INT = i;
}

/* Swap two integers in memory
	*param A - first pointer to integer
	*param B - second pointer to integer
*/
void swap(unsigned int *A, unsigned int *B)
{
	*A = *A ^ *B;
	*B = *A ^ *B;
	*A = *A ^ *B;
}

/* Function for get ID in pyiramid number organisation (number of pairs)
	*param i - index of node
	*param N - number of pairs
	*return offset
*/
unsigned int triangle_sum(unsigned int i, unsigned int N)
{
	return ( (N-1)*(N) - (N-1-i)*(N-i) ) / 2;
}

/* Get index of pair in distince matrix
	*param i - first node
	*param j - second node
	*param N - number of nodes
	*return hash value of pair (i,j)
*/
unsigned int get_real_index(unsigned int i, unsigned int j, unsigned int N)
{
	if ( i > j )
		swap(&i, &j);

	// i < j
	// j is some number between i+1 and N-1
	//we put j in interval from 0:
	j = j - (i+1);

	//the node 0 have N-1 (0,j) pairs, the node 1 have N-2, ...
	//so we need to jump over all nodes before 
	//this offset number is triangle_sum
	return j + triangle_sum(i, N); 
}

/* Get sum of distances for formulas in algorithm
	*param index - index of node in node_array
	*param node_array - array of nodes
	*return sum of distances
*/
double get_sum(unsigned int index, struct node **node_array)
{
	return node_array[index]->distance_sum;
}
