#include <stdio.h>
#include "structure.h"
#include "util.h"

/* Print tree recursive tree structure
	*param root - node who doesn't have parent
*/
void rek_print_solution(struct node *root)
{
	if ( root->left )
	{
		printf("%u %u %lf\n", root->index, root->left->index, 
										   root->left_distance);
		rek_print_solution(root->left);
	}

	if ( root->right )
	{
		printf("%u %u %lf\n", root->index, root->right->index, 
										   root->right_distance);
		rek_print_solution(root->right);
	}
}

/* Print solution
	*param node_array - array of nodes
	*param ROOT - last three nodes in algorithm
*/
void print_solution(struct node **node_array, struct nj_root ROOT)
{
	
	unsigned int master_node = ROOT.master_node;

	//Print root (last) node
	printf("%u %u %lf\n", master_node, ROOT.node1->index, ROOT.d1);
	printf("%u %u %lf\n", master_node, ROOT.node2->index, ROOT.d2);
	printf("%u %u %lf\n", master_node, ROOT.node3->index, ROOT.d3);

	//Print tree
	rek_print_solution(node_array[0]);
	rek_print_solution(node_array[1]);
	rek_print_solution(node_array[2]);
}