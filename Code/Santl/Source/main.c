#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "structure.h"
#include "init.h"
#include "util.h"
#include "find_best_pair.h"
#include "delete_and_set.h"
#include "print_solution.h"
#include "free_memory.h"

//Neighbor joining algorithm
void nj_algorithm(struct node **node_array, 
				  struct pair **distance_matrix, 
				  unsigned int node_size, 
				  unsigned int pair_size,
				  struct nj_root *ROOT)
{
	//Helper array for hash
	double *distance_hash = (double*) malloc(sizeof(double) * pair_size);
	
	//When we have only 3 nodes then is algorithm over
	while( node_size > 3)
	{
		unsigned int best_pair_index;

		//compute distance hash
		distance_hash = compute_distance_hash(distance_matrix, 
											  distance_hash, 
											  node_size,
											  pair_size);

		//compute Q values for pairs
		distance_matrix = compute_Q_function(node_array, 
											distance_matrix,
											distance_hash, 
											node_size, 
											pair_size);
		
		//find best pair
		best_pair_index = find_best_pair(distance_matrix, pair_size);
		
		
		//delete worst pair and generate new
		delete_and_set_arrays(node_array, 
							  distance_matrix,
							  distance_hash, 
							  best_pair_index,
							  &node_size,
							  &pair_size);
	}
	
	ROOT = connect_to_root(ROOT, distance_matrix);

	free(distance_hash);
}

int main(void)
{ 
	unsigned int iterator, i, j; //helper variables
	
	double distance; //helper variable for distance input
	
	struct node **node_array; //all nodes in current interation
	struct pair **distance_matrix; //simualtion of distance matrix
	struct nj_root ROOT; //root of tree
	
	unsigned int number_of_OUT; //number of OUTs nodes
	unsigned int number_of_pair; //number of pairs

	scanf("%u", &number_of_OUT);

	//init
	init_int_generator(number_of_OUT);
	number_of_pair = number_of_OUT*(number_of_OUT-1)/2;

	node_array = init_node_array(number_of_OUT);
	distance_matrix = init_distance_matrix(number_of_pair);

	//input
	iterator = 0;
	for(i = 0 ; i < number_of_OUT ; ++i)
	{
		for(j = i+1 ; j < number_of_OUT ; ++j)
		{
			scanf("%*d %*d %lf", &distance);
			distance_matrix[iterator] = create_pair(node_array, i, j, distance);		
			iterator += 1;
		}
	}

	//run nj algorithm
	nj_algorithm(node_array, distance_matrix, 
				 number_of_OUT, number_of_pair, &ROOT);

	//print solution
	print_solution(node_array, distance_matrix, ROOT);

	free_memory(node_array, distance_matrix, number_of_pair);

	return 0;
}