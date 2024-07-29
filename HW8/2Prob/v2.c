#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>

//global variables for function to access
//need to assign values to these through user input

int num_terms, nthreads;
long double val = 0.0;


void *pi_calculate(void *id){
        int *myid = (int *)id;
        //printf("Thread number: %d \n", *myid);

	int start_term = num_terms / nthreads*(*myid)+1;
	int end_term = num_terms / nthreads*(*myid + 1);
	long double partial_sum = 0;

        for (int j = start_term; j <= end_term; j++){
		double x = ((double)j - 0.5)/num_terms;
                partial_sum += 4.0 / (1.0 + x*x);
        }
	//printf("partial sum for process %i: %.21Lf \n", *myid, partial_sum);
	val += partial_sum;
        return NULL;
}

int main(int argc, char **argv){

        int i;
        //int nthreads;
        pthread_t *thread_array;
        int *thread_ids;
        long double pi = 3.14159265358979323846264338327950288419716939937510;

	printf("Enter number of threads: \n");
	scanf("%d", &nthreads);
        printf("Enter number of terms you would like: \n");
        scanf("%d", &num_terms);
	if(num_terms > 20){
		printf("Too many terms for type long double \n");
		return 0;
	}


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
	
	val /= num_terms;
        printf("Value: %.21Lf \nMay have garbage values beyond %d digits \n", val, num_terms);
        return 0;

}
