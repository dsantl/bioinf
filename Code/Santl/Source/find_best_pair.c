#include "structure.h"
#include "util.h"

/* Update distance sum from one node to all others
	*param node_array - array who contain all nodes
	*param distance_hash - double array of distances in hash
	*param N - number of nodes in node_array
	*return - node_array after operation
*/ 
struct node** refresh_distance_sum(struct node** node_array, 
								   double *distance_hash, 
								   unsigned int N)
{
	int i, k;
	double sum = 0;
	
	for(i = 0 ; i < N ; ++i)
	{
		sum = 0;
		for(k = 0 ; k < N ; ++k)
		{
			if (i != k)
			{	
				sum += distance_hash[get_real_index(i, k, N)];
			}
		}
		node_array[i]->distance_sum = sum;
	}

	
	return node_array;
}

/* Update hash for pair distance
	*param distance_matrix - array of distances
	*param distance_hash - double array of distances in hash
	*param node_size - number of nodes
	*param pair_size - number of distances
	*return - distance_hash after operation
*/
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

/* Compute Q value for pairs
	*param node_array - array who contain all nodes
	*param q_pair - pair type (distance) for Q value
	*param distance_hash - double array of distances in hash
	*param node_size - number of nodes
	*return q_pair after operation
*/
struct pair* compute_Q_for_pair(struct node **node_array,
								struct pair* q_pair, 
								double *distance_hash, 
								unsigned int node_size)
{
	int i, j;
	double Q_distance, distance_i_j, sum_i = 0, sum_j = 0;

	i = q_pair->left->node_array_index;
	j = q_pair->right->node_array_index;

	sum_i = get_sum(i, node_array);
	sum_j = get_sum(j, node_array);
	
	distance_i_j = distance_hash[get_real_index(i, j, node_size)];

	Q_distance = (node_size-2) * distance_i_j - sum_i - sum_j;

	q_pair->Q_function = Q_distance;

	return q_pair;
}

/* Compute Q value for every pair
	*param node_array - array who contain all nodes
	*param distance_matrix - array of distances
	*param distance_hash - double array of distances in hash
	*param node_size - number of nodes
	*param pair_size - number of distances
	*return distance_matrix after operation	
*/
struct pair** compute_Q_function(struct node **node_array, 
						  		 struct pair **distance_matrix, 
						  		 double *distance_hash,
						  		 unsigned int node_size, 
						  		 unsigned int pair_size)
{
	int i;

	for(i = 0 ; i < pair_size ; ++i)
	{
		distance_matrix[i] = compute_Q_for_pair(node_array,
												distance_matrix[i], 
												distance_hash, 
												node_size);
	}

	return distance_matrix;
}


/* Find pair with smallest Q value
	*param distance_matrix - array of distances
	*param pair_size - number of distances	
	*return index of best distance
*/
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