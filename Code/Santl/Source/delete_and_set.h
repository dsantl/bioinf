#ifndef DELETE_AND_SET
#define DELETE_AND_SET

//Set tree root and connect last three nodes
struct nj_root* connect_to_root(struct nj_root *ROOT, 
								struct pair **distance_matrix);

//Delete nodes from node_array who have index i or index j
struct node** delete_index_node_array(struct node **node_array,
									  unsigned int *node_size,  
							 		  unsigned int i, 
							 		  unsigned int j);

//Delete pairs from distance matrix with index i or index j
struct pair** delete_index_pair_array(struct pair **distance_matrix,
									  unsigned int *pair_size,
									  unsigned int i,
									  unsigned int j);


//Add new node in node array
struct node** add_new_node(struct node **node_array, 
						   unsigned int *node_size,
						   double *distance_hash,
						   struct node *left,
						   struct node *right,
						   unsigned int old_size);

//Add new pair in distance matrix
struct pair **add_new_pairs(struct node **node_array, 
						   struct pair **distance_matrix,
						   double *distance_hash, 
						   unsigned int *node_size,
						   unsigned int *pair_size,
						   unsigned int master_index,
						   unsigned int i,
						   unsigned int j,
						   unsigned int node_array_old_size);

//Update node_array_index in node structure for all nodes
struct node** update_array_indices(struct node **node_array, int node_size);

//Global function for delete and set structures
void delete_and_set_arrays(struct node **node_array, 
						   struct pair **distance_matrix,
						   double *distance_hash, 
						   unsigned int best_pair_index,
						   unsigned int *node_size,
						   unsigned int *pair_size);
#endif