#include "structure.h"
#include "util.h"

//Update hash for pair distance
double *compute_distance_hash(struct pair **distance_matrix, 
							  double *distance_hash, 
							  unsigned int node_size,
							  unsigned int pair_size)
{
	unsigned int k, i, j;
	unsigned int real_index;

	for(k = 0 ; k < pair_size ; ++k)
	{
		i = distance_matrix[k]->left->node_array_index;
		j = distance_matrix[k]->right->node_array_index;
		real_index = get_real_index(i, j, node_size); 
		distance_hash[real_index] = distance_matrix[k]->distance;
	}

	return distance_hash;
}

//Compute Q value for pairs
struct pair* compute_Q_for_pair(struct pair* q_pair, 
								double *distance_hash, 
								unsigned int node_size)
{
	int i, j;
	double Q_distance, distance_i_j, sum_i = 0, sum_j = 0;

	i = q_pair->left->node_array_index;
	j = q_pair->right->node_array_index;

	sum_i = get_sum(i, distance_hash, node_size);
	sum_j = get_sum(j, distance_hash, node_size);
	
	distance_i_j = distance_hash[get_real_index(i, j, node_size)];

	Q_distance = (node_size-2) * distance_i_j - sum_i - sum_j;

	q_pair->Q_function = Q_distance;

	return q_pair;
}

//Compute Q value for every pair
struct pair** compute_Q_function(struct node **node_array, 
						  		 struct pair **distance_matrix, 
						  		 double *distance_hash,
						  		 unsigned int node_size, 
						  		 unsigned int pair_size)
{
	int i;

	for(i = 0 ; i < pair_size ; ++i)
	{
		distance_matrix[i] = compute_Q_for_pair(distance_matrix[i], 
												distance_hash, 
												node_size);
	}

	return distance_matrix;
}


//Find pair with smallest Q value
unsigned int find_best_pair(struct pair **distance_matrix, 
							unsigned int pair_size)
{
	unsigned int ret = 0, i;
	double min_Q_function, tmp_Q_function;

	min_Q_function = distance_matrix[ret]->Q_function;

	for(i = 1 ; i < pair_size ; ++i)
	{
		tmp_Q_function = distance_matrix[i]->Q_function;
		if ( min_Q_function > tmp_Q_function )
		{
			ret = i;
			min_Q_function = tmp_Q_function;
		}
	}
	
	return ret;
}