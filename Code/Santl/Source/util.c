
//Integer generator
unsigned int GLOBAL_INT;

//Generate new int
unsigned int generate_new_int()
{	
	GLOBAL_INT += 1;
	return GLOBAL_INT-1;
}

//Init generator
void init_int_generator(unsigned int i)
{
	GLOBAL_INT = i;
}

//Swap two integers in memory
void swap(unsigned int *A, unsigned int *B)
{
	*A = *A ^ *B;
	*B = *A ^ *B;
	*A = *A ^ *B;
}

//Function for get ID in pyiramid number organisation (number of pairs)
unsigned int triangle_sum(unsigned int i, unsigned int N)
{
	return ( (N-1)*(N) - (N-1-i)*(N-i) ) / 2;
}

//Get index of pair in distince matrix
unsigned int get_real_index(unsigned int i, unsigned int j, unsigned int N)
{
	if ( i > j )
		swap(&i, &j);

	j = j - (i+1);

	return j + triangle_sum(i, N); 
}

//Get sum of distances for formulas in algorithm
double get_sum(unsigned int p, double *distance_hash, unsigned int N)
{
	int i;
	double sum = 0;
	for(i = 0 ; i < N ; ++i)
	{
		if (i != p)
		{	
			sum += distance_hash[get_real_index(p, i, N)];
		}
	}
	return sum;
}
