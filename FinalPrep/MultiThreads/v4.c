#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//try to use struct for arguments and mutexes

int total = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

struct args{
	int index;
	int partial_sum;
};

void *calculate(void *p_arg){
	struct args* data = (struct args*) p_arg;
	data->partial_sum *= (data-> index +1);
	pthread_mutex_lock(&mutex1);
	total += data->partial_sum;
	pthread_mutex_unlock(&mutex1);
	printf("total: %d \n", total);
	//printf("value: %d \n", data->partial_sum);
}

int main(){

	int n_threads;
	printf("Enter number of threads: \n");
	scanf("%d", &n_threads);

	pthread_t *thread_array = (pthread_t *)malloc(sizeof(pthread_t) * n_threads);
	struct args* p_args = (struct args *)malloc(sizeof(struct args)*n_threads);
	for(int i = 0; i < n_threads; i++){
		(p_args + i) -> index = i;
		(p_args + i) -> partial_sum = 2;
		pthread_create(&thread_array[i], NULL, calculate, p_args + i); //same as &p_args[i]
	}

	for(int i = 0; i < n_threads; i++){
		pthread_join(thread_array[i], NULL);
	}

	printf("final total: %d \n", total);
}
