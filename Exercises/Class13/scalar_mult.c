#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

long *array, nthreads, length, s; //this is in global scope, so all threads can access

void *scalar( void *id){
	long *myid = (long *)id;

	//dividing array into chunks and assigning each chunk to a thread
	
	long chunk = length / nthreads;
	long start = (*myid) * chunk; //for start index
	long end = start + chunk;

	//performing scalar mult
	for(int i = start; i < end; i++){
		array[i] *= s;
	}

	return NULL;
}

int main(int argc, char **argv){
	pthread_t *thread_array;
	long *thread_ids;

	nthreads = strtol(argv[1], NULL, 10);
	length = strtol(argv[2], NULL, 10);
	s = strtol(argv[3], NULL, 10);
	
	//allocating memory arrays
	thread_array = malloc(nthreads * sizeof(pthread_t));
	thread_ids = malloc(nthreads * sizeof(long *));
	array = (long *)malloc(length * sizeof(long *));

	//initialize array
	for(int i = 0; i < length; i++){
		array[i] = i + 1;
	}

	//create and run threads
	for(int i = 0; i < nthreads; i++){
		thread_ids[i] = i;
		pthread_create(&thread_array[i], NULL, scalar, &thread_ids[i]); 
	}

	for(int i = 0; i < nthreads; i++){
		pthread_join(thread_array[i], NULL);
	}

	for(int i = 0; i < length; i++){
		printf("%ld ", array[i]);
	}

}
