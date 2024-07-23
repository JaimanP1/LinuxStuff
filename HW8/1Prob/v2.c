#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main( int argc, char **argv) {

    int i, fd;
    unsigned int *map; //pointer to read binary data
    int numints, filesize; 
    void *address; 
    unsigned long long int total = 0; //using this type because sum of all ints in file could exceed 4 bytes

    //opening file
    fd=open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    //determing file size
    lseek(fd, 0, SEEK_END);
    filesize = lseek(fd, 0, SEEK_CUR);
    //integers/floats are 4 bytes, so numints is filesize/4 
    numints = filesize >> 2;

    //pointer to location in memory with contents of input file
    map = mmap(0, filesize, PROT_READ, MAP_SHARED, fd, 0);
    if(map == MAP_FAILED){
        close(fd);
        perror("Error mapping file");
        exit(EXIT_FAILURE);
    }

    //typecast?
    address = map;
    total = *map;

    //looping through mapped memory
    for(int i = 0; i < numints; i++){
        map++;
        total += *map;
        address = map;
    }

    printf("%lld\n", total);


}