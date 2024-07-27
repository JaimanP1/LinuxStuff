//adding sequential count sort to program, will parallelize in later version

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <mpi.h>
#include <pthread.h>

void file_reader(int *fd, int *numints, int *filesize, unsigned int **map, char **argv){
    *fd = open(argv[1], O_RDONLY);
    if(*fd == -1){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    lseek(*fd, 0, SEEK_END);
    *filesize = lseek(*fd, 0, SEEK_CUR);
    *numints = *filesize >> 2;

    *map = mmap(0, *filesize, PROT_READ, MAP_SHARED, *fd, 0); 
    if(*map == MAP_FAILED){
        close(*fd);
        perror("Error mapping file");
        exit(EXIT_FAILURE);
    }
}

void file_writer(int *fd, int *numints, int *filesize, unsigned int **map, char **argv){
    *fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
	if (*fd == -1) {
		perror("Error opening file for writing");
		exit(EXIT_FAILURE);
	}

	int result = lseek(*fd, *filesize-1, SEEK_SET);
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

//first argument is file to be read from, second argument is file to be written to
int main (int argc, char **argv){

    int i, fd, numints, filesize;
    unsigned int *map;
    unsigned long long int total = 0, sum = 0;

    //mpi part
    int rank, size;
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);	

    file_reader(&fd, &numints, &filesize, &map, argv);

    //count sort portion
    int *count = (int *)malloc(sizeof(int) * 1000);
    total = *map;
    for(int i = 0; i < numints; i++){
        count[*map]++;
        map++;
        total += *map;
    }
    int *final = (int *)malloc(sizeof(int) * numints);
    int k = 0;
    for(int i = 0; i < 1000; i++){
        int freq = count[i];
        for(int j = 0; j < freq; j++){
            final[k] = i;
            k++;
            sum += i;
        }
    }
    printf("total: %lld, sum: %lld \n", total, sum);

    munmap(map, filesize);
    close(fd);

    printf("I am a %d of %d\n", rank++, size);
	MPI_Finalize();

    //writing binary values to another file for checkdata
    file_writer(&fd, &numints, &filesize, &map, argv);

    for (i = 0; i <numints; ++i) {
		map[i] = final[i];
	}
	if (munmap(map, filesize) == -1) {
		perror("Error un-mmapping the file");
    }
	close(fd);
    
	return 0;

}
