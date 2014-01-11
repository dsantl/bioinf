#ifndef FIND_BEST_PAIR
#define FIND_BEST_PAIR
//Update hash for pair distance
double *compute_distance_hash(struct pair **distance_matrix, 
							  double *distance_hash, 
							  unsigned int node_size,
							  unsigned int pair_size);

//Compute Q value for pairs
struct pair* compute_Q_for_pair(struct pair* q_pair, 
								double *distance_hash, 
								unsigned int node_size);

//Compute Q value for every pair
struct pair** compute_Q_function(struct node **node_array, 
						  		 struct pair **distance_matrix, 
						  		 double *distance_hash,
						  		 unsigned int node_size, 
						  		 unsigned int pair_size);

//Find pair with smallest Q value
unsigned int find_best_pair(struct pair **distance_matrix, 
							unsigned int pair_size);

#endif