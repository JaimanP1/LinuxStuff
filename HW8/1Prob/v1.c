/*Simple program to parallelize count sort to get used to mpi.
array of size 100 with random values with values from 1-10*/

#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#define NUMINTS 100
#define DIGITS 10

void frequency(int *split_array, int *count, int total){
    for(int i = 0; i < NUMINTS; i++){
        count[*split_array]++;
        split_array++;
    }
    
}

int aggregate(int *sorted, int *sum_counts){
	sorted = (int *)malloc(sizeof(int) * NUMINTS);
	int k = 0, sum = 0;
	for(int i = 0; i < NUMINTS; i++){
		int freq = sum_counts[i];
		for(int j = 0; j < freq; j++){
			sorted[k] = i;
			k++;
			sum += i;
		}
	}
}

int main( int argc, char **argv){
	int my_array[NUMINTS];
	int *split_array;
	srand(0);
	int i;
	for(i = 0; i < NUMINTS; i++) {
		my_array[i] = rand() % DIGITS;
	}


	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int local_size = NUMINTS / size; 
	split_array = malloc(sizeof(int) * local_size);
	MPI_Scatter(my_array, local_size, MPI_INT, split_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);

	//do count sort: count the frequency of each digit in chunk of my_array
	int *count = (int *)malloc(sizeof(int) * DIGITS);
	int total;
	int *sum_counts = NULL, *sorted = NULL;
	frequency(split_array, count, total);


	if(rank == 0) {
        sum_counts = (int *)malloc(sizeof(int) * DIGITS);
	}

	//maybe try without reduce function
	MPI_Reduce(count, sum_counts, DIGITS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if(rank == 0){
		int sum = aggregate(sorted, sum_counts);
		printf("sum: %d\n", sum);
    }

	MPI_Finalize();

	return 0;

}
