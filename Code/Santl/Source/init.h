#ifndef INIT
#define INIT

//Function for create new node, original index is given
struct node* create_OUT_node(unsigned int index);

//Function for init node array, create array of size nodes
struct node** init_node_array(unsigned int size);

//Function for init distance array of pairs
struct pair** init_distance_matrix(unsigned int size);

//Function for create pair, i and j are indices in node_array
struct pair* create_pair(struct node** node_array, 
						 unsigned int i, 
						 unsigned int j, 
						 double distance);
#endif