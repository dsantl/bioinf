#include <malloc.h>
#include "structure.h"
#include "util.h"
#include "init.h"

/* Set tree root and connect last three nodes
	*param ROOT - structure for last three nodes
	*param distance_matrix - array od distances
	*return structure for last three nodes in algorithm
*/
struct nj_root* connect_to_root(struct nj_root *ROOT, 
								struct pair **distance_matrix)
{
	unsigned int master_node = generate_new_int();
	struct node *node_a, *node_b, *node_c;
	double a, b, c;
	struct node *left1, *left2, *left3;
	struct node *right1, *right2, *right3; 

	double d1 = distance_matrix[0]->distance;
	double d2 = distance_matrix[1]->distance;
	double d3 = distance_matrix[2]->distance;

	left1 = distance_matrix[0]->left;
	left2 = distance_matrix[1]->left;
	left3 = distance_matrix[2]->left;

	right1 = distance_matrix[0]->right;
	right2 = distance_matrix[1]->right;
	right3 = distance_matrix[2]->right;

	//Find last three nodes:
	if ( left1->index == left2->index || left1->index == right2->index )
		node_a = left1;
	else
		node_a = right1;

	if ( left2->index == left3->index || left2->index == right3->index )
		node_b = left2;
	else
		node_b = right2;

	if ( left3->index == left1->index || left3->index == right1->index )
		node_c = left3;
	else
		node_c = right3;

	a = 0.5*(d1+d2-d3);
	b = 0.5*(d2+d3-d1);
	c = 0.5*(d1+d3-d2);

	ROOT->node1 = node_a; 
	ROOT->node2 = node_b;
	ROOT->node3 = node_c;
	ROOT->d1 = a;
	ROOT->d2 = b; 
	ROOT->d3 = c;
	ROOT->master_node = master_node; 
	
	return ROOT;
}

/* Delete nodes from node_array who have index i or index j
	*param node_array - array of nodes 
	*param node_size - number of nodes
	*param i - first node in (i,j) pair
	*param j - second node in (i,j) pair
	*return node_array after operation
*/
struct node** delete_index_node_array(struct node **node_array,
									  unsigned int *node_size,  
							 		  unsigned int i, 
							 		  unsigned int j)
{
	unsigned int k, mode = 0;
	
	for(k = 0 ; k < *node_size ; ++k)
	{
		if ( k == i || k == j)
			mode += 1;
		else
			node_array[k-mode] = node_array[k];
	}

	*node_size = *node_size - mode;
	return node_array;
}

/* Delete pairs from distance matrix with index i or index j
	*param distance_matrix - array of distances 
	*param pair_size - number of pairs in distance matrix
	*param i - first node for delete
	*param j - second node for delete
*/
struct pair** delete_index_pair_array(struct pair **distance_matrix,
									  unsigned int *pair_size,
									  unsigned int i,
									  unsigned int j)
{
	unsigned int k, mode = 0;
	unsigned int a, b;
	
	for(k = 0 ; k < *pair_size ; ++k)
	{
		a = distance_matrix[k]->left->node_array_index;
		b = distance_matrix[k]->right->node_array_index;
		
		if ( a == i || b == i || a == j || b == j)
			mode = mode + 1;
		else
			distance_matrix[k-mode] = distance_matrix[k];
	}	

	*pair_size = *pair_size - mode;

	return distance_matrix;
}


/* Add new pair in distance matrix
	*param node_array - array of nodes
	*param node_size - pointer to number of nodes
	*param distance_hash - double array contains distances in hash
	*param left - left node 
	*param right - right node
	*param old_size - size before delete 
	*param sum1 - sum of distances for left node
	*param sum2 - sum of distances for right node
	*return node_array after operation
*/
struct node** add_new_node(struct node **node_array, 
						   unsigned int *node_size,
						   double *distance_hash,
						   struct node *left,
						   struct node *right,
						   unsigned int old_size,
						   double sum1,
						   double sum2)
{
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	unsigned int right_index;
	unsigned int left_index;
	double d, d1, d2;
	int N;

	N = old_size;

	new_node->node_array_index = *node_size;
	new_node->index = generate_new_int();

	left_index = left->node_array_index;
	right_index = right->node_array_index;

	d = distance_hash[get_real_index(right_index, left_index, N)];
	d1 = 0.5*d + 1.0/(2*(N-2)) * (sum1 - sum2);
	d2 = d - d1;

	new_node->left_distance = d1;
	new_node->right_distance = d2;
	
	new_node->left = left;
	new_node->right = right;
	
	node_array[*node_size] = new_node;

	
	*node_size = *node_size + 1;
	return node_array;
}

/* Add new pair in distance matrix
	*param node_array - array of nodes
	*param distance_matrix - distance array
	*param distance_hash - double array contains distances in hash
	*param node_size - pointer to number of nodes
	*param pair_size - pointer to number of distances
	*param i - first node
	*param j - second node
	*param node_array_old_size - size before delete
	*return distance_matrix after operation
*/
struct pair **add_new_pairs(struct node **node_array, 
						   struct pair **distance_matrix,
						   double *distance_hash, 
						   unsigned int *node_size,
						   unsigned int *pair_size,
						   unsigned int i,
						   unsigned int j,
						   unsigned int node_array_old_size)
{
	struct pair *new_pair;
	unsigned int k, pair_cnt = 0, master;
	unsigned int old_index;
	double distance, d1, d2, d3;
	
	master = node_array[*node_size-1]->index;

	for(k = 0 ; k < *node_size - 1 ; ++k)
	{
		old_index = node_array[k]->node_array_index; 
		d1 = distance_hash[get_real_index(old_index, i, node_array_old_size)];
		d2 = distance_hash[get_real_index(old_index, j, node_array_old_size)];
		d3 = distance_hash[get_real_index(i, j, node_array_old_size)];
		distance = 0.5 * (d1+d2-d3);

		new_pair = create_pair(node_array, 
							   node_array[k]->index, master, distance);
		
		new_pair->left = node_array[k];
		new_pair->right = node_array[*node_size-1];

		distance_matrix[*pair_size+pair_cnt] = new_pair;
		pair_cnt += 1;
	}

	*pair_size = *pair_size + pair_cnt; 

	return distance_matrix;	
}

/* Update node_array_index in node structure for all nodes
	*param node_array - array of nodes
	*param node_size - number of nodes
	*return node_array after operation
*/
struct node** update_array_indices(struct node **node_array, int node_size)
{
	int i;
	for( i = 0 ; i < node_size ; ++i)
		node_array[i]->node_array_index = i;

	return node_array;
}

/* Global function for delete and set structures
	*param node_array - array of nodes
	*param distance_matrix - distance array
	*param distance_hash - double array contains distances in hash
	*param best_pair_index - index of best pair
	*param node_size - number of nodes
	*param pair_size - number of distances
*/
void delete_and_set_arrays(struct node **node_array, 
						   struct pair **distance_matrix,
						   double *distance_hash, 
						   unsigned int best_pair_index,
						   unsigned int *node_size,
						   unsigned int *pair_size)
{
	unsigned int i, j, old_size;
	double sum1, sum2;
	
	struct node *left = distance_matrix[best_pair_index]->left;
	struct node *right = distance_matrix[best_pair_index]->right; 

	i = left->node_array_index;
	j = right->node_array_index;
	old_size = *node_size;
	sum1 = get_sum(i, node_array);
	sum2 = get_sum(j, node_array);

	//delete elements i and j from node array then shift array
	node_array = delete_index_node_array(node_array, node_size, i, j);
	
	//delete elements from distance matrix who contains i and j 
	distance_matrix = delete_index_pair_array(distance_matrix, pair_size, i, j);

	node_array = add_new_node(node_array, node_size, distance_hash, 
							  left, right, old_size, sum1, sum2);
	
	distance_matrix = add_new_pairs(node_array, 
									distance_matrix,
									distance_hash, 
									node_size, 
									pair_size,
									i,
									j,
									old_size); 

	node_array = update_array_indices(node_array, *node_size);
}