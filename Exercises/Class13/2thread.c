#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

void *hello(void *id){
	
	long *myid =  (long *)id;
	printf("I'm running in a thread %ld \n", *myid);
	return NULL;
}

int main(int argc, char **argv){
	long nthreads; //number of threads
	pthread_t *thread_array;
	long *thread_ids;

	nthreads = strtol(argv[1], NULL, 10); //converts string to type long
	
	//allocate memory for thread array;
	
	thread_array = malloc(nthreads * sizeof(pthread_t));
	thread_ids = malloc(nthreads * sizeof(long *)); //why do we need this malloc statement? It is because thread_ids is a pointer (of type long) which is equivalent to an array because name of array is just a pointer
	
	for(int i = 0; i < nthreads; i++){
		thread_ids[i] = i;
		pthread_create(&thread_array[i], NULL, hello, &thread_ids[i]); //why is last argument not typecasted to a void. It is because address of anything, including elements of an array, is automatically a void pointer.
	}

	for(int i = 0; i < nthreads; i++){
		pthread_join(thread_array[i], NULL);
	}
}
