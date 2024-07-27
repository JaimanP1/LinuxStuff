#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mpi.h>

#define DIGITS 1000

void file_reader(int *fd, int *numints, int *filesize, unsigned int **map, char **argv) {
    *fd = open(argv[1], O_RDONLY);
    if (*fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    lseek(*fd, 0, SEEK_END);
    *filesize = lseek(*fd, 0, SEEK_CUR);
    *numints = *filesize >> 2;

    *map = mmap(0, *filesize, PROT_READ, MAP_SHARED, *fd, 0);
    if (*map == MAP_FAILED) {
        close(*fd);
        perror("Error mapping file");
        exit(EXIT_FAILURE);
    }
}

void file_writer(int *fd, int *numints, int *filesize, unsigned int **map, char **argv) {
    *fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
    if (*fd == -1) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }

    int result = lseek(*fd, *filesize - 1, SEEK_SET);
    if (result == -1) {
        close(*fd);
        perror("Error calling lseek() to 'stretch' the file");
        exit(EXIT_FAILURE);
    }

    result = write(*fd, "", 1);
    if (result != 1) {
        close(*fd);
        perror("Error writing last byte of the file");
        exit(EXIT_FAILURE);
    }

    *map = mmap(0, *filesize, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (*map == MAP_FAILED) {
        close(*fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
}

void frequency(int *split_array, int *count, int local_size) {
    for (int i = 0; i < local_size; i++) {
        count[split_array[i]]++;
    }
}

void aggregate(int *sorted, int *sum_counts, int numints) {
    int k = 0;
    for (int i = 0; i < DIGITS; i++) {
        int freq = sum_counts[i];
        for (int j = 0; j < freq; j++) {
            sorted[k] = i;
            k++;
        }
    }
}

int main(int argc, char **argv) {
    int i, fd, numints, filesize;
    unsigned int *map;
    int *split_array;
    unsigned long long int total = 0, sum = 0;

    file_reader(&fd, &numints, &filesize, &map, argv);

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int local_size = numints / size;
    split_array = (int *)malloc(sizeof(int) * local_size);
    MPI_Scatter(map, local_size, MPI_INT, split_array, local_size, MPI_INT, 0, MPI_COMM_WORLD);

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
        for (int i = 0; i < DIGITS; i++) {
            sum_counts[i] = 0;
        }
        sorted = (int *)malloc(sizeof(int) * numints);
    }

    MPI_Reduce(count, sum_counts, DIGITS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        aggregate(sorted, sum_counts, numints);
        for (i = 0; i < numints; i++) {
            sum+= sorted[i];
            //printf("%d ", sorted[i]);
        }
        printf("Total: %lld \n", sum);
        free(sum_counts);  // Free the sum_counts array
    }

    free(split_array);
    free(count);

    MPI_Finalize();

    munmap(map, filesize);
    close(fd);

    if (rank == 0) {
        file_writer(&fd, &numints, &filesize, &map, argv);

        for (i = 0; i < numints; ++i) {
            map[i] = sorted[i];
        }
        if (munmap(map, filesize) == -1) {
            perror("Error un-mmapping the file");
        }
        close(fd);
        free(sorted);
    }

    return 0;
}
