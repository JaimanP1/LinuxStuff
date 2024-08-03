//without file handling first

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100
#define R 10

int unsorted_array[N];
int total_freq_array[R];

int main(int argc, char **argv){
    int rank, size;
    
    printf("unsorted array: \n");
    srand(time(NULL));
    for(int i = 0; i < N; i++){
        unsorted_array[i] = rand()%R;
        printf("%d ", unsorted_array[i]);
    }
    printf("\n");

    int *freq_array = (int *)malloc(sizeof(int) * R);
    for(int i = 0; i < N; i++){
        freq_array[unsorted_array[i]]++;
    }

    int sorted_array[N];
    for(int i = 0, count = 0; i < R; i++){
        for(int j = 0; j < freq_array[i]; j++){
            sorted_array[count] = i;
            count++;
        }
    }

    printf("sorted array: \n");
    for(int i = 0; i < N; i++){
        printf("%d ", sorted_array[i]);
    }
    printf("\n");

    return 0;
}