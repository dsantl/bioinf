#include "structure.h" 

#ifndef UTIL
#define UTIL

//Generate new int
unsigned int generate_new_int();

//Init generator, set first number
void init_int_generator(unsigned int i);

//Swap two integers in memory
void swap(unsigned int *A, unsigned int *B);

//Function for get ID in pyiramid number organisation (number of pairs)
unsigned int triangle_sum(unsigned int i, unsigned int N);

//Get index of pair in distince matrix
unsigned int get_real_index(unsigned int i, unsigned int j, unsigned int N);

//Get sum of distances for formulas in algorithm
double get_sum(unsigned int index, struct node **node_array);


#endif