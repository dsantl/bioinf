#ifndef STRUCTURE
#define STRUCTURE 

/* Structure for one node */
struct node
{
	unsigned int node_array_index; //current index in array
	unsigned int index; //static index (ID)

	double left_distance; //distance from node to left child
	double right_distance; //distance from node to right child
	struct node *left; //pointer to left child
	struct node *right; //pointer to right child
};

/* Structure for distance matrix (distance from node1 to node2)*/
struct pair
{
	double distance; //distance
	double Q_function; //Q distance
 
 	struct node *left; //node1
	struct node *right; //node2
};

/* Structure for root node who connects 3 nodes */ 
struct nj_root
{
	struct node *node1, *node2, *node3; //top three nodes
	double d1, d2, d3; //distances to nodes
	unsigned int master_node; //new root node
};

#endif