//without file handling first

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 100
#define R 10

int unsorted_array[N];
int total_freq_array[R];

int main(int argc, char **argv){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        printf("unsorted array: \n");
        srand(time(NULL));
        for(int i = 0; i < N; i++){
            unsorted_array[i] = rand()%R;
            printf("%d ", unsorted_array[i]);
        }
        printf("\n");
    }

    int size_chunks = N/size;
    int *split_array = (int *)malloc(sizeof(int) * size_chunks);
    MPI_Scatter(unsorted_array, size_chunks, MPI_INT, split_array, size_chunks, MPI_INT, 0, MPI_COMM_WORLD);

    int *freq_array = (int *)calloc(R, sizeof(int));
    for(int i = 0; i < size_chunks; i++){
        freq_array[split_array[i]]++;
    }

    MPI_Reduce(freq_array, total_freq_array, R, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        int sorted_array[N];
        for(int i = 0, count = 0; i < R; i++){
            for(int j = 0; j < total_freq_array[i]; j++){
                sorted_array[count++] = i;
            }
        }

        printf("\nsorted array: \n");
        for(int i = 0; i < N; i++){
            printf("%d ", sorted_array[i]);
        }
        printf("\n");
    }

    free(split_array);
    free(freq_array);

    MPI_Finalize();
    return 0;
}