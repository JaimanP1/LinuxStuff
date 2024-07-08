#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

struct t_args{
	int *array;
	long length;
	long s;
	long nthreads;
	long id;


};

//passing these as inputs through struct to each thread, running variables independently


void *scalar(void *args){
	struct t_args *myargs = (struct t_args *)args;
	
	//extracting members
	
	long myid = myargs -> id;
	long length = myargs -> length;
	long s = myargs -> s;
	long nthreads = myargs -> nthreads;
	int *arr = myargs -> array;

	long chunk = length / nthreads;
	long start = myid * chunk;
	long end = start + chunk;
	
	//edge case for last thread
	if (myid == nthreads - 1){
		end = length;
	}

	//performing scalar mult
	for (int i = 0; i < length; i++){
		arr[i] *= s;
	}

	return NULL;
}

int main(int argc, char **argv){
	
	pthread_t *thread_array;
	long *thread_ids;

	//command line arguments
	nthreads = strtol(argv[1], NULL, 10);
	length = strtol(argv[2], NULL, 10);
	long s = strtol(argv[3], NULL, 10);
	struct t_args *thread_args = malloc(nthreads * sizeof(struct t_args));

	//allocating memory
	int *array = malloc(length * sizeof(long));
	thread_array = malloc(nthreads * sizeof(pthread_t *));
	thread_ids = malloc(thread_ids * sizeof(long *));

	//populating threads
	for(int i = 0; i < nthreads; i++){
		thread_args[i].array = array;
		thread_args[i].length = length;
		thread_args[i].s = s;
		thread_args[i].nthreads = nthreads;
		thread_args[i].id = i;

	}
	
	//initialize threads
	for (int i = 0; i < length; i++){
		array[i] = i + 1;
	}

	//creating threads
	for (int i = 0; i < nthreads; i++){
		pthread_create(&thread_array[i], NULL, scalar, &thread_args[i]);
	}

	//joining threads 
	for (int i = 0; i < nthreads; i++){
		pthread_join(thread_array[i], NULL);
	}

	//printing array
	for (int i = 0; i < length; i++){
		printf("%d, ", array[i]);
	}
}

