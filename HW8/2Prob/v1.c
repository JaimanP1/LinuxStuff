#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

//global variables for function to access
//need to assign values to these through user input

int num_terms, nthreads;
double val = 3.0;

double neg_power(int base, unsigned int exp) {
    double i, result = 1;
    for (i = 0; i <= exp; i++)
        result /= base;
    return result;
 }

void *pi_calculate(void *id){
	int *myid = (int *)id;
	printf("Thread number: %d \n", *myid);
	
	//just checking to see if I can access global variables
	int max_terms = num_terms / nthreads;
	int start_term = (*myid) * max_terms;
	
	for (int j = start_term; j < start_term + max_terms; j++){
		double exp = neg_power(10, j);
		double term_val = (*myid)*(*myid);
		val += term_val * exp;
	}

	return NULL;
}

int main(int argc, char **argv){

	int i;
	//int nthreads; 
	pthread_t *thread_array; 
	int *thread_ids;
	long double pi = 3.14159265358979323846264338327950288419716939937510;

	if(argc < 2){

		printf("Need number of threads \n");
		return 0;
	}

	printf("Enter number of terms you would like: \n");
	scanf("%d", &num_terms);
	
	nthreads = strtol(argv[1], NULL, 10);
	
	thread_array = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);
	thread_ids = (int *)malloc(sizeof(int) * nthreads);

	for (int i = 0; i < nthreads; i ++){
		thread_ids[i] = i;
		pthread_create(&thread_array[i], NULL, pi_calculate, &thread_ids[i]);

	}

	for(int i = 0; i < nthreads; i++){
		pthread_join(thread_array[i], NULL);
	}

	free(thread_array);
	free(thread_ids);

	printf("Value: %.32f \n", val);
	return 0;

}
