#ifndef PRINT_SOLUTION
#define PRINT_SOLUTION

//Print tree recursive tree structure
void rek_print_solution(struct node *root);

//Print solution
void print_solution(struct node **node_array, struct pair** distance_matrix,
					struct nj_root ROOT);

#endif