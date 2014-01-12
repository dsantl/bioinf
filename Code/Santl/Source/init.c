#include <malloc.h>

#include "structure.h"

/* Function for create new node, original index is given
	*param index - id of node
	*return new node
*/
struct node* create_OUT_node(unsigned int index)
{	
	struct node* ret = (struct node*) malloc(sizeof(struct node));
	ret->node_array_index = index;
	ret->index = index;
	ret->left = NULL;
	ret->right = NULL;
	ret->left_distance = 0;
	ret->right_distance = 0;
	return ret;
}

/* Function for init node array, create array of size nodes
	*param size - number of nodes
	*return new node array
*/
struct node** init_node_array(unsigned int size)
{	
	int i;
	struct node** ret = (struct node**) malloc(sizeof(struct node*) * size);
	for(i = 0 ; i < size ; ++i)
		ret[i] = create_OUT_node(i);

	return ret; 
}

/* Function for init distance array of pairs
	*param size - size of distances
	*return distance matrix array
*/
struct pair** init_distance_matrix(unsigned int size)
{
	return (struct pair**) malloc(sizeof(struct pair*) * size);
}

/* Function for create pair, i and j are indices in node_array
	*param node_array - array who contain all nodes
	*param i - index of first node
	*param j - index of second node
	*param distance - double value of distance
	*return new distance (pair)
*/
struct pair* create_pair(struct node** node_array, 
						 unsigned int i, 
						 unsigned int j, 
						 double distance)
{
	struct pair* ret = (struct pair*) malloc(sizeof(struct pair));
	ret->left = node_array[i];
	ret->right = node_array[j];
	ret->distance = distance;
	ret->Q_function = 0;
	return ret;
}