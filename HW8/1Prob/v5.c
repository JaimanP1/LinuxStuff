#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

#define NUMINTS 100000
#define DIGITS 1000

void frequency(int *split_array, int *count, int local_size) {
    for (int i = 0; i < local_size; i++) {
        count[split_array[i]]++;
    }
}

int aggregate(int *sorted, int *sum_counts) {
    sorted = (int *)malloc(sizeof(int) * NUMINTS);
    int k = 0, sum = 0;
    for (int i = 0; i < DIGITS; i++) {
        int freq = sum_counts[i];
        for (int j = 0; j < freq; j++) {
            sorted[k] = i;
            k++;
            sum += i;
        }
    }
    free(sorted);  // Free the sorted array
    return sum;
}

int main(int argc, char **argv) {
    int my_array[NUMINTS];
    int *split_array;
    srand(0);
    int i;
    for (i = 0; i < NUMINTS; i++) {
        my_array[i] = rand() % DIGITS;
    }

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_size = NUMINTS / size;
    split_array = (int *)malloc(sizeof(int) * local_size);
    MPI_Scatter(my_array, local_size, MPI_INT, split_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Initialize the count array
    int *count = (int *)malloc(sizeof(int) * DIGITS);
    for (int i = 0; i < DIGITS; i++) {
        count[i] = 0;
    }

    frequency(split_array, count, local_size);

    int *sum_counts = NULL;
    int *sorted = NULL;

    if (rank == 0) {
        sum_counts = (int *)malloc(sizeof(int) * DIGITS);
    }

    
    //see if there is clearer way to do this
    MPI_Reduce(count, sum_counts, DIGITS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int sum = aggregate(sorted, sum_counts);
        printf("sum: %d\n", sum);
        free(sum_counts);  // Free the sum_counts array
    }

    free(split_array);
    free(count);

    MPI_Finalize();

    return 0;
}
