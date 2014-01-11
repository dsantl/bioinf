#include "malloc.h"
#include "structure.h"


//Free tree structure of nodes
void rec_free_node_array(struct node *node)
{
	if ( node->right )
		rec_free_node_array(node->right);
	if ( node->left) 
		rec_free_node_array(node->left);
	free(node);
}

//Global memory free
void free_memory(struct node **node_array, struct pair **distance_matrix, int N)
{
	int i;
	rec_free_node_array(node_array[0]);
	free(node_array);
	for(i = 0 ; i < N ; ++i)
	{
		free(distance_matrix[i]);
	}
	free(distance_matrix);
}