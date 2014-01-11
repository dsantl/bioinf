#ifndef FREE_MEMORY
#define FREE_MEMORY

//Free tree structure of nodes
void rec_free_node_array(struct node *node);

//Global memory free
void free_memory(struct node **node_array, struct pair **distance_matrix, int N);

#endif